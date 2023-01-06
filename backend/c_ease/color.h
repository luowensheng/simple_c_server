// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
#ifndef __C_EASE_COLORS_H
#define __C_EASE_COLORS_H

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE    "\x1b[47m"

#define ANSI_COLOR_RESET   "\x1b[0m"

#define RED(s) ANSI_COLOR_RED s ANSI_COLOR_RESET  
#define GREEN(s) ANSI_COLOR_GREEN s ANSI_COLOR_RESET  
#define YELLOW(s) ANSI_COLOR_YELLOW s ANSI_COLOR_RESET  
#define BLUE(s) ANSI_COLOR_BLUE s ANSI_COLOR_RESET  
#define MAGENTA(s) ANSI_COLOR_MAGENTA s ANSI_COLOR_RESET  
#define CYAN(s) ANSI_COLOR_CYAN s ANSI_COLOR_RESET  
#define WHITE(s) ANSI_COLOR_WHITE s ANSI_COLOR_RESET  

#endif