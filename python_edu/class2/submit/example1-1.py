side_lengths = tuple(map(int, [input() for _ in range(3)]))
a, b, c = sorted(side_lengths)
print("YES" if a + b > c else "NO")