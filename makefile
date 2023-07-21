build:
	g++ -std=c++11  minesweep.cpp -o minesweeper
play:build
	./minesweeper
	
clean:
	rm minesweeper
