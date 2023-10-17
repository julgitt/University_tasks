from collections import deque 

def find_longest_palindromes(text):
    longest_palindromes = deque()


    def expand_around_center(left, right):
        while left >= 0 and right < len(text) and text[left] == text[right]:
            left -= 1
            right += 1
        return text[left + 1:right]
    

    def add_palindrome(len, i, j):
         if len > 1:
            longest_palindromes.append((i - len // 2 + j, len))
    

    for i in range(len(text)):
        palindrome = expand_around_center(i, i)
        add_palindrome(len(palindrome), i, 0)

        palindrome = expand_around_center(i, i + 1)
        add_palindrome(len(palindrome), i, 1)

    return longest_palindromes




text = "abbaccdcddcbaab"
result = find_longest_palindromes(text)
print(result)



