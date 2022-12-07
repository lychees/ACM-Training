# Function to generate a list of numbers obtained by replacing each digit in the original number with the given digit
def generate_numbers(number, digit):
  # Convert the number to a string
  number_str = str(number)
  
  # Initialize a list to store the generated numbers
  numbers = []
  
  # Loop through each digit in the number
  for i in range(len(number_str)):
    # Replace the current digit with the given digit
    new_number_str = number_str[:i] + str(digit) + number_str[i+1:]
    
    # Convert the string back to an integer and append it to the list
    numbers.append(int(new_number_str))
  
  # Return the list of generated numbers
  return numbers

# Function to check if a number is prime
def is_prime(n):
  # Check if n is less than 2 (prime numbers must be greater than or equal to 2)
  if n < 2:
    return False
  
  # Loop through the numbers from 2 to the square root of n
  for i in range(2, int(n ** 0.5) + 1):
    # If n is divisible by i, it is not prime
    if n % i == 0:
      return False
  
  # If n is not divisible by any number from 2 to the square root of n, it is prime
  return True

# Initialize a variable to store the smallest prime number with 8 prime numbers in its family
smallest_prime = None

# Loop through all possible numbers
for number in range(11, 1000000):
  # Loop through all possible digits
  for digit in range(0, 10):
    # Generate the numbers obtained by replacing each digit in the original number with the given digit
    numbers = generate_numbers(number, digit)
    
    # Count the number of prime numbers in the generated numbers
    prime_count = 0
    for n in numbers:
      if is_prime(n):
        prime_count += 1
    
    # If there are 8 prime numbers in the generated numbers, update the smallest prime number with 8 prime numbers in its family
    if prime_count == 8:
      if smallest_prime is None or number < smallest_prime:
        smallest_prime = number

# Print the smallest prime number with 8 prime numbers in its family
print(smallest_prime)