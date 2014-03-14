CC = gcc
BIN = ./bin/
INC = ./include/
OBJ = ./obj/
SRC = ./src/
CFLAGS = -Wall -W -g -ansi -pedantic
LDFLAGS = -L/usr/X11R6/lib -lX11 -lXext -lm

all: $(BIN)zombie-main

$(BIN)zombie-main: $(OBJ)zombie-score.o $(OBJ)zombie-algorithm.o $(OBJ)zombie-main.o $(OBJ)zombie-user.o $(OBJ)zombie-graphics.o $(OBJ)zombie-events.o $(OBJ)ez-draw.o $(OBJ)ez-image.o $(OBJ)stb_image.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ)zombie-score.o: $(SRC)zombie-score.c
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJ)zombie-algorithm.o: $(SRC)zombie-algorithm.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)zombie-main.o: $(SRC)zombie-main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)zombie-user.o: $(SRC)zombie-user.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)zombie-graphics.o: $(SRC)zombie-graphics.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)zombie-events.o: $(SRC)zombie-events.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)ez-draw.o: $(SRC)ez-draw.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)ez-image.o: $(SRC)ez-image.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)stb_image.o: $(SRC)stb_image.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJ)*.o $(BIN)zombie-main
