%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "symtable.h"
#include "hash.h"
#include "list.h"
  
  /* MACROS FOR BISON */
  /* This macro prints verbose error messages when syntax errors happen. */
#define YYERROR_VERBOSE
#define YYDEBUG 1
  
#define MAX_IDEN_LEN 50

  extern int yydebug; /* For parser-trace facilities. */
  extern int yylineno; /* Making the global variable yylineno available to us. */
  extern char yytext[]; /* Making global variable yytext available to us. */
  extern int yyleng; /* Length of the yytext returned. */
  char* file_name; /* The name of the file that we are parsing. */

  int yywrap (void); /* Function that is called when scanner reaches EOF. */
  void yyerror (const char* s);  /* Function that is called when a parsing error occurs. */
  void print_warning (const char* s);
  void AddCode();
  int codeGen(char*);
  
  char* id_arr[50]; 
  int id_arr_size = 0;
  bool inside_paramlist = false; /* Used during variable declarations. */

  typedef struct kiran
  {
    char name[20];
    int offset;
  }ret_off;
  
  ret_off  ret_offset[20];
  int ret_address=0;
 
  //LATEST
  /* Global function/scope table. */
  struct hash func_table;

  /* Current scope. */
  func_entry_t* current_scope; /* The current scope's symbol table is available in this itself. */

  /* Functions for semantic actions. */
  void init_global_scope (char* iden);
  void idarr_assign_types (enum type enumtype, int lower_bound, int upper_bound);
  void idarr_assign_array_types (enum type id_type, int lower_bound, int upper_bound);
  void idarr_assign_simple_types (enum type id_type);
  void switch_to_newscope (char* iden);
  func_entry_t* lookup_func_entry (char* iden);
  func_entry_t* lookup_func_scope (char* iden);
  id_entry_t* lookup_id_entry (char* iden, func_entry_t* scope);
  id_entry_t* lookup_id_scopes (char* iden);
  void make_idarray_entry (char* iden);
  void make_scope_entry (func_entry_t* scope);
  int offset=0;
  int return_offset=1000;

  /* Next line no in intermediate code. */ //ASSGN4
  int next_quad = 1;

  /* Structures for intermediate code generation. */ //ASSGN4
  struct three_addr
  {
    float lineno; //line number ("float" because of need during sorting)
    char* code; //string containing the three address code
    struct list_elem elem;
  };
  
  struct list code_list; //list of three_addr

  typedef struct
  {
    int* lst;
    int length;
  } lst_t;

  bool lineno_less (const struct list_elem* a, const struct list_elem* b, void* aux);
  void backpatch (lst_t* lst, int quad);
  lst_t* merge_list (lst_t* lst1, lst_t* lst2);
  lst_t* make_list (int num);
  char* new_temp (void);
%}


%union
 {
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
}


/* Here we list out all the tokens that LEX identifies (in some cases with the return type of yylval). */
//%token <symTableLoc> IDENTIFIER   //pointer to location in symbol table
%token <iden> IDENTIFIER
%token <value> INTNUM //integer value
%token <fl> REALNUM //floating point value
%token <value> ADDOP MULOP RELOP ASSIGNOP

 /* Specifying the type and value info for the non-terminals. */
%type <type_simple> standard_type
%type <type_detail> type
%type <expr_detail> variable expression simple_exp term factor
%type <stmt_detail> statement
%type <argument_detail> actual_arguments_lst
 /*%type <argument_detail> arguments*/
%type <iden> function_identifier procedure_identifier
%type <quad_detail> M1
%type <stmt_detail> N1
%type <stmt_detail> compound_statement
%type <stmt_detail> statement_lst
%type <iden> sign


/* Tokens for keywords. */
%token  ARRAY
%token  BEG BOOLEAN
%token  CASE CHAR
%token  DO
%token  ELSE END
%token  FUNCTION
%token  IF IN INTEGER
%token  NOT
%token  OF
%token  PROCEDURE PROGRAM
%token  REAL REPEAT
%token  THEN TYPE
%token  UNTIL
%token  VAR
%token  WHILE WITH

%token  INPUT OUTPUT

 /* Tokens for other lex declarations. */
%token PLUS
%token MINUS
%token OR_OP
%token MULTIPLY
%token DIVIDE
%token INT_DIVIDE
%token MOD_OP
%token AND_OP
%token DIGITS

%token EQ
%token NEQ
%token LT
%token LTE
%token GT
%token GTE

 /* For wrong sequence of characters representing identifier. */
%token <value> WRONG_IDENTIFIER
%token INVALID_CHAR

 /* Specifying associativity. */
%left PLUS MINUS
%left MULTIPLY DIVIDE

%start program

%%

program : 
program_heading declarations subprogram_declarations M2 BEG compound_statement '.'
{
  /* Generating the final line of the code. */
  backpatch($6.nextlist,next_quad);
  struct three_addr* addr = malloc (sizeof (struct three_addr)); 
  addr->lineno = next_quad;
  addr->code = malloc (11);
  sprintf(addr->code, "%d:\t halt", (int)next_quad);
  list_push_back(&code_list, &addr->elem);
  next_quad++;
}

M2:
{
  struct three_addr* addr = malloc (sizeof (struct three_addr));
  addr->lineno = next_quad - 0.5;
  addr->code = malloc (strlen (current_scope->name));
  sprintf(addr->code, "%s:",current_scope->name);
  list_push_back(&code_list, &addr->elem);
}
;

//| PROGRAM IDENTIFIER error  {yyerror("Expected ( after the program name ");} program_argument_lst ')' ';' declarations subprogram_declarations BEG compound_statement '.'

//| PROGRAM IDENTIFIER '(' program_argument_lst ')' error declarations subprogram_declarations BEG compound_statement '.' {yyerror("Expected ; after ) paranthesis");}

//| PROGRAM IDENTIFIER '(' program_argument_lst ')' ';' declarations subprogram_declarations error compound_statement '.' {yyerror("Expected keyword begin after the subprogram declarations");}

//| PROGRAM IDENTIFIER '(' program_argument_lst ')' ';' declarations subprogram_declarations BEG compound_statement error {yyerror("Expected a . after the keyword end at the end of the program ");}
 
//| error {yyerror("Expected keyword program at the beginning of the code"); YYABORT;} 

//  IDENTIFIER '(' program_argument_lst ')' ';' declarations subprogram_declarations BEG compound_statement '.'
;


program_heading:
PROGRAM program_identifier '(' program_argument_lst ')' ';' { make_scope_entry (current_scope); }
;


program_identifier: /* New non-terminal! */
IDENTIFIER {init_global_scope ($1);}
;

program_argument_lst: /* New non-terminal! */

INPUT
{
  current_scope->num_args = 1;
  current_scope->arg_types = malloc (sizeof (enum type));
  *current_scope->arg_types = INPUT_TYPE;
}

| INPUT ',' OUTPUT
{
  current_scope->num_args = 2;
  current_scope->arg_types = malloc (2 * sizeof (enum type));
  *current_scope->arg_types = INPUT_TYPE;
  *(current_scope->arg_types + 1) = OUTPUT_TYPE;
}

| OUTPUT ',' INPUT
{
  current_scope->num_args = 2;
  current_scope->arg_types = malloc (2 * sizeof (enum type));
  *current_scope->arg_types = OUTPUT_TYPE;
  *(current_scope->arg_types + 1) = INPUT_TYPE;
}

| OUTPUT
{
  current_scope->num_args = 1;
  current_scope->arg_types = malloc (sizeof (enum type));
  *current_scope->arg_types = OUTPUT_TYPE;
}

| error {yyerror ("expected 'input' or 'output' in program heading"); }

| error ',' INPUT {yyerror ("expected 'output' in program header");}

| error ',' OUTPUT {yyerror ("expected 'input' in program header");}

| INPUT ',' error {yyerror ("expected 'output' in program header");}

| OUTPUT ',' error {yyerror ("expected 'input' in program header");}

;


declarations : /* Made changes here! Made changes again. */
declarations VAR var_declarations ';'

| declarations error var_declarations {yyerror("Expected keyword var in the declarations statement");}

