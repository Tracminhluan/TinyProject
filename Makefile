CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC_DIR = src
BUILD_DIR = build

SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/Vector.cpp \
          $(SRC_DIR)/Matrix.cpp \
          $(SRC_DIR)/LinearSystem.cpp \
          $(SRC_DIR)/PosSymLinSystem.cpp

OBJECTS = $(BUILD_DIR)/main.o \
          $(BUILD_DIR)/Vector.o \
          $(BUILD_DIR)/Matrix.o \
          $(BUILD_DIR)/LinearSystem.o \
          $(BUILD_DIR)/PosSymLinSystem.o

TARGET = $(BUILD_DIR)/myProgram

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Vector.o: $(SRC_DIR)/Vector.cpp $(SRC_DIR)/Vector.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Vector.cpp -o $(BUILD_DIR)/Vector.o

$(BUILD_DIR)/Matrix.o: $(SRC_DIR)/Matrix.cpp $(SRC_DIR)/Matrix.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Matrix.cpp -o $(BUILD_DIR)/Matrix.o

$(BUILD_DIR)/LinearSystem.o: $(SRC_DIR)/LinearSystem.cpp $(SRC_DIR)/LinearSystem.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/LinearSystem.cpp -o $(BUILD_DIR)/LinearSystem.o

$(BUILD_DIR)/PosSymLinSystem.o: $(SRC_DIR)/PosSymLinSystem.cpp $(SRC_DIR)/PosSymLinSystem.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/PosSymLinSystem.cpp -o $(BUILD_DIR)/PosSymLinSystem.o

clean:
	rmdir /S /Q $(BUILD_DIR) 2>nul || rm -rf $(BUILD_DIR)

run: all
	cd $(BUILD_DIR) && myProgram

.PHONY: all clean run
