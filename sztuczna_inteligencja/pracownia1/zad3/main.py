from typing import List    
import random

from winnerFinder import WinnerFinder


colors = ['Red', 'Black']
figures = ['Ace', 'King', 'Queen', 'Jack']
# low_cards = ['2', '3', '4', '5', '6', '7', '8', '9', '10']
low_cards = [ '8', '9', '10']
figurant_deck = [(figure, color) for color in colors for figure in figures for _ in range(2)]
bluffer_deck = [(low, color) for color in colors for low in low_cards for _ in range(2)]
random.shuffle(figurant_deck)
random.shuffle(bluffer_deck)

    
def draw_cards(deck, num_cards=5):
    return random.sample(deck, num_cards)

def estimateVictory(samplesNumber):
    winrate = 0.0
    for i in range(samplesNumber):
        figurant_cards = draw_cards(figurant_deck)
        bluffer_cards = draw_cards(bluffer_deck)
        winnerFinder = WinnerFinder(figurant_cards, bluffer_cards)
        if winnerFinder.find_a_winner() == "bluffer":
            winrate += 1.0
            
    return (winrate * 100) / samplesNumber        
    
def main():

    print(estimateVictory(10000))

if __name__ == "__main__":
    main()
