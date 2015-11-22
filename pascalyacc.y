%{
  #include <iostream>
  #include <fstream>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <string>
  #include <stack>
  #include "y.tab.h"
  #include "hashtable.h"
  #include <string>

  using std::cout;
  int line_num = 1;
  void yyerror(const char*);
  void semanticerror(const char*);
  void undeclarederror(const char *identifier);
  int yylex();

  int* Merge(int* ,int* );
  void Backpatch(int*,int);
  void Gen();
  int* Makelist(int);
  char* Newtemp();
  string inttostr(int num);
  void enterThreeAddr(int index, string opcode, string result = "\0", string arg1 = "\0", string arg2 = "\0");
  void codegeneration();
  string getCcode(vector<string> &v, int, int &);
  
    
  //  adj_list hashtable;
  list<node>::iterator it;
  list<node>::iterator nodeit;
  list<string> lst_identifiers;
  
  arrnode a;
  stack<symbol_table *> tblptr;       // this is the stack for symbol tables

  #define FILE_NAME_LENGTH 50
  char filename[FILE_NAME_LENGTH];
  
  #define START 100
  int nextquad = START;
  
  char code[50][60];
  vector< vector<string> > threeaddr(50, vector<string>(5, "\0"));
  vector<bool> labelFlag(nextquad - START + 1, false);

  int mycount;
  bool funcStart = false;
  int functionBaseAddr = 0;
  int functionReturn;
  bool error = false;

%}


%union
 {
   char type[20];
   double dval;
   int ival;
   char id[20];
   char exprtype[100];
   struct
   {
     int* true_list;
     int* false_list;
     int* next;
     int quad;
     char place[5];
     char type[20];
   }eval;
   char symbol[4];
   struct 
   {
     char type[20];
     int width;         // width for integer = 4, width for real = 4 
   }typeinfo;
 }

%token KEYWORD ASSIGNOP PUNCTUATION NOT DOUBLEQUOTE
%token IF WHILE DO THEN ELSE FUNCTION PROGRAM BEGIN1 END1 VAR PROCEDURE ARRAY OF

%token <ival> DIGITS
%token <dval> NUM
%token <id> ID
%token <type> INTEGER REAL
%token <symbol> ADDOP MULOP RELOP

%type <eval> expression simple_expression term statement factor sign compound_statement 
%type <eval> statement_list M1 N1 variable optional_statements procedure_statement subprogram_head
 //%type <eval> expression factor term simple_expression variable procedure_statement
%type <typeinfo> type standard_type
%type <exprtype> expression_list parameter_list 

%type <id> N

%%
program : M ID '(' identifier_list ')' ';'
          declarations
          subprogram_declarations T
          compound_statement TT
          '.'
{
  int i;
  Backpatch($10.next, nextquad);
  /*  for(i = START; i < nextquad; i++)
    printf("%s\n", code[i-START]);
  printf("%d\t%s\n", nextquad, "halt"); 
  */
  enterThreeAddr(nextquad - START, "halt");
  
  cout << "\n-------Structured 3 Address code-------\n";
  for(i = START; i <= nextquad; i++){
    cout << threeaddr[i - START][0] << '\t';
    cout << threeaddr[i - START][1] << '\t';
    cout << threeaddr[i - START][2] << '\t';
    cout << threeaddr[i - START][3] << '\t';
    cout << threeaddr[i - START][4] << '\t';
    cout << '\n';
  }
  //  printf("%d\n", nextquad);
}
;

M :PROGRAM
{
  symbol_table * t = mktable(NULL, "main");
  tblptr.push(t);
}
;

/*code for printing main hashtable*/
T :
{
  //sprintf(code[nextquad-START], "program");

  funcStart = true;
  tblptr.top()->label = nextquad;
  /*
  cout<<tblptr.top()->name<<endl;
  cout<<tblptr.top()->rettype<<endl;
  cout << tblptr.top()->argtypes << endl;
  cout << tblptr.top()->width;
  cout<<endl;
  print_hash_table(tblptr.top()->hashtable); */
}
;
/*end of code*/

TT :
{
  /*  cout<<tblptr.top()->name<<endl;
  cout<<tblptr.top()->rettype<<endl;
  cout << tblptr.top()->argtypes << endl;
  cout << tblptr.top()->width;
  cout<<endl;
  print_hash_table(tblptr.top()->hashtable); */
}
;

