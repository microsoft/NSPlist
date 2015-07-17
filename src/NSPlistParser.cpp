/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140422

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "NSPlistParser.y"
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

#line 65 "NSPlistParser.y"
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
#line 99 "NSPlistParser.cpp"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

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
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    3,    4,    4,    5,    5,    5,    6,    6,    7,
    8,    8,    1,    1,    1,    1,    2,    2,    2,    2,
    2,    2,    2,    2,    2,
};
static const YYINT yylen[] = {                            2,
    1,    3,    5,    0,    4,    3,    2,    3,    1,    3,
    2,    0,    1,    1,    1,    1,    1,    3,    1,    3,
    1,    3,    1,    3,    2,
};
static const YYINT yydefred[] = {                         0,
   17,   19,   21,   23,    0,    4,   12,    0,    0,    1,
   16,   13,   14,   15,    7,    9,    0,    0,    0,    0,
    0,    0,    0,   25,    6,    0,    2,    0,   11,   10,
   18,   20,   22,   24,    5,    8,    0,    0,    3,
};
static const YYINT yydgoto[] = {                          9,
   10,   11,   12,   18,   13,   17,   14,   19,
};
static const YYINT yysindex[] = {                      -212,
    0,    0,    0,    0, -239,    0,    0, -256,    0,    0,
    0,    0,    0,    0,    0,    0, -259, -251, -219, -260,
 -258, -254, -253,    0,    0, -224,    0, -244,    0,    0,
    0,    0,    0,    0,    0,    0, -212, -242,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
   -5,   10,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 56
static const YYINT yytable[] = {                         16,
   20,   21,   22,   25,   23,    1,    2,    3,   31,    4,
   32,   26,   24,   27,   33,   34,    8,    1,    2,    3,
   36,    4,    5,   15,    6,   37,    7,   28,    8,   39,
    0,   38,    1,    2,    3,    0,    4,    5,   35,    6,
   29,    7,    0,    8,    1,    2,    3,   30,    4,    5,
    0,    6,    0,    7,    0,    8,
};
static const YYINT yycheck[] = {                          5,
  257,  258,  259,  263,  261,  257,  258,  259,  269,  261,
  269,  271,  269,  265,  269,  269,  268,  257,  258,  259,
   26,  261,  262,  263,  264,  270,  266,   18,  268,  272,
   -1,   37,  257,  258,  259,   -1,  261,  262,  263,  264,
  260,  266,   -1,  268,  257,  258,  259,  267,  261,  262,
   -1,  264,   -1,  266,   -1,  268,
};
#define YYFINAL 9
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 272
#define YYUNDFTOKEN 283
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"INTEGER","REAL","DATE",
"HEXSTRING","STRING","LBRACKET","RBRACKET","LBRACE","RBRACE","LCHEVRON",
"RCHEVRON","LQUOTE","RQUOTE","EQUAL","COMMA","SEMICOLON",0,0,0,0,0,0,0,0,0,0,
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : plist",
"plist : value",
"dictionary : LBRACE assignments RBRACE",
"assignments : assignments keyvalue EQUAL value SEMICOLON",
"assignments :",
"array : LBRACKET values COMMA RBRACKET",
"array : LBRACKET values RBRACKET",
"array : LBRACKET RBRACKET",
"values : values COMMA value",
"values : value",
"data : LCHEVRON hexvalues RCHEVRON",
"hexvalues : hexvalues HEXSTRING",
"hexvalues :",
"value : dictionary",
"value : array",
"value : data",
"value : keyvalue",
"keyvalue : INTEGER",
"keyvalue : LQUOTE INTEGER RQUOTE",
"keyvalue : REAL",
"keyvalue : LQUOTE REAL RQUOTE",
"keyvalue : DATE",
"keyvalue : LQUOTE DATE RQUOTE",
"keyvalue : STRING",
"keyvalue : LQUOTE STRING RQUOTE",
"keyvalue : LQUOTE RQUOTE",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 95 "NSPlistParser.y"
	{ plistVal = yystack.l_mark[0].value; }
break;
case 2:
#line 98 "NSPlistParser.y"
	{ yyval.dict_val = yystack.l_mark[-1].dict_val; }
break;
case 3:
#line 101 "NSPlistParser.y"
	{ yystack.l_mark[-4].dict_val->insert(yystack.l_mark[-3].string_val, yystack.l_mark[-1].value); yyval.dict_val = yystack.l_mark[-4].dict_val; }
break;
case 4:
#line 102 "NSPlistParser.y"
	{ yyval.dict_val = new NSPlistDictionary(); }
break;
case 5:
#line 105 "NSPlistParser.y"
	{ yyval.array_val = yystack.l_mark[-2].array_val; }
break;
case 6:
#line 106 "NSPlistParser.y"
	{ yyval.array_val = yystack.l_mark[-1].array_val; }
break;
case 7:
#line 107 "NSPlistParser.y"
	{ yyval.array_val = new NSPlistArray(); }
break;
case 8:
#line 110 "NSPlistParser.y"
	{ yystack.l_mark[-2].array_val->insert(yystack.l_mark[0].value); yyval.array_val = yystack.l_mark[-2].array_val; }
break;
case 9:
#line 111 "NSPlistParser.y"
	{ yyval.array_val = new NSPlistArray(); yyval.array_val->insert(yystack.l_mark[0].value); }
break;
case 10:
#line 114 "NSPlistParser.y"
	{ yyval.data_val = yystack.l_mark[-1].data_val; }
break;
case 11:
#line 117 "NSPlistParser.y"
	{ yystack.l_mark[-1].data_val->insert(yystack.l_mark[0].string); yyval.data_val = yystack.l_mark[-1].data_val; }
break;
case 12:
#line 118 "NSPlistParser.y"
	{ yyval.data_val = new NSPlistData(); }
break;
case 13:
#line 121 "NSPlistParser.y"
	{ yyval.value = yystack.l_mark[0].dict_val; }
break;
case 14:
#line 122 "NSPlistParser.y"
	{ yyval.value = yystack.l_mark[0].array_val; }
break;
case 15:
#line 123 "NSPlistParser.y"
	{ yyval.value = yystack.l_mark[0].data_val; }
break;
case 16:
#line 124 "NSPlistParser.y"
	{ yyval.value = yystack.l_mark[0].string_val; }
break;
case 17:
#line 127 "NSPlistParser.y"
	{ yyval.string_val = new NSPlistString(yystack.l_mark[0].string, NSPlistIntegerString); }
break;
case 18:
#line 128 "NSPlistParser.y"
	{ yyval.string_val = new NSPlistString(yystack.l_mark[-1].string, NSPlistIntegerString); }
break;
case 19:
#line 129 "NSPlistParser.y"
	{ yyval.string_val = new NSPlistString(yystack.l_mark[0].string, NSPlistRealString); }
break;
case 20:
#line 130 "NSPlistParser.y"
	{ yyval.string_val = new NSPlistString(yystack.l_mark[-1].string, NSPlistRealString); }
break;
case 21:
#line 131 "NSPlistParser.y"
	{ yyval.string_val = new NSPlistString(yystack.l_mark[0].string, NSPlistDateString); }
break;
case 22:
#line 132 "NSPlistParser.y"
	{ yyval.string_val = new NSPlistString(yystack.l_mark[-1].string, NSPlistDateString); }
break;
case 23:
#line 133 "NSPlistParser.y"
	{ yyval.string_val = new NSPlistString(yystack.l_mark[0].string, NSPlistStringString); }
break;
case 24:
#line 134 "NSPlistParser.y"
	{ yyval.string_val = new NSPlistString(yystack.l_mark[-1].string, NSPlistStringString); }
break;
case 25:
#line 135 "NSPlistParser.y"
	{ yyval.string_val = new NSPlistString("", NSPlistStringString); }
break;
#line 587 "NSPlistParser.cpp"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
