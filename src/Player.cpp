#include "Player.h"

Player::Player(std::string name, Board* b){
    _id = _count;
    _count++;
    _name = name;
    _b = b;

}

int Player::getId(){
    return _id;
}

std::string Player::getName(){
    return _name;
}

std::vector<Piece*> Player::getAlive(){
    return _alive;
}

void Player::setName(std::string name){
    _name = name;
}

void Player::addPiece_alive(Piece* piece){
    _alive.push_back(piece);
    _b->setTab(piece->getX(), piece->getY(), piece);
}

void Player::removePiece_alive(Piece* piece){
    int pos = 0;
    for(Piece * temp : _alive){
	if(temp == piece){
	    _alive.erase(_alive.begin() + pos);
	    break;
	}
	pos++;
    }
}

void Player::addPiece_dead(Piece* piece){
    _dead.push_back(piece);
}


void Player::debug_display_alive(){
    for(int i = 0; i < _alive.size(); i++){
	std::cout << _alive[i]->getSprite() << std::endl;
    }
}
void Player::debug_display_dead(){
    for(int i = 0; i < _dead.size(); i++){
	std::cout << _dead[i] << std::endl;
    }
}
