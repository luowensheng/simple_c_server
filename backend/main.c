/*
	Create a TCP socket
    https://www.binarytides.com/winsock-socket-programming-tutorial/
*/
/*
	Live Server on port 8888
*/
#include "./server.h"

// "HTTP/1.1 200 OK\r\n
// Content-Length: 77\r\n
// Content-Type: text/html\r\n
// \r\n
// <html><head><title>Example</title></head><body><p>Worked!!!</p></body></html>";



void handle_index(ResponseWriter* rw, Request* r){
    HTML(
		<html>
			<head>
				<title>Example</title>
			</head>
			<body>
				<p>Worked!!!</p>
			</body>
		</html>
	);
}


char* handle_html(){

    return HTML(
		<html>
			<head>
				<title>Example</title>
			</head>
			<body>
				<p>Worked!!!</p>
			</body>
		</html>
	);
}

void print_string(String* x){
	printf("%s", x->chars);
}

void print_char(char* x){
	printf("%c", *x);
}

int main(){
	// char* test = "test is a nice car right?";
	// string_split(test, " ");

	List_char *x = new_char_list();
	push_char(x, 'c');
	push_char(x, ' ');
	push_char(x, 'a');
	push_char(x, ' ');
	push_char(x, 'd');
	push_char(x, 'c');
	each_char(x, print_char);

	// each_String(res, print_string);

	// App* app = create_app();

	// app_get(app, "/",  &handle_index);
	// app_gets(app, "/html",  handle_html);

	// return app_listen(app, 8080);

}

// List(int);

// void print_int(int* x){
// 	printf("%d", *x);
// }

// int main2(){
//    List_int* arr = new_int_list();
//    push_int(arr, 1);
//    each_int(arr, print_int);
//    puts("");

//    push_int(arr, 2);
//    each_int(arr, print_int);
//    puts("");


//    push_int(arr, 3);
//    each_int(arr, print_int);
//    puts("");


//    push_int(arr, 4);
//    each_int(arr, print_int);
//    puts("");

// }