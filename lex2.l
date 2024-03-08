%{
    #include <stdio.h>
    #include <stdlib.h>
%}

%option nounput
%option noinput
%option noyywrap

%{
typedef enum {
    tID,
    tNB,
    tIF,
    tELSE,
    tWHILE,
    tPRINT,
    tRETURN,
    tINT,
    tVOID,
    tADD,
    tSUB,
    tMUL,
    tDIV,
    tLT,
    tGT, 
    tNE, 
    tEQ, 
    tGE,
    tLE,
    tASSIGN, 
    tAND,
    tOR, 
    tNOT, 
    tLBRACE, 
    tRBRACE, 
    tLPAR, 
    tRPAR, 
    tSEMI, 
    tCOMMA, 
    tERROR
} TokenType ;

%}

/*  define a letter as a character between a and z or A and Z */
alpha [a-zA-Z] 

/* define a digit as a character between 0 and 9 */
digit [0-9]

/* define a hexa as a character between 0 and 9 or a and f or A and F */
hexa [0-9A-Fa-f]


%%
"if"        {return tIF;}
"else"      {return tELSE;}
"while"     {return tWHILE;}
"printf"    {return tPRINT;}
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
[ \t\n]*                      { ; } // Tabs, whitespace and newlines

(0x({hexa}+))               {;} //???
({digit}*)                  {yyval.n = atoi(yytext); return tNB;}
({alpha}({alpha}|{digit})*) {strcpy(yyval.id, yytext); return tID;}

.                           {return tERROR;} //Default case: all that has not been matched
%%


int main(){
    yylex();
    return 0;
}


