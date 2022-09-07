hepsi:derle calistir	
derle:
	g++ -I ./include -c ./src/WorkersTree.cpp -o ./lib/WorkersTree.o
	g++ -I ./include -c ./src/CompanyTree.cpp -o ./lib/CompanyTree.o
	g++ -I ./include -c ./src/Main.cpp -o ./lib/Main.o
	g++ ./lib/WorkersTree.o ./lib/CompanyTree.o ./lib/Main.o -o ./bin/program
calistir:
	./bin/program
	