  #include <errno.h>
  #include <netdb.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include <unistd.h>
  
  extern int errno;
  extern int h_errno;
  
  int main( int argc, char **argv )
  {
    int                  s, n, port_no, r, i, len, nData;
    struct sockaddr_in   server_addr;
    printf("Starting UDP CLIENT\n");    

    if ( argc < 3 )
    {
      printf( "Invalid number of arguments  \n" );
      return (EINVAL); /* Invalid argument */
    }
  
    port_no = atoi(argv[2]);
  
    if ( port_no < 1 || port_no > 65535 )
    {
      printf( "client: invalid port number\n" );
      return (EINVAL);
    }
  
    printf("Argument values received by CLIENT - Server IP address: %s\nServer Port Number: %s\nMessage: %s\n",argv[1], argv[2], argv[3]);

    //  Build the socket
 
    s = socket(PF_INET,SOCK_DGRAM,0);
    bzero(&server_addr, sizeof(server_addr));
    if(s == -1)
    {
	    printf("There was an error creating the socket\n");
    } else {
	    printf("Socket created\n");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);  // "198.162.21.132");//arg[1]
    server_addr.sin_port = htons(port_no);

    len = sizeof(server_addr);
 
    nData = sendto( s, argv[3], strlen(argv[3]), 0, (struct sockaddr *)&server_addr, len); 
    if( nData == -1 ) { 
       printf("Error sending data to SERVER\n"); 
    }
    
    printf("Message sent to SERVER: %s \n", argv[3]); 
       
    nData = recvfrom( s, argv[3], strlen(argv[3]), 0, (struct sockaddr *)&server_addr, &len); 
 
    if( nData == -1 ) { 
  		printf("Error receiving data from SERVER\n"); 
    } 

    printf("ECHO:Message echoed back from SERVER: %s\n", argv[3]); 
    printf("Client is closing down .... \n");    
  
    close(s);
    return (0);
}
