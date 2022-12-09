# Sieve of Eratosthenes to generate a list of primes up to n
def sieve(n):
  # Create a boolean array of length n+1 to
  # mark the primes
  primes = [True] * (n+1)

  # Set 0 and 1 to be not prime
  primes[0] = False
  primes[1] = False

  # Iterate through the array and mark
  # all non-prime numbers
  for i in range(2, int(n**0.5)+1):
    if primes[i]:
      for j in range(i*i, n+1, i):
        primes[j] = False

  # Return a list of prime numbers
  return [i for i in range(len(primes)) if primes[i]]

# Generate a list of primes up to one million
primes = sieve(1000000)

# Find the prime below one million that can be written as the sum of the most consecutive primes
def find_prime(primes):
  # Start with the longest sequence of primes and work our way down
  for i in range(len(primes), 0, -1):
    # Skip sequences that are not possible based on Rosser's theorem
    if i * primes[i-1] >= sum(primes[:i]):
      continue
    print(i)

    # Iterate over all possible combinations of consecutive primes
    for j in range(len(primes)-i+1):
      # Check if the sum of the primes is a prime
      if sum(primes[j:j+i]) in primes:
        # Return the prime
        return sum(primes[j:j+i])

  # If no such prime is found, return 0
  return 0

# Generate a list of primes up to one million
primes = sieve(1000000)

# Find the prime below one million that can be written as the sum of the most consecutive primes
result = find_prime(primes)

# Print the result
print(result)