/*****************************************************************************
*	FILENAME : threadedfs.c
*	DESCRIPTION:Contains Code for a file server , that will accept a filename
*	from a file client process  read that file and sends it over socket  
*	to the client process .(Shows a typical THREADED SERVER )
*	Invoke the Executable as a.out   
*       You may use the same fileclient, which was used for iterative demo.
******************************************************************************/


#include	<stdio.h>
#include	<stdlib.h>
#include	<errno.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<sys/wait.h>
#include	<fcntl.h>
#include	<pthread.h>
#include	<unistd.h>
#define MYPORT 16651 

void *doit(void *);

int main( int C, char *V[] )
{
	int	sd,connfd,retbind;
	struct	sockaddr_in
		serveraddress,cliaddr;
	socklen_t len;
	pthread_t th1;
	char buf[100];

	sd = socket( AF_INET, SOCK_STREAM, 0 );
	if( sd < 0 ) {
		perror( "socket" );
		exit( 1 );
	}

	memset( &serveraddress, 0, sizeof(serveraddress) );
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_port = htons(MYPORT);//PORT NO
	serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);//ADDRESS
	retbind=bind(sd,(struct sockaddr*)&serveraddress,sizeof(serveraddress));
	if(-1==retbind)
	{
		perror("Bind Fails\n");
		exit(1);
	}
	listen(sd,5);
	/*Beginning of the Main Server Processing Loop*/
	
	for(;;){
		printf("I am waiting-----Start of Main Loop\n");
		len=sizeof(cliaddr);
		connfd=accept(sd,(struct sockaddr*)&cliaddr,&len);
		if ( connfd < 0)
		{
			if (errno == EINTR) 
			printf("Interrupted system call ??");
			continue;
		}
		printf("Connection from %s\n",
		inet_ntop(AF_INET,&cliaddr.sin_addr,buf,sizeof(buf)));
		pthread_create(&th1,NULL,&doit,(void*)connfd);		
			
	}
	
}



/*********************************************************************
*	FUNCTION NAME:doit
*	DESCRIPTION: Reads the filename , opens the file , reads it and 
*	writes it on the socket.
*	NOTES : 
*	RETURNS :void 
********************************************************************/



void * doit(
	void *connfd) /*The connection socket is passed as the argument */

/*********************************************************************/
	

{
	char fname[1024] , sendbuffer[1024];
	int pointer=0,n,fd;
	pthread_detach(pthread_self());
	/*Now Reading the File Name */
	while ((n=read((int)connfd,(fname + pointer),1024))>0){
		pointer=pointer+n;
	}
	fname[pointer]='\0';
	printf("SERVER THREAD %d  :Request to send file  %s\n " ,pthread_self(),fname);
	/*Now Opening the file */
	fd = open(fname, O_RDONLY);
	if (fd < 0 )
	{
			printf("SERVER  THREAD %d: ERROR OPENING FILE \n",
				 pthread_self());
			pthread_exit(NULL);
	}
	while ( (n=read( fd , sendbuffer , 1024)) >0)
		write( (int)connfd , sendbuffer , n);
	printf ("File sending successful \n");
	close((int)connfd);
	close(fd);
	pthread_exit(NULL);
}

/*********************************************************************/

