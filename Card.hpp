#ifndef CARD_HPP_
#define CARD_HPP_

#include <cstddef>

class Card {
    private:
        char* value;
        char* suit;
        unsigned* playerId;
        bool* discard;

    public:
        //default constructor
        Card();

        //overload constructor
        Card(char, char);

        //destructor
        ~Card();

        //getters
        char getValue() const;
        char getSuit() const;
        unsigned getPlayerId() const;
        bool isDiscard() const;

        //setters
        void setPlayerId(unsigned);

        void flipDiscard();
};

#endif /* CARD_HPP_ */

