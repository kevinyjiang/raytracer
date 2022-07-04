CC = g++

CFLAGS = -std=c++11 

# The build target 
TARGET = main

rt: 
	$(CC) $(CFLAGS) -o rt main.cpp

clean:
	$(RM) rt
	$(RM) *.ppm
	
image:
	./rt > i.ppm
