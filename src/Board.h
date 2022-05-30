#ifndef DEF_BOARD_H
#define DEF_BOARD_H

#include <vector>

class Player;

class Piece;

class Entity;

class Board{
	private :
		int _width;
		int _height;
		Entity*** _tab;
		Player* _current_player;
		std::vector<Player*> _players;

	public : 
		Board();
		int getWidth();
		int getHeight();
		Entity*** getTab();
		Player* getCurrent_player();
		std::vector<Player*> getPlayers();

		void setCurrent_player(Player* p);

		void addPiece(Piece* p);
		void removePiece(int x, int y);
		Piece* selectPiece(int x, int y);
		void movePiece(Piece *p, int x, int y);

		void setTab(int x, int y, Entity* ent);

		void addPlayer(Player* player);

		void displayTab();
		bool isEmpty(int x, int y);
		bool isEnnemy(int x, int y, Player* owner);
		bool inBoundaries(int x, int y);

};

#endif