identifier_list : ID  
{ if( find(lst_identifiers.begin(), lst_identifiers.end(), $1) != lst_identifiers.end() )
	  semanticerror("redeclaration");
     else
	  lst_identifiers.push_back($1); 
}
| identifier_list ',' ID 
{ if( find(lst_identifiers.begin(), lst_identifiers.end(), $3) != lst_identifiers.end() )
	  semanticerror("redeclaration");
     else
	  lst_identifiers.push_back($3);
}
;

declarations : declarations VAR identifier_list ':' type ';'  
{ int num_ident = 0;
  if(!strcmp($5.type, "array"))
    {
      tr(lst_identifiers, it)
	{
	  nodeit = look_up(*it, tblptr.top()->hashtable);
	  if(nodeit->type == "\0"){
	    num_ident++;
	    insert_arr_type(*it, tblptr.top()->hashtable, $5.type, a, tblptr.top()->width);
	    tblptr.top()->width += $5.width;
	  }
	  else
	    semanticerror("redeclaration");
	}
    }
  else
    {
      tr(lst_identifiers, it)
	{
	  nodeit = look_up(*it, tblptr.top()->hashtable);
	  if(nodeit->type == "\0"){
	    insert_type(*it, tblptr.top()->hashtable, $5.type, tblptr.top()->width );
	    tblptr.top()->width += $5.width;
	  }
	  else
	    semanticerror("redeclaration"); 
	}
    }
  lst_identifiers.resize(0);
}
|
;

type : standard_type 
{ 
  strcpy($$.type, $1.type); 
  $$.width = 4;
}
| ARRAY '[' DIGITS DOUBLEQUOTE DIGITS ']' OF standard_type
  { a.insert_info($8.type, $3, $5);
    strcpy($$.type, "array");
    $$.width = ($5 - $3) * $8.width;
  }
; 

standard_type : INTEGER 
{
  strcpy($$.type, $1); 
  $$.width = 4;
} 
| REAL { strcpy($$.type, $1); $$.width = 4;}
;

subprogram_declarations : subprogram_declarations subprogram_declaration ';'
|
;

subprogram_declaration : subprogram_head declarations compound_statement
{
  symbol_table *t = tblptr.top();
  
  /* code for printing symboltable */
  /*cout << tblptr.top() -> name << endl;
  cout << tblptr.top() -> rettype << endl;
  cout << tblptr.top() -> width << endl;
  cout << tblptr.top()->argtypes;
  cout<<endl;
  print_hash_table(tblptr.top()->hashtable); */
  /*end of code*/

  funcStart = false;
  
  sprintf(code[nextquad - START], "%d\t%s", nextquad, "return");
  enterThreeAddr(nextquad - START, "return");     // Entering 3 address code  
  Gen();

  tblptr.pop();
  enterproc(tblptr.top(), t->name, t);
}
;

/* semantic rules to install type information of arguments and return type in this symmbol table */
subprogram_head : FUNCTION N arguments ':' standard_type ';'
{
  //sprintf(code[nextquad-START],"%s", $2);

  tblptr.top()->rettype = $5.type;
  symbol_table *prev = tblptr.top()->previous;

  insert_type(tblptr.top()->name, prev->hashtable, $5.type, prev->width);  
  insert_type(tblptr.top()->name, tblptr.top()->hashtable, $5.type, 0);
  prev->width += $5.width;
  
}
| PROCEDURE N arguments ';' 
{
  //sprintf(code[nextquad-START],"%s", $2);

  tblptr.top()->rettype = "";
  symbol_table *prev = tblptr.top()->previous;
  insert_type(tblptr.top()->name, prev->hashtable, "", 0);  
  insert_type(tblptr.top()->name, tblptr.top()->hashtable, "", 0);
}
; 

N : ID
{
  strcpy($$, $1);

  funcStart = true;
  //  putLabel();
  symbol_table *t = mktable(tblptr.top(), $1);
  tblptr.push(t);
  t->label = nextquad;
  copy_parent_data( tblptr.top() );
}
;

arguments : '(' parameter_list ')'
{
  tblptr.top()->argtypes = $2;
}
|
;

