# Start with x = 1
x = 1

# Keep looping until we find the smallest number that satisfies the condition
while True:
    # Count the number of occurrences of each digit in x, 2x, 3x, 4x, 5x, and 6x
    counts = [0] * 10
    for num in [x, 2*x, 3*x, 4*x, 5*x, 6*x]:
        for digit in str(num):
            counts[int(digit)] += 1

        # If the counts of any digit are not equal, this number does not satisfy the condition
        # We can break out of the loop and try the next number
        if not all(count == counts[0] for count in counts):
            break
    else:
        # If we reach this point, it means that all of the numbers satisfy the condition
        # Print the result and exit the loop
        print(x)
        break

    # Increment x and try again
    x += 1