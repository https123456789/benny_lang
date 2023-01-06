# Lexing Plan

## Simple

Input:

```
fn main() <> int {
	return 0;
}
```

Tokens:

```
[
	FN,
	IDENT(main),
	LPAREN,
	RPAREN,
	PRODUCES,
	LIT_TYPENAME(int),
	LBRACE,
	RETURN
	LIT_NUM(0),
	SEMICOLON,
	RBRACE
]
```

AST:

```json
{
    "type": "Program",
    "ast_version": 0,
    "nodes": [
        {
            "type": "Fn",
            "name": "_int_main",
            "ret_type": "int",
            "args": [],
            "nodes": [
                {
                    "type": "Return",
                    "value": {
                        "type": "LitNum",
                        "value": 0
                    }
                }
            ]
        }
    ]
}
```

## Multiple Functions

Input:

```
fn main() <> int {
	int result = calculate(5, 5);
	return result;
}

fn calculate(num1: int, num2: int) <> int {
	return num1 + num2;
}
```

Tokens:

```
[
	FN,
	IDENT(main),
	LPAREN,
	RPAREN,
	PRODUCES,
	LIT_TYPENAME(int),
	LBRACE,
	LIT_TYPENAME(int),
	IDENT(result),
	ASSIGNMENT,
	IDENT(calculate),
	LPAREN,
	RPAREN,
	SEMICOLON,
	RBRACE,
	FN,
	IDENT(calculate),
	LPAREN,
	IDENT(num1),
	COLON,
	LIT_TYPENAME(int),
	COMMA,
	IDENT(num2),
	COLON,
	LIT_TYPENAME(int),
	RPAREN,
	PRODUCES
	LIT_TYPENAME(int),
	RETURN,
	IDENT(num1),
	ADD,
	IDENT(num2),
	SEMICOLON,
	RBRACE
]
```

AST:

```json
{
    "type": "Program",
    "ast_version": 0,
    "nodes": [
        {
            "type": "Fn",
            "name": "_int_main",
            "ret_type": "int",
            "args": [],
            "nodes": [
                {
                    "type": "VarConstruct",
                    "name": "_int_main_vars_result",
                    "var_type": "int",
                    "init": {
                        "type": "FnCall",
                        "res_format": "immediate",
                        "name": "_int_int_int_calculate",
                        "args": [
                            {
                                "type": "LitNum",
                                "value": 5
                            },
                            {
                                "type": "LitNum",
                                "value": 5
                            }
                        ]
                    }
                },
                {
                    "type": "Return",
                    "value": {
                        "type": "Var",
                        "name": "_int_main_vars_result"
                    }
                }
            ]
        },
        {
            "type": "Fn",
            "name": "_int_int_int_calculate",
            "ret_type": "int",
            "args": [
                {
                    "name": "_int_int_int_calculate_vars_num1",
                    "type": "int"
                },
                {
                    "name": "_int_int_int_calculate_vars_num2",
                    "type": "int"
                }
            ],
            "nodes": [
                {
                    "type": "MathOp",
                    "math_op": "add",
                    "left": {
                        "type": "Var",
                        "name": "_int_int_int_calculate_vars_num1"
                    },
                    "right": {
                        "type": "Var",
                        "name": "_int_int_int_calculate_vars_num2"
                    },
                    "name": "_int_int_int_calculate_tempvars_0"
                },
                {
                    "type": "Return",
                    "value": {
                        "type": "Var",
                        "name": "_int_int_int_calculate_tempvars_0"
                    }
                }
            ]
        }
    ]
}
```
