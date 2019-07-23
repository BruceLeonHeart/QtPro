#it's a example for describing makefile
app : Interrupt.o main.o Student.o thread.o
	cc -o app Interrupt.o main.o Student.o thread.o

Interrupt.o: Interrupt.cpp
	cc -c Interrupt.cpp

main.o:main.cpp
	cc -c main.cpp
		
Student.o: Student.h Student.cpp
	cc -c Student.cpp

thread.o: thread.cpp
	cc -c thread.cpp

clean: rm app Interrupt.o main.o Student.o thread.o
  
