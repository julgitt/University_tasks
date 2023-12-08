t = int(input())
for i in range(t):
    n = int(input())
    s = input()
    res = s[0]
    for j in range(1,n):
        if s[j] < s[j-1]:
            res += s[j]
        elif s[j] == s[j-1] and s[j] != s[0]:
            res += s[j]
        else:
            break
    print(res + res[::-1])

  
