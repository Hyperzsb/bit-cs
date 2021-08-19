grammar C;

//////////////////
// Parser Rules //
//////////////////

primaryExpression
    : Identifier
    | IntegerConstant
    | FloatingConstant
    | CharacterConstant
    | StringLiteral
    | '(' expression ')'
;

postfixExpression
    : primaryExpression 
    | postfixExpression '[' expression ']'
    | postfixExpression '(' argumentExpressionList? ')'
    | postfixExpression  ('++' | '--')
;

/* Undo */
argumentExpressionList
    : assignmentExpression ( ',' assignmentExpression )*
;

unaryExpression
    : postfixExpression
    | ('++' | '--') unaryExpression
    | unaryOperator castExpression
    | 'sizeof' unaryExpression
    | 'sizeof' '(' typeName ')'
;

/* Undo */
unaryOperator
    : '&'
    | '*'
    | '+'
    | '-'
    | '~'
    | '!'
;

castExpression
    : '(' typeName ')' castExpression
    | unaryExpression
;

multiplicativeExpression
    : castExpression
    | multiplicativeExpression ('*'|'/'|'%') castExpression
;

additiveExpression
    : multiplicativeExpression
    | additiveExpression ('+'|'-') multiplicativeExpression
;

relationalExpression
    : additiveExpression
    | relationalExpression ('<'|'>'|'<='|'>=') additiveExpression
;

equalityExpression
    : relationalExpression
    | equalityExpression ('=='| '!=') relationalExpression
;

andExpression
    : equalityExpression
    | andExpression '&' equalityExpression
;

exclusiveOrExpression
    : andExpression
    | exclusiveOrExpression '^' andExpression
;

inclusiveOrExpression
    : exclusiveOrExpression
    | inclusiveOrExpression '|' exclusiveOrExpression
;

logicalAndExpression
    : inclusiveOrExpression
    | logicalAndExpression '&&' inclusiveOrExpression
;

logicalOrExpression
    : logicalAndExpression
    | logicalOrExpression '||' logicalAndExpression
;

conditionalExpression
    : logicalOrExpression
    | logicalOrExpression '?' expression ':' conditionalExpression
;

assignmentExpression
    : conditionalExpression
    | unaryExpression assignmentOperator assignmentExpression
;

/* Undo */
assignmentOperator
    : '=' 
    | '*=' 
    | '/=' 
    | '%=' 
    | '+=' 
    | '-='
    | '&=' 
    | '^=' 
    | '|='
;

/* Undo */
expression
    : assignmentExpression (',' assignmentExpression)*
;

declaration
    : declarationSpecifiers initDeclaratorList? ';'
;

/* Undo */
declarationSpecifiers
    : declarationSpecifier+
;

/* Undo */
declarationSpecifier
    : typeSpecifier
;

/* Undo */
initDeclaratorList
    : initDeclarator (',' initDeclarator)*
;

initDeclarator
    : declarator ('=' initializer)?
;

/* Undo */
typeSpecifier
    : 'void'
    | 'char'
    | 'int'
    | 'float'
    | 'double'
;

declarator
    : directDeclarator
;

directDeclarator
    : Identifier
    | '(' declarator ')'
    | directDeclarator '[' assignmentExpression ']'
    | directDeclarator '(' parameterTypeList ')'
    // 2
    | directDeclarator '(' identifierList? ')'
;

/* Undo */
parameterTypeList
    : parameterList
;

/* Undo */
parameterList
    : parameterDeclaration (',' parameterDeclaration)*
;

parameterDeclaration
    : declarationSpecifiers declarator?
;

//3
identifierList
    : Identifier (',' Identifier)*
;

typeName
    : typeSpecifier
;

initializer
    : assignmentExpression
    | '{' initializerList ','? '}'
;

initializerList
    :  initializer (',' initializer)*
;

/* Undo */
statement
    : labeledStatement
    | compoundStatement
    | expressionStatement
    | selectionStatement
    | iterationStatement
    | jumpStatement
;

labeledStatement
    : Identifier ':' statement
;

compoundStatement
    : '{' blockItemList? '}'
;

/* Undo */
blockItemList
    : blockItem+
;

/* Undo */
blockItem
    : statement
    | declaration
;

expressionStatement
    : expression? ';'
;

selectionStatement
    : 'if' '(' expression ')' statement ('else' statement)?
;

// 5 Why?
iterationStatement
    : 'for' '(' expressionA? ';' expressionB?  ';' expressionC? ')' statement       # firstForStatement
    | 'for' '(' declaration  expressionA? ';' expressionB? ')' statement            # secondForStatement
;

expressionA
    : expression
;

expressionB
    : expression
;

expressionC
    : expression
;

jumpStatement
    : 
    ( 'goto' Identifier
    | 'continue'
    | 'break'
    | 'return' expression?
    )
    ';'
;

compilationUnit
    : translationUnit? EOF
;

/* Undo */
translationUnit
    : externalDeclaration+
;

/* Undo */
externalDeclaration
    : functionDefinition
    | declaration
    | ';'
;

functionDefinition
    : declarationSpecifiers? declarator compoundStatement
;

////////////////
// Token Name //
////////////////

Break : 'break';
Case : 'case';
Char : 'char';
Continue : 'continue';
Default : 'default';
Do : 'do';
Double : 'double';
Else : 'else';
Float : 'float';
For : 'for';
Goto : 'goto';
If : 'if';
Int : 'int';
Return : 'return';
Sizeof : 'sizeof';
Void : 'void';
While : 'while';

