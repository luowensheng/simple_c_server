@echo off

SET var1=%1
SET var2=%2
SET current_dir=%cd%

SET examples_dir=%current_dir%\examples
SET out_dir=%current_dir%\examples\out

if %var1%==backend ( CALL :run_example %var1% %var2%) else ( echo "unknown command %var1%" )

echo %main_filepath%


EXIT /B %ERRORLEVEL% 
:run_example
SET out=%out_dir%\%var2%
gcc -Wall %examples_dir%\%var1%\%var2%\main.c -lwsock32 -o %out% && %out%
EXIT /B 0