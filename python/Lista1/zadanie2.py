
def is_palindrom(text):
    alnum_text = ''.join(char for char in text.lower() if char.isalnum())
    return alnum_text == alnum_text[::-1]


print(is_palindrom("Eine güldne, gute Tugend: Lüge nie!"))
print(is_palindrom("Míč omočím."))
print("Not-pallindrom: " + str(is_palindrom("Not-palindrom")))
