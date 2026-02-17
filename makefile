# makefile for modular code compilation and execution.
# Compiler
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Detect OS and set appropriate remove command
ifeq ($(OS),Windows_NT)
    RM = del /Q
else
    RM = rm -f
endif

# Executable name
TARGET = cvault

# Source files
SRCS = main.cpp cmd.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Build target
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build (clear .o files)
clean:
	$(RM) *.o $(TARGET)