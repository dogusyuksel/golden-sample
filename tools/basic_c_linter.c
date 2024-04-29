#include <stdio.h>
#include <stdint.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <err.h>
#include <fts.h>
#include <assert.h>
#include <sys/queue.h>

static bool glb_any_error_found = false;
static char *restricted_list[] = {"#define", "typedef", "#include"};
static char *skip_error = NULL;

enum CHECK_RETURNS {
    SUCCESS,
    FAIL,
    CONTINUE,
    BREAK,
    GOTO
};

#define VERSION                 "1.0.0"

#define MAX_FUNCTION_CHAR_LEN   32768
#define MAX_LINE_CHAR_LEN       1024

#define PRINT_ERROR(s)  fprintf(stderr, "(%s - %d): %s\n", __func__, __LINE__, #s)
#define PRINT_ERROR_PRM1(s, prm1)  fprintf(stderr, "(%s - %d): %s %s\n", __func__, __LINE__, #s, prm1)

struct function_entry {
    unsigned int starting_line;
    unsigned int ending_line;
    TAILQ_ENTRY(function_entry) entries;
};

struct file_queue_entry {
    char *filename;
    TAILQ_HEAD(function_queue_head, function_entry) functions;
    TAILQ_ENTRY(file_queue_entry) entries;
};
TAILQ_HEAD(file_queue_head, file_queue_entry);

struct stats {
    unsigned int total_checked_file_count;
    unsigned int total_checked_function_count;
    unsigned int total_found_possible_leaks;
};

static struct option parameters[] = {
    { "help",           no_argument,        0,        'h'        },
    { "directory",      required_argument,  0,        'd'        },
    { "file",           required_argument,  0,        'f'        },
    { "skip",           required_argument,  0,        's'        },
    { NULL,            0,                   0,         0         },
};

static void print_help(char *app_name)
{
    int i = 0;

    if (!app_name) {
        return;
    }

    printf("usage of %s (version %s)\n", app_name, VERSION);
    while (parameters[i].name != NULL) {
        printf("\t--%s or -%c, %s\n", parameters[i].name, (char)parameters[i].val,
            (parameters[i].has_arg == no_argument) ? ("no_argument") :
                ((parameters[i].has_arg == required_argument) ? ("required_argument") :
                    ("optional_argument")));
        i++;
    }
}

static bool is_dir_exist(char *directory)
{
    DIR *dir = NULL;

    if (!directory) {
        return false;
    }

    dir = opendir(directory);
    if (dir) {
        closedir(dir);
        return true;
    }

    return false;
}

static void add_filename_to_queue(char *filename, struct file_queue_head *queue)
{
    struct file_queue_entry *fentry;

    if (!filename || !queue) {
        return;
    }

    fentry = malloc(sizeof(struct file_queue_entry));
    if (!fentry) {
        PRINT_ERROR("malloc() failed");
        return;
    }

    fentry->filename = strdup(filename);
    if (!(fentry->filename)) {
        PRINT_ERROR("strdup() failed");
        return;
    }

    TAILQ_INSERT_HEAD(queue, fentry, entries);
}

static void print_queue(struct file_queue_head *queue)
{
    int i = 0;
    struct file_queue_entry *np = NULL;
    struct function_entry *fp = NULL;

    if (!queue) {
        return;
    }

    TAILQ_FOREACH(np, queue, entries) {
        printf("entry %d\n", i);
        if (np->filename) {
            printf("\tfilename: %s\n", np->filename);
        }
        TAILQ_FOREACH(fp, &(np->functions), entries) {
            printf("\t\tfirst %d\n", fp->starting_line);
            printf("\t\tlast %d\n", fp->ending_line);
        }
        i++;
    }
}

static void free_function_queue(struct function_queue_head *fqueue)
{
    struct function_entry *n1, *n2 = NULL;

    if (!fqueue) {
        return;
    }

    n1 = TAILQ_FIRST(fqueue);
    while (n1 != NULL) {
        n2 = TAILQ_NEXT(n1, entries);
        if (n1) {
            free(n1);
        }
        n1 = n2;
    }
    TAILQ_INIT(fqueue);
}

static void free_queue(struct file_queue_head *queue)
{
    struct file_queue_entry *n1, *n2 = NULL;

    if (!queue) {
        return;
    }

    n1 = TAILQ_FIRST(queue);
    while (n1 != NULL) {
        n2 = TAILQ_NEXT(n1, entries);
        if (n1->filename) {
            free(n1->filename);
        }
        free_function_queue(&(n1->functions));
        if (n1) {
            free(n1);
        }
        n1 = n2;
    }
    TAILQ_INIT(queue);
}

