#include "Piece.h"
int Piece::_count = 0;

template<typename Base, typename T>

inline bool instanceof(const T*){
    return std::is_base_of<Base, T>::value;
}

//--------------------------------------------------------------------------------------

Entity::Entity(int id, Board* b, int x, int y, char sprite) : _id(id), _b(b), _x(x), _y(y), _sprite(sprite){};

int Entity::getId(){
    return _id;
}

Board* Entity::getBoard(){
    return _b;
}

int Entity::getX(){
    return _x;
}

int Entity::getY(){
    return _y;
}

char Entity::getSprite(){
    return _sprite;
}

void Entity::setX(int x){
	_x = x;
}

void Entity::setY(int y){
    _y = y;
}

//--------------------------------------------------------------------------------------

Empty::Empty(Board* b, int x, int y, char sprite) : Entity(-1, b, x, y, sprite){}

//--------------------------------------------------------------------------------------

Piece::Piece(Board* b, Player* owner, int x, int y, char sprite) : Entity(_count, b, x, y, sprite){
    _count++;
    _owner = owner;
    _count_move = 0;
}

bool Piece::onBoard(int x, int y){
    if(x >= 0 && x < 8){
	if(y >= 0 && y < 8){
	    return true;
	}
    }
    return false;
}

Player* Piece::getOwner(){
    return _owner;
}

int Piece::getCount_move(){
    return _count_move;
}

std::vector<int*> Piece::getMoves(){
    return _moves;
}

void Piece::setMoves(std::vector<int*> moves){
    _moves = moves;
}

void Piece::addPos(std::vector<int*> &res, int x, int y){
	int* var = (int*) malloc(sizeof(int) * 2);
	var[0] = x;
	var[1] = y;
	res.push_back(var);
}

//--------------------------------------------------------------------------------------

Pawn::Pawn(Board* b, Player* owner, int x, int y, char sprite) : Piece(b, owner, x, y, sprite){}


std::vector<int*> Pawn::calculatingMoves(Player* p){

    std::vector<int*> res;

    if(getOwner() == Entity::getBoard()->getCurrent_player()){
	int sens = 2 * (getOwner()->getName() == "black") - 1;
	int a = getX() + 1 * sens;
	int b = getY();

	checkMovement(a, b, res, p);

	if(getCount_move() == 0){
	    a = getX() + 2 * sens;
	    b = getY();
	    checkMovement(a, b, res, p);
	}

	a = getX() + 1 * sens;
	b = getY() + 1;

	checkAttack(a, b, res, p);

	a = getX() + 1 * sens;
	b = getY() - 1;

	checkAttack(a, b, res, p);
    }

    setMoves(res);
    return res;
}

bool Pawn::checkMovement(int x, int y, std::vector<int*> &res, Player* p){
	if(x >= 0 && x < 8){

	    if(getBoard()->isEmpty(x, y)){
		addPos(res, x, y);
	    }

	    else{
	    	Piece* tempp = static_cast<Piece*>(getBoard()->getTab()[x][y]);
	    	if(tempp->getOwner() != p){
			addPos(res, x, y);
		}
	    }
	}

    return true;
}

bool Pawn::checkAttack(int x, int y, std::vector<int*> &res, Player* p){
	if(x >= 0 && x < 8 && y >= 0 && y < 8){

	    if(getBoard()->isEmpty(x, y)){
		return true;
	    }

	    else{
	    	Piece* tempp = static_cast<Piece*>(getBoard()->getTab()[x][y]);
	    	if(tempp->getOwner() != getOwner()){
			addPos(res, x, y);
		}
	    }
	}
	return true;
}

//--------------------------------------------------------------------------------------

Knight::Knight(Board* b, Player* owner, int x, int y, char sprite) : Piece(b, owner, x, y, sprite){}

std::vector<int*> Knight::calculatingMoves(Player* p){
    std::vector<int*> res;

    if(getOwner() == p){
	int a = getX() + 2;
	int b = getY() + 1;

	checkMovement(a, b, res, p);

	a = getX() + 1;
	b = getY() + 2;

	checkMovement(a, b, res, p);
	
	a = getX() - 1;
	b = getY() + 2;

	checkMovement(a, b, res, p);

	a = getX() - 2;
	b = getY() + 1;

	checkMovement(a, b, res, p);

	a = getX() - 2;
	b = getY() - 1;

	checkMovement(a, b, res, p);

	a = getX() - 1;
	b = getY() - 2;

	checkMovement(a, b, res, p);

	a = getX() + 1;
	b = getY() - 2;

	checkMovement(a, b, res, p);

	a = getX() + 2;
	b = getY() - 1;

	checkMovement(a, b, res, p);

    }


    setMoves(res);
    return res;

}


