#include <iostream>
#include "Card.hpp"
#include "Player.hpp"
#include <cstddef>
#include <iomanip>
using namespace std;


bool isGameOver(Card*[], const unsigned);
Card* assignRandomCard(Card*[], const unsigned, Player*);
void checkScore(Card*[], const unsigned, Player*, char);
void initDeck(Card*[]);

int main() {
    // seed RNG
    srand(time(0));

    // create the deck of cards as an array of dynamic objects
    const unsigned DECK_SIZE = 52;
    Card** deck = new Card*[DECK_SIZE];

    // initialize deck
    initDeck(deck);

    // debug
    // print deck - keep commented
    // for (int i = 0; i < DECK_SIZE; ++i)
    // {
    //     cout << deck[i]->getValue() << "/" << deck[i]->getSuit() << endl;
    //     cout << deck[i]->getPlayerId() << "/" << deck[i]->isDiscard() << endl;
    // }

    // welcome message
    cout << setfill('*') << setw(50) << '\n';
    cout << "Welcome to my Go Fish game!\n";
    cout << setfill('*') << setw(50) << '\n' << endl;

    // create the two players dynamically
    // (label the variables as player1 and player2)
    string name;
    cout << "Player 1, enter your name: ";
    cin >> name;
    Player* player1 = new Player(name);
    cout << name << ", your ID is " << player1->getId() << endl;


    cout << "Player 2, enter your name: ";
    cin >> name;
    Player* player2 = new Player(name);
    cout << name << ", your ID is " << player2->getId() << endl;

    // randomly assign 7 cards from the deck to each player
    Card* cardPtr = nullptr;
    for (unsigned cardNum = 0; cardNum < 7; cardNum++) {
        cardPtr = assignRandomCard(deck, DECK_SIZE, player1);
        checkScore(deck, DECK_SIZE, player1, cardPtr->getValue());
    }
    for (unsigned cardNum = 0; cardNum < 7; cardNum++) {
        cardPtr = assignRandomCard(deck, DECK_SIZE, player2);
        checkScore(deck, DECK_SIZE, player2, cardPtr->getValue());
    }

    // game loop
    char value = '\0';
    bool handFlag = false;
    Player* currentPlayer = player1;
    Player* otherPlayer = player2;
    while (!isGameOver(deck, DECK_SIZE)) {
        cout << "\n\n\n\n\n";
        cout << "The current player is " << currentPlayer->getName() << endl;
        cout << "Your score: " << currentPlayer->getScore() << endl;

        // print the player's hand, if possible
        handFlag = false;
        cout << "Your hand is: ";
        for (unsigned i = 0; i < DECK_SIZE; i++) {
            if (deck[i]->getPlayerId() == currentPlayer->getId() &&
                !deck[i]->isDiscard())
            {
                handFlag = true;
                cout << deck[i]->getValue() << '/' << deck[i]->getSuit() << ' ';
            }
        }

        // the player's hand is empty, let them know!
        if (!handFlag) {
            cout << "empty!\n";
        }

        // otherwise, let the player ask
        else {
            cout << endl;
            value = currentPlayer->ask(deck, DECK_SIZE);
        }

        // check if the other player has that card value
        if (handFlag && otherPlayer->check(deck, DECK_SIZE, value)) {
            // display message
            cout << "Nice, good guess!\n";

            // reassign all the cards from the other player
            // that match the value
            for (int i = 0; i < DECK_SIZE; i++)
            {
                if (deck[i]->getPlayerId() == otherPlayer->getId() && deck[i]->getValue() == value) {
                    deck[i]->setPlayerId(currentPlayer->getId());
                }
            }

            // update score?
            checkScore(deck, DECK_SIZE, currentPlayer, value);
        }

        // otherwise, the player needs to go fish for a new card
        else {
            // display message
            cout << "Oops, go fish!\n";

            // get a new random card for the player
            cardPtr = assignRandomCard(deck, DECK_SIZE, currentPlayer);

            // update score?
            checkScore(deck, DECK_SIZE, currentPlayer, cardPtr->getValue());

            // if the card they got was the one they asked for, they go again
            if (cardPtr->getValue() == value) {
                cout << "Oh wait... you drew the card you wanted! Go again!\n";
                continue;
            }
        }

        // alternate the players
        Player* temp = otherPlayer;
        otherPlayer = currentPlayer;
        currentPlayer = temp;
    }

    // print out the final scores and determine the winner

    cout << setfill('*') << setw(50) << '\n';
    cout << "Final scores!" << endl;
    cout << player1->getName() << " has " << player1->getScore() << " points" << endl;
    cout << player2->getName() << " has " << player2->getScore() << " points" << endl;

    if (player1->getScore() >= player2->getScore()) {
        cout << player1->getName();
    } else {
        cout << player2->getName();
    }

    cout << " wins!" << endl;

    cout << setfill('*') << setw(50) << '\n' << endl;

    // release dynamic memory

    delete player2;
    delete player1;

    for (int i = 0; i < DECK_SIZE; i++)
    {
        delete deck[i];
    }

    delete[] deck;

    // terminate


    cout << "\nThanks for playing! Peace among worlds!" << endl;
    return 0;
}//main