parameter_list : identifier_list ':' type
{ if(!strcmp($3.type, "array"))
    {
      tr(lst_identifiers, it)
	{
	  nodeit = look_up(*it, tblptr.top()->hashtable);
	  if(nodeit->type == "\0"){
	    insert_arr_type(*it, tblptr.top()->hashtable, $3.type, a, tblptr.top()->width);
	    tblptr.top()->width += $3.width;
	  }
	  else
	    semanticerror("redeclaration");
	}
    }
  else
    {
      tr(lst_identifiers, it)
	{
	  nodeit = look_up(*it, tblptr.top()->hashtable);
	  if(nodeit->type == "\0"){
	    insert_type(*it, tblptr.top()->hashtable, $3.type, tblptr.top()->width);
	    tblptr.top()->width += $3.width;
	  }
	  else
	    semanticerror("redeclaration"); 
	}
    }
  int i;
  strcpy( $$, "" );
  for( i = 0; i < lst_identifiers.size(); i++ ){
    strcat( $$, $3.type );
    strcat( $$, " " );
  }
  lst_identifiers.resize(0);
}
| parameter_list ';' identifier_list ':' type
{ if(!strcmp($5.type, "array"))
    {
      tr(lst_identifiers, it)
	{
	  nodeit = look_up(*it, tblptr.top()->hashtable);
	  if(nodeit->type == "\0"){
	    insert_arr_type(*it, tblptr.top()->hashtable, $5.type, a, tblptr.top()->width);
	    tblptr.top()->width += $5.width;
	  }
	  else
	    semanticerror("redeclaration");
	}
    }
  else
    {
      tr(lst_identifiers, it)
	{
	  nodeit = look_up(*it, tblptr.top()->hashtable);
	  if(nodeit->type == "\0"){
	    insert_type(*it, tblptr.top()->hashtable, $5.type, tblptr.top()->width );
	    tblptr.top()->width += $5.width;
	  }
	  else
	    semanticerror("redeclaration"); 
	}
    }
  int i;

  for( i = 0; i < lst_identifiers.size(); i++ ){
    strcat( $1, $5.type );
    strcat( $1, " " );
  }
  strcpy( $$, $1 );
  lst_identifiers.resize(0);
}
;

compound_statement : BEGIN1
optional_statements
END1
{
  $$.next = (int*)malloc(sizeof(int)*15);
  $$.next = $2.next;
}
;

optional_statements : statement_list
{
  $$.next=(int*)malloc(sizeof(int)*15);$$.next=$1.next;
}
|
{
  $$.next=(int*)malloc(sizeof(int)*15);
}
;

statement_list : statement
{
  $$.next = (int*)malloc(sizeof(int)*15);
  $$.next = $1.next;
}
| statement_list M1 ';' statement
{
  $$.next = (int*)malloc(sizeof(int)*15);

  Backpatch($1.next, $2.quad);
  $$.next = $4.next;
  //  Gen();
}
;

M1: 
{
  $$.quad = nextquad;
} 
;

statement : variable ASSIGNOP expression
{
  if(strcmp($1.type, $3.type) != 0 && strcmp($1.type, "default") != 0)
    //semanticerror("type mismatch");
    ;
  

  /*  printf("variable : %s\texpression : %s\n", $1.place ,$3.place);
  printf("index : %d\n", nextquad-START);
  */
  $$.next = (int*)malloc(sizeof(int)*15);
  $$.next[0] = 0;
  if(funcStart){
    sprintf(code[nextquad-START],
	  "*%d\t%s = %s", nextquad, $1.place, $3.place);

    enterThreeAddr(nextquad - START, "=", $1.place, $3.place);  // Enter 3 address code   
    funcStart = false;
  }
  else{
    sprintf(code[nextquad-START],
	    "%d\t%s = %s", nextquad, $1.place, $3.place);
    enterThreeAddr(nextquad - START, "=", $1.place, $3.place);
  }

  Gen();
  /*int i;
  cout << "current status :\n";
  for(i = START; i < nextquad; i++)
    printf("%s\n", code[i-START]);
    cout << nextquad << '\n'; */
}
| procedure_statement 
{
  $$.next = (int*)malloc(sizeof(int)*15);
}
| compound_statement
{
  $$.next = (int*)malloc(sizeof(int)*15);
  $$.next = $1.next;
}
| IF expression THEN M1 statement N1 ELSE M1 statement
{
  if(strcmp($2.type, "boolean") != 0)
    semanticerror("boolean expression required");

  $$.next = (int*)malloc(sizeof(int)*15);
  Backpatch($2.true_list, $4.quad);
  Backpatch($2.false_list, $8.quad);

  $$.next = Merge($9.next, $6.next);
  $$.next = Merge($$.next, $5.next);
  
  //Backpatch($$.next, nextquad);
}
| WHILE M1 expression DO M1 statement
{
  if(strcmp($3.type, "boolean") != 0)
    semanticerror("boolean expression required");

  Backpatch($6.next, $2.quad);
  Backpatch($3.true_list, $5.quad);
  $$.next = $3.false_list;
  
  //Backpatch($$.next, nextquad);
  if(funcStart){
    sprintf(code[nextquad-START],
	    "*%d\tgoto %d", nextquad, $2.quad);
    enterThreeAddr(nextquad - START, "goto", inttostr($2.quad - START));
    funcStart = false;
  }
  else{
    sprintf(code[nextquad-START],
	    "%d\tgoto %d", nextquad, $2.quad);
    enterThreeAddr(nextquad - START, "goto", inttostr($2.quad - START));
  }

  Gen();
}
;

