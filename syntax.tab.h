
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     INTNUM = 259,
     REALNUM = 260,
     ADDOP = 261,
     MULOP = 262,
     RELOP = 263,
     ASSIGNOP = 264,
     ARRAY = 265,
     BEG = 266,
     BOOLEAN = 267,
     CASE = 268,
     CHAR = 269,
     DO = 270,
     ELSE = 271,
     END = 272,
     FUNCTION = 273,
     IF = 274,
     IN = 275,
     INTEGER = 276,
     NOT = 277,
     OF = 278,
     PROCEDURE = 279,
     PROGRAM = 280,
     REAL = 281,
     REPEAT = 282,
     THEN = 283,
     TYPE = 284,
     UNTIL = 285,
     VAR = 286,
     WHILE = 287,
     WITH = 288,
     INPUT = 289,
     OUTPUT = 290,
     PLUS = 291,
     MINUS = 292,
     OR_OP = 293,
     MULTIPLY = 294,
     DIVIDE = 295,
     INT_DIVIDE = 296,
     MOD_OP = 297,
     AND_OP = 298,
     DIGITS = 299,
     EQ = 300,
     NEQ = 301,
     LT = 302,
     LTE = 303,
     GT = 304,
     GTE = 305,
     WRONG_IDENTIFIER = 306,
     INVALID_CHAR = 307
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 92 "syntax.y"

   /* For integer values and all other token values. */
   int value;

   /* For floating point values. */
   float fl;

   /* String that stores the identifier. */
   char* iden;

   /* Stores one of the basic types - use in expressions. */
   enum type type_simple;

   /* Stores also the array type information. */
   struct type_struct
   {
     enum type enumtype;
     int lower_bound;
     int upper_bound;
   } type_detail;

   /* For storing details of actual arguments passed to procs/funcs. */
   struct actualargs_struct
   {
     enum type* arg_types;
     int num_args;
   } argument_detail;

   /* For intermediate code generation. */ //ASSGN4
   struct expr_struct
   {
     enum type type_simple;
     char* place;
     lst_t* truelist;
     lst_t* falselist;
   } expr_detail;

   /* For each statement. */ //ASSGN4
   struct stmt_struct
   {
     lst_t* nextlist;
   } stmt_detail;

   /* For keeping track of line numbers during intermediate code generation. */  //ASSGN4
   struct quad_struct
   {
     int quad;
   } quad_detail;



/* Line 1676 of yacc.c  */
#line 156 "syntax.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


