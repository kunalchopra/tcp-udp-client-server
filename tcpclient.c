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
    int  lenData, recData, s, n, port_no, r, i;
    struct sockaddr_in   server_addr;
    char buffer[512];
    printf("Starting TCP CLIENT\n");    
    
    //check number of arguments
    if ( argc < 3 )
    {
       printf( "Client: Invalid number of arguments  \n" );
       return (EINVAL); 
    }
  
    port_no = atoi(argv[2]);
  
    if ( port_no < 1 || port_no > 65535 )
    {
      printf( "Client: Invalid port number\n" );
      return (EINVAL);
    }
  
    s = socket(PF_INET,SOCK_STREAM,0);
    bzero(&server_addr, sizeof(server_addr));
    
    if(s == -1)
    {
	    printf("There was an error creating the socket\n");
    } else {
	    printf("Socket created\n");
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);  
    server_addr.sin_port = htons(port_no);

    printf("Will attempt to connect with SERVER \n");
    r = connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    if(r == -1)
    {
	    printf("Connection refused\n");
    } else {
	    printf("Connection successful\n");
    }

    // process data 
 
    lenData = write( s, argv[3], 512); 
 
    if ( lenData == -1 ) { 
      printf("Error sending data to SERVER\n"); 
    } 
      
    printf("Message sent to SERVER: %s\n", argv[3]); 
    
    recData = read( s, buffer, 512); 
    
    if( recData == -1 ) { 
		  printf("Error receiving data from SERVER\n"); 
	  } else {
 		  buffer[recData] = '\0';
	  }
	
   printf("Message echoed back from SERVER: %s\n", buffer); 
 
   printf("Closing connection .... \n");    
    close(s);
    return (0);
  }
