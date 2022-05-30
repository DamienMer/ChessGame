#ifndef DEF_PLAYER_H
#define DEF_PLAYER_H

#include <string>
#include <vector>
#include "Piece.h"
#include "Board.h"

class Player{
    private :
    	static int _count;
    	int _id;
    	std::string _name;
	Board* _b;

	std::vector<Piece*> _alive;
	std::vector<Piece*> _dead;

    public :
    	Player(std::string name, Board* b);

	int getId();
    	std::string getName();
	std::vector<Piece*> getAlive();

    	void setName(std::string name);

	void addPiece_alive(Piece* piece);
	void removePiece_alive(Piece* piece);
	void addPiece_dead(Piece* piece);
	
	void debug_display_alive();
	void debug_display_dead();
};


#endif