static int ptree(char *curpath, char * const path, struct file_queue_head *queue)
{
    char ep[512];
    char p[512 ];
    DIR *dirp;
    struct dirent entry;
    struct dirent *endp;
    struct stat st;

    if (curpath != NULL)
        snprintf(ep, sizeof(ep), "%s/%s", curpath, path);
    else
        snprintf(ep, sizeof(ep), "%s", path);

    if (stat(ep, &st) == -1)
        return EXIT_FAILURE;

    if ((dirp = opendir(ep)) == NULL)
        return EXIT_FAILURE;

    for (;;) {
        endp = NULL;
        if (readdir_r(dirp, &entry, &endp) == -1) {
            closedir(dirp);
            return EXIT_FAILURE;
        }
        if (endp == NULL)
            break;
        assert(endp == &entry);
        if (strcmp(entry.d_name, ".") == 0 ||
            strcmp(entry.d_name, "..") == 0)
            continue;
        if (curpath != NULL)
            snprintf(ep, sizeof(ep), "%s/%s/%s", curpath,
                path, entry.d_name);
        else
            snprintf(ep, sizeof(ep), "%s/%s", path,
                entry.d_name);
        if (stat(ep, &st) == -1) {
            closedir(dirp);
            return EXIT_FAILURE;
        }
        if (S_ISREG(st.st_mode) || S_ISDIR(st.st_mode)) {
            if (!S_ISDIR(st.st_mode)) {
                if (ep[strlen(ep) - 2] == '.' &&
                    (ep[strlen(ep) - 1] == 'c' || ep[strlen(ep) - 1] == 'C'))
                add_filename_to_queue(ep, queue);
            }
        }

        if (S_ISDIR(st.st_mode) == 0)
            continue;
        if (curpath != NULL)
            snprintf(p, sizeof(p), "%s/%s", curpath, path);
        else
            snprintf(p, sizeof(p), "%s", path);
        snprintf(ep, sizeof(ep), "%s", entry.d_name);
        ptree(p, ep, queue);
    }
    closedir(dirp);

    return EXIT_SUCCESS;
}

static int find_files_in_directory(char *directory, struct file_queue_head *queue)
{
    if (!directory || !queue) {
        return EXIT_FAILURE;
    }

    return ptree(NULL, directory, queue);
}

static bool contains_restricted(char *line)
{
    int i = 0;
    int size = sizeof(restricted_list) / sizeof(restricted_list[0]);

    if (!line || !strlen(line)) {
        return false;
    }

    if (strlen(line) == 1 && line[0] == '\n') {
        return true;
    }

    for (i = 0; i < size; i++) {
        if (strstr(line, restricted_list[i])) {
            return true;
        }
    }

    return false;
}

static bool contains_function(char *line)
{
    if (!line) {
        return false;
    }

    //TODO, find something more clever. maybe use regex

    if (strstr(line, "){")) {
        return true;
    }

    return false;
}

static void remove_space(char *input)
{
    char *beg = NULL;
    int i = 0, len = 0;

    if (!input) {
        return;
    }

    while ((beg = strstr(input, " ")) != NULL) {
        len = strlen(input);
        memmove(beg, beg + 1, len - (beg - input));
        beg = NULL;
    }
}

static unsigned int update_brace_count(unsigned int old_brace_count, char *line)
{
    int i = 0;
    int len = 0;
    unsigned int ret_val = old_brace_count;

    if (!line) {
        return old_brace_count;
    }

    len = strlen(line);
    for (i = 0; i < len; i++) {
        if (line[i] == '{') {
            ret_val++;
        } else if  (line[i] == '}') {
            ret_val--;
        }
    }

    return ret_val;
}

static struct function_entry *create_function_const_to_entry(void)
{
    struct function_entry *fentry;

    fentry = malloc(sizeof(struct function_entry));
    if (!fentry) {
        PRINT_ERROR("malloc() failed");
        return NULL;
    }

    fentry->ending_line = 0;
    fentry->starting_line = 0;

    return fentry;
}

