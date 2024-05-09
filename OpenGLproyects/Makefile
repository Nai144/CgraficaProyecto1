CXX= g++
LDFLAGS = -lGL -lglfw -ldl
OBJS = main.o OpenGlShadder.o Circle.o glad/glad.o


TARGET = main

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)