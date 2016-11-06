all: parser lexer
parser: sqlparser.yy
	bison -d -v sqlparser.yy

lexer: sqllexer.l
	flex -s --outfile=sqllexer.cpp  $<