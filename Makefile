MAKEFLAGS += --silent

CC=g++
CC_FLAGS_GENERIC=-Wall -std=c++20
CC_FLAGS_OBJ=-I /usr/local/include
CC_FLAGS_EXEC=-L /usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system


SRC_PATH=src
OBJ_PATH=obj

SRC=$(wildcard $(SRC_PATH)/*.cpp)
OBJ=$(patsubst $(SRC_PATH)/%.cpp,$(OBJ_PATH)/%.o,$(SRC))

EXEC=app

all: $(EXEC)

clean:
	@echo cleaning...
	rm $(OBJ_PATH)/*.o
	rm $(EXEC)
	@echo finished cleaning

run: all
	export LD_LIBRARY_PATH=/usr/local/lib && ./$(EXEC)

$(EXEC): $(OBJ)
	@echo "building executable '$(EXEC)'"
	$(CC) $(OBJ) $(CC_FLAGS_GENERIC) $(CC_FLAGS_EXEC) -o $(EXEC)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	@echo "building object file '$@'"
	$(CC) $(CC_FLAGS_GENERIC) $(CC_FLAGS_OBJ) -c $^ -o $@