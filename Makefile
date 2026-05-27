CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinc
LDFLAGS  = -lncurses

SRC_DIR  = src
INC_DIR  = inc
BUILD_DIR = build

SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/cpu_monitor.cpp \
       $(SRC_DIR)/mem_monitor.cpp \
       $(SRC_DIR)/proc_monitor.cpp

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

TARGET = system_monitor

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