|

;

var_declarations : /* New non-terminal! Made changes. */
var_declarations ';' var_identifier_lst ':' type
{
  if (inside_paramlist)
    {
      current_scope->arg_types = realloc (current_scope->arg_types, current_scope->num_args * sizeof (enum type));
      int i;
      for (i = current_scope->num_args - id_arr_size; i < current_scope->num_args; i++)
	current_scope->arg_types[i] = $5.enumtype;
    }
  idarr_assign_types ($5.enumtype, $5.lower_bound, $5.upper_bound);
}

| var_identifier_lst ':' type
{
  if (inside_paramlist)
    {
      current_scope->arg_types = malloc (current_scope->num_args * sizeof (enum type));
      int i;
      for (i = 0; i < id_arr_size; i++)
	current_scope->arg_types[i] = $3.enumtype;
    }
  idarr_assign_types ($3.enumtype, $3.lower_bound, $3.upper_bound);
}

| var_declarations ';' var_identifier_lst error type {yyerror("expected : before specifying the type for the list of identifiers");}

| var_declarations error var_identifier_lst ':' type {yyerror("expected ; after specifying the type for the list of identifiers");}

| var_declarations var_identifier_lst ':' type {yyerror ("Missing ; between variable declarations"); }

| var_identifier_lst error type {yyerror("Expected : before specifying the type for the list of identifiers");}

;


var_identifier_lst: /* New non-terminal! Only the identifier list for variable declarations. */
var_identifier_lst ',' IDENTIFIER 
{
  make_idarray_entry ($3);

  if (inside_paramlist)
    current_scope->num_args++;
}

| IDENTIFIER
{
  make_idarray_entry ($1);

  if (inside_paramlist)
    current_scope->num_args++;
}

;


type :
standard_type {$$.enumtype = $1;}

| ARRAY '[' INTNUM '.''.' INTNUM ']' OF standard_type 
{
  switch ($9)
    {
    case INT_TYPE:
      $$.enumtype = ARRAY_INT_TYPE;
      $$.lower_bound = $3;
      $$.upper_bound = $6;
      break;
    case REAL_TYPE:
      $$.enumtype = ARRAY_REAL_TYPE;
      $$.lower_bound = $3;
      $$.upper_bound = $6;
      break;
    case CHAR_TYPE:
      $$.enumtype = ARRAY_CHAR_TYPE;
      $$.lower_bound = $3;
      $$.upper_bound = $6;
      break;
    case BOOL_TYPE:
      $$.enumtype = ARRAY_BOOL_TYPE;
      $$.lower_bound = $3;
      $$.upper_bound = $6;
      break;
    default:
      break;
    }

  if ($3 > $6)
    yyerror ("invalid index range for the array type");
}

/* | error '[' INTNUM '.''.' INTNUM ']' OF standard_type {yyerror("Expected keyword array before [ ");} */

/* | ARRAY INTNUM '.''.' INTNUM ']' OF standard_type {yyerror("Expected [ after the keyword array");yynerrs++;YYERROR} */

/* | ARRAY '[' '.''.' ']' OF standard_type {yyerror("Expected the array range between [ and ]");yynerrs++;YYERROR;} */

/* | ARRAY '[' ']' OF standard_type {yyerror("Expected the array range between [ and ]");yynerrs++;YYERROR;} */

/* | ARRAY  OF standard_type {yyerror("Expected [ and ] after keyword array with the array range provided between [ and ]");yynerrs++;YYERROR;} */

/* | ARRAY '[' '.''.' INTNUM ']' OF standard_type {yyerror("Expected a base integer for the array range after [");yynerrs++;YYERROR;} */

/* | ARRAY '[' INTNUM '.' INTNUM ']' OF standard_type {yyerror("Expected a .. between the range integers of the array");yynerrs++;YYERROR;} */

/* | ARRAY '[' INTNUM '.''.' ']' OF standard_type {yyerror("Expected an upper limit integer for the array range before ]");yynerrs++;YYERROR;} */

/* | ARRAY '[' INTNUM '.''.' INTNUM OF standard_type {yyerror("Expected a ] after the array limits specification");yynerrs++;YYERROR;} */

/* | ARRAY '[' INTNUM '.''.' INTNUM ']' standard_type {yyerror("Expected keyword of before the type ");yynerrs++;YYERROR;}       */

/* | ARRAY error INTNUM '.''.' INTNUM ']' OF standard_type {yyerror("Expected '[' after keyword array");} */

/* | ARRAY '[' error '.''.' INTNUM ']' OF standard_type {yyerror("Expected a valid base integer for the array range after [");} */

/* | ARRAY '[' INTNUM error '.' INTNUM ']' OF standard_type {yyerror("Expected a .. between the range integers of the array");} */

/* | ARRAY '[' INTNUM '.' error INTNUM ']' OF standard_type {yyerror("Expected a .. between the range integers of the array");} */

/* | ARRAY '[' INTNUM '.''.' error ']' OF standard_type {yyerror("Expected a valid upper limit integer for the array range before ]");}  */

/* | ARRAY '[' INTNUM '.''.' INTNUM error OF standard_type {yyerror("Expected a ] after the array limits specification")}  */

/* | ARRAY '[' INTNUM '.''.' INTNUM ']' error standard_type {yyerror("Expected keyword of before the type ");}  */

;

standard_type :
INTEGER {$$ = INT_TYPE;}

| REAL  {$$ = REAL_TYPE;}

| CHAR  {$$ = CHAR_TYPE;}

| BOOLEAN  {$$ = BOOL_TYPE;}

| error {$$ = NO_TYPE; yyerror ("expected a valid type");}

;

subprogram_declarations :
subprogram_declarations subprogram_declaration ';'
{
  /* Thats the end of a function/procedure definition. 
     So now we switch back to the parent scope. */
  current_scope = current_scope->parent_scope;

  /* Generating 3addr code. */
  struct three_addr* addr = malloc (sizeof (struct three_addr)); 
  addr->lineno = next_quad;
  addr->code = malloc (13);
  sprintf(addr->code, "%d:\t return\n", (int)next_quad);
  list_push_front(&code_list, &addr->elem);
  next_quad++;
}

| subprogram_declarations subprogram_declaration error {yyerror("Expected ; at the end of the declarations");} 

|

;

subprogram_declaration :
subprogram_head declarations BEG compound_statement

| subprogram_head declarations error compound_statement { yyerror("Expected keyword begin after all the declarations ");}

;


subprogram_head :
FUNCTION function_identifier '(' arguments ':' standard_type ';'
{
  /* Parameters have already been entered into symbol table now. One more entry left in sym table. 
     That is the name of the function itself, with the return type as the type. */
  inside_paramlist = false;
  id_arr[0] = $2;
  id_arr_size = 1;
  current_scope->return_type = $6;
  idarr_assign_types ($6, 0, 0);
  id_arr_size = 0;
  make_scope_entry (current_scope);
  
  struct three_addr* addr = malloc (sizeof (struct three_addr)); 
  addr->lineno = next_quad - 0.5; //to make it appear before the first statement of the procedure/function
  addr->code = malloc (strlen($2)+2);
  sprintf(addr->code, "%s:",$2);
  list_push_front(&code_list, &addr->elem);
  //next_quad++;
  
}

| PROCEDURE procedure_identifier '(' arguments ';'
{
  inside_paramlist = false;
  current_scope->return_type = NO_TYPE;
  make_scope_entry (current_scope);
  
  struct three_addr* addr = malloc (sizeof (struct three_addr)); 
  addr->lineno = next_quad - 0.5; //to make it appear before the first statement of the procedure/function
  addr->code = malloc (strlen($2)+2);
  sprintf(addr->code, "%s:",$2);
  list_push_front(&code_list, &addr->elem);
  //next_quad++;
}

/* | error ';' {yyerror("Expected Reserved word Function or Procedure at the beginning of the declaration");} */

/* | error '\n' {yyerror("Expected Reserved word Function or Procedure at the beginning of the declaration");} */

/* | FUNCTION error ';' {yyerror("Expected valid Identifier after keyword FUNCTION ");} */

