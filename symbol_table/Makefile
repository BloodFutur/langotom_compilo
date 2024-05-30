all: c

c.tab.c c.tab.h: c.y
	bison -Wconflicts-sr -Wcounterexamples -t -v -d c.y

lex.yy.c: c.l c.tab.h
	flex c.l

c: lex.yy.c c.tab.c c.tab.h
	gcc -o c c.tab.c symbol_table.c instructions_table.c functions_table.c asm.c lex.yy.c -lfl

clean:
	rm c c.tab.c lex.yy.c c.tab.h c.output

test: all
	cat grammartest.c | ./c