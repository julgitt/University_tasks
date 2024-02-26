from typing import List, Tuple

from pokerRules import PokerRules


class WinnerFinder:
    def __init__(self, figurant_deck: List[Tuple], blotkarz_deck: List[Tuple]):
        self.figurant_deck = figurant_deck
        self.blotkarz_deck = blotkarz_deck
        self.rules = [PokerRules.is_straight_flush, PokerRules.is_four_of_a_kind,
                      PokerRules.is_full_house, PokerRules.is_flush,
                      PokerRules.is_straight, PokerRules.is_three_of_a_kind,
                      PokerRules.is_two_pairs]
        
    def find_a_winner(self) -> str:
        for rule in self.rules:
            if rule(self.figurant_deck):
                return "figurant"
            elif rule(self.blotkarz_deck):
                return "blotkarz"
        return "figurant"