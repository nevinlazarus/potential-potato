py_connect4: connect4.cpp monty.cpp main.cpp alphabeta.cpp
	g++ -shared -o connect4_ai.so -fPIC -lpython3.5m -I/usr/include/python3.5m --std=c++11 main.cpp monty.cpp alphabeta.cpp connect4.cpp

connect4: connect4.cpp monty.cpp alphabeta.cpp
	g++ -o connect4 connect4.cpp monty.cpp alphabeta.cpp -lm --std=c++11 -pthread
