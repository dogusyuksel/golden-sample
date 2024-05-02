# common usage
	> add -DDMALLOC in to the Makefile, -DDMALLOC_FUNC_CHECK is optional. This will allow the library to check all of the arguments of a number of common string and utility routines.
	> add -ldmallocth at the end of library list in Makefile
	> Include header like below
		#ifdef DMALLOC
		#include "dmalloc.h"
		#endif
	> add below lines top of the main function
		#ifdef DMALLOC	dmalloc_debug_setup("log-stats,log-non-free,log-trans,check-fence,check-funcs,log=logfile.log");
		dmalloc_log_stats();
		dmalloc_log_unfreed();
		#endif //DMALLOC
	> add below lines at the end of main function;
		#ifdef DMALLOC
		dmalloc_shutdown();
		#endif //DMALLOC
	> then check logfile.log file content