/* | FUNCTION error '\n' {yyerror("Expected valid Identifier after keyword FUNCTION ");} */

/* | PROCEDURE error ';' {yyerror("Expected valid Identifier after keyword PROCEDURE ");} */

/* | PROCEDURE error '\n' {yyerror("Expected valid Identifier after keyword PROCEDURE ");} */

/* | PROCEDURE IDENTIFIER error ';' {yyerror("Expected ( after Procedure name ");}  */

/* | PROCEDURE IDENTIFIER error '\n' {yyerror("Expected ( after Procedure name ");}  */

/* | FUNCTION IDENTIFIER error ';'  {yyerror("Expected ( after Function name ");} */

/* | FUNCTION IDENTIFIER error '\n'  {yyerror("Expected ( after Function name ");} */

/* | FUNCTION IDENTIFIER '(' arguments error ';' {yyerror("Expected : after the list of arguments ");} */

/* | FUNCTION IDENTIFIER '(' arguments error '\n' {yyerror("Expected : after the list of arguments ");} */

/* | FUNCTION IDENTIFIER '(' arguments ':' standard_type error {yyerror("Expected ; at the end of the function declaration");}   */

/* | PROCEDURE IDENTIFIER '(' arguments error {yyerror("Expected ; at the end of the procedure declaration");} */

|

;


function_identifier: /* New non-terminal! */
IDENTIFIER 
{
  $$ = $1;
  /* If not already present. */
  if (!lookup_func_entry ($1))
    {
      switch_to_newscope ($1); /* Create a new scope (which is the 'child') and assign it to current scope. */
      inside_paramlist = true; /* We are now entering the formal parameter list. */
    }
  else
    yyerror ("redeclaration of function: two functions cannot have same name");
}
;

procedure_identifier: /* New non-terminal! */
IDENTIFIER
{
  $$ = $1;
  /* If not already present. */
  if (!lookup_func_entry ($1))
    {
      switch_to_newscope ($1); /* Create a new scope (which is the 'child') and assign it to current scope. */
      inside_paramlist = true;
    }
  else
    yyerror ("redeclaration of procedure: two procedure cannot have same name");
}
;


/* This one is for arguments to a function/procedure. */
arguments:
var_declarations ')'

| ')'

| var_declarations error {yyerror("Expected ) after list of parameters");}

;


compound_statement :
statement_lst END  { $$.nextlist = $1.nextlist;}

| statement_lst error {yyerror("Expected keyword end at the end of the list of statements");}

;


statement_lst :
statement_lst M1 ';' statement { backpatch($1.nextlist,$2.quad); $$.nextlist = $4.nextlist;}

| statement {$$.nextlist = $1.nextlist;}

//| statement_lst ';' statement ';' {yyerror ("unexpected statement terminator ;");}

| statement_lst error statement {yyerror("Expected ; between two statements");}

| {$$.nextlist = (lst_t*) malloc(sizeof(lst_t)); $$.nextlist->lst = (int*) malloc(20*sizeof(int)); $$.nextlist->length =0;}

;

statement :
variable ASSIGNOP expression
{
  if (! ($1.type_simple == REAL_TYPE && $3.type_simple == INT_TYPE)
      && $1.type_simple != $3.type_simple)
    yyerror ("incompatible types in assignment");
  else if ($1.type_simple == ARRAY_INT_TYPE || $1.type_simple == ARRAY_REAL_TYPE
	   || $1.type_simple == ARRAY_CHAR_TYPE || $1.type_simple == ARRAY_BOOL_TYPE)
    yyerror ("assignment operation cannot be done on arrays");
  else
    {
      /* Generate the three address code. */
      struct three_addr* addr_n = malloc (sizeof (struct three_addr));
      addr_n->code = malloc (11 + strlen ($1.place) + strlen ($3.place));
      addr_n->lineno = next_quad;
      sprintf(addr_n->code,"%d:\t %s := %s",(int)next_quad,$1.place,$3.place);
      list_push_front(&code_list, &addr_n->elem);
      next_quad++;
    }
}

| procedure_statement
{
  $$.nextlist = (lst_t*)malloc(sizeof(lst_t));
  $$.nextlist->lst = (int*)malloc(sizeof(int)*20);
  $$.nextlist->length = 0;
}

| BEG compound_statement
{
  $$.nextlist = $2.nextlist
}

| IF expression THEN M1 statement N1 ELSE M1 statement
{
  if ($2.type_simple != BOOL_TYPE)
    yyerror ("boolean type expected for 'if' condition");
  else
    {
      $$.nextlist = (lst_t*)malloc(sizeof(lst_t)*20);
      backpatch ($2.truelist,$4.quad);
      backpatch ($2.falselist,$8.quad);
      //$$.nextlist = merge_list ($2.falselist,$9.nextlist);
      $$.nextlist = merge_list ($9.nextlist,$6.nextlist);
      $$.nextlist = merge_list ($$.nextlist,$5.nextlist);
    }
}

| WHILE M1 expression DO M1 statement
{
  if ($3.type_simple != BOOL_TYPE)
    yyerror ("boolean type expected for 'while' condition");
  else
    {
      //printf ("I am here 1 for backpatch in the list %x \n",$6.nextlist);
      backpatch ($6.nextlist, $2.quad);
      //printf ("I am here 2 \n");
      backpatch ($3.truelist, $5.quad);
      //printf ("I am here 3 \n");
      $$.nextlist = $3.falselist;
    }

  /* Goto statement for looping back. */
  struct three_addr* addr_n = malloc (sizeof (struct three_addr));
  addr_n->code = malloc (17);
  addr_n->lineno = next_quad;
  sprintf(addr_n->code,"%d:\t goto %d",(int)next_quad,$2.quad);
  list_push_front(&code_list, &addr_n->elem);
  next_quad++;
}

| variable error expression {yyerror("Expected := between LHS and expression ");}

//| IF expression THEN statement error statement {yyerror("Expected keyword else after the statement following keyword then or a statement terminator ;");}

//| IF expression error statement ELSE statement {yyerror("Expected keyword 'then' after condtional expression");}

//| IF expression statement ELSE statement {yyerror("Missing keyword 'then' after condtional expression");}

;

N1: 
{
  //printf ("Reducing N\n");
  $$.nextlist = make_list(next_quad);
 
  struct three_addr* addr = malloc (sizeof (struct three_addr));
  addr->code = malloc (13);
  addr->lineno = next_quad;
  sprintf(addr->code,"%d:\t goto ",(int)next_quad);      
  list_push_front(&code_list, &addr->elem);

  next_quad++;
}  
;

variable :
IDENTIFIER
{
  //printf ("Variable is %s\n", $1);

  //printf ("Current scope is %s\n", current_scope->name);
  /* We will check current scope. If not, then we shall iteratively check all
     visible scopes. If it is declared in some other visible scope, then we will make
     an entry in our scope too. */
  id_entry_t* t;
  if (t = lookup_id_scopes ($1))
    {
      $$.type_simple = t->id_type; /* BEWARE: this could be any of the ARRAY types too. But that is checked elsewhere, not here. */
      if (t->scope_name != current_scope->name)
	hash_insert (current_scope->symbol_table, &t->sym_table_elem);

      /* For 3addr code. */
      $$.place = malloc (strlen ($1) + 1);
      strcpy ($$.place, $1);
    }
  else
    yyerror ("undeclared identifier");
}
| IDENTIFIER '['expression']'
{
  id_entry_t* t;
  if ((t = lookup_id_scopes ($1)) && $3.type_simple == INT_TYPE)
    {
      switch (t->id_type)
	{
	case ARRAY_INT_TYPE:
	  $$.type_simple = INT_TYPE;
	  break;
	case ARRAY_REAL_TYPE:
	  $$.type_simple = REAL_TYPE;
	  break;
	case ARRAY_CHAR_TYPE:
	  $$.type_simple = CHAR_TYPE;
	  break;
	case ARRAY_BOOL_TYPE:
	  $$.type_simple = BOOL_TYPE;
	  break;

	default:
	  yyerror ("identifier is not an array variable: dereference on non-array types invalid");
	  break;
	}
      
      if (t->scope_name != current_scope->name)
	hash_insert (current_scope->symbol_table, &t->sym_table_elem);

      /* Generating 3addr code. */
      $$.place = (char*) malloc (strlen ($1) + 1 + 2 + strlen ($3.place) + 1);
      strcpy ($$.place, $1);
      strcat ($$.place, "[");
      strcat ($$.place, $3.place);
      strcat ($$.place, "]");
    }
  else 
    {
      if (t == NULL)
	yyerror ("undeclared array identifier");
      if ($3.type_simple != INT_TYPE)
	yyerror ("array index should be an integer");
    }
}

