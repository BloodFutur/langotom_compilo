%{
    #include <stdio.h>
    #include <stdlib.h>
%}

%option nounput
%option noinput
%option noyywrap

/*  define a letter as a character between a and z or A and Z */
alpha [a-zA-Z] 

/* define a digit as a character between 0 and 9 */
digit [0-9]

/* define a hexa as a character between 0 and 9 or a and f or A and F */
hexa [0-9A-Fa-f]

%%
"if"        {printf("tIF\n"); }
"else"      {printf("tELSE\n"); }
"while"     {printf("tWHILE\n"); }
"print"     {printf("tPRINT\n"); }
"return"    {printf("tRETURN\n"); }
"int"       {printf("tINT\n"); }
"void"      {printf("tVOID\n"); }
"+"         {printf("tADD\n"); }
"-"         {printf("tSUB\n"); }
"*"         {printf("tMUL\n"); }
"/"         {printf("tDIV\n"); }
">="        {printf("tGE\n"); }
"<="        {printf("tLE\n"); }
"<"         {printf("tLT\n"); }
">"         {printf("tGT\n"); }
"!="        {printf("tNE\n"); }
"=="        {printf("tEQ\n"); }
"="         {printf("tASSIGN\n"); }
"&&"        {printf("tAND\n"); }
"||"        {printf("tOR\n"); }
"!"         {printf("tNOT\n"); }
"{"         {printf("tLBRACE\n"); }
"}"         {printf("tRBRACE\n"); }
\(          {printf("tLPAR\n"); }
\)          {printf("tRPAR\n"); }
;           {printf("tSEMI\n"); }
,           {printf("tCOMMA\n"); }

\/\/.*                      { ; } // Singleline comment
\/\*(.*\n)*.*\*\/           { ; } // Multiline comment
[ \t\n]*                      { ; } // Tabs, whitespace and newlines

(0x({hexa}+)) {printf("tNB: '%d[%s]'\n", (unsigned int)strtol(yytext, NULL,16), yytext); } // Hexadecimal number and print the value in decimal and hexadecimal
({digit}*)   {printf("tNB: '%s[0x%x]'\n", yytext, (unsigned int)strtol(yytext, NULL,10)); } // Decimal number and print the value in decimal and hexadecimal
({alpha}({alpha}|{digit})*) {printf("tID: '%s'\n", yytext); } // Identifier, starting by a letter and followed by letters or digits

. {printf("tERROR\n"); }
%%


// Main function given by the GOAT
int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s filename\n", argv[0]);
    exit(1);
  }
  yyin = fopen(argv[1], "r");
  if (!yyin) {
    fprintf(stderr, "invalid filename: %s\n", argv[1]);
    exit(2);
  }
  yylex();
  fclose(yyin);
  return 0;
}