//******************************************************************************
//
// Copyright (c) 2015 Microsoft Corporation. All rights reserved.
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
//******************************************************************************

%{
#include "NSPlist.h"
#include "NSPlistParser.h"
#define SAVE_TOKEN yylval.string = strdup(yytext)
#define UNESCAPE_STRING processEscapes(yylval.string)

#ifdef DEBUG_NSPARSER
#define TERMINATE_LEXER printf("Unrecognized character: %s\n", yytext); yyterminate();
#else
#define TERMINATE_LEXER yyterminate();
#endif

static char getUnescapedChar(char c)
{
  switch (c) {
    case 't': return '\t';
    case 'r': return '\r';
    case 'n': return '\n';
    default: return c;
  }
}

static void processEscapes(char *data)
{
  unsigned s = 0; /* scanning index */
  unsigned w = 0; /* write-back index */
  char p = 0; /* previous character */
  char c = 0; /* current character */

  while ((c = data[s++]) != '\0') {
    if (p == '\\') {
      data[w++] = getUnescapedChar(c);
    } else if (c != '\\') {
      data[w++] = c;
    }
    p = c;
  }
  data[w] = '\0';
}

%}

%option noyywrap
%option yylineno
%option nounistd
%option never-interactive
%x COMMENT
%x QUOTED
%x DATABLOCK

D [0-9]

%%

\/\/.*$                                                 // eat up comment

<INITIAL>"/*"                                           BEGIN(COMMENT);
<COMMENT>"*/"                                           BEGIN(INITIAL);
<COMMENT>[^*]+                                          // eat comment in chunks
<COMMENT>"*"                                            // eat the lone star

<INITIAL>\"                                             BEGIN(QUOTED); return LQUOTE;
<QUOTED>\"                                              BEGIN(INITIAL); return RQUOTE;

[-]?{D}+                                                SAVE_TOKEN; return INTEGER;

-?{D}*\.?{D}+([eE][-]?{D}+)?                            SAVE_TOKEN; return REAL;

<DATABLOCK>([0-9a-fA-F]{2})+                            SAVE_TOKEN; return HEXSTRING;

[0-9a-zA-Z_\-\.\$\/]+                                   SAVE_TOKEN; return STRING;

<QUOTED>[+-]?{D}+                                       SAVE_TOKEN; return INTEGER;

<QUOTED>[+-]?{D}*\.?{D}+([eE][+-]?{D}+)?                SAVE_TOKEN; return REAL;

<QUOTED>({D}{4})(-({D}{2}){2})T({D}{2})(:({D}{2}){2})Z  SAVE_TOKEN; return DATE;

<QUOTED>(\\.|[^"\\])*                                   SAVE_TOKEN; UNESCAPE_STRING; return STRING;

\{                                                      return LBRACE;

\}                                                      return RBRACE;

\(                                                      return LBRACKET;

\)                                                      return RBRACKET;

\<                                                      BEGIN(DATABLOCK); return LCHEVRON;

<DATABLOCK>\>                                           BEGIN(INITIAL); return RCHEVRON;

=                                                       return EQUAL;

,                                                       return COMMA;

;                                                       return SEMICOLON;

<INITIAL,DATABLOCK>[ \t\r\n]+                           // eat up whitespace

<*>.                                                    TERMINATE_LEXER;

%%