| IDENTIFIER '['expression error {yyerror("Expected ] after expression");}

| IDENTIFIER error expression ']'{yyerror("Expected [ before expression");}

| IDENTIFIER expression {yyerror("Expected [ and ] before and after the expression"); yynerrs++; YYERROR;}

;


procedure_statement :
IDENTIFIER 
{
  //printf ("This is %s\n", $1);

  /* This represents a procedure/function call. The procedure/function must be declared within the current scope. */
  bool flag = true;
  func_entry_t* f;
  if (f = lookup_func_scope ($1))
    {
      /* Now we need to do validity checks. */

      /*(1) checking number of arguments */
      if (f->num_args != 0)
	{
	  flag = false;
	  yyerror ("procedure/function call expects arguments");
	}
    }
  else
    {
      flag = false;
      yyerror ("undeclared procedure/function name");
    }

  if (flag)
    {
      struct three_addr* addr = malloc (sizeof (struct three_addr)); 
      addr->lineno = next_quad;
      addr->code = malloc (13 + strlen ($1));
      sprintf(addr->code,"%d:\t call %s,0",(int)next_quad,$1);
      list_push_front(&code_list, &addr->elem);
      next_quad++;
    }
}

| IDENTIFIER '(' actual_arguments_lst ')'
{
  //printf ("I am here");
  bool flag = true;
  func_entry_t* f;
  if (f = lookup_func_scope ($1))
    {
      /* Now we need to do validity checks. */
      
      /*(1) checking number of arguments */
      if (f->num_args != $3.num_args)
	{
	  flag = false;
	  yyerror ("number of arguments mismatch in call to procedure/function");
	  printf ("expected %d arguments for function but received %d\n", f->num_args, $3.num_args);
	}
      
      /*(2) checking types of arguments */
      else
	{
	  int i;
	  for (i = 0; i < $3.num_args; i++)
	    {
	      if ($3.arg_types[i] != f->arg_types[i])
		{
		  flag = false;
		  yyerror ("conflicting types for actual argument(s) of procedure/function call");
		  break;
		}
	    }
	  free ($3.arg_types);
	}
    }
  else
    {
      yyerror ("undeclared procedure/function name");
      flag = false;
    }

  if (flag)
    {
      struct three_addr* addr = malloc (sizeof (struct three_addr)); 
      addr->lineno = next_quad;
      addr->code = malloc (16 + strlen ($1));
//      printf (" I am here ");
      sprintf(addr->code,"%d:\t call %s,%d",(int) next_quad, $1, f->num_args);
      list_push_front(&code_list, &addr->elem);
      next_quad++;
    }
}

| WRONG_IDENTIFIER {yyerror("Expected valid identifier for procedure/function name ");yynerrs++;YYERROR;}

| WRONG_IDENTIFIER '(' actual_arguments_lst ')' {yyerror("Expected valid identifier for procedure/function name ");yynerrs++;YYERROR;}

| IDENTIFIER error actual_arguments_lst ')' {yyerror("Expected ( before the expression list");}

| IDENTIFIER '(' actual_arguments_lst error {yyerror("Expected ) after the expression list");}

| IDENTIFIER actual_arguments_lst {yyerror("Expected ( and ) paranthesis before and after the list of expressions");yynerrs++;YYERROR;}

;

actual_arguments_lst :
actual_arguments_lst ',' expression
{
  $$.num_args = $1.num_args + 1;
  $$.arg_types = realloc ($1.arg_types, $$.num_args * sizeof (enum type));
  if ($$.arg_types != $1.arg_types)
    free ($1.arg_types); /* If block of memory was moved, then free the old block. */
  $$.arg_types[$1.num_args] = $3.type_simple;  

  /* Generating the 3addr code. */
  struct three_addr* addr = malloc (sizeof (struct three_addr)); 
  addr->lineno = next_quad;
  addr->code = malloc (13 + strlen ($3.place));
  sprintf(addr->code,"%d:\t param %s",(int)next_quad, $3.place);
  list_push_front (&code_list, &addr->elem);
  next_quad++;
}

| expression
{
  $$.num_args  = 1;
  $$.arg_types = realloc ($$.arg_types, 1 * sizeof (enum type));
  $$.arg_types[0] = $1.type_simple;

  /* Generating the 3addr code. */
  struct three_addr* addr = malloc (sizeof (struct three_addr)); 
  addr->lineno = next_quad;
  addr->code = malloc (13 + strlen ($1.place));  
  sprintf(addr->code,"%d:\t param %s",(int)next_quad,$1.place);
  list_push_front(&code_list, &addr->elem);
  next_quad++;
}

| actual_arguments_lst error expression {yyerror("Expected , between two expressions");}

;

expression :
simple_exp RELOP simple_exp
{
  enum type t = $1.type_simple;
  if (t == INT_TYPE && $3.type_simple == REAL_TYPE 
      || t == REAL_TYPE && $3.type_simple == INT_TYPE)
    {
      print_warning ("no typecasting provided for integer operand");
    }
  else if (t != $3.type_simple)
    yyerror ("incompatible types in comparison");
  else if (t >= ARRAY_INT_TYPE && t <= ARRAY_BOOL_TYPE)
    yyerror ("array types cannot be compared");
  else if (t == CHAR_TYPE)
    yyerror ("characters cannot be compared");
  else if (t == BOOL_TYPE)
    yyerror ("booleans cannot be compared ");
  else
    {
      /* Generating 3addr code. */
      $$.place = new_temp();
      $$.truelist = make_list (next_quad);
      $$.falselist = make_list (next_quad + 1);

      struct three_addr* addr = malloc (sizeof (struct three_addr)); //struct three_addr will have "char* addr and struct list_elem elems"
      addr->lineno = next_quad;
      addr->code = malloc (20 + strlen ($1.place) + strlen ($3.place));
      switch($2)
	{ 
        case EQ:  sprintf(addr->code,"%d:\t if %s = %s goto " , (int)next_quad, $1.place,$3.place);break;
	case NEQ: sprintf(addr->code,"%d:\t if %s <> %s goto ", (int)next_quad, $1.place,$3.place);break;
	case GT:  sprintf(addr->code,"%d:\t if %s > %s goto " , (int)next_quad, $1.place,$3.place);break;
	case GTE: sprintf(addr->code,"%d:\t if %s >= %s goto ", (int)next_quad, $1.place,$3.place);break;
	case LT:  sprintf(addr->code,"%d:\t if %s < %s goto " , (int)next_quad, $1.place,$3.place);break;
	case LTE: sprintf(addr->code,"%d:\t if %s <= %s goto ", (int)next_quad, $1.place,$3.place);break;
	}
      
      list_push_front (&code_list, &addr->elem);
      next_quad++;
      struct three_addr* addr_next = malloc (sizeof (struct three_addr)); //struct three_addr will have "char* addr and struct list_elem elems"
      addr_next->lineno = next_quad;
      addr_next->code = malloc (12); 
      sprintf(addr_next->code,"%d:\t goto ",(int)next_quad);
      list_push_front (&code_list, &addr_next->elem);
      next_quad++;
    }
  
  $$.type_simple = BOOL_TYPE; /* Whatever happens, finally the type of expression will be BOOLEAN. */
  id_entry_t* ent = lookup_id_entry ($$.place, current_scope);
  ent->id_type = BOOL_TYPE;
}
| simple_exp
{
  $$.type_simple = $1.type_simple;
  $$.truelist = make_list (next_quad);
  $$.falselist = make_list (next_quad + 1);
  $$.place = $1.place;
  //printf ("$1.place here in expression->simple_exp is %s\n", $1.place);
}