LeftParen : '(';
RightParen : ')';
LeftBracket : '[';
RightBracket : ']';
LeftBrace : '{';
RightBrace : '}';

Less : '<';
LessEqual : '<=';
Greater : '>';
GreaterEqual : '>=';

Plus : '+';
PlusPlus : '++';
Minus : '-';
MinusMinus : '--';
Star : '*';
Div : '/';
Mod : '%';

And : '&';
Or : '|';
AndAnd : '&&';
OrOr : '||';
Caret : '^';
Not : '!';
Tilde : '~';

Question : '?';
Colon : ':';
Semi : ';';
Comma : ',';

Assign : '=';
StarAssign : '*=';
DivAssign : '/=';
ModAssign : '%=';
PlusAssign : '+=';
MinusAssign : '-=';
AndAssign : '&=';
XorAssign : '^=';
OrAssign : '|=';

Equal : '==';
NotEqual : '!=';

///////////////////
// Scanner Rules //
///////////////////

Identifier
    : IdentifierNondigit
        ( IdentifierNondigit
        | Digit
        )*
;

fragment
IdentifierNondigit
    : Nondigit
    | UniversalCharacterName
;

fragment
Nondigit
    : [a-zA-Z_]
;

fragment
Digit
    : [0-9]
;

fragment
UniversalCharacterName
    : '\\u' HexQuad
    | '\\U' HexQuad HexQuad
;

fragment
HexQuad
    : HexadecimalDigit HexadecimalDigit HexadecimalDigit HexadecimalDigit
;

IntegerConstant
    : DecimalConstant IntegerSuffix?
    | OctalConstant IntegerSuffix?
    | HexadecimalConstant IntegerSuffix?
    | BinaryConstant
;

fragment
BinaryConstant
	: '0' [bB] [0-1]+
;

fragment
DecimalConstant
    : NonzeroDigit Digit*
;

fragment
OctalConstant
    : '0' OctalDigit*
;

fragment
HexadecimalConstant
    : HexadecimalPrefix HexadecimalDigit+
;

fragment
HexadecimalPrefix
    : '0' [xX]
;

fragment
NonzeroDigit
    : [1-9]
;

fragment
OctalDigit
    : [0-7]
;

fragment
HexadecimalDigit
    : [0-9a-fA-F]
;

fragment
IntegerSuffix
    : UnsignedSuffix LongSuffix?
    | UnsignedSuffix LongLongSuffix
    | LongSuffix UnsignedSuffix?
    | LongLongSuffix UnsignedSuffix?
;

fragment
UnsignedSuffix
    : [uU]
;

fragment
LongSuffix
    : [lL]
;

fragment
LongLongSuffix
    : 'll' | 'LL'
;

FloatingConstant
    : DecimalFloatingConstant
    | HexadecimalFloatingConstant
;

fragment
DecimalFloatingConstant
    : FractionalConstant ExponentPart? FloatingSuffix?
    | DigitSequence ExponentPart FloatingSuffix?
;

fragment
HexadecimalFloatingConstant
    : HexadecimalPrefix (HexadecimalFractionalConstant | HexadecimalDigitSequence) BinaryExponentPart FloatingSuffix?
;

fragment
FractionalConstant
    : DigitSequence? '.' DigitSequence
    | DigitSequence '.'
;

fragment
ExponentPart
    : [eE] Sign? DigitSequence
;

fragment
Sign
    : [+-]
;

DigitSequence
    : Digit+
;

fragment
HexadecimalFractionalConstant
    : HexadecimalDigitSequence? '.' HexadecimalDigitSequence
    | HexadecimalDigitSequence '.'
;

fragment
BinaryExponentPart
    : [pP] Sign? DigitSequence
;

fragment
HexadecimalDigitSequence
    : HexadecimalDigit+
;

fragment
FloatingSuffix
    : [flFL]
;

CharacterConstant
    : '\'' CCharSequence '\''
    | 'L\'' CCharSequence '\''
    | 'u\'' CCharSequence '\''
    | 'U\'' CCharSequence '\''
;

fragment
CCharSequence
    : CChar+
;

fragment
CChar
    : ~['\\\r\n]
    | EscapeSequence
;

fragment
EscapeSequence
    : SimpleEscapeSequence
    | OctalEscapeSequence
    | HexadecimalEscapeSequence
    | UniversalCharacterName
;

fragment
SimpleEscapeSequence
    : '\\' ['"?abfnrtv\\]
;

fragment
OctalEscapeSequence
    : '\\' OctalDigit OctalDigit? OctalDigit?
;

fragment
HexadecimalEscapeSequence
    : '\\x' HexadecimalDigit+
;

StringLiteral
    : EncodingPrefix? '"' SCharSequence? '"'
;

fragment
EncodingPrefix
    : 'u8'
    | 'u'
    | 'U'
    | 'L'
;

fragment
SCharSequence
    : SChar+
;

fragment
SChar
    : ~["\\\r\n]
    | EscapeSequence
    | '\\\n'
    | '\\\r\n'
;

Whitespace
    : [ \t]+
    -> skip
;

Newline
    :
    ( '\r' '\n'?
    | '\n'
    )
    -> skip
;

BlockComment
    : '/*' .*? '*/'
    -> skip
;

LineComment
    : '//' ~[\r\n]*
    -> skip
;
