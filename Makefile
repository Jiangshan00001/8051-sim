SRC_DIR := src
OBJ_DIR := out
INCLUDE_DIR := inc

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(CPP_FILES:.cpp=.o)))

LD_FLAGS := -Bstatic
LD_LIBS := -lncurses
CC_FLAGS := -I $(INCLUDE_DIR) -O3 -g -std=c++11 -Wall

EXE_FILE := 8051-sim

.PHONY: all clean test
all: $(OBJ_DIR)/$(EXE_FILE)

clean:
	rm -rf $(OBJ_DIR)

test: $(OBJ_DIR)/$(EXE_FILE)
	cat ./bin/cmd | ./$(OBJ_DIR)/$(EXE_FILE)

$(OBJ_DIR)/$(EXE_FILE): $(OBJ_FILES)
	@echo "Linking $@"
	@g++ $(LD_FLAGS) -o $@ $^ $(LD_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<"
	@mkdir -p $(OBJ_DIR)
	@g++ $(CC_FLAGS) -c -o $@ $<

CC_FLAGS += -MMD -MP
-include $(OBJ_FILES:.o=.d)
