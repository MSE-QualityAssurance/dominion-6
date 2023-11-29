import random

# Card definitions
class Card:
    def __init__(self, name, cost, card_type):
        self.name = name
        self.cost = cost
        self.card_type = card_type

# Player definitions
class Player:
    def __init__(self, name):
        self.name = name
        self.deck = self.initial_deck()
        self.hand = []
        self.discard_pile = []
        random.shuffle(self.deck)
        self.draw_hand()

    def initial_deck(self):
        return [Card("Copper", 0, "Treasure")] * 7 + [Card("Estate", 2, "Victory")] * 3

    def draw_hand(self):
        for _ in range(5):
            if not self.deck:
                self.deck, self.discard_pile = self.discard_pile, []
                random.shuffle(self.deck)
            self.hand.append(self.deck.pop())

# Game mechanics
class Game:
    def __init__(self, players):
        self.players = players
        self.supply = self.initialize_supply()

    def initialize_supply(self):
        return {"Copper": 60, "Silver": 40, "Gold": 30, "Estate": 24, "Duchy": 12, "Province": 12}

    def play_game(self):
        game_over = False
        while not game_over:
            for player in self.players:
                self.play_turn(player)
                if self.is_game_over():
                    game_over = True
                    break
        self.calculate_scores()

    def play_turn(self, player):
        print(f"{player.name}'s turn")
        # For simplicity, skip Action phase
        self.buy_phase(player)
        self.cleanup_phase(player)

    def buy_phase(self, player):
        # Simplified buying logic
        if self.supply["Copper"] > 0:
            player.discard_pile.append(Card("Copper", 0, "Treasure"))
            self.supply["Copper"] -= 1

    def cleanup_phase(self, player):
        player.discard_pile.extend(player.hand)
        player.hand = []
        player.draw_hand()

    def is_game_over(self):
        # Check if Province cards are gone or any three supply piles are empty
        empty_piles = sum(1 for card, count in self.supply.items() if count == 0)
        return self.supply["Province"] == 0 or empty_piles >= 3

    def calculate_scores(self):
        for player in self.players:
            score = sum(1 for card in player.deck + player.hand + player.discard_pile if card.card_type == "Victory")
            print(f"{player.name}'s score: {score}")

def main():
    players = [Player("Alice"), Player("Bob")]
    game = Game(players)
    game.play_game()

if __name__ == "__main__":
    main()
