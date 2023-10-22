#include "elf64.h"
#include "sysdefs.h"

extern void *vector[];
#define MAX_INPUT_LEN 200
#define O_RDWR 2
/* ---------- */

/* write these functions */
int read(int fd, void *ptr, int len){
    if (len < 0) {
		return -1;
	}

	return syscall(__NR_read, fd, ptr, len);
}
int write(int fd, void *ptr, int len){
    if (len < 0) {
        return -1;
    }

    return syscall(__NR_write, fd, ptr, len);
} 
void exit(int err){
    syscall(__NR_exit, err);
}                  
int open(char *path, int flags){
    int fd = syscall(__NR_open, path, flags, 0644);
    if (fd < 0) {
        return -1; 
    }
    return fd;
}
int close(int fd){
    return syscall(__NR_close, fd);
}
int lseek(int fd, int offset, int flag){
    return syscall(__NR_lseek, fd, offset, flag);
}
void *mmap(void *addr, int len, int prot, int flags, int fd, int offset){
    void *result = syscall(__NR_mmap, addr, len, prot, flags, fd, offset);
    return result;
}
int munmap(void *addr, int len){
    return syscall(__NR_munmap, addr, len);
}

/* ---------- */

/* Write the three 'system call' functions - do_readline, do_print, do_getarg */
void do_readline(char *buf, int len) {
    char c;
    int i;
    for (i = 0; i < len - 1; i++) {
        if (read(0, &c, 1) <= 0) {
            break; // Handle read error or end of file
        }
        buf[i] = c;
        if (c == '\n') {
            buf[i + 1] = '\0';
            break;
        }
    }
    buf[len - 1] = '\0';
}

void do_print(char *buf) {
    char *buffer = (char *)buf;
    int i = 0;
    while (buffer[i] != '\0'){
        write(1, &buf[i], 1);
        i++;
    }
}

char *do_getarg(int i) {
    // Your implementation here
    char inputBuffer[MAX_INPUT_LEN+1];
    do_readline(inputBuffer, sizeof(inputBuffer));

    char *args[10];
    int argc = split(args, 10, inputBuffer);
    if (i >= 0 && i< argc) {
        return args[i];
    }else{
        return NULL;
    }
}

/* ---------- */



/* simple function to split a line:
 *   char buffer[200];
 *   <read line into 'buffer'>
 *   char *argv[10];
 *   int argc = split(argv, 10, buffer);
 *   ... pointers to words are in argv[0], ... argv[argc-1]
 */
int split(char **argv, int max_argc, char *line)
{
	int i = 0;
	char *p = line;

	while (i < max_argc) {
		while (*p != 0 && (*p == ' ' || *p == '\t' || *p == '\n'))
			*p++ = 0;
		if (*p == 0)
			return i;
		argv[i++] = p;
		while (*p != 0 && *p != ' ' && *p != '\t' && *p != '\n')
			p++;
	}
	return i;
}

/* ---------- */

/* This is where you write the details of the function exec(char* filename) called by main()
* Follow instructions listed in project description.
* the guts of part 2
*   read the ELF header
*   for each segment, if b_type == PT_LOAD:
*     create mmap region
*     read from file into region
*   function call to hdr.e_entry
*   munmap each mmap'ed region so we don't crash the 2nd time
*
*   don't forget to define offset, and add it to virtual addresses read from ELF file
*
*               your code here
*/
 void exec(char *filename) ;
 //{
//     // Your implementation here
//     int fd = open(filename, 0);
//     if (fd < 0) {
//         exit(1); // Open failed
//     }

//     Elf64_Ehdr hdr;
//     if (read(fd, &hdr, sizeof(hdr)) != sizeof(hdr)) {
//         close(fd);
//         exit(1); // Read ELF header failed
//     }

//     if (hdr.e_ident[0] != 0x7F || hdr.e_ident[1] != 'E' || hdr.e_ident[2] != 'L' || hdr.e_ident[3] != 'F') {
//         close(fd);
//         exit(1); // Not a valid ELF file
//     }

//     // Your code for loading and executing the ELF file here

//     close(fd); // Close the file descriptor when done
// }




/* ---------- */
void main(void) {
    /*
    vector[0] = do_readline;
    vector[1] = do_print;
    vector[2] = do_getarg;

    char filename[200];
    do_readline(filename, 200);

    exec(filename); // Execute the specified ELF file
    */
    int fs = open("test.txt",O_RDWR);
    if(fs<0){
        do_print("dsdsdsds");
        exit(1);
    }
}
