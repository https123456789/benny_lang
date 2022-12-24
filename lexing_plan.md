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
	"ast_version": "0.0.1",
	"lang_version": "0.0.1",
	"entrypoint": "global.main",
	"exit_fn": "_special.exit",
	"scopes": {
		"_special": {
			"s_type": "module",
			"exit": {
				"s_type": "PROG_INTERNAL_FN",
				"ret_type": "t_never",
				"parameters": [
					{
						"ident": "code",
						"type": "int",
						"default": {
							"type": "LIT_NUM",
							"value": 0
						}
					}
				],
				"internal_sector": "0"
			}
		},
		"main": {
			"s_type": "FN",
			"ret_type": "int",
			"parameters": [],
			"instructions": [
				{
					"type": "RETURN",
					"value": {
						"type": "LIT_NUM",
						"value": 0
					}
				}
			]
		}
	},
	"expansions": [
		{
			"type": "lit",
			"on": "CALL",
			"from": "exit",
			"to": "_special.exit"
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
	"ast_version": "0.0.1",
	"lang_version": "0.0.1",
	"entrypoint": "global.main",
	"scopes": {
		"_special": {
			"s_type": "module",
			"exit": {
				"s_type": "PROG_INTERNAL_FN",
				"ret_type": "t_never",
				"parameters": [
					{
						"ident": "code",
						"type": "int",
						"default": {
							"type": "LIT_NUM",
							"value": 0
						}
					}
				],
				"internal_sector": "0"
			}
		},
		"main": {
			"s_type": "FN",
			"ret_type": "int",
			"parameters": [],
			"instructions": [
				{
					"type": "CONSTRUCT",
					"modifiers": {
						"type": "var"
					},
					"value": {
						"type": "int",
						"name": "result"
					}
				},
				{
					"type": "CALL",
					"modifiers": {},
					"value": {
						"name": "calculate",
						"args": [
							{
								"type": "LIT_NUM",
								"value": 5
							},
							{
								"type": "LIT_NUM",
								"value": 5
							}
						],
						"tmp_assign": "___tmp_assign_0"
					}
				},
				{
					"type": "ASSIGN",
					"value": {
						"source": "___tmp_assign_0",
						"dest": "result"
					}
				},
				{
					"type": "RETURN",
					"value": {
						"type": "IDENT",
						"value": "result"
					}
				}
			]
		},
		"calculate": {
			"s_type": "FN",
			"ret_type": "int",
			"parameters": [
				{
					"ident": "num1",
					"type": "int",
					"default": null
				},
				{
					"ident": "num2",
					"type": "int",
					"default": null
				}
			],
			"instructions": [
				{
					"type": "ADD",
					"value": {
						"op1": {
							"type": "ident",
							"value": "num1"
						},
						"op2": {
							"type": "ident",
							"value": "num2"
						}
					},
					"tmp_assign": "___tmp_assign_1"
				},
				{
					"type": "RETURN",
					"value": {
						"type": "ident",
						"value": "___tmp_assign_1"
					}
				}
			]
		}
	},
	"expansions": [
		{
			"type": "lit",
			"on": "CALL",
			"from": "exit",
			"to": "_special.exit"
		}
	]
}
```
