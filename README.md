calc
====

**this is a project with the goal of learning compiler design theory and not intended for efficient use as a calculator**

reader
------

generic code for reading characters from an input buffer.

to port new input, you only need to write `peek`, `next`, and `isEOF` methods.

input support: 
- [x] file
- [x] interactive stdio

lexer
-----

hand written state machine lexer. 

- ascii converted to input enum `Q` to save space (our language only needs to accept a few characters)
- implemented in a somewhat hacky way so might be kinda difficult to expand. make sure to change `NSTATES`, `NINPUT` and `TOKEN_NAME` when expanding.

parser
------

hand written recursive descent LL parser.

- at the consequence of writing a simple LL parser, I needed to complicate the grammar a little in order to remove ambiguity and left recursion
