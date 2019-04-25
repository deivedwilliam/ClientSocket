 #include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 


#define PORT 8080 


int main(int argc, char const *argv[]) 
{ 
	int client_fd, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	const char *hello = "Hello from server"; 
	
	client_fd = socket(AF_INET, SOCK_STREAM, 0);


	// Creating socket file descriptor 
	if(client_fd == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if(setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 

	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY;
	
	#ifdef DEBUG_ON 
	printf("%i\n", INADDR_ANY);
	#endif

	address.sin_port = htons(PORT); 

	if(connect(client_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 

	
	send(client_fd , hello , strlen(hello) , 0); 
	printf("Hello message sent\n"); 

	valread = read(client_fd, buffer, 1024); 
	printf("%s\n", buffer); 
	return 0; 
} 
