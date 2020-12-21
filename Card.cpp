#include "Card.hpp"

using namespace std;

//default constructor
Card::Card()
{
    playerId = new unsigned;
    discard = new bool;
    *playerId = 0;
    *discard = false;
    value = nullptr;
    suit = nullptr;
}


//overload constructor
Card::Card(char v, char s) : Card()
{
    value = new char;
    suit = new char;

    *value = v;
    *suit = s;
}


//destructor
Card::~Card()
{
    delete playerId;
    delete discard;

    if (value) {
        delete value;
    }

    if (suit) {
        delete suit;
    }

}


//getters
char Card::getValue() const
{
    return *value;
}


char Card::getSuit() const
{
    return *suit;
}


unsigned Card::getPlayerId() const
{
    return *playerId;
}


bool Card::isDiscard() const
{
    return *discard;
}


//setters
void Card::setPlayerId(unsigned p)
{
    *playerId = p;
}


void Card::flipDiscard()
{
    *discard = !*discard;
}
