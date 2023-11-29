#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

// Define Card class
class Card {
public:
    string name;
    int cost;

    Card(string n, int c) : name(n), cost(c) {}

    void print() {
        cout << name << " (Cost: " << cost << ")";
    }
};

// Define Player class
class Player {
public:
    string name;
    vector<Card> deck;
    vector<Card> hand;

    Player(string n) : name(n) {}

    void printDeck() {
        cout << name << "'s Deck: ";
        for (const auto &card : deck) {
            card.print();
            cout << " ";
        }
        cout << endl;
    }

    void printHand() {
        cout << name << "'s Hand: ";
        for (const auto &card : hand) {
            card.print();
            cout << " ";
        }
        cout << endl;
    }

    void drawCard() {
        if (!deck.empty()) {
            hand.push_back(deck.back());
            deck.pop_back();
        }
    }
};

// Define DominionGame class
class DominionGame {
public:
    vector<Card> kingdomCards;
    vector<Player> players;

    void initializeGame() {
        // Initialize kingdom cards (you can add more cards)
        kingdomCards.push_back(Card("Copper", 0));
        kingdomCards.push_back(Card("Silver", 3));
        kingdomCards.push_back(Card("Gold", 6));
        kingdomCards.push_back(Card("Estate", 2));
        kingdomCards.push_back(Card("Duchy", 5));
        kingdomCards.push_back(Card("Province", 8));

        // Initialize players (you can add more players)
        players.push_back(Player("Player 1"));
        players.push_back(Player("Player 2"));

        // Shuffle and draw starting cards for each player
        for (auto &player : players) {
            shuffleDeck(player.deck);
            drawStartingCards(player.deck, player.hand);
        }
    }

    void shuffleDeck(vector<Card> &deck) {
        random_shuffle(deck.begin(), deck.end());
    }

    void drawStartingCards(vector<Card> &deck, vector<Card> &hand) {
        for (int i = 0; i < 5; ++i) {
            if (!deck.empty()) {
                hand.push_back(deck.back());
                deck.pop_back();
            }
        }
    }

    void printKingdomCards() {
        cout << "Kingdom Cards: ";
        for (const auto &card : kingdomCards) {
            card.print();
            cout << " ";
        }
        cout << endl;
    }

    void printGameState() {
        cout << "=== Game State ===" << endl;
        for (const auto &player : players) {
            player.printDeck();
            player.printHand();
            cout << endl;
        }
        printKingdomCards();
        cout << "==================" << endl;
    }
};

int main() {
    srand(static_cast<unsigned>(time(0))); // Seed for random shuffle

    DominionGame game;
    game.initializeGame();
    game.printGameState();

    return 0;
}
