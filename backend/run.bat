@echo off
gcc %1.c -lwsock32 -o ./out/%1.o && out\%1.o