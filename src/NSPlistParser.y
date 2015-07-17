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
#include <stdio.h>
#include "NSPlist.h"

typedef struct yy_buffer_state* YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char* str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern int yyparse();
extern FILE* yyin;
extern int yylineno;

int yylex();

static NSPlistValue *plistVal;


void yyerror(const char* s)
{
#ifdef DEBUG_NSPARSER
  printf("ERROR: %s, line %d\n", s, yylineno);
#endif
}

bool loadPlistFromBuffer(const char* byteArray, NSPlistValue*& plist)
{
  plistVal = NULL;

  YY_BUFFER_STATE buf = yy_scan_string(byteArray);
  int result = yyparse();
  yy_delete_buffer(buf);

  if (!result) {
    plist = plistVal;
  } else {
    delete plistVal;
    plist = NULL;
  }

  return !result;
}

bool loadPlistFromFile(const char* filePath, NSPlistValue*& plist)
{
  plistVal = NULL;
  int result = -1;

  yyin = fopen(filePath, "r");
  if (yyin) {
    result = yyparse();
    fclose(yyin);
  }

  if (!result) {
    plist = plistVal;
  } else {
    delete plistVal;
    plist = NULL;
  }

  return !result;
}

%}

%union {
  NSPlistValue* value;
  NSPlistString* string_val;
  NSPlistData* data_val;
  NSPlistArray* array_val;
  NSPlistDictionary* dict_val;
  char* string;
}

%token <string> INTEGER
%token <string> REAL
%token <string> DATE
%token <string> HEXSTRING
%token <string> STRING
%token LBRACKET RBRACKET LBRACE RBRACE LCHEVRON RCHEVRON
%token LQUOTE RQUOTE EQUAL COMMA SEMICOLON

%type <value> value
%type <string_val> keyvalue
%type <dict_val> dictionary
%type <dict_val> assignments
%type <array_val> array
%type <array_val> values
%type <data_val> data
%type <data_val> hexvalues

%start plist

%%

plist : value                                 { plistVal = $1; }
      ;

dictionary : LBRACE assignments RBRACE        { $$ = $2; }
           ;

assignments : assignments keyvalue EQUAL value SEMICOLON    { $1->insert($2, $4); $$ = $1; }
            | /* Empty */                     { $$ = new NSPlistDictionary(); }
            ;

array : LBRACKET values COMMA RBRACKET        { $$ = $2; }
      | LBRACKET values RBRACKET              { $$ = $2; }
      | LBRACKET RBRACKET                     { $$ = new NSPlistArray(); }
      ;

values : values COMMA value                   { $1->insert($3); $$ = $1; }
       | value                                { $$ = new NSPlistArray(); $$->insert($1); }
       ;

data : LCHEVRON hexvalues RCHEVRON            { $$ = $2; }
     ;

hexvalues : hexvalues HEXSTRING               { $1->insert($2); $$ = $1; }
          | /* Empty */                       { $$ = new NSPlistData(); }
          ;

value : dictionary                            { $$ = $1; }
      | array                                 { $$ = $1; }
      | data                                  { $$ = $1; }
      | keyvalue                              { $$ = $1; }
      ;

keyvalue : INTEGER                            { $$ = new NSPlistString($1, NSPlistIntegerString); }
         | LQUOTE INTEGER RQUOTE              { $$ = new NSPlistString($2, NSPlistIntegerString); }
         | REAL                               { $$ = new NSPlistString($1, NSPlistRealString); }
         | LQUOTE REAL RQUOTE                 { $$ = new NSPlistString($2, NSPlistRealString); }
         | DATE                               { $$ = new NSPlistString($1, NSPlistDateString); }
         | LQUOTE DATE RQUOTE                 { $$ = new NSPlistString($2, NSPlistDateString); }
         | STRING                             { $$ = new NSPlistString($1, NSPlistStringString); }
         | LQUOTE STRING RQUOTE               { $$ = new NSPlistString($2, NSPlistStringString); }
         | LQUOTE RQUOTE                      { $$ = new NSPlistString("", NSPlistStringString); }
         ;

%%