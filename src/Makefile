CC= g++
CFLAGS= -Wall -O0 -std=c++17
LDFLAGS=
EXEC= executable

all : $(EXEC)

$(EXEC) : main.o Board.o Player.o Piece.o
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ 

clean :
	rm *.o $(EXEC)
