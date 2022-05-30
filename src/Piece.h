#ifndef DEF_PIECE_H
#define DEF_PIECE_H

#include "Board.h"
#include "Player.h"
#include <iostream>

class Player;

//--------------------------------------------------------------------------------------

class Entity{
    private:
    	int _id;
    	Board* _b;
	int _x;
	int _y;
	char _sprite;
    public:
    	Entity(int id, Board* b, int x, int y, char sprite);
	int getId();
	Board* getBoard();
	int getX();
	int getY();
	char getSprite();
	void setX(int x);
	void setY(int y);
};

//--------------------------------------------------------------------------------------

class Empty : public Entity{
    	private:
    	public:
		Empty(Board* b, int x, int y, char sprite);
};
	
//--------------------------------------------------------------------------------------

class Piece : public Entity{
    private:
    	int _id;
	int static _count;
	Player* _owner;
	int _count_move;
	std::vector<int*> _moves;

    public:
    	Piece(Board* b, Player* owner, int x, int y, char sprite);
	Player* getOwner();
	int getCount_move();
	std::vector<int*> getMoves();
	void setMoves(std::vector<int*> moves);

	bool onBoard(int x, int y);
	virtual std::vector<int*> calculatingMoves(Player* p) = 0;
	void addPos(std::vector<int*> &res, int x, int y);	
};

//--------------------------------------------------------------------------------------

class Pawn : public Piece{
    	private:
	public:
		Pawn(Board* b, Player* owner, int x, int y, char sprite);
		std::vector<int*> calculatingMoves(Player* p);
		bool checkMovement(int x, int y, std::vector<int*> &res, Player* p);
		bool checkAttack(int x, int y, std::vector<int*> &res, Player* p);
};

class Knight : public Piece{
	public:
		Knight(Board* b, Player* owner, int x, int y, char sprite);
		std::vector<int*> calculatingMoves(Player* p);
		bool checkMovement(int x, int y, std::vector<int*> &res, Player* p);
};

class Bishop : public Piece{
	public:
      		Bishop(Board* b, Player* owner, int x, int y, char sprite);
      		std::vector<int*> calculatingMoves(Player* p);
};

class Tower : public Piece{
	public:
      		Tower(Board* b, Player* owner, int x, int y, char sprite);
      		std::vector<int*> calculatingMoves(Player* p);
};

class Queen : public Piece{
	public:
      		Queen(Board* b, Player* owner, int x, int y, char sprite);
      		std::vector<int*> calculatingMoves(Player* p);
};

class King : public Piece{
	public:
		King(Board* b, Player* owner, int x, int y, char sprite);
      		std::vector<int*> calculatingMoves(Player* p);
		bool checkMovement(int x, int y, std::vector<int*> &res, Player* p);
};

#endif
