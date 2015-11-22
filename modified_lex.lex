
%{
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include "symtable.h"

  //void _resword (void);
  //void _identifier (void);
  //void _addop (void);
  //void _mulop (void);
  //void _relop (void);
  
  //{identifier}				{_identifier (); return IDENTIFIER;}
  
  //{identifier}				{node temp; strcpy (temp.identifier,yytext); temp.id_type = NO_TYPE; return &temp;}
%}


whitespace	[ \t\n]

letter		[a-zA-Z]

digit		[0-9]

digits		{digit}{digit}*

fraction	[\.]{digits}

exponent	[Ee][\+\-]?{digits}

realnum	        {fraction} | {fraction}{exponent} | {digits}{fraction} | {digits}{exponent} | {digits}{fraction}{exponent}

intnum          {digits}

comment		[{][^\}]*[}]

assop		\:\=

comma           \,
  
open_paren      \(
  
close_paren     \)

open_sq		\[

close_sq	\]

semicolon       \;

colon           \:

fullstop        \.

plusminus	[\+\-]

multdiv		[\*\/]

eq		\=

neq		\<\>

lte		\<\=

lt		\<

gte		\>\=

gt		\>

identifier      {letter}({letter}|{digit})*

wrong_identifier {digits}{letter}*


%option yylineno



%%

{whitespace}		{}
{comment}		{}

[aA][rR][rR][aA][yY]			{return ARRAY;}
[bB][eE][gG][iI][nN]			{return BEG;}
[bB][oO][oO][lL][eE][aA][nN]		{return BOOLEAN;}
[cC][aA][sS][eE]		        {return CASE;}
[cC][hH][aA][rR]			{return CHAR;}
[dD][oO]				{return DO;}
[eE][lL][sS][eE]			{return ELSE;}
[eE][nN][dD]				{return END;}
[fF][uU][nN][cC][tT][iI][oO][nN]	{return FUNCTION;}
[iI][fF]				{return IF;}
[iI][nN]				{return IN;}
[iI][nN][tT][eE][gG][eE][rR]		{return INTEGER;}
[nN][oO][tT]				{return NOT;}
[oO][fF]				{return OF;}
[pP][rR][oO][cC][eE][dD][uU][rR][eE]	{return PROCEDURE;}
[pP][rR][oO][gG][rR][aA][mM]		{return PROGRAM;}
[rR][eE][aA][lL]			{return REAL;}
[rR][eE][pP][eE][aA][tT]		{return REPEAT;}
[tT][hH][eE][nN]			{return THEN;}
[tT][yY][pP][eE]			{return TYPE;}
[uU][nN][tT][iI][lL]			{return UNTIL;}
[vV][aA][rR]				{return VAR;}
[wW][hH][iI][lL][eE]			{return WHILE;}
[wW][iI][tT][hH]			{return WITH;}

[iI][nN][pP][uU][tT]                    {return INPUT;}
[oO][uU][tT][pP][uU][tT]                {return OUTPUT;}

[oO][rR]                                {yylval.value = OR_OP; return ADDOP;}
[dD][iI][vV]                            {yylval.value = INT_DIVIDE; return MULOP;}
[mM][oO][dD]                            {yylval.value = MOD_OP; return MULOP;}
[aA][nN][dD]                            {yylval.value = AND_OP; return MULOP;}

{assop}					{yylval.value = ASSIGNOP; return ASSIGNOP;}

{comma}					{return ',';}
{open_paren}				{return '(';}
{close_paren}				{return ')';}
{open_sq}				{return '[';}
{close_sq}				{return ']';}
{semicolon}				{return ';';}
{colon}					{return ':';}
{fullstop}				{return '.';}

{plusminus}				{yylval.value = (yytext[0] == '+')? PLUS : MINUS; return ADDOP;}
{multdiv}				{yylval.value = (yytext[0] == '*')? MULTIPLY : DIVIDE; return MULOP;}
{eq}					{yylval.value = EQ; return RELOP;}
{neq}					{yylval.value = NEQ; return RELOP;}
{lte}					{yylval.value = LTE; return RELOP;}
{lt}					{yylval.value = LT; return RELOP;}
{gte}					{yylval.value = GTE; return RELOP;}
{gt}					{yylval.value = GT; return RELOP;}

{fraction}                              {yylval.fl = atof(yytext); return REALNUM; }
{fraction}{exponent}                    {yylval.fl = atof(yytext); return REALNUM; }
{digits}{exponent}                      {yylval.fl = atof(yytext); return REALNUM; }
{digits}{fraction}                      {yylval.fl = atof(yytext); return REALNUM; }
{digits}{fraction}{exponent}            {yylval.fl = atof(yytext); return REALNUM; }

{intnum}				{yylval.value = atoi(yytext);  return INTNUM; }

{identifier}                            {yylval.iden = malloc (strlen (yytext) + 1); strcpy (yylval.iden,yytext); return IDENTIFIER;}

{wrong_identifier}			{yylval.value = WRONG_IDENTIFIER; return WRONG_IDENTIFIER;}

.                                       {return INVALID_CHAR;}

%%

/*
void _identifier (void)
{
  if ((yylval.symTableLoc = hashtable_search_identifier (yytext)) == NULL)
    yylval.symTableLoc = hashtable_insert (yytext);
}
*/