| simple_exp error simple_exp {yyerror("Expected either * =,<,>,<=,>=,<> or a ,");}

;

simple_exp :
simple_exp ADDOP M1 term
{
  bool flag = true;
  enum type t = $1.type_simple;
  if ($2 == OR_OP)
    {
      if ($1.type_simple != BOOL_TYPE || $4.type_simple != BOOL_TYPE)
	{
	  yyerror ("invalid operands: logical OR operation requires boolean operands");
	  flag = false;
	}
      $$.type_simple = BOOL_TYPE;
    }
  else if (t == INT_TYPE && $4.type_simple == REAL_TYPE 
      || t == REAL_TYPE && $4.type_simple == INT_TYPE)
    {
      print_warning ("no typecasting provided for integer operand");
      $$.type_simple = REAL_TYPE;
    }
  else 
    {
      $$.type_simple = NO_TYPE;
      flag = false;
      if (t != $4.type_simple)
	yyerror ("incompatible types for add op");
      else if (t >= ARRAY_INT_TYPE && t <= ARRAY_BOOL_TYPE)
	yyerror ("add ops cannot be used on array type");
      else if (t == CHAR_TYPE)
	yyerror ("add ops cannot be used on character type");
      else if (t == BOOL_TYPE)
	yyerror ("add ops cannot be used on boolean type");
      else
	{
	  $$.type_simple = t;
	  flag = true;
	}
    }

  /* Generating the 3addr code. */
  if (flag)
    {
      if($2 == OR_OP)
	{
	  backpatch ($1.falselist,$3.quad);
	  $$.truelist = merge_list ($1.truelist,$4.truelist);
	  $$.falselist = $4.falselist;
	}
      else
	{
	  strcpy($$.place, new_temp());
	  struct three_addr* addr = malloc (sizeof (struct three_addr)); //struct three_addr will have "char* addr and struct list_elem elems"
	  addr->lineno = next_quad;
	  addr->code = malloc (14 + strlen ($$.place) + strlen ($1.place) + strlen ($4.place));
	  if($2 == PLUS)
	    sprintf(addr->code,"%d:\t %s := %s + %s",(int)next_quad,$$.place,$1.place,$4.place);
	  else
	    sprintf(addr->code,"%d:\t %s := %s - %s",(int)next_quad,$$.place,$1.place,$4.place);
	  
	  list_push_front(&code_list, &addr->elem);
	  next_quad++;

	  id_entry_t* ent = lookup_id_entry ($$.place, current_scope);
	  //printf ("value of ent = %p\n", (void*)ent);
   	  ent->id_type = $$.type_simple;
	}
    }
}

| sign term
{
  $$.type_simple = $2.type_simple;
  $$.place = malloc (strlen ($2.place) + 2);
  strcpy ($$.place,$1);
  strcat ($$.place,$2.place);
}

| term
{
  $$.type_simple = $1.type_simple;
  //$$.place = malloc (strlen ($1.place) + 1);
  //strcpy ($$.place, $1.place);
  $$.place = $1.place;
}

| simple_exp error term {yyerror("Expected either +,-,or between two terms");}

;


term :
factor
{
  $$.type_simple = $1.type_simple;
  //$$.place = malloc (strlen ($1.place) + 1);
  //strcpy ($$.place, $1.place);
  $$.place = $1.place
}

| term MULOP M1 factor
{
  bool flag = true;
  enum type t = $1.type_simple;
  if ($2 == AND_OP)
    {
      if ($1.type_simple != BOOL_TYPE || $4.type_simple != BOOL_TYPE)
	{
	  yyerror ("invalid operands: logical AND operation requires boolean operands");
	  flag = false;
	}
      $$.type_simple = BOOL_TYPE;
    }
  else if (t == INT_TYPE && $4.type_simple == REAL_TYPE 
      || t == REAL_TYPE && $4.type_simple == INT_TYPE)
    {
      print_warning ("no typecasting provided for integer operand");
      $$.type_simple = REAL_TYPE;
    }
  else 
    {
      $$.type_simple = NO_TYPE;
      flag = false;
      if (t != $4.type_simple)
	yyerror ("incompatible types for mul op");
      else if (t >= ARRAY_INT_TYPE && t <= ARRAY_BOOL_TYPE)
	yyerror ("mul ops cannot be used on array type");
      else if (t == CHAR_TYPE)
	yyerror ("mul ops cannot be used on character type");
      else if (t == BOOL_TYPE)
	yyerror ("mul ops cannot be used on boolean type");
      else
	{
	  $$.type_simple = t;
	  flag = true;
	}
    }

  /* Generating the 3addr code. */
  if (flag)
    {
      if($2 == AND_OP)
	{
	  backpatch ($1.truelist,$3.quad);
	  $$.truelist = $4.truelist;
	  $$.falselist = merge_list ($1.falselist,$4.falselist);
	}
      else
	{
	  $$.place = new_temp();
	  struct three_addr* addr = malloc (sizeof (struct three_addr)); //struct three_addr will have "char* addr and struct list_elem elems"
	  addr->lineno = next_quad;
	  addr->code = malloc (14 + strlen ($$.place) + strlen ($1.place) + strlen ($4.place));
	  switch($2)
	    {
	    case MOD_OP:   sprintf(addr->code,"%d:\t %s := %s %% %s",(int)next_quad,$$.place,$1.place,$4.place); break;
	    case INT_DIVIDE: 
	    case DIVIDE:   sprintf(addr->code,"%d:\t %s := %s / %s",(int)next_quad,$$.place,$1.place,$4.place); break;
	    case MULTIPLY: sprintf(addr->code,"%d:\t %s := %s * %s",(int)next_quad,$$.place,$1.place,$4.place); break;
	    default: break;
	    }
	  list_push_front (&code_list, &addr->elem);
	  next_quad++;

	  id_entry_t* ent = lookup_id_entry ($$.place, current_scope);
	  ent->id_type = $$.type_simple;
	}
    }
}

| term error factor {yyerror("Expected either * ,/,div,mod,and or a relational operator or a ,");} 

;


factor :
IDENTIFIER
{
  //printf ("Variable use is %s\n", $1);

  //printf ("Current scope is %s\n", current_scope->name);
  /* We will check current scope. If not, then we shall iteratively check all
     visible scopes. If it is declared in some other visible scope, then we will make
     an entry in our scope too. */
  id_entry_t* t;
  if (t = lookup_id_scopes ($1))
    {
      $$.type_simple = t->id_type; /* BEWARE: this could be any of the ARRAY types too. But that is checked elsewhere, not here. */
      if (t->scope_name != current_scope->name)
	hash_insert (current_scope->symbol_table, &t->sym_table_elem);

      /* Generating 3 addr code */
      $$.place = malloc (strlen ($1) + 1);
      strcpy($$.place, $1); 
    }
  else
    {
      yyerror ("undeclared identifier");
      $$.type_simple = NO_TYPE;
    }
  
  /* /\* This represents a function call. The function must be declared within the current scope. *\/ */
  /* func_entry_t* f; */
  /* if (f = lookup_func_scope ($1)) */
  /*   { */
  /*     /\* Now we need to do validity checks. *\/ */

  /*     /\*(1) checking number of arguments *\/ */
  /*     if (f->num_args != 0) */
  /* 	yyerror ("function call expects no arguments"); */

  /*     /\*(2) checking return type *\/ */
  /*     if (f->return_type == NO_TYPE)  */
  /* 	yyerror ("function doesn't return any value: illegal use of a procedure call"); */
  /*     else */
  /* 	$$ = f->return_type; /\* Return type is only one of the standard_type values. *\/ */
  /*   } */
  /* else */
  /*   yyerror ("undeclared function name"); */
}

| WRONG_IDENTIFIER { yyerror ("expected an identifier: valid identifier cannot begin with a numeral"); yynerrs++; YYERROR; }

