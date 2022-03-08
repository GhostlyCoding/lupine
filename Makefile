CXX = clang++
CXXFLAGS = -g
LDFLAGS = -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -Iinclude

app: $(wildcard src/*.cpp) $(wildcard include/*.cpp)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -std=c++17 $^ -o $@

clean:
	rm -f src/*.o
