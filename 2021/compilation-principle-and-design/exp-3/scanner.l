%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNDEFINED -1
#define END_OF_FILE 0
#define KEY_WORD 1
#define IDENTIFIER 2
#define NUMERICAL_CONSTANT 3
#define CHAR_CONSTANT 4
#define STRING_LITERAL 5
#define SYMBOL 6

int tokens_count = 0;
int lines_count = 1;
int columns_count = 0;

%}

 /* Keywords */
keywords auto|continue|enum|if|restrict|static|unsigned|break|default|extern|inline|return|struct|void|case|char|do|double|float|for|int|long|short|signed|switch|typedef|volatile|while|const|else|goto|register|sizeof|union
 
 /* Identifier */
digit [0-9]
no_digit [_a-zA-Z]
indentifier {no_digit}({digit}|{no_digit})*
 
 /* Numerical Constant */
 
 /* Integer Constant */
unsigned_suffix u|U
long_suffix l|L
long_long_suffix (ll)|(LL)
integer_suffix ({unsigned_suffix}{long_suffix}?)|({unsigned_suffix}{long_long_suffix}?)|({long_suffix}{unsigned_suffix}?)|({long_long_suffix}{unsigned_suffix}?)
hexadecimal_digit [0-9a-fA-F]
octal_digit [0-7]
nonzero_digit [1-9]
hexadecimal_prefix (0x)|(0X)
hexadecimal_constant {hexadecimal_prefix}{hexadecimal_digit}+
octal_constant 0{octal_digit}+
decimal_constant 0|{nonzero_digit}{digit}*
integer_constant ({decimal_constant}{integer_suffix}?)|({octal_constant}{integer_suffix}?)|({hexadecimal_constant}{integer_suffix}?)
 
 /* Float Constant */
float_suffix f|l|F|l
sign (\-)|(\+)
binary_exponent_part (p|P){sign}{digit}+
exponent_part (e|E){sign}{digit}+
hexadecimal_fractional_constant {hexadecimal_digit}+\.{hexadecimal_digit}*
decimal_fractional_constant {digit}+\.{digit}*
hexadecimal_float_constant ({hexadecimal_prefix}{hexadecimal_fractional_constant}{binary_exponent_part}?{float_suffix}?)|({hexadecimal_prefix}{hexadecimal_digit}+{binary_exponent_part}{float_suffix}?)
decimal_float_constant ({decimal_fractional_constant}{exponent_part}?{float_suffix}?)|({digit}+{exponent_part}{float_suffix}?)
float_constant {decimal_float_constant}|{hexadecimal_float_constant}
 
 /* Char Constant */
