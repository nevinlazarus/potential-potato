py_connect4: connect4.cpp monty.cpp main.cpp
	g++ -shared -o connect4_ai.so -fPIC -lpython3.5m -I/usr/include/python3.5m --std=c++11 main.cpp monty.cpp connect4.cpp 

connect4: connect4.cpp monty.cpp
	g++ -o connect4 connect4.cpp monty.cpp -lm --std=c++11 -pthread