N1: 
{
  $$.next = Makelist(nextquad);

  if(funcStart){
    sprintf(code[nextquad-START], "*%d\tgoto ", nextquad);
    enterThreeAddr(nextquad - START, "goto");
    funcStart = false;
  }
  else{
    sprintf(code[nextquad-START], "%d\tgoto ", nextquad);
    enterThreeAddr(nextquad - START, "goto");
  }

  Gen();
}  
;

variable : ID
{ string s = look_up_type($1, tblptr.top()->hashtable);
  if(s != "\0"){
    it = look_up($1, tblptr.top()->hashtable);
    strcpy($$.type, s.c_str());
    if(it->type == "array")
      semanticerror("incompatible types in assignment");
  }
  else{
    undeclarederror($1);
    insert_type($1, tblptr.top()->hashtable, "default", -1);
    strcpy($$.type, "default");
  }

  //  printf("variable : %s\n", $1);
  strcpy($$.place, $1);
}
| ID '[' DIGITS ']'
{ string s = look_up_type($1, tblptr.top()->hashtable);
  if(s == "array"){
    it = look_up($1, tblptr.top()->hashtable);
    int lb = it->is_array->lower_bound;
    int ub = it->is_array->upper_bound;
    strcpy($$.type, (it->is_array->type).c_str());
    if($3 < lb || $3 > ub)
      semanticerror("constant out of range");
  }
  else{
    strcpy($$.type, "default");
    semanticerror("subscripted object is not an array");
  }

  char buffer[1][10];
  sprintf(buffer[0],"%d",$3);
  strcat($1,"[");
  strcat($1,buffer[0]);
  strcat($1,"]");
  strcpy($$.place,$1);
}
;

/* Writing rules for checking number of parameter are equal for function calls */
procedure_statement : ID
{
  it = look_up($1, tblptr.top()->hashtable);
  if(it -> is_procedure == NULL)
    semanticerror("expression used as a statement");
  else{
    if( ((symbol_table *)it->is_procedure)->argtypes != "")
      semanticerror("missing arguments in procedure call");
    strcpy($$.type, ((symbol_table *)(it->is_procedure))->rettype.c_str());
  }

  if(funcStart){
    sprintf(code[nextquad-START],
	    "*%d\tcall %s,0", nextquad, $1);
    enterThreeAddr(nextquad - START, "call", $1, "0");
    funcStart = false;
  }
  else{
    sprintf(code[nextquad-START],
	    "%d\tcall %s,0", nextquad, $1);
    enterThreeAddr(nextquad - START, "call", $1, "0");
  }

  Gen();
}
| ID '(' expression_list ')'
{
  it = look_up($1, tblptr.top()->hashtable);
  if(it->type == "\0" || it -> is_procedure == NULL)
    semanticerror("called object is not a procedure or statement");
  else{
    string argtypes = ((symbol_table *)it->is_procedure)->argtypes;
    string rettype = ((symbol_table *)it->is_procedure)->rettype;
    
    if( strcmp( $3, argtypes.c_str() ) != 0)
      {
	semanticerror("Number of elements passed in the function are not same or there is a type mismatch");
      }
    strcpy($$.type, rettype.c_str());
  }

  if(funcStart){
    sprintf(code[nextquad-START],
	  "*%d\tcall %s,%d", nextquad, $1, mycount);
    
    enterThreeAddr(nextquad - START, "call", $1, inttostr(mycount)); 
    funcStart = false;
  }
  else{
    sprintf(code[nextquad-START],
	  "%d\tcall %s,%d", nextquad, $1, mycount);
    enterThreeAddr(nextquad - START, "call", $1, inttostr(mycount)); 
  }
  Gen();
}
;

