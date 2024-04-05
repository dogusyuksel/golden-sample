
This folder contains most common makefile commands usage

Subfolder names have their own meaning.

Go into these folders and simply type "make"

FROM here: https://www.gnu.org/software/make/manual/make.html#Reading

Simple Makefile Syntax

    edit : main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
            cc -o edit main.o kbd.o command.o display.o \
                    insert.o search.o files.o utils.o

    main.o : main.c defs.h
            cc -c main.c
    kbd.o : kbd.c defs.h command.h
            cc -c kbd.c
    command.o : command.c defs.h command.h
            cc -c command.c
    display.o : display.c defs.h buffer.h
            cc -c display.c
    insert.o : insert.c defs.h buffer.h
            cc -c insert.c
    search.o : search.c defs.h buffer.h
            cc -c search.c
    files.o : files.c defs.h buffer.h command.h
            cc -c files.c
    utils.o : utils.c defs.h
            cc -c utils.c
    clean :
            rm edit main.o kbd.o command.o display.o \
            insert.o search.o files.o utils.o


to this


    objects = main.o kbd.o command.o display.o \
            insert.o search.o files.o utils.o

    edit : $(objects)
            cc -o edit $(objects)
    main.o : main.c defs.h
            cc -c main.c
    kbd.o : kbd.c defs.h command.h
            cc -c kbd.c
    command.o : command.c defs.h command.h
            cc -c command.c
    display.o : display.c defs.h buffer.h
            cc -c display.c
    insert.o : insert.c defs.h buffer.h
            cc -c insert.c
    search.o : search.c defs.h buffer.h
            cc -c search.c
    files.o : files.c defs.h buffer.h command.h
            cc -c files.c
    utils.o : utils.c defs.h
            cc -c utils.c
    clean :
            rm edit $(objects)


to this


    objects = main.o kbd.o command.o display.o \
            insert.o search.o files.o utils.o

    edit : $(objects)
            cc -o edit $(objects)

    main.o : defs.h
    kbd.o : defs.h command.h
    command.o : defs.h command.h
    display.o : defs.h buffer.h
    insert.o : defs.h buffer.h
    search.o : defs.h buffer.h
    files.o : defs.h buffer.h command.h
    utils.o : defs.h

    .PHONY : clean
    clean :
            rm edit $(objects)


to this


    objects = main.o kbd.o command.o display.o \
            insert.o search.o files.o utils.o

    edit : $(objects)
            cc -o edit $(objects)

    $(objects) : defs.h
    kbd.o command.o files.o : command.h
    display.o insert.o search.o files.o : buffer.h



