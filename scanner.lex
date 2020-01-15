%{

/* Declarations section */
#include <stdio.h>
#include "hw3_output.hpp"
#include "parser.hpp"
#include "parser.tab.hpp"

void ErrorOccured();

%}

%option yylineno
%option noyywrap
digit   		([0-9])
nozero   		([1-9])
letter  		([a-zA-Z])
whitespace		([\t\r\n ])
printable		([\x20-\x7E\x09\x0A\x0D])
printableWithoutSpecial      ([ -!#-[\]-~])
%%

void						return VOID;
int							return INT;
byte						return BYTE;
b							return B;
bool						return BOOL;
enum 						return ENUM;
and							return AND;
or							return OR;
not							return NOT;
true						return TRUE;
false						return FALSE;
"return"					return RETURN;	
if							return IF;
else						return ELSE;
while						return WHILE;
break						return BREAK;
continue					return CONTINUE;
";"							return SC;
","							return COMMA;
"("							return LPAREN;
")"							return RPAREN;
"{"							return LBRACE;
"}"							return RBRACE;
"=="						{
                                yylval = new Equality("==");
                                return EQUALITY;
                            }
"="							return ASSIGN;
"!="						{
                                yylval = new Equality("!=");
                                return EQUALITY;
                            }
"<="						{
                                yylval = new Relational("<=");
                                return RELATIONAL;
                            }
">="						{
                                yylval = new Relational(">=");
                                return RELATIONAL;
                            }
">"							{
                                yylval = new Relational(">");
                                return RELATIONAL;
                            }
"<"							{
                                yylval = new Relational("<");
                                return RELATIONAL;
                            }
"+"							{
								yylval = new Additive("+");
								return ADDITIVE;
							}
"-"							{
								yylval = new Additive("-");
								return ADDITIVE;
							}
\*							{
								yylval = new Multiplicative("*");
								return MULTIPLICATIVE;
							}
"/"							{
								yylval = new Multiplicative("/");
								return MULTIPLICATIVE;
							}
[a-zA-Z][a-zA-Z0-9]*		{
								yylval = new Identifier(string(yytext));				
								return ID;
							}
0|[1-9][0-9]*				{
                                yylval = new Num(atoi(yytext));
                                return NUM;
                            }
\"([^\n\r\"\\]|\\[rnt"\\])+\"	{
                                    yylval = new StringToken(yytext);
                                    return STRING;
                                }
}
\/\/[^\r\n]*[\r|\n|\r\n]?	;
{whitespace}				;

.							ErrorOccured();

%%

void ErrorOccured(){
	
	output::errorLex(yylineno);
	exit(0);
}

