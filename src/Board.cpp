#include <stdlib.h>
#include <iostream>
#include "Board.h"
#include "Piece.h"

Board::Board(){
    _width = 8;
    _height = 8;
    _tab = (Entity***) malloc(_height * sizeof(Entity**));
    for(int i = 0; i < _height; i++){
	_tab[i] = (Entity**) malloc(_width * sizeof(Entity*));
	for(int j = 0; j < _width; j++){
		_tab[i][j] = new Empty(this, i, j, '|');
	}
    }
}


int Board::getWidth(){
    return _width;
}

int Board::getHeight(){
    return _height;
}

Entity*** Board::getTab(){
    return _tab;
}

Player* Board::getCurrent_player(){
    return _current_player;
}

std::vector<Player*> Board::getPlayers(){
    return _players;
}

void Board::setCurrent_player(Player* p){
    _current_player = p;
}


void Board::addPiece(Piece* p){
    _tab[p->getX()][p->getY()] = p;
    p->getOwner()->addPiece_alive(p);
    return;	
}

void Board::removePiece(int x, int y){
	if(isEmpty(x, y)){
	    std::cout << "cannot remove empty case" << std::endl;
	    return;
	}
	else{
	    Piece* p = static_cast<Piece*>(selectPiece(x, y));
	    Player* o = p->getOwner();

	    o->removePiece_alive(p);
	    o->addPiece_dead(p);
	    _tab[x][y] = new Empty(this, p->getX(), p->getY(), '|');

	    //for(int i = 0; i < p->getOwner()->getAlive().size(); i++){
	    //    //TODO
	    //    if(p->getId() == o->getAlive()[i]->getId()){
	    //        o->setAlive
	    //}

	}

}

Piece* Board::selectPiece(int x, int y){
    if(!isEmpty(x, y)){
    	Piece* temp = static_cast<Piece*>(getTab()[x][y]);

    	if(temp->getOwner() == _current_player){
	    	std::cout << "piece correct" << std::endl;
		return temp;
    	}
    	std::cout << "veuillez déplacer vos pièces" << std::endl;
    	return NULL;
    }
    std::cout << "impossible de sélectionner une case vide" << std::endl;
    return NULL;
}

void Board::movePiece(Piece* p, int x, int y){
    	std::vector<int*> m = p->getMoves();
	for(int i = 0; i < m.size(); i ++){
	    if(m[i][0] == x){
	    	if(m[i][1] == y){
		    std::cout << "tu peux déplacer ça" << std::endl;
		    if(isEmpty(x, y)){
			setTab(x, y, p);
			_tab[p->getX()][p->getY()] = new Empty(this, p->getX(), p->getY(), '_');
			p->setX(x);
			p->setY(y);
			std::cout << "déplacé" << std::endl;
		    }
		    else{
			removePiece(x, y);
			setTab(x, y, p);
			p->setX(x);
			p->setY(y);
			std::cout << "mangé" << std::endl;
		    }
		    break;
		}
	    }
	}
}

void Board::setTab(int x, int y, Entity* ent){
    _tab[x][y] = ent;
}

void Board::addPlayer(Player* player){
    _players.push_back(player);

    std::cout << "done" << std::endl;
    return;
}


void Board::displayTab(){
    for(int i = 0; i < _height; i++){
	for(int j = 0; j < _width; j++){
	    std::cout << _tab[i][j]->getSprite() << "  ";
	}
    std::cout << std::endl;
    }
}


bool Board::isEmpty(int x, int y){
    if(_tab[x][y]->getId() == -1){
	return true;
    }
    return false;
}

bool Board::isEnnemy(int x, int y, Player* owner){
    	Piece* tempp = static_cast<Piece*>(getTab()[x][y]);
	if(tempp->getOwner() != owner){
	    return true;
	}
	return false;
}

bool Board::inBoundaries(int x, int y){
    return (x >= 0 && x < _height && y >= 0 && y < _width);
}
