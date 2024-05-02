# common usage
	> gdb --args myapp arg1 arg2
	> help [command]
	> run
	> break sourcefile.c:80
	> break myfunction
	> info breakpoints
	> delete ->breakpoint number<-
	> watch myvariable
	> info watchpoints
	> delete ->watchpoint number<-
	> continue --> after break
	> step --> step into
	> next
	> finish --> until the end of current function
	> print ->variable<-
	> print/x variable
	> where --> runtime breakpoint
	> backtrace --> use after segfault
	> quit

# notes
    openocd and gdb-multiarch can be used to debugging a remote host (a stm board maybe via linux terminal)
