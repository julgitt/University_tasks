from typing import List, Tuple
import random

from winnerFinder import WinnerFinder


#region variables
SUITS = ['Red', 'Black', 'Red1', 'Black1']
FACE_CARDS = ['Ace', 'King', 'Queen', 'Jack']
NUMBER_CARDS = ['2', '3', '4', '5', '6', '7', '8', '9', '10']
# NUMBER_CARDS = [ '8', '9', '10']
FIGURANT_DECK = [(rank, suit) for suit in SUITS for rank in FACE_CARDS]
BLOTKARZ_DECK = [(rank, suit) for suit in SUITS for rank in NUMBER_CARDS]
random.shuffle(FIGURANT_DECK)
random.shuffle(BLOTKARZ_DECK)
#endregion

#region estimation
def estimateVictory(samplesNumber: int) -> float:
    winrate = 0.0
    for _ in range(samplesNumber):
        figurant_cards = draw_cards(FIGURANT_DECK)
        blotkarz_cards = draw_cards(BLOTKARZ_DECK)
        winnerFinder = WinnerFinder(figurant_cards, blotkarz_cards)
        if winnerFinder.find_a_winner() == "blotkarz":
            winrate += 1.0
            
    return (winrate * 100) / samplesNumber        

    
def draw_cards(deck: List[Tuple], num_cards: int=5) -> List[Tuple]:
    return random.sample(deck, num_cards)
#endregion
    
#region main    
def main():
    print(estimateVictory(10000))


if __name__ == "__main__":
    main()
#endregion
