CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2

TARGET = slm
SOURCES = src/main.cpp src/LanguageModel.cpp src/TextGenerator.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean