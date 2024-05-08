CXX= g++
CXXFLAGS = -O3 -Wall -Wextra -std=c++14
LDFLAGS = -lGL -lglfw -ldl
OBJS = main.o glad/glad.o


TARGET = main

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)