# get_next_line (GNL)

### Core Focus: 
-Dynamic I/O buffering, file descriptor manipulation, and state persistence.

### Technical Highlights:
-Engineered a line-by-line file reader utilizing C static variables to preserve state across consecutive function calls.

-Optimized heap memory by managing a single persistent buffer allocated dynamically based on variable BUFFER_SIZE macro definitions.

-Handled concurrent multi-file stream reading by tracking separate tracking instances utilizing an array of File Descriptors (FD).

-Eliminated memory leaks, dangling pointers, and segmentation faults during unaligned block reads or abrupt EOF (End Of File).