expression_list : expression 
{
  strcpy($$, $1.type);
  strcat($$, " ");

  if(funcStart){
    sprintf(code[nextquad-START],
	    "*%d\tparam %s",nextquad,$1.place);
    enterThreeAddr(nextquad - START, "param", $1.place);
    funcStart = false;
  }
  else{
    sprintf(code[nextquad-START],
	    "%d\tparam %s",nextquad,$1.place);
    enterThreeAddr(nextquad - START, "param", $1.place);
  }

  mycount=1;
  Gen();
}
| expression_list ',' expression
{
  strcat( $1, $3.type );
  strcat( $1, " " ); 
  strcpy( $$, $1 );

  if(funcStart){
    sprintf(code[nextquad-START],
	    "*%d\tparam %s", nextquad, $3.place);
    enterThreeAddr(nextquad - START, "param", $3.place);
    funcStart = false;
  }
  else{
    sprintf(code[nextquad-START],
	    "%d\tparam %s", nextquad, $3.place);
    enterThreeAddr(nextquad - START, "param", $3.place);
  }
  mycount++;
  Gen();
}
;

expression : simple_expression 
{
  strcpy($$.type, $1.type); 

  $$.true_list = Makelist(nextquad);
  $$.false_list = Makelist(nextquad + 1);
  strcpy($$.place, $1.place);
  //Gen();
}
| simple_expression RELOP simple_expression
{ if( (strcmp($1.type, "integer") == 0 || strcmp($1.type, "real") == 0 || strcmp($1.type, "default") == 0) 
      && (strcmp($3.type, "integer") == 0 || strcmp($3.type, "real") == 0 || strcmp($1.type, "default") == 0))
    strcpy($$.type, "boolean");
  else{
    strcpy($$.type, "error");
  }

  $$.true_list = Makelist(nextquad);
  $$.false_list = Makelist(nextquad+1);

  if(funcStart){
    sprintf(code[nextquad-START],
	    "*%d\tif %s %s %s goto ", nextquad, $1.place,
	    $2, $3.place);
    enterThreeAddr(nextquad - START, $2, "\0", $1.place, $3.place);
    funcStart = false;
  }
  else{
    sprintf(code[nextquad-START],
	    "%d\tif %s %s %s goto ", nextquad, $1.place,
	    $2, $3.place);
    enterThreeAddr(nextquad - START, $2, "\0", $1.place, $3.place);
  }

  Gen();

  if(funcStart){
    sprintf(code[nextquad-START], "*%d\tgoto ", nextquad);
    enterThreeAddr(nextquad - START, "goto");
    funcStart = false;
  }
  else{
    sprintf(code[nextquad-START], "%d\tgoto ", nextquad);
    enterThreeAddr(nextquad - START, "goto");
  }
    

  Gen();
}
;

simple_expression : term   
{ 
  strcpy($$.type, $1.type);
 
  strcpy($$.place, $1.place);
}
| sign term 
{ 
  strcpy($$.type, $2.type);
  
  strcat($1.place,$2.place);
  strcpy($$.place,$1.place);
}
| simple_expression ADDOP term
{ 
  if(strcmp($1.type, "integer") == 0 || strcmp($1.type, "default") == 0) {
    if( strcmp($3.type, "integer") == 0 || strcmp($3.type, "default") == 0)
      strcpy($$.type, "integer");
    else if( strcmp($3.type, "real") == 0)
      strcpy($$.type, "real");
    else{
      strcpy($$.type, "error");
    }
  }
  else if( strcmp($1.type, "real") == 0) {
    if( strcmp($3.type, "integer") == 0)
      strcpy($$.type, "integer");
    else if( strcmp($3.type, "real") == 0 || strcmp($3.type, "default") == 0)
      strcpy($$.type, "real");
    else{
      strcpy($$.type, "error");
    }
  }
  else{
    strcpy($$.type, "error");
  }

  strcpy($$.place, Newtemp());

  if(funcStart){
    sprintf(code[nextquad-START],
	    "*%d\t%s = %s %s %s", nextquad, $$.place,
	    $1.place, $2, $3.place);
    enterThreeAddr(nextquad - START, $2, $$.place, $1.place, $3.place);
    funcStart = false;
  }
  else{
    sprintf(code[nextquad-START],
	    "%d\t%s = %s %s %s", nextquad, $$.place,
	    $1.place, $2, $3.place);
    enterThreeAddr(nextquad - START, $2, $$.place, $1.place, $3.place);
  }
  Gen(); 
}
;

