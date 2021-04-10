# Specify the compiler
GXX=g++ -g -w

# Specifiy the target
all: predictor

# Specify the object files that the target depends on
# Also, specify the object files needed to create the executable
predictor: predictor.o
	$(GXX) predictor.o -o predictor

# Specify how the object files should be created from source files
predictor.o: predictor.cpp
	$(GXX)  -c  predictor.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o *~ core out.txt predictor