from sympy import isprime

# Function to check the ratio of prime numbers along the diagonals of a square spiral
def check_ratio():    
    # Calculate the number of numbers along the diagonals
    # Initialize counters for the number of prime numbers and the total number of numbers along the diagonals
    prime_count = 0
    total_count = 1
    # Loop through the numbers along the top-right diagonal
    
    n = 1
    i1 = 1
    d1 = 2
    i2 = 1
    d2 = 4
    while 1:
        i1 += d1
        if isprime(i1):
            prime_count += 1        
        d1 += 2
        i1 += d1
        if isprime(i1):
            prime_count += 1                
        d1 += 2

        i2 += d2
        if isprime(i2):
            prime_count += 1                    
        i2 += d2
        if isprime(i2):
            prime_count += 1
        d2 += 4
        total_count += 4
        n += 2
        print(prime_count/total_count)
        if prime_count * 10 < total_count: 
            print (n, prime_count, total_count)
            return n

def find_side_length():
    return check_ratio()

# Find the side length of the square spiral for which the ratio of primes along the diagonals first falls below 10%
side_length = find_side_length()

# Print the result
print(side_length)