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
    int sock_server, sock_client, r, len, l, n;
    int nData = 0;
    char buffer[512];
    struct sockaddr_in   my_addr, client_addr;
    printf("NAME: Kunal Chopra\nTRU#: 9543391\n");    
    printf("Starting UDP SERVER\n"); 
 
    //  Build a socket  
    sock_server = socket(AF_INET,SOCK_DGRAM,0);

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
    
    printf("Will try to bind now\n");
    r = bind(sock_server,(struct sockaddr *)&my_addr, sizeof(my_addr));
    if (r < 0)
    {
      printf("Binding was not successful\n");
    } else {
      printf("Binding successful\n");;
    }
    printf("Waiting for receiving a datagram packet ............\n");

    len = sizeof(client_addr);
 
    nData = recvfrom(sock_server, buffer, nLeft, 0, (struct sockaddr *)&client_addr, &len);
    printf("Message recieved from CLIENT: %s", buffer); 
 
    nData = sendto( sock_server, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, len); 
    printf("\nServer will shutdown now ....\n");
    close(sock_server );
    return (0);
}
