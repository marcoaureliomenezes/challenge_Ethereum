# challenge_Ethereum
Challenge proposed by Ethereum
Software where the user can parse and evaluate arithmetic expressions.
Parsing and evaluating are two independent steps that are separated
by a data structure, the abstract syntax tree (AST).

Arithmetic expressions consist of decimal integers (to simplify,
only numbers from 0 to 9 are allowed as literals, i.e. neither
multi-digit nor fractional numbers are allowed as literals).
combined using the binary operators +, *, /, - and parentheses
and should respect the usual precedence relations.

Since tokens consist of single characters only, the parser
can be implemented without a tokenizer. Furthermore, a simple
top-down parser should be sufficient, implementing the shunting-yard
algorithm is not required.

The program detects invalid input and reports the respective error.

Unit tests were used (Google test) in other to test different inputs.
