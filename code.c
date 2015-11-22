//VARIABLES USED FOR INTERMEDIATE CODE GENERATION

//CODE_LIST - GLOBAL VARIABLE LIST TO STORE A LIST OF THREE ADDRESS CODES

//NEXTQUAD - THE CURRENT LINE NUMBER - GLOBAL VARIABLE

//variables to be put in union - how u should think

//quad - number - used for Marker M 

//truelist and falselist - list of numbers

//nextlst - list of numbers

//place - string

// i might have missed out on some variables - pls check on them 


//Functions used : 

//Backpatch, merge_list, make_list,new_temp - functions whose logic has been taught in class - to be implemented


struct three_addr
{
  int lineno; //line number
  char* code; //string containing the three address code
  struct list_elem elem;
};

struct list code_list; //list of three_addr


//  intermediate code for if then else production 

IF expression THEN M statement N1 ELSE M statement

      // first should have checked whether expression.type is a boolean or not
{   
      $$.nextlist = (int*)malloc(sizeof(int)*20);

      Backpatch($2.truelist,$4.quad);

      Backpatch($2.falselist,$8.quad);
 
      $$.nextlist = merge_list($2.falselist,$9.nextlist);

      $$.nextlist = merge_list($$.nextlist,$5.nextlist);
}  
 
// intermediate code for while loop

WHILE M expression DO M statement

// first check whether expression.type is a boolean or not
{
      Backpatch($6.nextlist,$2.quad);

      Backpatch($3.truelist,$5.quad);

      $$.nextlist = $3.falselist;

// intermediate code for ADDOP operations

      simple_exp ADDOP M term

      // if ADDOP is or , check whether simple_exp and term are boolean

      if($2.value == OR_OP)
          {
              Backpatch($1.falselist,$3.quad);

              $$.truelist = merge_list($1.truelist,$4.truelist);

              $$.falselist = $4.falselist;
         }
      else
	{
	  
	  strcpy($$.place, new_temp());
	  
	     struct three_addr* addr = malloc (sizeof (struct three_addr)); //struct three_addr will have "char* addr and struct list_elem elems"
	     
             if($2.value == PLUS)
                sprintf(addr->code,"%d:%s := %s + %s \n",nextquad,$$.place,$1.place,$4.place);

             if($2.value == MINUS)
               sprintf(addr->code,"%d:%s := %s - %s \n",nextquad,$$.place,$1.place,$4.place);


             list_push_front(&code_list, &addr->elem);

             nextquad++;
        }

}

// intermediate code for MULOP operations


      term MULOP M factor

     //if MULOP is and operator check whether the term and factor are boolean or not .
{
     if($2.value == AND_OP)
       {
          Backpatch($1.truelist,$3.quad);

          $$.truelist = $4.truelist

          $$.falselist = merge_list($1.falselist,$4.falselist);

       }
     else
       {
          $$.place = new_temp();

           struct three_addr* addr = malloc (sizeof (struct three_addr)); //struct three_addr will have "char* addr and struct list_elem elems"

          switch($2.value)
            {
                case MOD_OP: sprintf(addr->code,"%d:%s := %s % %s \n",nextquad,$$.place,$1.place,$4.place); break;

                case INT_DIVIDE : 

                case DIVIDE : sprintf(addr->code,"%d:%s := %s / %s \n",nextquad,$$.place,$1.place,$4.place); break;

                case MULTIPLY : sprintf(addr->code,"%d:%s := %s * %s \n",nextquad,$$.place,$1.place,$4.place); break;

                default: break;
           }

        list_push_front(&code_list, &addr->elem);

        nextquad++;
       }
 
}

// intermediate code for relop operation

   simple_expression RELOP simple_expression

   {

      $$.place = new_temp();

      $$.truelist = make_list(nextquad);
  
      $$.falselist = make_list(nextquad+1);

      struct three_addr* addr = malloc (sizeof (struct three_addr)); //struct three_addr will have "char* addr and struct list_elem elems"

     switch($2.value)
     {
 
        case EQ: sprintf(addr->code,"%d:if %s = %s goto ", nextquad, $1.place,$3.place);break;

        case NEQ: sprintf(addr->code,"%d:if %s <> %s goto ", nextquad, $1.place,$3.place);break;
 
        case GT : sprintf(addr->code,"%d:if %s > %s goto ", nextquad, $1.place,$3.place);break;
   
        case GTE : sprintf(addr->code,"%d:if %s >= %s goto ", nextquad, $1.place,$3.place);break;

        case LT : sprintf(addr->code,"%d:if %s < %s goto ", nextquad, $1.place,$3.place);break;

       case LTE :sprintf(addr->code,"%d:if %s <= %s goto ", nextquad, $1.place,$3.place);break;
    }

   list_push_front(&code_list, &addr->elem);

   nextquad++;

   struct three_addr* addr_n = malloc (sizeof (struct three_addr)); //struct three_addr will have "char* addr and struct list_elem elems"

   sprintf(addr_n->code,"%d:goto ",nextquad);

   list_push_front(&code_list, &addr_n->elem);

   nextquad++;

 }

