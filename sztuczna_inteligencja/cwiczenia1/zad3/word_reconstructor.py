
class Reconstructor:
    def __init__(self, text, max_word_len, words):
        self.text = text
        self.max_word_len = max_word_len
        self.words = words

    def find_words(self):
        memo = {}

        def dp(start):
            if start in memo:
                return memo[start]

            if start == len(self.text):
                return ""

            best_peak = ""
            max_sum = 0
            for end in range(start + 1, min(start + self.max_word_len + 1, len(self.text) + 1)):
                word = self.text[start:end]
                if word in self.words:
                    rest = dp(end)
                    if rest is not None:
                        squared_sum = self._sum_of_squared_word_lengths(word + " " + rest)
                        if squared_sum > max_sum:
                            max_sum = squared_sum
                            best_peak = word + " " + rest
            if best_peak == "":
                memo[start] = None
                return None
            memo[start] = best_peak
            return best_peak

        return dp(0)

    @staticmethod
    def _sum_of_squared_word_lengths(text):
        return sum(len(word) ** 2 for word in text.split())


