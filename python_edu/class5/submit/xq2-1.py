numbers_set = set(range(2, 100001))
primes_set = set()

while True:
    prime_erasing = min(numbers_set)
    numbers_set.remove(prime_erasing)
    primes_set.add(prime_erasing)

    multiplier = prime_erasing
    while True:
        if prime_erasing > 316:
            break
        erase = prime_erasing * multiplier
        if erase <= 100000:
            numbers_set.discard(erase)
            multiplier += 1
        else:
            break
    
    if len(numbers_set) == 0:
        break

print(len(primes_set))