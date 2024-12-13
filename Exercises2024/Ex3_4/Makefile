CC = g++
FLAGS = -std=c++20 -w
TARGET = Test
OBJECTS = Test.o FiniteFunctions.o Distributions.o
LIBS = -I ../../GNUplot/ -lboost_iostreams

${TARGET}: ${OBJECTS}
	${CC} ${FLAGS} ${OBJECTS} ${LIBS} -o ${TARGET}

Test.o: Test.cxx FiniteFunctions.h Distributions.h
	${CC} ${FLAGS} ${LIBS} -c Test.cxx

FiniteFunctions.o: FiniteFunctions.cxx FiniteFunctions.h
	${CC} ${FLAGS} ${LIBS} -c FiniteFunctions.cxx

Distributions.o: Distributions.cxx Distributions.h
	${CC} ${FLAGS} ${LIBS} -c Distributions.cxx

clean:
	rm -f *.o *~
