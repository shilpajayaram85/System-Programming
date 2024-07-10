/*
When a process duplicates itself, the kernel makes a copy of all open file 
descriptors. A file descriptor is an integer that refers to an open file or 
device, and it is used for reading and writing. If a program has a file open 
before the fork, what happens if both processes try a read or a write? Will one process overwrite data from the other? Will two copies of the file be read? This code investigates this by opening up two files -- one for reading and one for 
writing -- and having both the parent and the child read and write 
simultaneously.
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void) 
{

   int n,fd_in, fd_out,fd_tmp;
   char buf[1024];

   memset(buf, 0, 1024); /* clear buffer*/
   fd_tmp = open("infile", O_WRONLY| O_CREAT|O_TRUNC , S_IRWXU);
   write(fd_tmp,"12345678",8);
   close(fd_tmp);
   fd_in = open("infile", O_RDONLY);
   fd_out = open("outfile", O_WRONLY| O_CREAT , S_IRWXU);

        fork(); /* It doesn't matter about child vs parent */

        while ((n=read(fd_in, buf, 1)) > 0)  /* Loop through the infile */
        {
				buf[n]='\0';
                printf("%d: %s\n", getpid(), buf);
                /* Write a line */
                sprintf(buf, "%d Hello, world!\n", getpid());
                write(fd_out, buf, strlen(buf));
                sleep(1);
                memset(buf, 0, 1024); /* clear buffer*/
        }
        sleep(1);
}




/*

This is a simple program that opens a file and forks into the parent and child. Each process reads from the same file descriptor (which is just a text file with the numbers 1 through 7), printing what was read along with the PID. After 
reading a line, the PID is written to the out file. The loop completes when 
there are no more characters to read in the in file.
*/

/*

This shows that as one process reads from the file, and the file pointer is 
moved for both processes. Likewise, when a file is written to, the next 
character goes to the end of the file. This makes sense, because the kernel 
keeps track of the open file's information. The file descriptor is merely an 
identifier for the process.

You might also know that the standard output (the screen) is a file descriptor, too. This is duplicated during the fork, which is why both processes can write 
to the screen.
*/











