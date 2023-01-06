/*
	Create a TCP socket
    https://www.binarytides.com/winsock-socket-programming-tutorial/
*/
/*
	Live Server on port 8888
*/
#include<io.h>
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc , char *argv[])
{
	WSADATA wsa;
	SOCKET s , new_socket;
	struct sockaddr_in server , client;
	int c;
	char *message;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}
	
	printf("Initialised.\n");
	
	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}

	printf("Socket created.\n");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	
	//Bind
	if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	
	puts("Bind done");

	//Listen to incoming connections
	listen(s , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	
	c = sizeof(struct sockaddr_in);
	
	while( (new_socket = accept(s , (struct sockaddr *)&client, &c)) != INVALID_SOCKET )
	{
		puts("Connection accepted");
		
		//Reply to the client
		message = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n\r\n";
		message = "HTTP/1.1 200 OK\r\nContent-Length: 77\r\nContent-Type: text/html\r\n\r\n<html><head><title>Example</title></head><body><p>Worked!!!</p></body></html>";
		int res = send(new_socket , message , strlen(message)*8 , 0);
		res = send(new_socket , message , strlen(message) , 0);
        printf("len of bytes %d\n", res);
        closesocket(new_socket);
	}
	
	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d" , WSAGetLastError());
		return 1;
	}

	closesocket(s);
	WSACleanup();
	
	return 0;
}

// int NEW_Main(int argc, char** argv);
// // int NEW_Main();
// void NEW_Exit(void);

// #define main(...) \
//   main(int argc, char** argv) { \
//     atexit(NEW_Exit); \
// 	QUOTE(__VA_ARGS__); \
//     return NEW_Main(argc, argv); \
//   }; \
//   int NEW_Main(int argc, char** argv)

// void NEW_Exit(){
// 	puts("DONE");
// }