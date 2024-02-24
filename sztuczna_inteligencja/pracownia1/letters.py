class Letter:
    def next_letter(letter: str) -> str:
        return chr(ord(letter) + 1)
    
    def previous_letter(letter: str) -> str:
        return chr(ord(letter) - 1) 