| IDENTIFIER '(' actual_arguments_lst ')'
{
  /* This represents a function call. */
  bool flag = true;
  func_entry_t* f;
  if (f = lookup_func_scope ($1))
    {
      /* Now we need to do validity checks. */
      
      /*(1) checking number of arguments */
      if (f->num_args != $3.num_args)
	{
	  flag = false;
	  yyerror ("number of arguments mismatch in call to function");
	  printf ("expected %d arguments for function but received %d\n", f->num_args, $3.num_args);
	}
      /*(2) checking types of arguments */
      else
	{
	  int i;
	  for (i = 0; i < $3.num_args; i++)
	    {
	      if ($3.arg_types[i] != f->arg_types[i])
		{
		  yyerror ("conflicting types for actual argument(s) of function call");
		  flag = false;
		  break;
		}
	    }
	  free ($3.arg_types);
	}
      
      /*(3) checking return type */
      if (f->return_type == NO_TYPE) 
	{
	  yyerror ("function doesn't return any value: illegal use of a procedure call");
	  flag = false;
	}
    }
  else
    {
      flag = false;
      yyerror ("undeclared procedure/function name");
      $$.type_simple = NO_TYPE;
    }

  if (flag == true)
    {
      $$.type_simple = f->return_type;
      
      /* Generating 3addr code. */
      struct three_addr* addr = malloc (sizeof (struct three_addr)); 
      addr->lineno = next_quad;
      addr->code = malloc (17 + strlen ($1));
      sprintf(addr->code,"%d:\t call %s,%d",(int)next_quad, $1, f->num_args);
      list_push_front(&code_list, &addr->elem);
      next_quad++;
      $$.place = malloc (strlen ($1) + 1);
      strcpy($$.place,$1);
    }
}

| WRONG_IDENTIFIER '(' actual_arguments_lst ')' { yyerror ("expected an identifier: valid identifier cannot begin with a numeral"); yynerrs++; YYERROR; }

/* Parentheses mismatch errors. */
| IDENTIFIER error actual_arguments_lst ')' { yyerror ("expected ( before function invokation"); }
| IDENTIFIER error actual_arguments_lst ';' { yyerror ("expected (, ) between arguments to function"); }
| IDENTIFIER error actual_arguments_lst '\n' { yyerror ("expected (, ) between arguments to function"); }
| IDENTIFIER '(' actual_arguments_lst error ';' { yyerror ("expected ) after function invokation"); }
| IDENTIFIER '(' actual_arguments_lst error '\n' { yyerror ("expected ) after function invokation"); }

| INTNUM
{
  $$.type_simple = INT_TYPE;
  $$.place = malloc (10);
  sprintf ($$.place, "%d", $1);
}

| REALNUM
{
  $$.type_simple = REAL_TYPE;
  $$.place = malloc (10);
  sprintf ($$.place, "%f", $1);
}

| NOT factor
{ /* Bitwise NOT operation. */
  if ($2.type_simple != INT_TYPE)
    {
      yyerror ("wrong type of argument to bitwise NOT operator");
      $$.type_simple = INT_TYPE;
      $$.truelist = $2.falselist;
      $$.falselist = $2.truelist;
    }
  else
    $$.type_simple = INT_TYPE;
}

| '(' expression ')'
{
  $$.type_simple = $2.type_simple;
  $$.truelist = $2.truelist;
  $$.falselist = $2.falselist;
}

/* Parentheses mismatch errors. */
| '(' expression error {yyerror("Expected ) after the expression");}

| error expression ')' {yyerror("Expected ( before the expression");}

| error expression {yyerror("Unexpected token before the expression");}

  /* Error in the starting term. */
//| error  { yyerror ("expected an identifier or numeral or function call or bracketed expression or a negated expression"); }


;


M1: /* New non-terminal! */
{
  //printf ("Reducing M\n");
  $$.quad = next_quad;
}
;
//N1: /* New non-terminal! */
//{
//}

sign : 
ADDOP 
{ 
  if ($1 == OR_OP) 
    {
      yyerror ("Expected either unary + or - before term"); yynerrs++;YYERROR; 
      $$ = malloc (1);
      *$$ = '\0';
    }
  else
    {
      $$ = malloc (2);
      if ($1 == PLUS)
	strcpy ($$, "+");
      else
	strcpy ($$, "-");
    }
}
//| error {yyerror("Expected either unary + or - before term");}

%%

#include "lex.yy.c"

void yyerror (const char* s)
{
  fprintf (stderr, "%s:%d: error:", file_name == NULL? "stdin" : file_name, yylineno, yytext);
  fprintf (stderr, "%s\n", s);
}

void print_warning (const char* s)
{
  fprintf (stderr, "%s:%d: warning:", file_name == NULL? "stdin" : file_name, yylineno, yytext);
  fprintf (stderr, "%s\n", s);
}


int yywrap (void)
{
  return 1;
}



/********* FUNCTIONS FOR SEMANTIC ACTIONS **********/

/* Initializes the global scope. */
void init_global_scope (char* iden)
{
  current_scope = malloc (sizeof (func_entry_t));
  current_scope->name = malloc (strlen (iden) + 1);
  strcpy (current_scope->name, iden);
  current_scope->return_type = NO_TYPE;
  current_scope->scope = 0;
  current_scope->symbol_table = malloc (sizeof (struct hash));
  hash_init (current_scope->symbol_table, symtable_hashpjw, symtable_less, (void*) NULL);
  current_scope->parent_scope = NULL;
  current_scope->num_childscopes = 0;
  current_scope->child_scopes = NULL;
}

/* Makes a entry of the current scope in the function table. */
void make_scope_entry (func_entry_t* scope)
{
  hash_insert (&func_table, &scope->func_table_elem);
}


/* Called whenever a variable declaration is seen. So if the variable is not already in the 
   current scope's symbol table, then it is added to the "id_arr" list of identifiers 
   (waiting to be assigned types). */
void make_idarray_entry (char* iden)
{
  if (!lookup_id_entry (iden, current_scope))
    {
      char* temp = malloc (strlen (iden) + 1);
      strcpy (temp, iden);
      id_arr[id_arr_size++] = temp;
    } //make_idarray_entry ($3.iden);
  else
    yyerror ("redeclaration of variable: same identifier cannot be used twice in the same scope");
}

/* Returns TRUE if iden is declared in any of the previous visible scopes. This is NOT called
   during variable declaration, but during the access of a variable. */
id_entry_t* lookup_id_scopes (char* iden)
{
  func_entry_t* f = current_scope;
  id_entry_t* t;
  
  do
    {
      t = lookup_id_entry (iden, f);
      if (t == NULL)
	f = f->parent_scope;
      else
	break;
    } while (f != NULL);

  return t;
}

/* Returns TRUE if iden is already declared as a variable in the CURRENT scope, else FALSE. */
id_entry_t* lookup_id_entry (char* iden, func_entry_t* scope)
{
  id_entry_t id;
  id.id_name = iden;
  struct hash_elem* e;
  
  e = hash_find (scope->symbol_table, &id.sym_table_elem);

  return e == NULL? NULL : hash_entry (e, id_entry_t, sym_table_elem);
}


/* Returns TRUE if iden represents a function that IS WITHIN the scope of current 
   scope (THAT IS VISIBLE FROM THE CURRENT SCOPE). */
func_entry_t* lookup_func_scope (char* iden)
{
  func_entry_t* func = lookup_func_entry (iden);
  func_entry_t* temp = current_scope; /* We start looking from current scope. */
  
  if (func == NULL)
    temp = NULL;
  else
    {
      /* FOR NOW WE SAY THAT ONLY SUCCESSIVE PARENTS AND CHILDREN ARE VISIBLE (NO AUNTS OR UNCLES). */
      if (func->scope < current_scope->scope)
	{
	  do
	    {
	      if (func == temp)
		break;
	      temp = temp->parent_scope;
	    } while (temp != NULL);
	}
      else if (func->scope == current_scope->scope)
	{
	  if (func->parent_scope != current_scope->parent_scope)
	    temp = NULL;
	}
      else
	{
	  int num = temp->num_childscopes;
	  int i;
	  for (i = 0; i < num; i++)
	    {
	      if ((temp->child_scopes)[i] == func)
		{
		  temp = (temp->child_scopes)[i];
		  break;
		}
	    }
	  if (i == num)
	    temp = NULL;
	}
    }
  return temp;
}

