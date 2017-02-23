/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_SINTACTICO_TAB_H_INCLUDED
# define YY_YY_SINTACTICO_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    MAIN = 258,
    NUMERO_ENTERO = 259,
    NUMERO_REAL = 260,
    IDENTIFICADOR = 261,
    INT = 262,
    FLOAT = 263,
    PARENTESIS_IZQUIERDA = 264,
    PARENTESIS_DERECHA = 265,
    LLAVE_IZQUIERDA = 266,
    LLAVE_DERECHA = 267,
    IF = 268,
    ELSE = 269,
    FOR = 270,
    WHILE = 271,
    PTOCOMA = 272,
    COMA = 273,
    ASPAS = 274,
    FINARCHIVO = 275,
    SUMA = 276,
    RESTA = 277,
    MULTIPLICACION = 278,
    DIVISION = 279,
    COMPARACION = 280,
    MAYOR_IGUAL = 281,
    MENOR_IGUAL = 282,
    MAYOR_QUE = 283,
    MENOR_QUE = 284,
    DIFERENTE = 285,
    OU = 286,
    E = 287,
    INCREMENTO = 288,
    DECREMENTO = 289,
    IGUAL = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SINTACTICO_TAB_H_INCLUDED  */