static int find_functions_in_a_file(char *filename, struct function_queue_head *fqueue)
{
    struct function_entry *funct_entry = NULL;
    unsigned int open_brace_count = 0;
    unsigned int line_number = 0;
    bool function_starting_found = false;
    bool cat_started = false;
    FILE *fs = NULL;
    char buffer[MAX_FUNCTION_CHAR_LEN] = {0};
    char line_buffer[MAX_LINE_CHAR_LEN] = {0};

    if (!filename) {
        return EXIT_FAILURE;
    }

    fs = fopen(filename, "r");
    if (!fs) {
        PRINT_ERROR("fopen() failed");
        EXIT_FAILURE;
    }

    TAILQ_INIT(fqueue);

    while (fgets(line_buffer, MAX_LINE_CHAR_LEN, fs) != NULL) {
        line_number++;
        if (!cat_started && contains_restricted(line_buffer)) {
            continue;
        }

        if (strlen(line_buffer) > 2 &&
            line_buffer[strlen(line_buffer) - 1] == '\\' &&
            line_buffer[strlen(line_buffer) - 2] == '*') {
            //go ahead till end of comment

            while (fgets(line_buffer, MAX_LINE_CHAR_LEN, fs) != NULL) {
                line_number++;
                 if (strlen(line_buffer) > 2 &&
                    line_buffer[strlen(line_buffer) - 1] == '*' &&
                    line_buffer[strlen(line_buffer) - 2] == '/') {
                    break;
                }

                memset(line_buffer, 0, sizeof(line_buffer));
            }
            continue;
        }

        if (strlen(line_buffer) > 2 &&  line_buffer[0] == '/' && line_buffer[1] == '/') {
            //skip comment
            continue;
        }

        cat_started = true;

        if (line_buffer[strlen(line_buffer) - 1] == '\n') {
            line_buffer[strlen(line_buffer) - 1] = '\0';
        }

        remove_space(line_buffer);

        strncat(buffer, line_buffer, sizeof(buffer) - strlen(buffer));

        if (!function_starting_found && !contains_function(buffer)) {
            continue;
        }
        if (!function_starting_found) {
            funct_entry = create_function_const_to_entry();
            if (funct_entry) {
                funct_entry->starting_line = line_number;
            }
        }
        function_starting_found = true;

        open_brace_count = update_brace_count(open_brace_count, line_buffer);
        if (open_brace_count == 0) {
            open_brace_count = 0;
            function_starting_found = false;
            cat_started = false;

            memset(buffer, 0, sizeof(buffer));

            if (funct_entry) {
                funct_entry->ending_line = line_number;
                if (funct_entry->ending_line >= funct_entry->starting_line) {
                    TAILQ_INSERT_HEAD(fqueue, funct_entry, entries);
                }
            }
        }

        memset(line_buffer, 0, sizeof(line_buffer));
    }

    if (fs) {
        fclose(fs);
    }

    return EXIT_SUCCESS;
}

