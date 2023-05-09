def count_strings(m, patterns, n):
    dp = [0] * (n + 1)
    dp[0] = 1

    for i in range(1, n + 1):
        for pattern in patterns:
            if i - len(pattern) >= 0:
                dp[i] += dp[i - len(pattern)]

    return dp[n]

m = 3
patterns = ["a", "b", "ab"]
n = 4
print(count_strings(m, patterns, n))