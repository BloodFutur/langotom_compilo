%option nounput
%option noinput
%option noyywrap

%{
    #include "c.tab.h"
    int line_number = 1;
%}


/*  define a letter as a character between a and z or A and Z */
alpha [a-zA-Z] 

/* define a digit as a character between 0 and 9 */
digit [0-9]

/* define a hexa as a character between 0 and 9 or a and f or A and F */
hexa [0-9A-Fa-f]


%%
"main"      {return tMAIN;}
"if"        {return tIF;}
"else"      {return tELSE;}
"while"     {return tWHILE;}
"print"    {return tPRINT;}
"return"    {return tRETURN;}
"int"       {return tINT;}
"void"      {return tVOID;}
"+"         {return tADD;}
"-"         {return tSUB;}
"*"         {return tMUL;}
"/"         {return tDIV;}
">="        {return tGE;}
"<="        {return tLE;}
"<"         {return tLT;}
">"         {return tGT;}
"!="        {return tNE;}
"=="        {return tEQ;}
"="         {return tASSIGN;}
"&&"        {return tAND;}
"||"        {return tOR;}
"!"         {return tNOT;}
"{"         {return tLBRACE;}
"}"         {return tRBRACE;}
\(          {return tLPAR;}
\)          {return tRPAR;}
;           {return tSEMI;}
,           {return tCOMMA;}

\/\/.*                      { ; } // Singleline comment
\/\*(.*\n)*.*\*\/           { ; } // Multiline comment
[ \t]*                      { ;} // Tabs, whitespace
[\n]                      { line_number++ ; } // newlines

(0x({hexa}+))               {yylval.n = (unsigned int)strtol(yytext, NULL,16); return tNB;}
({digit}*)                  {yylval.n = atoi(yytext); return tNB;}
({alpha}({alpha}|{digit})*) {strcpy(yylval.id, yytext); return tID;}

.                           {return tERROR;} //Default case: all that has not been matched
%%