term : factor  
{ 
  strcpy($$.type, $1.type); 
  
  strcpy($$.place, $1.place);
}
| term MULOP factor
{ if(strcmp($1.type, "integer") == 0 || strcmp($1.type, "default") == 0) {
    if( strcmp($3.type, "integer") == 0 || strcmp($3.type, "default") == 0)
      strcpy($$.type, "integer");
    else if( strcmp($3.type, "real") == 0)
      strcpy($$.type, "real");
    else{
      strcpy($$.type, "error");
    }
  }
  else if( strcmp($1.type, "real") == 0) {
    if( strcmp($3.type, "integer") == 0)
      strcpy($$.type, "integer");
    else if( strcmp($3.type, "real") == 0 || strcmp($3.type, "default") == 0)
      strcpy($$.type, "real");
    else{
      strcpy($$.type, "error");
    }
  }
  else{
    strcpy($$.type, "error");
  }

  strcpy($$.place, Newtemp());
  
  if(funcStart){
    sprintf(code[nextquad-START],
	    "*%d\t%s = %s %s %s", nextquad, $$.place,
	    $1.place, $2, $3.place);
    enterThreeAddr(nextquad - START, $2, $$.place, $1.place, $3.place);
    funcStart = false;
  }
  else{
    sprintf(code[nextquad-START],
	    "%d\t%s = %s %s %s", nextquad, $$.place,
	    $1.place, $2, $3.place);
    enterThreeAddr(nextquad - START, $2, $$.place, $1.place, $3.place);
  }
  Gen(); 
}
;

factor : ID   
{ string s = look_up_type($1, tblptr.top()->hashtable);
  it = look_up($1, tblptr.top()->hashtable);
  if(s != "\0" && it->is_procedure == NULL)
    strcpy($$.type, s.c_str());
  else{
    if(it->is_procedure != NULL)
      {
	//it = look_up($1, tblptr.top()->hashtable);
	string rettype = ((symbol_table *)it->is_procedure)->rettype;
	if(rettype == ""){
	  semanticerror("procedure used as an expression");
	  strcpy($$.type, "default");
	}
	else
	  strcpy($$.type, rettype.c_str());
      }
    else
      strcpy($$.type, "default");
  }

  strcpy($$.place, $1);
}
| ID '(' expression_list ')' 
{
  it = look_up($1, tblptr.top()->hashtable);
  if(it->type == "\0" || it -> is_procedure == NULL)
    semanticerror("called object is not a procedure or statement");
  else{
    string argtypes = ((symbol_table *)it->is_procedure)->argtypes;
    string rettype = ((symbol_table *)it->is_procedure)->rettype;
    
    if( strcmp( $3, argtypes.c_str() ) != 0)
      {
	semanticerror("Number of elements passed in the function are not same or there is a type mismatch");
      }
    strcpy($$.type, rettype.c_str());
  }

  if(funcStart){
    sprintf(code[nextquad-START], "*%d\tcall %s,%d",
	    nextquad, $1, mycount);
    enterThreeAddr(nextquad - START, "call", $1, inttostr(mycount));
    funcStart = false;
  }
  else{
    sprintf(code[nextquad-START], "%d\tcall %s,%d",
	    nextquad, $1, mycount);
    enterThreeAddr(nextquad - START, "call", $1, inttostr(mycount));
  }
  strcpy($$.place,$1);
  Gen();
}
| DIGITS 
{ 
  strcpy($$.type, "integer"); 
  
  char str[10];
  sprintf(str,"%d",$1);//Gen();
  strcpy($$.place,str);
}
| NUM  
{ 
  strcpy($$.type, "real");

  char str[10];
  sprintf(str, "%f", $1);
  //Gen();
  strcpy($$.place, str);
}
| '(' expression ')' 
{ 
  strcpy($$.type, $2.type); 

  $$.true_list = $2.true_list;
  $$.false_list = $2.false_list;
}
| NOT factor 
{ 
  strcpy($$.type, $2.type);

  $$.true_list = $2.false_list;
  $$.false_list = $2.true_list;
}
;

sign : '+'
{
  strcpy($$.place,"+");
}
| '-'
{
  strcpy($$.place,"-");
}
;

%%
#include "lex.yy.c"

void yyerror(const char *msg)
{
  printf("%s:%d: error: %s before `%s'\n", filename, line_num, msg, yytext);
  error = true;
}

void semanticerror(const char *msg)
{
     printf("%s:%d: semantic error: %s\n", filename, line_num, msg);
     error = true;
}

void undeclarederror(const char *identifier)
{
     printf("%s:%d: semantic error: undeclared identifier `%s' (first use in this routine)\n", filename, line_num, identifier);
     error = true;
}

int yywrap()
{
  return 1;
}

