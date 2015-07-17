#define INTEGER 257
#define REAL 258
#define DATE 259
#define HEXSTRING 260
#define STRING 261
#define LBRACKET 262
#define RBRACKET 263
#define LBRACE 264
#define RBRACE 265
#define LCHEVRON 266
#define RCHEVRON 267
#define LQUOTE 268
#define RQUOTE 269
#define EQUAL 270
#define COMMA 271
#define SEMICOLON 272
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
  NSPlistValue* value;
  NSPlistString* string_val;
  NSPlistData* data_val;
  NSPlistArray* array_val;
  NSPlistDictionary* dict_val;
  char* string;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
