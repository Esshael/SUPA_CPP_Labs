CC=g++               # Name of compiler
FLAGS=-std=c++20 -w  # Compiler flags (-w suppresses warnings)
TARGET=Test          # Executable name
OBJECTS=Test.o FiniteFunctions.o Distributions.o
LIBS=-I ../../GNUplot/ -lboost_iostreams

# Default target
${TARGET}: ${OBJECTS}
	@echo "Linking..."
	${CC} ${FLAGS} ${OBJECTS} ${LIBS} -o ${TARGET}
	@make clean

# Compile Test.o
Test.o: Test.cxx FiniteFunctions.h Distributions.h
	${CC} ${FLAGS} ${LIBS} -c Test.cxx

# Compile FiniteFunctions.o
FiniteFunctions.o: FiniteFunctions.cxx FiniteFunctions.h
	${CC} ${FLAGS} ${LIBS} -c FiniteFunctions.cxx

# Compile Distributions.o
Distributions.o: Distributions.cxx Distributions.h
	${CC} ${FLAGS} ${LIBS} -c Distributions.cxx

clean:
	rm -f *.o *~

cleantarget:
	rm -f ${TARGET}
