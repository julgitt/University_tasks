from random import choice


class RandomReconstructor:
    def __init__(self, text, max_word_len, words):
        self.text = text
        self.max_word_len = max_word_len
        self.words = words

    def find_words(self):
        memo = {}

        def dp(start):
            if start in memo:
                _, value = memo.get(start)
                return value

            if start == len(self.text):
                return ""

            correct_words = set()
            for end in range(start + 1, min(start + self.max_word_len + 1, len(self.text) + 1)):
                word = self.text[start:end]
                if word in self.words:
                    correct_words.add(word)

            while len(correct_words) > 0:
                word = choice(tuple(correct_words))
                rest = dp(start + len(word))
                if rest is not None:
                    if rest == "":
                        peak = word + rest
                    else:
                        peak = word + " " + rest
                    memo[start] = (True, peak)
                    return peak
                correct_words.remove(word)

            memo[start] = (False, None)
            return None

        return dp(0)