/**
 * Game is over when all cards are in the discard pile.
 */
bool isGameOver(Card* deck[], const unsigned DECK_SIZE) {
    // total and size of array
    // true if game is over, otherwise false
    for (int i = 0; i < DECK_SIZE; i++)
    {
        if (!deck[i]->isDiscard()) {
            return false;
        }
    }

    return true;
}//isGameOver

Card* assignRandomCard(Card* deck[], const unsigned DECK_SIZE, Player* p) {
    unsigned lb = 0;
    unsigned ub = DECK_SIZE - 1;
    unsigned randIndex;

    do {
        randIndex = ( lb + ( rand() % ( ub - lb + 1 ) ) );
    } while (deck[randIndex]->getPlayerId() != 0 || deck[randIndex]->isDiscard());

    // set player Id for the card
    deck[randIndex]->setPlayerId(p->getId());
    return deck[randIndex];
}//assignRandomCard

void checkScore(Card* deck[], const unsigned DECK_SIZE, Player* p, char value) {
    char* playersHand = new char[DECK_SIZE];
    int sizeOfPlayersHand = p->getPlayersHand(deck, DECK_SIZE, playersHand);
    int count = 0;

    for (int i = 0; i < sizeOfPlayersHand; i++)
    {
        if (playersHand[i] == value) {
            count++;
        }
    }

    // if, player has a book
    if (count == 4)
    {
        p->updateScore();
        cout << setfill('*') << setw(50) << '\n';
        cout << p->getName() << " just scored a point!" << endl;
        cout << setfill('*') << setw(50) << '\n' << endl;

        // put the book in the discard pile
        for (int i = 0; i < DECK_SIZE; i++)
        {
            if (deck[i]->getValue() == value) {
                deck[i]->flipDiscard();
            }
        }
    }

    delete[] playersHand;
}//checkScore

void initDeck(Card* deck[])
{
    char suits[] = {'D', 'H', 'C', 'S'};
    int step = 0;

    // loop for each suit
    for (int i = 0; i < 4; i++)
    {
        // 2 - 9
        int j;
        int k = 2;
        for (j = 0 + step; j < 8 + step ; j++)
        {
            deck[j] = new Card(k + '0', suits[i]);
            k++;
        }

        // 10
        deck[j] = new Card('0', suits[i]);
        j++;

        // Jack
        deck[j] = new Card('J', suits[i]);
        j++;

        // Queen
        deck[j] = new Card('Q', suits[i]);
        j++;

        // King
        deck[j] = new Card('K', suits[i]);
        j++;

        // Ace
        deck[j] = new Card('A', suits[i]);

        step += 13; // 13 cards in a deck
    }
}
