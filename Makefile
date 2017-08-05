connect4: connect4.cpp monty.cpp
	g++ -o connect4 connect4.cpp monty.cpp -lm --std=c++11 -pthread
