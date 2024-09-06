#!/bin/bash

yacc -d -Wcounterexamples -Wother -Wconflicts-sr 1905080.y
flex 1905080.l
g++ -w -g lex.yy.c y.tab.c -o out
./out noerror.c
rm lex.yy.c y.tab.c y.tab.h out