/*
void insert_keyword(adj_list &hashtable)
{
     int i = 0;
     node sym_entry;
     
     while(i < NUM_KEYWORDS){
	  sym_entry.str = keywords[i];
	  search_ins(sym_entry, hashtable);
	  i++;
     }
}
*/

int main(int argc, char *argv[])
{
  if(argc == 2){
    strcpy(filename, argv[1]);
    yyin = fopen(argv[1], "r");
    if(!yyin){
      printf("%s: cannot open file.\n", argv[1]);
      return 1;
    }
  }
  
  //  hashtable.resize(SIZE);
  // Insert KEYWORDS into the symbol table
//  insert_keyword(hashtable);
     
  //  yydebug = 1;
  yyparse();

  if(!error)
    codegeneration();
  
  
  //  print_hash_table(tblptr.top()->hashtable);
  /*insert_type( "x", hashtable, "integer" );
  lst_it it;
  it = look_up( "x", hashtable );
  cout << it->str << " " << it->type << "\n";*/
  return 0;
}


int* Makelist(int nquad)
{ 
  int* list=(int*)malloc(sizeof(int)*15); 
  list[0] = nquad; 
  list[1] = 0;
  return list;
}
 
 
int* Merge(int* list1,int* list2)
{
  int* temp = list1, count1 = 0, count2 = 0;
  while(list1[count1] != 0) count1++;
  while(list2[count2] != 0)
    {
      list1[count1] = list2[count2];
      count1++;
      count2++;
    }
  return temp;
}
 
void Backpatch(int* list,int nquad)
{
  char addr[10];
  char three[10];
  sprintf(addr, "%d", nquad);
  sprintf(three, "%d", nquad - START);
  while(*list!=0)
    {
      int index=*list++-START;
      strcat(code[index], addr);
      threeaddr[index][2] = three;
    }
}
 
void Gen()
{
  /*  if(nextquad[nextquad.length()] == '*')
    nextquad[nextquad.length] = '\0';

  int nq = atoi(nextquad.c_str());
  nq++;
  sprintf(nextquad, "%d", nq); */
  nextquad++;
}

char* Newtemp()
{
  static int count=1;
  char* ch=(char*)malloc(sizeof(char)*5);
  sprintf(ch,"T%d",count++);

  //  cout << "new temporary : " << ch << '\n';
  
  /* Inserting temporaries in symbol table */
  insert_symboltable(ch);
  insert_type(ch, tblptr.top()->hashtable, "real", tblptr.top()->width);
  tblptr.top()->width += 4;
  /* Done */

  return ch;
}

/*
void putLabel()
{
  int length = nextquad.length();
  nextquad[length] = '*';
  nextquad[length + 1] = '\0';
} 
*/

string inttostr(int num)
{
     char str[10];
     sprintf(str, "%d", num);
     return str;
}

void enterThreeAddr(int index, string opcode, string result, string arg1, string arg2)
{
  threeaddr[index][0] = inttostr(index);
  threeaddr[index][1] = opcode;
  threeaddr[index][2] = result;
  threeaddr[index][3] = arg1;
  threeaddr[index][4] = arg2;
}


void codegeneration()
{
  symbol_table * t = tblptr.top();
  int i;
  int width = t->width;
  int start = t->label - START;

  
  vector<float> mem(width/4);
  
  string ccode = "";
  
  ccode += "#include <iostream>\n#include <iomanip>\n#include <vector>\n\nusing namespace std;\nint main(){\n";

  ccode += "\tvector<float> mem(";
  ccode += inttostr(width/4);
  ccode += ");\n";
  
  for(i = start; i <= nextquad - START; i++)
    {
      if(labelFlag[i])
	ccode += "lb" + inttostr(i) + ": ";
            
      ccode += getCcode(threeaddr[i], i, i);
    }
  ccode += "}";

  ofstream f("p2c.cpp");
  
  f << ccode << endl;
  f.close();
  
}