Special Built-in Target Names (https://www.gnu.org/software/make/manual/make.html#Special-Targets)
---------------------------------
Certain names have special meanings if they appear as targets.

.PHONY

The prerequisites of the special target .PHONY are considered to be phony targets. When it is time to consider such a target, make will run its recipe unconditionally, regardless of whether a file with that name exists or what its last-modification time is. See Phony Targets.

.DEFAULT

The recipe specified for .DEFAULT is used for any target for which no rules are found (either explicit rules or implicit rules). See Defining Last-Resort Default Rules. If a .DEFAULT recipe is specified, every file mentioned as a prerequisite, but not as a target in a rule, will have that recipe executed on its behalf. See Implicit Rule Search Algorithm.

.PRECIOUS

The targets which .PRECIOUS depends on are given the following special treatment: if make is killed or interrupted during the execution of their recipes, the target is not deleted. See Interrupting or Killing make. Also, if the target is an intermediate file, it will not be deleted after it is no longer needed, as is normally done. See Chains of Implicit Rules. In this latter respect it overlaps with the .SECONDARY special target.

You can also list the target pattern of an implicit rule (such as ‘%.o’) as a prerequisite file of the special target .PRECIOUS to preserve intermediate files created by rules whose target patterns match that file’s name.

.LOW_RESOLUTION_TIME

If you specify prerequisites for .LOW_RESOLUTION_TIME, make assumes that these files are created by commands that generate low resolution time stamps. The recipe for the .LOW_RESOLUTION_TIME target are ignored.

The high resolution file time stamps of many modern file systems lessen the chance of make incorrectly concluding that a file is up to date. Unfortunately, some hosts do not provide a way to set a high resolution file time stamp, so commands like ‘cp -p’ that explicitly set a file’s time stamp must discard its sub-second part. If a file is created by such a command, you should list it as a prerequisite of .LOW_RESOLUTION_TIME so that make does not mistakenly conclude that the file is out of date. For example:

    .LOW_RESOLUTION_TIME: dst
    dst: src
            cp -p src dst

Since ‘cp -p’ discards the sub-second part of src’s time stamp, dst is typically slightly older than src even when it is up to date. The .LOW_RESOLUTION_TIME line causes make to consider dst to be up to date if its time stamp is at the start of the same second that src’s time stamp is in.

Due to a limitation of the archive format, archive member time stamps are always low resolution. You need not list archive members as prerequisites of .LOW_RESOLUTION_TIME, as make does this automatically.

.SILENT

If you specify prerequisites for .SILENT, then make will not print the recipe used to remake those particular files before executing them. The recipe for .SILENT is ignored.

If mentioned as a target with no prerequisites, .SILENT says not to print any recipes before executing them. You may also use more selective ways to silence specific recipe command lines. See Recipe Echoing. If you want to silence all recipes for a particular run of make, use the ‘-s’ or ‘--silent’ option (see Summary of Options).

.EXPORT_ALL_VARIABLES

Simply by being mentioned as a target, this tells make to export all variables to child processes by default. This is an alternative to using export with no arguments. See Communicating Variables to a Sub-make.

.NOTPARALLEL

If .NOTPARALLEL is mentioned as a target with no prerequisites, all targets in this invocation of make will be run serially, even if the ‘-j’ option is given. Any recursively invoked make command will still run recipes in parallel (unless its makefile also contains this target).

If .NOTPARALLEL has targets as prerequisites, then all the prerequisites of those targets will be run serially. This implicitly adds a .WAIT between each prerequisite of the listed targets. See Disabling Parallel Execution.

.ONESHELL

If .ONESHELL is mentioned as a target, then when a target is built all lines of the recipe will be given to a single invocation of the shell rather than each line being invoked separately. See Recipe Execution.


Automatic Variables (https://www.gnu.org/software/make/manual/make.html#Automatic-Variables)
--------------------------------------------

Here is a table of automatic variables, where a rule is like

    target … : prerequisites …
        recipe
        …
        …

$@

The file name of the target of the rule. If the target is an archive member, then ‘$@’ is the name of the archive file. In a pattern rule that has multiple targets (see Introduction to Pattern Rules), ‘$@’ is the name of whichever target caused the rule’s recipe to be run.

$%

The target member name, when the target is an archive member. See Using make to Update Archive Files. For example, if the target is foo.a(bar.o) then ‘$%’ is bar.o and ‘$@’ is foo.a. ‘$%’ is empty when the target is not an archive member.

$<

The name of the first prerequisite. If the target got its recipe from an implicit rule, this will be the first prerequisite added by the implicit rule (see Using Implicit Rules).

$?

The names of all the prerequisites that are newer than the target, with spaces between them. If the target does not exist, all prerequisites will be included. For prerequisites which are archive members, only the named member is used (see Using make to Update Archive Files).

‘$?’ is useful even in explicit rules when you wish to operate on only the prerequisites that have changed. For example, suppose that an archive named lib is supposed to contain copies of several object files. This rule copies just the changed object files into the archive:

    lib: foo.o bar.o lose.o win.o
            ar r lib $?

$^

The names of all the prerequisites, with spaces between them. For prerequisites which are archive members, only the named member is used (see Using make to Update Archive Files). A target has only one prerequisite on each other file it depends on, no matter how many times each file is listed as a prerequisite. So if you list a prerequisite more than once for a target, the value of $^ contains just one copy of the name. This list does not contain any of the order-only prerequisites; for those see the ‘$|’ variable, below.

$+

This is like ‘$^’, but prerequisites listed more than once are duplicated in the order they were listed in the makefile. This is primarily useful for use in linking commands where it is meaningful to repeat library file names in a particular order.

$|

The names of all the order-only prerequisites, with spaces between them.

$*

The stem with which an implicit rule matches (see How Patterns Match). If the target is dir/a.foo.b and the target pattern is a.%.b then the stem is dir/foo. The stem is useful for constructing names of related files.

In a static pattern rule, the stem is part of the file name that matched the ‘%’ in the target pattern.

In an explicit rule, there is no stem; so ‘$*’ cannot be determined in that way. Instead, if the target name ends with a recognized suffix (see Old-Fashioned Suffix Rules), ‘$*’ is set to the target name minus the suffix. For example, if the target name is ‘foo.c’, then ‘$*’ is set to ‘foo’, since ‘.c’ is a suffix. GNU make does this bizarre thing only for compatibility with other implementations of make. You should generally avoid using ‘$*’ except in implicit rules or static pattern rules.

If the target name in an explicit rule does not end with a recognized suffix, ‘$*’ is set to the empty string for that rule.

