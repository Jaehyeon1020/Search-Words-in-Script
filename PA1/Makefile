TARGET=pa1
CXX=gcc
OBJECTS=Main.o Functions.o

$(TARGET) : $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)

Main.o : Main.c
	$(CXX) -c Main.c

Functions.o : Functions.c

clean:
	rm *.o pa1