bool Knight::checkMovement(int x, int y, std::vector<int*> &res, Player* p){
	if(x >= 0 && x < 8 && y >= 0 && y < 8){
	    Entity* tempe = getBoard()->getTab()[x][y];

	    if(tempe->getId() == -1){
		addPos(res, x, y);	
	    }

	    else{
	    	Piece* tempp = static_cast<Piece*>(tempe);
	    	if(tempp->getOwner() != p){
			addPos(res, x, y);	
		}
	    }
	}

    return true;
}

//--------------------------------------------------------------------------------------

Bishop::Bishop(Board* b, Player* owner, int x, int y, char sprite) : Piece(b, owner, x, y, sprite){}

std::vector<int*> Bishop::calculatingMoves(Player* p){
    std::vector<int*> res;

    if(getOwner() == p){

	int x = getX();
	int y = getY();

	for(int i = 1; i < 8; i++){
		if(getBoard()->inBoundaries(x+i, y+i)){
		    	if(getBoard()->isEmpty(x+i, y+i)){
				addPos(res, x+i, y+i);
			}
			else if(getBoard()->isEnnemy(x+i, y+i, getOwner())){
				addPos(res, x+i, y+i);
				break;
			}
			else{
			    	break;
			}
		}
	}
	for(int i = 1; i < 8; i++){
		if(getBoard()->inBoundaries(x-i, y-i)){
		    	if(getBoard()->isEmpty(x-i, y-i)){
				addPos(res, x-i, y-i);
			}
			else if(getBoard()->isEnnemy(x-i, y-i, getOwner())){
				addPos(res, x-i, y-i);
				break;
			}
			else{
			    	break;
			}
		}
	}
	for(int i = 1; i < 8; i++){
		if(getBoard()->inBoundaries(x+i, y-i)){
		    	if(getBoard()->isEmpty(x+i, y-i)){
				addPos(res, x+i, y-i);
			}
			else if(getBoard()->isEnnemy(x+i, y-i, getOwner())){
				addPos(res, x+i, y-i);
				break;
			}
			else{
			    	break;
			}
		}
	}
	for(int i = 1; i < 8; i++){
		if(getBoard()->inBoundaries(x-i, y+i)){
		    	if(getBoard()->isEmpty(x-i, y+i)){
				addPos(res, x-i, y+i);
			}
			else if(getBoard()->isEnnemy(x-i, y+i, getOwner())){
				addPos(res, x-i, y+i);
				break;
			}
			else{
			    	break;
			}
		}
	}
    }

    setMoves(res);
    return res;

}

//--------------------------------------------------------------------------------------

Tower::Tower(Board* b, Player* owner, int x, int y, char sprite) : Piece(b, owner, x, y, sprite){}

std::vector<int*> Tower::calculatingMoves(Player* p){
    std::vector<int*> res;

    if(getOwner() == p){

	int x = getX();
	int y = getY();

	for(int i = 1; i < 8; i++){
		if(getBoard()->inBoundaries(x+i, y)){
		    	if(getBoard()->isEmpty(x+i, y)){
				addPos(res, x+i, y);
			}
			else if(getBoard()->isEnnemy(x+i, y, getOwner())){
				addPos(res, x+i, y);
				break;
			}
			else{
			    	break;
			}
		}
	}
	for(int i = 1; i < 8; i++){
		if(getBoard()->inBoundaries(x-i, y)){
		    	if(getBoard()->isEmpty(x-i, y)){
				addPos(res, x-i, y);
			}
			else if(getBoard()->isEnnemy(x-i, y, getOwner())){
				addPos(res, x-i, y);
				break;
			}
			else{
			    	break;
			}
		}
	}
	for(int i = 1; i < 8; i++){
		if(getBoard()->inBoundaries(x, y-i)){
		    	if(getBoard()->isEmpty(x, y-i)){
				addPos(res, x, y-i);
			}
			else if(getBoard()->isEnnemy(x, y-i, getOwner())){
				addPos(res, x, y-i);
				break;
			}
			else{
			    	break;
			}
		}
	}
	for(int i = 1; i < 8; i++){
		if(getBoard()->inBoundaries(x, y+i)){
		    	if(getBoard()->isEmpty(x, y+i)){
				addPos(res, x, y+i);
			}
			else if(getBoard()->isEnnemy(x, y+i, getOwner())){
				addPos(res, x, y+i);
				break;
			}
			else{
			    	break;
			}
		}
	}
    }

    setMoves(res);
    return res;
}

//--------------------------------------------------------------------------------------

Queen::Queen(Board* b, Player* owner, int x, int y, char sprite) : Piece(b, owner, x, y, sprite){}

