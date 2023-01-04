/*
	Create a TCP socket
    https://www.binarytides.com/winsock-socket-programming-tutorial/
*/
/*
	Live Server on port 8888
*/
#include "./string.h"
#include "./server.h"




void handle_index(ResponseWriter* rw, Request* r){
    response_writer_set_content(rw, 
	HTML(
		<html>
			<head>
				<title>Example</title>
			</head>
			<body>
				<ul>ROUTES
				<li><a href="/page-1"> Page 1</a></li>
				<li><a href="/page-2"> Page 2</a></li>
				<li><a href="/page-3"> Page 3</a></li>
				<li><a href="/page-4"> Page 4</a></li>
				<li><a href="/page-5"> Page 5</a></li>
				</ul>
			</body>
		</html>
	));
}

void handle_page_1(ResponseWriter* rw, Request* r){
    response_writer_set_content(rw, 
	HTML(
		<html>
			<head>
				<title>Example</title>
			</head>
			<body>
				<h1> WELCOME TO PAGE 1 </h1>
				<h2> Calculator APP </h2>
				<div>
				    
				</div>
			<script>	
			</script>		
			</body>
		</html>
	));
}

void handle_page_2(ResponseWriter* rw, Request* r){
    response_writer_set_content(rw, 
	HTML(
		<html>
			<head>
				<title>Example</title>
			</head>
			<body>
				<h1> WELCOME TO PAGE 2 </h1>
			</body>
		</html>
	));
}

void handle_page_3(ResponseWriter* rw, Request* r){
    response_writer_set_content(rw, 
	HTML(
		<html>
			<head>
				<title>Example</title>
			</head>
			<body>
				<h1> WELCOME TO PAGE 3 </h1>
			</body>
		</html>
	));
}

void handle_page_4(ResponseWriter* rw, Request* r){
    response_writer_set_content(rw, 
	HTML(
		<html>
			<head>
				<title>Example</title>
			</head>
			<body>
				<h1> WELCOME TO PAGE 4 </h1>
			</body>
		</html>
	));
}

void handle_page_5(ResponseWriter* rw, Request* r){
    response_writer_set_content(rw, 
	HTML(
		<html>
			<head>
				<title>Example</title>
			</head>
			<body>
				<h1> WELCOME TO PAGE 5 </h1>
			</body>
		</html>
	));
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


int main(){

	App* app = create_app();

	app_get(app, "/",  &handle_index);

	app_get(app, "/page-1",  &handle_page_1);
	app_get(app, "/page-2",  &handle_page_2);
	app_get(app, "/page-3",  &handle_page_3);
	app_get(app, "/page-4",  &handle_page_4);
	app_get(app, "/page-5",  &handle_page_5);


	app_gets(app, "/html",  handle_html);

	return app_listen(app, 8080);
	return 0;

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