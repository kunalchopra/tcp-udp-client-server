  #include <errno.h>
  #include <netdb.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <string.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  
  extern int errno;
  extern int h_errno;
  
 

int main( int argc, char **argv )
{
    int                  sock_server, sock_client, r, len, l, n;
    char                 buffer[512];
    struct sockaddr_in   my_addr, client_addr;
    int writData  = 0; 
    int lenData = 0; 
    
    printf("Starting TCP SERVER\n"); 

    //Build a socket
    sock_server = socket(PF_INET,SOCK_STREAM,0);

    if(sock_server == -1)
    {
	    printf("There was an error creating the socket\n");
    } else {
    	printf("Socket created\n");
    }

    bzero(&my_addr,sizeof(my_addr));

    my_addr.sin_family = AF_INET; 
    my_addr.sin_port = htons(atoi(argv[1]));
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    r = bind(sock_server,(struct sockaddr *)&my_addr, sizeof(my_addr));
    
    printf("called bind \n");
    if (r < 0)
    {
      printf("Binding was not successful\n");
    } else {
      printf("Binding successful\n");;
    }

    while(1) 
    { 
      printf("Listening for connections ...........\n"); 
      // listen 
      l = listen( sock_server, 5 ); 
 
      if( l == -1 ) 
      { 
         printf("Failed to listen, connection refused\n"); 
      } 
      // connect 
	    len = sizeof(client_addr);
	    sock_client = accept(sock_server,(struct sockaddr *)&client_addr, &len);
 
      if( sock_client == -1 ) 
	    { 
         printf("Invalid client socket, connection failed\n"); 
	    } else {
         printf("Connection estabilished\n");
    	}
    
      // process data received in the buffer
     
      lenData = read( sock_client, buffer, 512 ); 
 
      if( lenData == -1 ) { 
          printf("Error receiving data from CLIENT\n"); 
          break; 
      } 
	    printf("Message received from Client: %s\n", buffer);
        
     writData = write( sock_client, buffer, lenData); 
     if( writData == -1 ) { 
          printf("Error sending data to CLIENT\n"); 
          break; 
     }
 
      // close client connection 
    printf("Closing connection now ....\n");
    close( sock_client ); 
    close(sock_server );
    return (0);
  }
}
