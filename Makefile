SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

EXE := $(BIN_DIR)/caskdb-demo
SRC := $(wildcard $(SRC_DIR)/*.cc)
OBJ := $(SRC:$(SRC_DIR)/%.cc=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP
CXXFLAGS := -std=c++20 -Wall
LDFLAGS  := -Llib
LDLIBS   := -lm

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)