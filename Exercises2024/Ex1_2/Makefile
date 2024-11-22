# Makefile example

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Source files and target
SOURCES = AnalyseData.cxx CustomFunctions.cxx
OBJECTS = $(SOURCES:.cxx=.o)
EXEC = AnalyseData

# Default target
all: $(EXEC)

# Rule to create the executable from object files
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC)

# Rule to create object files from source files
%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove object and executable files
clean:
	rm -f $(OBJECTS) $(EXEC)