/* Returns TRUE if iden is already declared as a function, else FALSE. 
   This is used whenever a function/procedure declaration is seen. 
   NO TWO FUNCTION/PROCEDURE NAMES ARE ALLOWED TO CLASH ANYWHERE IN THE PROGRAM. */
func_entry_t* lookup_func_entry (char* iden)
{
  func_entry_t func;
  func.name = iden;
  struct hash_elem* e;
  
  e = hash_find (&func_table, &func.func_table_elem);

  return e == NULL? NULL : hash_entry (e, func_entry_t, func_table_elem);
}


/* This one creates a child scope and assigns it to current scope. */
void switch_to_newscope (char* iden)
{
  func_entry_t* func = malloc (sizeof (func_entry_t));
  func->name = malloc (strlen (iden) + 1);
  strcpy (func->name, iden);
  func->scope = current_scope->scope + 1;
  func->symbol_table = malloc (sizeof (struct hash));
  hash_init (func->symbol_table, symtable_hashpjw, symtable_less, (void*) NULL);
  func->parent_scope = current_scope;
  current_scope->num_childscopes += 1;
  current_scope->child_scopes = realloc (current_scope->child_scopes, (current_scope->num_childscopes) * sizeof (func_entry_t*));
  (current_scope->child_scopes)[current_scope->num_childscopes - 1] = func;
  func->num_args = 0;
  func->arg_types = NULL;
  func->return_type = NO_TYPE;
  current_scope = func;
}


/* Called when type of a list of variables becomes known. So it assigns the types and updates symbol table. */
void idarr_assign_simple_types (enum type id_type)
{
  id_entry_t* temp;
  int i;
  for (i = 0; i < id_arr_size; i++)
    {
      temp = malloc (sizeof (id_entry_t));
      temp->id_name = id_arr[i];
      temp->scope_name = current_scope->name;
      temp->offset = offset++; //incrementing offset (global var)
      temp->id_type = id_type;

      /* If it is global scope, then allocate space for variables. */
      if (current_scope->scope == 0)
	{
	  switch (id_type)
	    {
	    case INT_TYPE:
	      temp->mem_loc.i = malloc (sizeof (int));
	      break;
	    case REAL_TYPE:
	      temp->mem_loc.f = malloc (sizeof (float));
	      break;
	    case CHAR_TYPE:
	      temp->mem_loc.c = malloc (sizeof (char));
	      break;
	    case BOOL_TYPE:
	      temp->mem_loc.b = malloc (sizeof (bool));
	      break;
	    }
	}
      
      /* Now that an id entry is initialized, make the entry in the symbol table. */
      hash_insert (current_scope->symbol_table, &temp->sym_table_elem);
    }
}

void idarr_assign_array_types (enum type id_type, int lower_bound, int upper_bound)
{
  id_entry_t* temp;
  int i;
  for (i = 0; i < id_arr_size; i++)
    {
      temp = malloc (sizeof (id_entry_t));
      temp->id_name = id_arr[i];
      temp->scope_name = current_scope->name;
      temp->id_type = id_type;
      temp->offset = offset++; //incrementing offset (global var)
      temp->mem_loc.arr.lower_bound = lower_bound;
      temp->mem_loc.arr.upper_bound = upper_bound;
      
      /* If it is global scope, then allocate space for variables. */
      int* int_ptr;
      float* fl_ptr;
      char* ch_ptr;
      bool*  bl_ptr;
      if (current_scope->scope == 0)
	{
	  switch (id_type)
	    {
	    case ARRAY_INT_TYPE:
	      int_ptr = ((int*)malloc ((temp->mem_loc.arr.upper_bound - temp->mem_loc.arr.lower_bound) * sizeof (int)));
	      temp->mem_loc.arr.ptr_val.iptr = &(int_ptr);
              break;
	    case ARRAY_REAL_TYPE:
	      fl_ptr = ((float*)malloc ((temp->mem_loc.arr.upper_bound - temp->mem_loc.arr.lower_bound) * sizeof (int)));
	      temp->mem_loc.arr.ptr_val.fptr = &(fl_ptr);
              break;
	    case ARRAY_CHAR_TYPE:
	      ch_ptr = ((char*)malloc ((temp->mem_loc.arr.upper_bound - temp->mem_loc.arr.lower_bound) * sizeof (int)));
	      temp->mem_loc.arr.ptr_val.cptr = &(ch_ptr);
              break;
	    case ARRAY_BOOL_TYPE:
	      bl_ptr = ((bool*)malloc ((temp->mem_loc.arr.upper_bound - temp->mem_loc.arr.lower_bound) * sizeof (int)));
	      temp->mem_loc.arr.ptr_val.bptr = &(bl_ptr);
              break;
	    }
	}
      
      /* Now that an id entry is initialized, make the entry in the symbol table. */
      hash_insert (current_scope->symbol_table, &temp->sym_table_elem);
    }
}

/* Function that assigns the type to the list of identifiers that have been seen so far. */
void idarr_assign_types (enum type enumtype, int lower_bound, int upper_bound)
{
  switch (enumtype)
    {
    case INT_TYPE:
    case REAL_TYPE:
    case CHAR_TYPE:
    case BOOL_TYPE:
      idarr_assign_simple_types (enumtype);
      id_arr_size = 0;
      break;
      
    case ARRAY_INT_TYPE:
    case ARRAY_REAL_TYPE:
    case ARRAY_CHAR_TYPE:
    case ARRAY_BOOL_TYPE:
      idarr_assign_array_types (enumtype, lower_bound, upper_bound);
      id_arr_size = 0;
      break;

    default:
      break;
    }
}


char* new_temp (void)
{
  static int count = 1;
  char* t = malloc (10);
  sprintf (t, "t_%d", count++);
  t = realloc (t, strlen (t));

  /* Installing new temp in symbol table. */
  id_entry_t* ent = malloc (sizeof (id_entry_t));
  ent->id_name = t;
  ent->scope_name = current_scope->name;
  ent->id_type = NO_TYPE;
  ent->offset = offset++;
  printf ("This scope = %s, symbol = %s\n", current_scope->name, t);
  hash_insert (current_scope->symbol_table, &ent->sym_table_elem);  
  return t;
}

lst_t* make_list(int num)
{
  lst_t* l = malloc (sizeof (lst_t));
  l->length = 1;
  l->lst = malloc (sizeof (int));
  l->lst[0] = num;
  return l;
}

lst_t* merge_list(lst_t* t1,lst_t* t2)
{
  int len1 = (t1 == NULL? 0 : t1->length);
  int len2 = (t2 == NULL? 0 : t2->length);
  int new_len = len1 + len2;
  int* new_arr = (int*)malloc(new_len*(sizeof(int)));
  int i,j;

  for(i=0;i<len1;i++)
    new_arr[i]= t1->lst[i];

  for(j=0;j<len2;j++)
    new_arr[i+j] = t2->lst[j];

  lst_t* new_lst = (lst_t*) malloc(sizeof(lst_t));
  new_lst->lst = new_arr;
  new_lst->length = new_len;

  if (t1 != NULL)
    free(t1->lst);
  if (t2 != NULL)
    free(t2->lst);
  free(t1);
  free(t2);

  return new_lst;
}


void backpatch(lst_t* l, int num)
{
  int i;
  //printf("the number is %d\n",num);
  //printf("this is %x",(int*)l);
  int len = (l == NULL)? 0 : l->length;
  for(i = 0; i < len; i++)
    {
      int ln_no = l->lst[i];
      //printf ("the line number is %d\n",ln_no);
      struct list_elem* e;
      struct three_addr* t;

      //printf("i came into backpatch\n");

      for (e = list_begin (&code_list); e != list_end (&code_list); e = list_next (e))
	{
	  t = list_entry (e, struct three_addr, elem);
	  if (t->lineno == ln_no)
	    {
	      char temp[10];
              sprintf(temp,"%d",num);
	      int len = strlen (t->code);
	      t->code = realloc (t->code, len + strlen (temp) + 1);
              strcat(t->code,temp);
	    }
	}
    }
}


