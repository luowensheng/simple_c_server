#include "../../../backend/c_ease/c_ease.h"


ROUTE_HTML(
INDEX_ROUTE,
	GET, 
	"/", 
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
)

ROUTE_HTML(
PAGE_1_ROUTE,
	GET, 
	"/page-1", 
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
)

ROUTE_HTML(
PAGE_2_ROUTE,
	GET, 
	"/page-2", 
	<html>
		<head>
			<title>Example</title>
		</head>
		<body>
			<h1> WELCOME TO PAGE 2 </h1>
			<h2> TIC TAC TOE APP </h2>
			<div>
			</div>
		<script>	
		</script>		
		</body>
	</html>
)

ROUTE_HTML(
PAGE_3_ROUTE,
	GET, 
	"/page-3", 
	<html>
		<head>
			<title>Example</title>
		</head>
		<body>
			<h1> WELCOME TO PAGE 3 </h1>
			<h2> IMAGE SLIDER APP </h2>
			<div>
			</div>
		<script>	
		</script>		
		</body>
	</html>
)

ROUTE_HTML(
PAGE_4_ROUTE,
	GET, 
	"/page-4", 
	<html>
		<head>
			<title>Example</title>
		</head>
		<body>
			<h1> WELCOME TO PAGE 4 </h1>
			<h2> VIDEO APP </h2>
			<div>
			</div>
		<script>	
		</script>		
		</body>
	</html>
)

void handle_page_5(Response* rw, Request* r){
    response_set_content(rw, 
	STRINGIFY(
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


