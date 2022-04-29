class Integer

  def factors
    array = Array.new
    factor = 1
      while factor <= self
        array.push(factor) if self % factor == 0
        factor += 1
      end
    array
    end

    def ack(m)
      if self == 0
         m + 1
      elsif m == 0
        (self - 1).ack(1)
      else
        (self - 1).ack(self.ack(m - 1))
      end
    end

    def perfect
      sum = 1
      number = self
      (2..Math.sqrt(self)).each { |i|
        if number % i == 0
          sum += i + number / i
        end
      }
      sum -= self if number == self * self
      number == sum
    end

    def in_words
      number = self
      dict = { 0 => 'zero ', 1 => 'one ', 2 => 'two ',
               3 => 'three ', 4 => 'four ', 5 => 'five ',
               6 => 'six ', 7 => 'seven ', 8 => 'eight ',
               9 => 'nine ' }

      return dict[0] if number == 0
      result = String.new
      while number > 0
        result.insert(0, dict[number % 10])
        number /= 10
      end
      result
    end
  end

  puts 3 + 3

  puts 2.ack(1)

  puts 6.perfect

  puts 7.perfect

  puts 123.in_words

  puts 24.factors