// procedure call 3 addr code 

//0 arguments production

procedure_statement : IDENTIFIER

// should have checked whether such a procedure has been declared first

{
   struct three_addr* addr = malloc (sizeof (struct three_addr)); 
   
   sprintf(code[addr->code,"%d:call %s,0", nextquad,$1.iden);

   list_push_front(&code_list, &addr->elem);
 
   nextquad++;

}

// if procedure has multiple arguments

   procedure_statement : IDENTIFIER (expression_lst)

   {

      func_entry_t* f = lookup_func_entry ($1.iden);
	
      int n = f->num_args;

      struct three_addr* addr = malloc (sizeof (struct three_addr)); 
   
     sprintf(addr->code,"%d:call %s,%d", nextquad,$1.iden,n);

     list_push_front(&code_list, &addr->elem);
 
     nextquad++;
  }

// in the expression list , writing intermediate code 

expression_list : expression 

{

   struct three_addr* addr = malloc (sizeof (struct three_addr)); 

   sprintf(addr->code,"%d:param %s",nextquad,$1.place);

   list_push_front(&code_list, &addr->elem);
 
   nextquad++;
}

expression_list ',' expression

{
 
   struct three_addr* addr = malloc (sizeof (struct three_addr)); 

   sprintf(addr->code,"%d:param %s",nextquad,$3.place);

   list_push_front(&code_list, &addr->elem);
 
   nextquad++;
}

// in expression production

expression : simple_expression 

{

  $$.truelist = make_list(nextquad);

  $$.falseslist = make_list(nextquad + 1);

}

// in simple expression productions

simple_expression : term 

{

  strcpy($$.place, $1.place);

}

single_expression : sign term 

{

   strcat($1.place,$2.place);
  
   strcpy($$.place,$1.place);

}

term : factor  

{

  strcpy($$.place, $1.place);

}

// factor production
 
factor : IDENTIFIER

{

  strcpy($$.place, $1.iden); 


factor : IDENTIFIER '(' expression_list ')' 

{
    func_entry_t* f = lookup_func_entry ($1.iden);
	
    int n = f->num_args;

    struct three_addr* addr = malloc (sizeof (struct three_addr)); 
   
    sprintf(addr->code,"%d:call %s,%d", nextquad,$1.iden,n);

    list_push_front(&code_list, &addr->elem);

    nextquad++;
   
    strcpy($$.place,$1.iden);

}

factor : INTNUM
{
  sprintf($$.place,"%d",$1.value);
}  


factor : REALNUM

{
  sprintf($$.place,"%f", $1.fl);
  
}

factor : (expression)

 $$.truelist = $2.truelist;
 
 $$.falselist = $2.falselist;

factor : NOT factor

  $$.truelist = $2.falselist;

  $$.falselist = $2.truelist;

// for sign production

sign : '+'
{
  strcpy($$.place,"+");
}
| '-'
{
  strcpy($$.place,"-");
}

variable : IDENTIFIER

{

  strcpy($$.place, $1.iden);

}


variable : IDENTIFIER '[' DIGITS ']'

{

  char temp[20];

  char temp_dig[10];

  sprintf(temp_dig,"%d",$3.place);

  strcpy(temp,$1.iden);

  strcat(temp,"[");

  strcat(temp,temp_dig);

  strcat(temp,"]");

  strcpy($$.place,temp);

}


M: 
{
  $$.quad = nextquad;
} 


subprogram_declaration : subprogram_head declarations compound_statement
{

   struct three_addr* addr = malloc (sizeof (struct three_addr)); 

   sprintf(addr->code, "%d:return", nextquad);

   list_push_front(&code_list, &addr->elem);

   nextquad++;

}

program : IDENTIFIER '(' identifier_list ')' ';' declarations subprogram_declarations  compound_statement  '.' 

 {

   struct three_addr* addr = malloc (sizeof (struct three_addr)); 

   sprintf(addr->code, "%d:halt",nextquad);

   list_push_front(&code_list, &addr->elem);

   nextquad++;

}

          
