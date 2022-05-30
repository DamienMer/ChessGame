#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Piece.h"

int Player::_count = 0;
//int Piece::_count = 0;

template<typename Base, typename T>

inline bool instanceof(const T* ptr){
    return static_cast<const Base*>(ptr) != nullptr;
}


void debug_display(Board* b, std::vector<int*> moves){
	for(int i = 0; i < moves.size(); i++){
	    b->setTab(moves[i][0], moves[i][1], new Empty(b, moves[i][0], moves[i][1], 'x'));
	}
    	for(int i = 0; i < moves.size(); i++){
    	    std::cout << moves[i][0] << ", " << moves[i][1] << std::endl;
    	}
	b->displayTab();
}

int main(){
    Board* b = new Board();

    Player* white = new Player("white", b);
    Player* black = new Player("black", b);

    b->addPlayer(white);
    b->addPlayer(black);

    b->setCurrent_player(white);

    

    Piece* pw1 = new Pawn(b, white, 6, 4, 'p');
    Piece* cb1 = new Knight(b, black, 5, 3, 'c');
    Piece* bw1 = new Bishop(b, white, 2, 2, 'b');
    Piece* kw1 = new King(b, white, 5, 5, 'K');
    Piece* qw1 = new Queen(b, white, 3, 3, 'Q');


    b->addPiece(pw1);
    b->addPiece(cb1);
    b->addPiece(bw1);
    b->addPiece(kw1);
    b->addPiece(qw1);

    b->displayTab();

    Piece* select = b->selectPiece(3, 3);
    std::cout << "selected val : " << select->getId() << std::endl;

    select->calculatingMoves(b->getCurrent_player());
    debug_display(b, select->getMoves());

    b->movePiece(select, 6, 0);
    b->displayTab();
    select = b->selectPiece(6, 0);
    select->calculatingMoves(b->getCurrent_player());
    debug_display(b, select->getMoves());
    

    //Piece* select = b->selectPiece(2, 3);
    //std::vector<int*> moves = select->calculatingMoves(b->getCurrent_player());


    //std::cout << "valeur de calcul : " << moves.size() << std::endl;




    return 0;
}
