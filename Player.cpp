#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Card.hpp"
#include "Player.hpp"

//default constructor
Player::Player()
{
    name = nullptr;

    // init score to 0
    score = new unsigned(0);

    // generate random ID
    srand(time(NULL));
    unsigned lb = 1000;
    unsigned ub = 9999;

    /*
     * rand() gives a number between 0 and RANDMAX.
     * To get a number between lb and ub, we need to take modulus of the random number
     * with (ub -lb + 1) (i.e. random_number % (ub -lb + 1)); and add lb to the result.
     */
    id = new unsigned ( lb + ( rand() % ( ub - lb + 1 ) ) );
}


//overload constructor
Player::Player(string n) : Player()
{
    name = new string(n);
}


//destructor
Player::~Player()
{
    delete score;
    delete id;

    if (name) {
        delete name;
    }

    score = nullptr;
    id = nullptr;
    name = nullptr;
}


//getters
unsigned Player::getId() const
{
    return *id;
}


string Player::getName() const
{
    return *name;
}


unsigned Player::getScore() const
{
    return *score;
}


//functions
void Player::updateScore()
{
    *score = *score + 1;
}


/**
 * Allow the player to ask which card value they want.
 */
char Player::ask(Card* deck[], const unsigned DECK_SIZE) const
{
    char val;
    
    do {
        cout << *name << ", which card value do you want to ask for? ";
        cin >> val;
    } while ( !check(deck, DECK_SIZE, val) );

    return val;
}


/**
 * Determine whether the given value parameter is for a card that is currently
 * in the player's hand. Only non-discarded cards should be considered.
 */
bool Player::check(Card* deck[], const unsigned DECK_SIZE, char value) const
{
    // get the card values that are in the player's hand
    char* playersHand = new char[DECK_SIZE];

    int sizeOfPlayersHand = getPlayersHand(deck, DECK_SIZE, playersHand);

    // debug - keep commented
    // playersHand[sizeOfPlayersHand] = '\0';
    // cout << *name << "'s hand: " << playersHand << endl;


    // perform the check
    for (int i = 0; i < sizeOfPlayersHand; i++)
    {
        if (playersHand[i] == value) {
            delete[] playersHand;
            return true;
        }
    }

    delete[] playersHand;

    return false;
}


/**
 * Get the player's hand as a char array (only card values)
 */
int Player::getPlayersHand(Card* deck[], const unsigned DECK_SIZE, char* playersHand) const
{
    int sizeOfPlayersHand = 0;
    for (int i = 0; i < DECK_SIZE; i++)
    {
        if (!deck[i]->isDiscard() && deck[i]->getPlayerId() == *id)
        {
            playersHand[sizeOfPlayersHand] = deck[i]->getValue();
            sizeOfPlayersHand++;
        }
    }

    return sizeOfPlayersHand;
}
