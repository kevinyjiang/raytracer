CC = g++

CFLAGS = -std=c++11 

TARGET = main

rt: 
	$(CC) $(CFLAGS) -o rt main.cpp

clean:
	$(RM) rt
	
image:
	./rt > i.ppm