static int find_functions(struct file_queue_head *queue)
{
    struct file_queue_entry *np = NULL;

    if (!queue) {
        return EXIT_FAILURE;
    }

    TAILQ_FOREACH(np, queue, entries) {
        if (find_functions_in_a_file(np->filename, &(np->functions))) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

static enum CHECK_RETURNS check_exits(bool *word_check, int *word_counter,
    char *line_buffer, char *enterance_word, char *exit_word)
{
    char *strstr_ptr = NULL;

    if (!line_buffer || !enterance_word || !exit_word) {
        return BREAK;
    }

    if (strstr(line_buffer, enterance_word)) {
        *word_check = true;
        (*word_counter)++;
    }

    if (*word_check) {
        if (strstr(line_buffer, exit_word)) {
            *word_check = true;
            (*word_counter)--;
        }
    }

    if (*word_check) {
        if ((strstr_ptr = strstr(line_buffer, "exit(")) &&
            strstr_ptr == line_buffer) {
            return BREAK;
        }
        if ((strstr_ptr = strstr(line_buffer, "abort(")) &&
            strstr_ptr == line_buffer) {
            return BREAK;
        }
        if ((strstr_ptr = strstr(line_buffer, "return")) &&
            strstr_ptr == line_buffer) {
            //just assuming first return is for the allocating function control
            if ((*word_counter) == 1) {
                return GOTO;
            }
            return BREAK;
        }
    }

    return SUCCESS;
}

static int find_leaks_in_a_function(char *filename,
    unsigned int start_line, unsigned int end_line,
    char *control_word, char *exiting_word, unsigned int *err_cnt)
{
    unsigned int line_number = 0;
    FILE *fs = NULL;
    char buffer[MAX_FUNCTION_CHAR_LEN] = {0};
    char line_buffer[MAX_LINE_CHAR_LEN] = {0};
    bool hit_control_word = false;
    int control_counter = 0;
    enum CHECK_RETURNS check = SUCCESS;

    if (!filename || !control_word ||
        !exiting_word || !err_cnt) {
        return EXIT_FAILURE;
    }

    fs = fopen(filename, "r");
    if (!fs) {
        PRINT_ERROR("fopen() failed");
        EXIT_FAILURE;
    }

    //jump to starting line
    while (fgets(line_buffer, MAX_LINE_CHAR_LEN, fs) != NULL) {
        line_number++;

        if (line_number == start_line) {
            break;
        }
    }

    //with first new line reading, we are in the first line of the function
    while (fgets(line_buffer, MAX_LINE_CHAR_LEN, fs) != NULL &&
        line_number < end_line) {
        line_number++;

        if (line_buffer[strlen(line_buffer) - 1] == '\n') {
            line_buffer[strlen(line_buffer) - 1] = '\0';
        }
        if (contains_restricted(line_buffer)) {
            continue;
        }

        if (skip_error && strstr(line_buffer, skip_error)) {
            continue;
        }
        remove_space(line_buffer);

        check = check_exits(&hit_control_word, &control_counter, line_buffer,
            control_word, exiting_word);
        if (check == BREAK) {
            break;
        } else if (check == GOTO) {
            goto cont;
        } else if (check == CONTINUE) {
            continue;
        } else if (check == FAIL) {
            PRINT_ERROR("check() failed");
        }

cont:
        memset(line_buffer, 0, sizeof(line_buffer));
    }

    if (fs) {
        fclose(fs);
    }

    if (control_counter > 0 && hit_control_word) {
        (*err_cnt)++;
        fprintf(stderr, "  ==> Be careful about %s:%d function. Possible ->%s<- leak (%d)\n",
            filename, start_line, control_word, control_counter);
        glb_any_error_found = true;
    }

    return EXIT_SUCCESS;
}

static int find_leaks(struct file_queue_head *queue)
{
    struct stats stats;
    struct file_queue_entry *np = NULL;
    struct function_entry *fp = NULL;

    if (!queue) {
        return EXIT_FAILURE;
    }

    memset(&stats, 0, sizeof(struct stats));

    TAILQ_FOREACH(np, queue, entries) {
        (stats.total_checked_file_count)++;
        TAILQ_FOREACH(fp, &(np->functions), entries) {
            (stats.total_checked_function_count)++;
            if (find_leaks_in_a_function(np->filename,
                fp->starting_line, fp->ending_line, "open(", "close(",
                &(stats.total_found_possible_leaks))) {
            }
            if (find_leaks_in_a_function(np->filename,
                fp->starting_line, fp->ending_line, "malloc(", "free(",
                &(stats.total_found_possible_leaks))) {
            }
            if (find_leaks_in_a_function(np->filename,
                fp->starting_line, fp->ending_line, "calloc(", "free(",
                &(stats.total_found_possible_leaks))) {
            }
            if (find_leaks_in_a_function(np->filename,
                fp->starting_line, fp->ending_line, "pthread_mutex_lock(", "pthread_mutex_unlock(",
                &(stats.total_found_possible_leaks))) {
            }
        }
    }

    if (stats.total_checked_file_count && stats.total_checked_function_count) {
        fprintf(stderr, "\nSUMMARY:\n");
        fprintf(stderr, "\tTotal Checked Files     :  %u\n", stats.total_checked_file_count);
        fprintf(stderr, "\tTotal Checked Functions :  %u\n", stats.total_checked_function_count);
        fprintf(stderr, "\tTotal Possible Leaks    :  %u\n", stats.total_found_possible_leaks);
    }

    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    int ret = EXIT_SUCCESS;
    int c, o;
    char *directory = NULL;
    char *file = NULL;
    struct file_queue_head head;

    while ((c = getopt_long(argc, argv, "hd:f:s:", parameters, &o)) != -1) {
        switch (c) {
            case 'h':
                print_help(argv[0]);
                goto success;
            case 'd':
                directory = strdup(optarg);
                if (!directory) {
                    PRINT_ERROR("strdup() failed");
                } else {
                    if (directory[strlen(directory) - 1] == '/') {
                        directory[strlen(directory) - 1] = '\0';
                    }
                }
                break;
            case 'f':
                file = strdup(optarg);
                if (!file) {
                    PRINT_ERROR("strdup() failed");
                }
                break;
            case 's':
                skip_error = strdup(optarg);
                if (!skip_error) {
                    PRINT_ERROR("strdup() failed");
                }
                break;
            default:
                PRINT_ERROR("option cannot be found");
                print_help(argv[0]);
                goto fail;
        }
    }

    if (!directory && !file) {
        PRINT_ERROR("you should point one directory or file out");
        print_help(argv[0]);
        goto fail;
    }

    TAILQ_INIT(&head);

    if (directory) {
        if (find_files_in_directory(directory, &head)) {
            PRINT_ERROR("find_files_in_directory() failed");
            print_help(argv[0]);
            goto fail;
        }
    } else if (file) {
        add_filename_to_queue(file, &head);
    } else {
        PRINT_ERROR("you should point one directory or file out");
        print_help(argv[0]);
        goto fail;
    }

    if (find_functions(&head)) {
        PRINT_ERROR("find_functions() failed");
        print_help(argv[0]);
        goto fail;
    }

    if (find_leaks(&head)) {
        PRINT_ERROR("find_leaks() failed");
        print_help(argv[0]);
        goto fail;
    }

    if (glb_any_error_found) {
        goto fail;
    }

    goto success;

fail:
    ret = EXIT_FAILURE;

success:

    free_queue(&head);
    if (skip_error) {
        free(skip_error);
    }
    if (file) {
        free(file);
    }
    if (directory) {
        free(directory);
    }

    return ret;
}