// v is a structured 3-address code
string getCcode(vector<string> &v, int currentQuad, int &mynextQuad)
{
  string code = "";
  int offsetRes;
  int offsetArg1;
  int offsetArg2;
  
  static int numParams = 0;
  
  symbol_table * t = tblptr.top();
  
  if( v[1] == "=")
    {
      offsetRes = getoffset(v[2], t) + functionBaseAddr;
      offsetArg1 = getoffset(v[3], t);
      
      code += "\tmem[" + inttostr(offsetRes) + "] = ";
      if(offsetArg1 == IS_REAL)
	code += v[3] + ";\n";
      else
	code += "mem[" + inttostr(offsetArg1 + functionBaseAddr) + "];\n";
      
    }
  else if( v[1] == "+" || v[1] == "-" || v[1] == "*" || v[1] == "/" )
    {
      offsetRes = getoffset(v[2], t) + functionBaseAddr;
      offsetArg1 = getoffset(v[3], t);
      offsetArg2 = getoffset(v[4], t);

      code += "\tmem[" + inttostr(offsetRes) + "] = ";

      if(offsetArg1 == IS_REAL)
	code += v[3] + v[1] + " ";
      else
	code += "mem[" + inttostr(offsetArg1 + functionBaseAddr) + "] " + v[1] + " ";

      if(offsetArg2 == IS_REAL)
	code += v[4] + ";\n";
      else
	code += "mem[" + inttostr(offsetArg2 + functionBaseAddr) + "];\n";

    }
  else if( v[1] == "halt" )
    {
      code += "\treturn 0;\n";
    }
  else if( v[1] == "<" || v[1] == ">" || v[1] == "<=" || v[1] == ">=" || v[1] == "=" || v[1] == "<>" )
    {
      offsetArg1 = getoffset(v[3], t);
      offsetArg2 = getoffset(v[4], t);

      
      code += "\tif ( ";
      if(offsetArg1 == IS_REAL)
	code += v[3];
      else
	code += "mem[" + inttostr(offsetArg1 + functionBaseAddr) + "]";
      
      if( v[1] == "=" )
	code += " == ";
      else if( v[1] == "<>" )
	code += " != ";
      else
	code += " " + v[1] + " ";
      
      if(offsetArg1 == IS_REAL)
	code += v[3];
      else
	code += "mem[" + inttostr(offsetArg2 + functionBaseAddr) + "]";

      code += " ) goto lb" + v[2] + ";\n";
      labelFlag[ atoi(v[2].c_str()) ] = true;
    } 
  else if( v[1] == "goto" )
    {
      code += "\t" + v[1] + " lb" + v[2] + ";\n";
      labelFlag[ atoi(v[2].c_str()) ] = true;
    }
  else if( v[1] == "param")
    {
      offsetRes = getoffset(v[2], t) + functionBaseAddr;
      if(numParams == 0)
	{
	  code += "\t_temp = mem.size();\n\tmem.resize( _temp + 3 );\n";
	  code += "\tmem[ _temp + 2 ] = mem[ " + inttostr(offsetRes) + " ];\n";
	  numParams++;
	}
      else
	{
	  code += "\t_temp = mem.size();\n\tmem.resize( _temp + 1 );\n";
	  code += "\tmem[ _temp ] = mem[ " + inttostr(offsetRes) + " ];\n";
	  numParams++;
	}
    }
  else if( v[1] == "call" )
    {
      functionBaseAddr = t->width/4;
      lst_it it = look_up(v[2], t->hashtable);
      int width = ((symbol_table *)(it->is_procedure))->width/4 - 2 - numParams;
      
      code += "\t_temp = mem.size();\n\tmem.resize( _temp + " + inttostr(width) + " );\n";
      code += "\tmem[ _temp - " + inttostr(numParams + 1) + " ] = " + inttostr(currentQuad + 1) + ";\n";
      labelFlag[currentQuad + 1] = true;
      functionReturn = currentQuad + 1;
      
      int label = ((symbol_table *)(it->is_procedure))->label;
      code += "\tgoto lb" + inttostr(label - START) + ";\n";
      labelFlag[label - START] = true;
      
      mynextQuad = label - START - 1;
      tblptr.push( (symbol_table *)it->is_procedure);
      
      numParams = 0;
    }
  else if( v[1] == "return" )
    { // write proper function goto's
      
      int width = t->width/4 - 1;
      code += "\t_temp = mem.size();\n\tmem.resize( _temp - " + inttostr(width) + " );\n";
      
      string fname = t->name;
      tblptr.pop();
      functionBaseAddr -= tblptr.top()->width/4;
      int offsetFunction = getoffset(fname, tblptr.top());
      
      code += "\tmem[" + inttostr(offsetFunction + functionBaseAddr) + "] = mem[mem.size() - 1];\n";
      code += "\tmem.resize(mem.size() - 1);\n";
      
      code += "\tgoto lb" + inttostr(functionReturn) +";\n";
      
      mynextQuad = functionReturn - 1;
      labelFlag[functionReturn] = true;
      
      
    }
  
  return code;
}
