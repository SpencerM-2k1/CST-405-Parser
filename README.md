# CST-405-Lexer
Original Lexer written by Evan Lloyd
Modified by Spencer Meren

## Compile

Flex must be installed in order to compile this program.
Run the following commands in sequence:

	flex lexer.l
	gcc lex.yy.c

## Execution

	./a.out [file-path]

`[file-path]` specifies the path of the source code file to parse. The following sample files are provided:

- `sample1.c`: Source code file with no errors.
- `sample2.c`: Modified version of `sample1.c` with two errors.
