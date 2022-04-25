# Tl13-Compiler
1. To generate bison files: `bison -d bison.y`
2. To generate flex files: `flex lex.l`
3. To compile: `gcc lex.yy.c bison.tab.c gencode.c symbol.c -lfl`
4. To run, where out.c is a file that does not have to exist: `./a.out <input.txt> out.c`
5. To see if c code was properly generated: `gcc out.c`
