#it's a example for describing makefile
CXX = g++
LIBS = -lpthread
app : Interrupt.o main.o Student.o thread.o
	$(CXX) -o app Interrupt.o main.o Student.o thread.o $(LIBS)

Interrupt.o: Interrupt.cpp
	$(CXX) -c Interrupt.cpp

main.o:main.cpp
	$(CXX) -c main.cpp
		
Student.o: Student.h Student.cpp
	$(CXX) -c Student.cpp

thread.o: thread.cpp
	$(CXX) -c thread.cpp

clean: 
	rm app Interrupt.o main.o Student.o thread.o

.PHONY : all clean
