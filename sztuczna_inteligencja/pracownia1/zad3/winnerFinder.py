from pokerRules import PokerRules

class WinnerFinder:
    def __init__(self, figurant, bluffer):
        self.figurant = figurant
        self.bluffer = bluffer
        
    def find_a_winner(self):
        winner = self._find_rule_winner(PokerRules.is_straight_flush)
        if winner != None:
            return winner
        winner = self._find_rule_winner(PokerRules.is_four_of_a_kind)
        if winner != None:
            return winner
        winner = self._find_rule_winner(PokerRules.is_ful_house)
        if winner != None:
            return winner
        winner = self._find_rule_winner(PokerRules.is_flush)
        if winner != None:
            return winner
        winner = self._find_rule_winner(PokerRules.is_straight)
        if winner != None:
            return winner
        winner = self._find_rule_winner(PokerRules.is_three_of_a_kind)
        if winner != None:
            return winner
        winner = self._find_rule_winner(PokerRules.is_two_pairs)
        if winner != None:
            return winner
        return "figurant"
            
    
    def _find_rule_winner(self, rule):
        if rule(self.figurant):
            return "figurant"
        if rule(self.bluffer):
            return "bluffer"
        return None