char_prefix L|u|U
escape_sequence (\\')|(\\\")|(\\?)|(\\\\)|(\\a)|(\\b)|(\\f)|(\\n)|(\\r)|(\\t)|(\\v)
c_char [^'\n\\]|{escape_sequence}
char_constant {char_prefix}?'{c_char}'
 
 /* String Literal */
encoding_prefix (u8)|u|U|L
s_char [^"\n\\]|{escape_sequence}
string_literal {encoding_prefix}?\"{s_char}*\"
 
 /* Symbol */
symbol "["|"]"|"++"|"--"|"/"|"%"|"=="|"!="|"?"|":"|"="|"*="|">>="|"&="|"^="|"<%"|"%>"|"("|")"|"{"|"}"|"."|"->"|"&"|"*"|"+"|"-"|"~"|"!"|"<<"|">>"|"<"|">"|"<="|">="|"^"|"|"|"&&"|"||"|";"|"..."|"/="|"%="|"+="|"-="|"<<="|"|="|","|"#"|"##"|"<:"|":>"|"%:"|"%:%:"

%s INLINE_COMMENT
%s BLOCK_COMMENT

%%

<INITIAL>"/*" {
    BEGIN BLOCK_COMMENT;
}
<BLOCK_COMMENT>\n {
    lines_count++;
}
<BLOCK_COMMENT>. {
    ;
}
<BLOCK_COMMENT>"*/" {
    BEGIN INITIAL;
}
<INITIAL>"//" {
    BEGIN INLINE_COMMENT;
}
<INLINE_COMMENT>\n {
    lines_count++;
    BEGIN INITIAL;
}
<INLINE_COMMENT>. {
    ;
}

<INITIAL>{keywords} {
    return KEY_WORD;
}
<INITIAL>{indentifier} {
    return IDENTIFIER;
}
<INITIAL>{integer_constant} {
    return NUMERICAL_CONSTANT;
}
<INITIAL>{float_constant} {
    return NUMERICAL_CONSTANT;
}
<INITIAL>{char_constant} {
    return CHAR_CONSTANT;
}
<INITIAL>{string_literal} {
    return STRING_LITERAL;
}
<INITIAL>{symbol} {
    return SYMBOL;
}
<INITIAL>" " {
    columns_count++;
}
<INITIAL>\t {
    columns_count += 4;
}
<INITIAL>\n {
    lines_count++;
    columns_count = 0;
}
<INITIAL>. {
    return UNDEFINED;
}
<<EOF>> {
    return END_OF_FILE;
}

%%

int GenerateToken(int token, const char *token_code, int index, int line, int column, FILE *out_file)
{
    switch (token)
    {
    case KEY_WORD:
    {
        fprintf(out_file, "[@%d,%d:%d=\'%s\',<'%s'>,%d:%d]\n", index, column, (int)(column + strlen(token_code) - 1),
                token_code, token_code, line, column);
        return KEY_WORD;
    }
    case IDENTIFIER:
    {
        fprintf(out_file, "[@%d,%d:%d=\'%s\',<Identifer>,%d:%d]\n", index, column, (int)(column + strlen(token_code) - 1),
                token_code, line, column);
        return IDENTIFIER;
    }
    case NUMERICAL_CONSTANT:
    {
        fprintf(out_file, "[@%d,%d:%d=\'%s\',<'Numercial Constant'>,%d:%d]\n", index, column, (int)(column + strlen(token_code) - 1),
                token_code, line, column);
        return NUMERICAL_CONSTANT;
    }
    case CHAR_CONSTANT:
    {
        fprintf(out_file, "[@%d,%d:%d=\'%s\',<Char Constant>,%d:%d]\n", index, column, (int)(column + strlen(token_code) - 1),
                token_code, line, column);
        return CHAR_CONSTANT;
    }
    case STRING_LITERAL:
    {
        fprintf(out_file, "[@%d,%d:%d=\'%s\',<String Literal>,%d:%d]\n", index, column, (int)(column + strlen(token_code) - 1),
                token_code, line, column);
        return STRING_LITERAL;
    }
    case SYMBOL:
    {
        fprintf(out_file, "[@%d,%d:%d=\'%s\',<'%s'>,%d:%d]\n", index, column, (int)(column + strlen(token_code) - 1),
                token_code, token_code, line, column);
        return SYMBOL;
    }
    case END_OF_FILE:
    {
        fprintf(out_file, "[@%d,%d:%d=\'<EOF>\',<EOF>,%d:%d]\n", index, column, (int)(column + strlen(token_code) - 1),
                line, column);
        return END_OF_FILE;
    }
    default:
    {
        fprintf(out_file, "[@%d,%d:%d=\'%s\',<Undefined>,%d:%d]\n", index, column, (int)(column + strlen(token_code) - 1),
                token_code, line, column);
        return UNDEFINED;
    }
    }
}


int main() {
    yyin = fopen("./source.c", "r");
    yyout = fopen("./source.tokens", "w");
    int token = 0;
    while((token = yylex())){
        GenerateToken(token, yytext, tokens_count, lines_count, columns_count, yyout);
        tokens_count++;
        columns_count += strlen(yytext);
    }
    GenerateToken(token, yytext, tokens_count, lines_count, columns_count, yyout);
    
    return 0;
}