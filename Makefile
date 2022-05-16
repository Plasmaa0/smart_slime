# MAKEFLAGS += --silent

SRC_PATH=src
INCLUDE_PATH=include
OBJ_PATH=obj

CC=g++
CC_FLAGS_GENERIC=-Wall -std=c++20
CC_FLAGS_OBJ=-I /usr/local/include -I $(INCLUDE_PATH)
CC_FLAGS_EXEC=-L /usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system

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
	export LD_LIBRARY_PATH=/usr/local/lib && ./$(EXEC)

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