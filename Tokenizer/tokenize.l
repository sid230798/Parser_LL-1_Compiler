/*

Name :- Siddharth Nahar
Entry No :- 2016csb1043
Date :- 6/2/19
Purpose :-

    1. Lexical Analysis of C-Program
    2. Will parse C-Code into Tokens and describing each token type

*/

/*Include Libraris*/
%{

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
%}


/*Different Definitions of Digits :- */
non_digit [_a-zA-Z]
digit [0-9]
non_zero_digit [1-9]
octal_digit [0-7]
hexa_decimal_digit [0-9a-zA-Z]

/*This are Keywords tokens and will be matched first*/
keywords auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while

/*Operators will be matched*/
operator ([.+-/^&|~!?<>]|"++"|"--"|"##"|"<<"|">>"|"&="|"*="|"/="|"%="|"<="|">="|"!="|"=="|"<<="|">>="|"^="|"|="|"->")

/*Punctuators will be matched*/
punctuator ([{};]|"...")

/*Can be both operators and punctuators*/
mixedOpPunc ([\[\](),*:#=])

/*

    Definition of Identifiers
        1. Starts with non-digit
        2. Followed by any _,digit or non digit

*/

identifier {non_digit}({non_digit}|{digit})*

/*Escape Sequence*/
simple_escape "\\"['"?abfnrtv]
octal_escape "\\"{octal_digit}{1,3}
hexa_escape "\\"[x]{hexa_decimal_digit}+
escape_sequence ({simple_escape}|{octal_escape}|{hexa_escape})

/*ALL constants definition*/
fractional_constant ({digit_sequence}?"."{digit_sequence}|{digit_sequence}".")
decimal_constant {non_zero_digit}{digit}*
octal_constant 0{octal_digit}*
hexadecimal_constant 0(x|X){hexa_decimal_digit}+ 
c_char ([^'\\\n]|{escape_sequence})
s_char ([^"\\\n]|{escape_sequence})
q_char [^"\n]
h_char [^>\n]

/*Digit sequence required later and character sequence*/
digit_sequence {digit}+
c_char_sequence {c_char}+
s_char_sequence {s_char}+
q_char_sequence {q_char}+
h_char_sequence {h_char}+

sign [+-]

/*Exponent part to recognize in constants*/
exponent [eE]{sign}?{digit_sequence}

/*Floating,Integer suffix suffix*/
floating_suffix [fFlL]
unsigned_suffix [uU]
long_suffix [lL]
integer_suffix ({unsigned_suffix}{long_suffix}?|{long_suffix}{unsigned_suffix}?)

/*Definition of all Constants*/
floating_constant ({fractional_constant}{exponent}?|{digit_sequence}{exponent}){floating_suffix}?
integer_constant ({decimal_constant}|{octal_constant}|{hexadecimal_constant}){integer_suffix}?
enumeration_constant {identifier}
character_constant L?[']{c_char_sequence}[']
string_literal L?["]{s_char_sequence}["]

constant ({floating_constant}|{integer_constant}|{enumeration_constant}|{character_constant})
header_name ("<"{h_char_sequence}">"|["]{q_char_sequence}["])
pp_number [.]?{digit}([.0-9a-zA-Z]|[eE][+-])*
comments "/*"([^*]|"*"+[^/])*"*"+"/"

/*Start of matching*/
%%

{comments}  {

                    /*Match for complete comment*/
                    printf("Comment : %s\n",yytext);

            }

{keywords}  {

                /*If matched with Keyword*/
                printf("Keyword : %s\n",yytext);

            }
            
{identifier}   {

                    /*If matched with Identifers*/
                    printf("Identifier : %s\n",yytext);
                }
                
{constant}     {

                    /*Matches for 4 type of constants specified above*/
                    printf("Constant : %s\n",yytext);
                }
                
{string_literal}    {
    
                        /*Match with string literal*/
                        printf("String Literal : %s\n",yytext);

                    }
                    
{operator}  {

                printf("Operator : %s\n",yytext);

            }
                
{punctuator}   {

                    printf("Punctuators : %s\n",yytext);
                }
                
{mixedOpPunc}   {

                    printf("Can be Punctuator or Operator : %s\n",yytext);
                }
                
{header_name}   {
                    printf("Header name : %s\n",yytext);
                }
 
.   {}

%%

/*Wraps the expression*/
int yywrap(){}

/*Driver code for Above*/
int main(int argc, char* argv[]){

	if(argc <= 1){
	
		printf("INPUT_FILE must be passed as argument\n");
		
	}else{

		/*Input C code for tokenizer*/
		yyin = fopen(argv[1],"r");
		yylex();
    }
    return 0;
	
}
