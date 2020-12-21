#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>
#include <cstddef>

using namespace std;

class Player {
private:
    unsigned* id;
    string* name;
    unsigned* score;

public:
    //default constructor
    Player();

    //overload constructor
    Player(string);

    //destructor
    ~Player();

    //getters
    unsigned getId() const;
    string getName() const;
    unsigned getScore() const;


    //functions
    void updateScore();
    char ask(Card*[], const unsigned) const;
    bool check(Card*[], const unsigned, char) const;

    int getPlayersHand(Card*[], const unsigned, char*) const;

};

#endif /* PLAYER_HPP_ */