bool lineno_less (const struct list_elem* a, const struct list_elem* b, void* aux)
{
  struct three_addr* s1 = list_entry (a, struct three_addr, elem);
  struct three_addr* s2 = list_entry (b, struct three_addr, elem);

  return (s1->lineno < s2->lineno);    
}


/***************************************************/

int main(int argc,char* argv[])
{
  int token;
  
  if(argc == 1)
    {
      yyin = stdin;
      file_name = NULL;
    }

  else
    {
      yyin=fopen(argv[1],"r");

      if (yyin == NULL)
	return -1;
      
      file_name = argv[1];
    }
  //yydebug = 1;

  /* Initializing tables. */
  hash_init (&func_table, functable_hashpjw, functable_less, (void*) NULL);

  /* Initializing global code list. */
  list_init (&code_list);
  
  if(yyparse() == 0)
{
    printf ("Parsing done.\n");
    printf("#include<stdio.h>\n#include<stdlib.h>\n#include<string.h>\n");
    printf("struct data_stack\n");
    printf("{\nint val;\nfloat fl;\n};\n");
    printf("typedef struct data_stack data_st;\n");
    printf("int main()\n");							 
    printf("{\ndata_st arr[1001];\n"); 
    AddCode();
}
  else
    printf ("Unrecoverable syntax error in line no %d.\n", yylineno);
  //printf ("No of syntax errors = %d.\n", yynerrs);
  /* while(token = yylex()) */
  /*   { */
  /*     printf("Token Read %d - %s\n", token, yytext); */
  /*   } */
  
  fclose (yyin);

  list_sort((&code_list),lineno_less,NULL);

  FILE* fout = fopen ("imcode.tmp","w");
  
  struct list_elem* e;
  struct three_addr* t;
  
  for (e = list_begin (&code_list); e != list_end (&code_list); e = list_next (e))
    {
      t = list_entry (e, struct three_addr, elem);
      fprintf (fout, "%s\n", t->code);
    }
  return 0;
}

int lookup(char str[])
{
  int i;
  for(i=0;i<20;i++)
    {
      if(strcmp(ret_offset[i].name,str)==0)
	{
	  return ret_offset[i].offset;
	}
    }
}

void add_return(char ret[])
{
  int temp=1000-return_offset;
  strcpy(ret_offset[temp].name,ret);
  ret_offset[temp].offset=return_offset;
  return_offset--;
}

char* getLabel(char * str,int b)
{
  char *ret;
  int len=strlen(str);
  ret=(char*)malloc(len);
  int i;
  for(i=0;i<len-1;i++)
    ret[i]=str[i];
  ret[i-1]='\0'; //ignoring the ':' character
  if(b==1)
    add_return(ret);
  return ret;
}

int codeGen(char* str)
{
  int i=0;
  int j=0;
  int z;
  char tac[50][50];
  char *pch;
  pch=(char*)malloc(50);
  pch = strtok (str," ");
  while (pch != NULL)
    {
      strcpy(tac[i++],pch);
      pch = strtok (NULL, " ,\n");
    }
  //  for(j;j<i;j++)
  //    printf("%s\n",tac[j]);
  if(i==1 && strcmp(tac[0],"\n")!=0)
    {
      //switch_to_newscope(getLabel(tac[0]));
      char* temp;
      temp=getLabel(tac[0],1);
      current_scope = lookup_func_entry (temp); //switch to existing scope
      printf("%s:\n",temp);
      return 0;
      //      printf ("Now current scope name is %s\n", temp);
    }
  else
    {
      if(strcmp(tac[0],"\n")!=0 && strcmp(tac[1],"param")!=0)
	printf("_%s  ",tac[0]);
    }
  if(strcmp(tac[0],"\n")==0)
    {
      return 0;
    }
  else if(strcmp(tac[1],"if")==0)
    {
      id_entry_t* t=lookup_id_scopes(tac[2]);
      if(isdigit(tac[4][0]))
	{
	  printf("if(arr[%d]%s%s) goto _%s;\n",t->offset,tac[3],tac[4],tac[6]);
	}
      id_entry_t* t2=lookup_id_scopes(tac[4]);
      if(t2!=NULL)
	printf("if(arr[%d]%sarr[%d]) goto _%s;\n",t->offset,tac[3],t2->offset,tac[6]);
      if(t2==NULL)
	printf("if(arr[%d]%sarr[%d]) goto _%s;\n",t->offset,tac[3],lookup(tac[3]),tac[6]);      
    }
  else if(strcmp(tac[1],"return")==0)
    {
      //      printf("%d",get_return_address(current_scope->name));
      printf("goto _%d;\n",ret_address+1);
    }
  else if(strcmp(tac[1],"halt")==0)
    {
      printf("return 0;\n}\n");
    }
  else if(strcmp(tac[2],":=")==0 && i==4)
    {
      //      printf("Current Scope is %s\n",current_scope->name);
      //printf("Search for ID %s ",tac[1]);
      //printf("Assignmnet Op\n");
      id_entry_t* t=lookup_id_scopes(tac[1]);
      if(t==NULL)
	printf("arr[%d]=%s;\n",lookup(tac[1]),tac[3]);
      //printf("Id Offset is %d\n",t->offset);
      if(isdigit(tac[3][0]))
	{
	  //printf("right is a num\n");
	  printf("arr[%d]=%s;\n",t->offset,tac[3]);
	}
      else if(t!=NULL)
	{
	  id_entry_t* t2=lookup_id_scopes(tac[3]);
	  if(t2!=NULL)
	    printf("arr[%d]=arr[%d];\n",t->offset,t2->offset);
	  if(t2==NULL)
	    printf("arr[%d]=arr[%d];\n",t->offset,lookup(tac[3]));
	}
    }
  else if(strcmp(tac[2],":=")==0 && i==6)
    {
      //      printf("Current Scope is %s\n",current_scope->name);
      //      printf("Search for ID %s ",tac[1]);
      //      printf("Assignmnet Op\n");
      id_entry_t* t1=lookup_id_scopes(tac[1]);
      if(isdigit(tac[3][0]) & isdigit(tac[5][0]))
	printf("arr[%d]=%s%s%s;\n",t1->offset,tac[3],tac[4],tac[5]);
      if(isdigit(tac[3][0]) & !isdigit(tac[5][0]))
	{
	  id_entry_t* t2=lookup_id_scopes(tac[5]);
	  printf("arr[%d]=%s%sarr[%d];\n",t1->offset,tac[3],tac[4],t2->offset);
	}
      if(!isdigit(tac[3][0]) & isdigit(tac[5][0]))
	{
	  id_entry_t* t2=lookup_id_scopes(tac[3]);
	  printf("arr[%d]=arr[%d]%s%s;\n",t1->offset,t2->offset,tac[4],tac[5]);
	}
      if(!isdigit(tac[3][0]) & !isdigit(tac[5][0]))
	{
	  id_entry_t* t2=lookup_id_scopes(tac[3]);
	  id_entry_t* t3=lookup_id_scopes(tac[5]);
	  printf("arr[%d]=arr[%d]%sarr[%d];\n",t1->offset,t2->offset,tac[4],t3->offset);
	}
      //      printf("Id Offset is %d\n",t->offset);
      //      printf("Assignment with binary ops\n");
    }
  else if(strcmp(tac[1],"call")==0)
    {
      printf("goto %s;\n",tac[2]);
      char* temp;
      temp=getLabel(tac[0],0);
      ret_address=atoi(temp);
      //      printf("Return address modified here\n");
    }
  else if(strcmp(tac[1],"param")==0)
    {
      //Include parameters to be added
    }
  else if(strcmp(tac[1],"goto")==0)
    {
      printf("goto _%s;\n",tac[2]);
    }
  return 0;
}
void AddCode()
{
  FILE *infile;
  infile=fopen("imcode.tmp","r");
  char* str;
  int i=0;
  str=(char*) malloc(50);
  char tac[50];
  while( fgets(str, 50, infile) != NULL ) 
    {
      codeGen(str);
    }
}

