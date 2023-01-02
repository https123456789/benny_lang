# Lexer Tokens

> Note:
> 
> A :x: means that the token is not implemented
> 
> A :heavy_check_mark: means that the token is in the process of being implemented
> 
> A :white_check_mark: means that the token is implemented.

## Literals

- :x: `LIT_NUM`: A numerical literal
- :x: `LIT_STR`: A string literal
- :x: `LIT_TYPENAME`: The name of a type

## Keywords

- :x: `IF`: An `if` keyword
- :x: `ELSE`: An `else` keyword
- :x: `IMPORT`: An `import` keyword
- :x: `EXPORT`: An `export` keyword
- :white_check_mark: `FN`: A `fn` keyword
- :x: `RETURN`: A `return` keyword

## Math

- :x: `ADD`: Addition operation
- :x: `SUB`: Subtraction operation
- :x: `MULT`: Multiplication operation
- :x: `DIV`: Division operation

## Misc

- :x: `WHITESPACE`: Whitespace
- :x: `UNKNOWN`: An unknown token
- :x: `IDENT`: An identifier
- :x: `LBRACE`: A left brace (`{`)
- :x: `RBRACE`: A right brace (`}`)
- :x: `SEMICOLON`: A semicolon (`;`)
- :x: `LPAREN`: A left parenthesis (`(`)
- :x: `RPAREN`: A right parenthesis (`)`)
- :x: `LBRACK`: A left bracket (`[`)
- :x: `RBRACK`: A right bracket (`]`)
- :x: `PRODUCES`: A produces symbol (`<>`)
