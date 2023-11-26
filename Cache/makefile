standart_c++ = -std=c++11
#debug = -DDEBUG
#tests = -DTESTS

LFU: main.cpp
	g++ main.cpp $(standart_c++) -DLFU_CACHE $(debug) $(tests) -o bin/LFU

LRU: main.cpp
	g++ main.cpp $(standart_c++) -DLRU_CACHE $(debug) $(tests) -o bin/LRU