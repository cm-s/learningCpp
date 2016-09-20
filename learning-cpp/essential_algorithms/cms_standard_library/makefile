TARGET = test
CXX = g++ -std=c++17

$(TARGET): testing.o cm.std.o
	$(CXX) -o testing.o cm.std.o

testing.o: testing.cpp cm.std.cpp
	$(CXX) -c testing.cpp cm.std.cpp

cm.std.o: cm.std.cpp
	$(CXX) -c cm.std.cpp

clean:
	rm *.o
	rm test
