#include "sysdefs.h"

/* write these functions */

int read(int fd, void *ptr, int len);
int write(int fd, void *ptr, int len);
void exit(int err);

/* The read function is given to you in the starter code, by analogy write the
   write() function and the exit() function.
   __NR_read is defined in file sysdefs.h, it is the system call number
   for the system function that performs reading.
   A link is provided after each function, to read about this system call function
   in the Linux manual page */

int read(int fd, void *ptr, int len) {
	if (len < 0) {
		return -1;
	}

	return syscall(__NR_read, fd, ptr, len);
} /*https://man7.org/linux/man-pages/man2/read.2.html */


int write(int fd, void *ptr, int len){
	if (len < 0) {
        return -1;
    }

    return syscall(__NR_write, fd, ptr, len);
} /* https://man7.org/linux/man-pages/man2/write.2.html */



void exit(int err){
	syscall(__NR_exit, err);
} /* https://man7.org/linux/man-pages/man2/exit.2.html */


/* Read one line from stdin (file descriptor 0) into a buffer pointed to by ptr. */
void readline(int fd, void *ptr, int max_len) {
    char *buffer = (char *)ptr;
    int i = 0;
    char c;

    while (i < max_len - 1) {
        if (read(fd, &c, 1) <= 0) {
            // Handle read error or end of file
            break;
        }

        buffer[i] = c;
        if (c == '\n') {
            buffer[i + 1] = '\0';
            break;
        }
        i++;
    }

    // Ensure null-terminated string
    buffer[max_len - 1] = '\0';
}

/* Print a string to stdout (file descriptor 1) */
void print_and_clean(int fd, void *ptr, int max_len) {
    char *str = (char *)ptr;
    int i = 0;

    while (str[i] != '\0' && i < max_len) {
        write(fd, &str[i], 1);
        str[i] = '\0'; // Clean the printed character
        i++;
    }
}

void main(void) {
    char line[200];

    while (1) {
        readline(0, line, 200);

        if (line[0] == 'q' || line[0] == 'u' || line[0] == 'i' || line[0] == 't') {
            exit(0); // Exit if the line starts with 'q', 'u', 'i', or 't'
        } else {
            print_and_clean(1, line, 200);
        }
    }
}
