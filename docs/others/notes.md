# COMPILER STEPS
	> Preprocessing
		> Single big source code generated by string replacemen
		> translation unit or compilation unit
	> compilation
		> Abstraction Syntax Tree generated by C grammar
	> Assembly
		> (dot)s file created which is machine code and assembly based
	> Linking
		> ld is the default linker
		> to create executable by combining object files
		> static linking and dynamic linking (need to loaded running process at runtime)

# SORTINGS
	> N2			--> Insertion, Selection, Bubble
	> NLogN			--> Heap, Quick, Merge
	> Below NLogN	--> Counting, Bucket

# SEARCHING
	> Linear Search		--> N best - N worst 
	> Binary Search		--> LogN best - N worst
	> Hash Search		--> 1 best - N worst

# PROCESS MEMORY LAYOUT
	> BSS segment: uninitialized global variables
	> Data Segment: Initialized global variables and depending on the platform static static variables inside a function
	> Text Segment: Code segment. Machine instructions
	> Stack Segment: After process spawn. Holds function returns, args, fixed lenght local variables
	> Heap Segment: Larger than stack, holds dynamic allocated variables

# KERNEL TASKS
	> Process Scheduling -> Round-Robin Time Sharing
	> Memory Management -> Virtual memory management leads to better CPU utilization
	> Provision of a file system
	> Device Accessing
	> Networking

# NETWORK LAYERS
	> Physical
	> Data Link: MAC (media access controller) and LLC (logical link conroller) sublayers
	> Network: IP
	> Transport: UDP and TCP
	> Session - Presentation - Application

# TCP vs UDP
	> connection oriented, datagram oriented
	> reliable, Not
	> extensive error checking, basic error checking
	> ack segment, no ack segment
	> Sequence of data matters, no ordering data
	> slower, faster
	> retransmit lost packets, not
	> no broadcast, broadcast
	> byte stream, message stream


# PRINTING FORMATS
	> %d, %i		--> signed int
	> %u			--> unsigned int
	> %hi			--> signed short
	> %hu			--> unsigned short
	> %l, %ld, %li	--> signed long
	> %lu			--> unsigned long
	> %lld			--> signed long long
	> %llu			--> unsigned long long
	> %f			--> float
	> %lf			--> double
	> %Lf			--> long double
	> %8d			--> add space
	> %08d			--> add zero
	> %0.2f			--> specify precision
