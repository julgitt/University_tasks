from typing import List, Tuple


class PokerRules:
    
    rank = {'Ace': 14, 'King': 13, 'Queen': 12, 'Jack': 11,
            '10': 10, '9': 9, '8': 8, '7': 7, '6': 6, '5': 5,
            '4': 4, '3': 3, '2': 2}

    
    @staticmethod
    def is_flush(hand: List[Tuple]) -> bool:
        first_card_suit = hand[0][1]
        return all(suit == first_card_suit for _, suit in hand[1:])
    
    @staticmethod
    def is_straight_flush(hand: List[Tuple]) -> bool:
        if not PokerRules.is_flush(hand):
            return False
        
        ranks = sorted([PokerRules.rank[rank] for rank, _ in hand])
        return all(ranks[i] == ranks[i - 1] + 1 for i in range(1, len(ranks)))
    
    @staticmethod        
    def is_four_of_a_kind(hand: List[Tuple]) -> bool:
        ranks = [PokerRules.rank[rank] for rank, _ in hand]
        return any(ranks.count(rank) >= 4 for rank in ranks)

    @staticmethod    
    def is_full_house(hand: List[Tuple]) -> bool:
        ranks = [PokerRules.rank[rank] for rank, _ in hand]
        unique_ranks = set(ranks)
        if len(unique_ranks) != 2:
            return False
        return 2 in [ranks.count(rank) for rank in unique_ranks]

    @staticmethod
    def is_straight(hand: List[Tuple]) -> bool:
        ranks = sorted([PokerRules.rank[rank] for rank, _ in hand])
        return all(ranks[i] == ranks[i - 1] + 1 for i in range(1, len(ranks)))
    
    @staticmethod
    def is_three_of_a_kind(hand: List[Tuple]) -> bool:
        ranks = [PokerRules.rank[rank] for rank, _ in hand]
        return any(ranks.count(rank) == 3 for rank in set(ranks))

    @staticmethod
    def is_two_pairs(hand: List[Tuple]) -> bool:
        ranks = [PokerRules.rank[rank] for rank, _ in hand]
        return sum(1 for rank in set(ranks) if ranks.count(rank) == 2) == 2