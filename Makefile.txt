CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2 -I.
TARGET = dbms
SRCS = main.cpp MyArray.cpp ForwardList.cpp DoublyList.cpp MyStack.cpp MyQueue.cpp AVLTree.cpp Database.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) data.json

run: $(TARGET)
	./$(TARGET) --file data.json --query "MPUSH arr hello"