std::vector<int*> Queen::calculatingMoves(Player* p){
    std::vector<int*> res;

    if(getOwner() == p){

	int x = getX();
	int y = getY();

	for(int i = 1; i < 8; i++){
		if(getBoard()->inBoundaries(x+i, y)){
		    	if(getBoard()->isEmpty(x+i, y)){
				addPos(res, x+i, y);
			}
			else if(getBoard()->isEnnemy(x+i, y, getOwner())){
				addPos(res, x+i, y);
				break;
			}
			else{
			    	break;
			}
		}
	}
	for(int i = 1; i < 8; i++){
		if(getBoard()->inBoundaries(x-i, y)){
		    	if(getBoard()->isEmpty(x-i, y)){
				addPos(res, x-i, y);
			}
			else if(getBoard()->isEnnemy(x-i, y, getOwner())){
				addPos(res, x-i, y);
				break;
			}
			else{
			    	break;
			}
		}
	}
	for(int i = 1; i < 8; i++){
		if(getBoard()->inBoundaries(x, y-i)){
		    	if(getBoard()->isEmpty(x, y-i)){
				addPos(res, x, y-i);
			}
			else if(getBoard()->isEnnemy(x, y-i, getOwner())){
				addPos(res, x, y-i);
				break;
			}
			else{
			    	break;
			}
		}
	}
	for(int i = 1; i < 8; i++){
		if(getBoard()->inBoundaries(x, y+i)){
		    	if(getBoard()->isEmpty(x, y+i)){
				addPos(res, x, y+i);
			}
			else if(getBoard()->isEnnemy(x, y+i, getOwner())){
				addPos(res, x, y+i);
				break;
			}
			else{
			    	break;
			}
		}
	}
	for(int i = 1; i < 8; i++){
		if(getBoard()->inBoundaries(x+i, y+i)){
		    	if(getBoard()->isEmpty(x+i, y+i)){
				addPos(res, x+i, y+i);
			}
			else if(getBoard()->isEnnemy(x+i, y+i, getOwner())){
				addPos(res, x+i, y+i);
				break;
			}
			else{
			    	break;
			}
		}
	}
	for(int i = 1; i < 8; i++){
		if(getBoard()->inBoundaries(x-i, y-i)){
		    	if(getBoard()->isEmpty(x-i, y-i)){
				addPos(res, x-i, y-i);
			}
			else if(getBoard()->isEnnemy(x-i, y-i, getOwner())){
				addPos(res, x-i, y-i);
				break;
			}
			else{
			    	break;
			}
		}
	}
	for(int i = 1; i < 8; i++){
		if(getBoard()->inBoundaries(x+i, y-i)){
		    	if(getBoard()->isEmpty(x+i, y-i)){
				addPos(res, x+i, y-i);
			}
			else if(getBoard()->isEnnemy(x+i, y-i, getOwner())){
				addPos(res, x+i, y-i);
				break;
			}
			else{
			    	break;
			}
		}
	}
	for(int i = 1; i < 8; i++){
		if(getBoard()->inBoundaries(x-i, y+i)){
		    	if(getBoard()->isEmpty(x-i, y+i)){
				addPos(res, x-i, y+i);
			}
			else if(getBoard()->isEnnemy(x-i, y+i, getOwner())){
				addPos(res, x-i, y+i);
				break;
			}
			else{
			    	break;
			}
		}
	}
    }

    setMoves(res);
    return res;

}

//--------------------------------------------------------------------------------------

King::King(Board* b, Player* owner, int x, int y, char sprite) : Piece(b, owner, x, y, sprite){}

std::vector<int*> King::calculatingMoves(Player* p){
    std::vector<int*> res;

    int x = getX() + 1;
    int y = getY();

    checkMovement(x, y, res, p);

    x = getX() + 1;
    y = getY() + 1;

    checkMovement(x, y, res, p);

    x = getX();
    y = getY() + 1;

    checkMovement(x, y, res, p);

    x = getX() - 1;
    y = getY() + 1;

    checkMovement(x, y, res, p);

    x = getX() - 1;
    y = getY();

    checkMovement(x, y, res, p);

    x = getX() - 1;
    y = getY() - 1;

    checkMovement(x, y, res, p);

    x = getX();
    y = getY() - 1;

    checkMovement(x, y, res, p);

    x = getX() + 1;
    y = getY() - 1;

    checkMovement(x, y, res, p);

    setMoves(res);
    return res;
}

bool King::checkMovement(int x, int y, std::vector<int*> &res, Player* p){
    	if(getBoard()->inBoundaries(x, y)){

	    if(getBoard()->isEmpty(x, y)){
		addPos(res, x, y);	
	    }

	    else{
	    	if(getBoard()->isEnnemy(x, y, p)){
			addPos(res, x, y);	
		}
	    }
	}

    return true;
}
