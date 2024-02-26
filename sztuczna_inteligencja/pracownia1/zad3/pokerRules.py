class PokerRules:
    
    rank = {'Ace': 14, 'King': 13, 'Queen': 12, 'Jack': 11,
                  '10': 10, '9': 9, '8': 8, '7': 7, '6': 6, '5': 5,
                  '4': 4, '3': 3, '2': 2}

    
    @staticmethod
    def is_flush(hand):
        first_card_color = hand[0][1]
    
        for _, color in hand[1:]:
            if color != first_card_color:
                return False
    
        return True
    
    @staticmethod
    def is_straight_flush(hand):
        if not PokerRules.is_flush(hand):
            return False
        
        values = sorted([PokerRules.rank.get(value) for value, _ in hand])
        
        for i in range(1, len(values)):
            if values[i] != values[i - 1] + 1:
                return False
        
        return True
    
    @staticmethod        
    def is_four_of_a_kind(hand):
        values = [PokerRules.rank.get(value) for value, _ in hand]
        for value in values:
            if values.count(value) >= 4:
                return True
        return False

    @staticmethod    
    def is_ful_house(hand):
        values = [PokerRules.rank.get(value) for value, _ in hand]
        unique_values = set(values)
        if len(unique_values) != 2:
            return False
        for value in unique_values:
            if values.count(value) not in [2, 3]:
                return False
        return True

    @staticmethod
    def is_straight(hand):
        values = sorted([PokerRules.rank.get(value) for value, _ in hand])
        
        for i in range(1, len(values)):
            if values[i] != values[i - 1] + 1:
                return False
        return True
    
    @staticmethod
    def is_three_of_a_kind(hand):
        values = [PokerRules.rank.get(value) for value, _ in hand]
        for value in set(values):
            if values.count(value) == 3:
                return True
        return False

    @staticmethod
    def is_two_pairs(hand):
        values = [PokerRules.rank.get(value) for value, _ in hand]
        pairs = 0
        for value in set(values):
            if values.count(value) == 2:
                pairs += 1
        return pairs == 2