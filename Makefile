MAKEFLAGS += --silent

SRC_PATH=src
INCLUDE_PATH=include
OBJ_PATH=obj

CC=g++
CC_FLAGS_GENERIC=-Wall -std=c++2a
CC_FLAGS_OBJ=-I $(INCLUDE_PATH) -D COLLISION_HELPERS
CC_FLAGS_EXEC=-lsfml-graphics -lsfml-window -lsfml-system

SRC=$(wildcard $(SRC_PATH)/*.cpp)
OBJ=$(patsubst $(SRC_PATH)/%.cpp,$(OBJ_PATH)/%.o,$(SRC))

EXEC=app.out

all: $(EXEC)

clean:
	@printf "cleaning..."
	rm -f $(OBJ_PATH)/*.o
	rm -f $(EXEC)
	@printf " finished\n"

run: all
	./$(EXEC)

$(EXEC): $(OBJ)
	@printf "building executable '$(EXEC)'"
	$(CC) $(OBJ) $(CC_FLAGS_GENERIC) $(CC_FLAGS_EXEC) -o $(EXEC)
	@printf " ok\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(INCLUDE_PATH)/%.h
	@printf "building object file '$@'"
	$(CC) $(CC_FLAGS_GENERIC) $(CC_FLAGS_OBJ) -c $< -o $@
	@printf " ok\n"

$(OBJ_PATH)/main.o: $(SRC_PATH)/main.cpp
	@printf "building object file '$@'"
	$(CC) $(CC_FLAGS_GENERIC) $(CC_FLAGS_OBJ) -c $< -o $@
	@printf " ok\n"
