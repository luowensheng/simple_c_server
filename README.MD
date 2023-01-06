# C_EASE 
### BUILD BACKEND SERVER in C (maybe unsafe)

- only supports windows at the moment
- still under construction


## BASIC DEMO

#### defining routes with macros

```c
// routes.h 

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
PAGE_3_ROUTE,
	GET, 
	"/page-3", 
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
PAGE_4_ROUTE,
	GET, 
	"/page-4", 
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
```

```c
// main.c

#include "./routes.h"

APP_MAIN(
	8080,
	INDEX_ROUTE,
	PAGE_1_ROUTE,
	PAGE_2_ROUTE,
	PAGE_3_ROUTE,
	PAGE_4_ROUTE
)

	
```