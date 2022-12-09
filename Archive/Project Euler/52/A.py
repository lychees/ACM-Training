# Start with x = 1
x = 1

# Keep looping until we find the smallest number that satisfies the condition
while True:
    # Convert x, 2x, 3x, 4x, 5x, and 6x to strings
    str_x = str(x)
    str_2x = str(2*x)
    str_3x = str(3*x)
    str_4x = str(4*x)
    str_5x = str(5*x)
    str_6x = str(6*x)

    # Sort the digits in each string
    sorted_str_x = sorted(str_x)
    sorted_str_2x = sorted(str_2x)
    sorted_str_3x = sorted(str_3x)
    sorted_str_4x = sorted(str_4x)
    sorted_str_5x = sorted(str_5x)
    sorted_str_6x = sorted(str_6x)

    # Convert the sorted lists of digits back into strings
    sorted_str_x = "".join(sorted_str_x)
    sorted_str_2x = "".join(sorted_str_2x)
    sorted_str_3x = "".join(sorted_str_3x)
    sorted_str_4x = "".join(sorted_str_4x)
    sorted_str_5x = "".join(sorted_str_5x)
    sorted_str_6x = "".join(sorted_str_6x)

    # If the sorted strings are all equal, we have found the smallest number that satisfies the condition
    if sorted_str_x == sorted_str_2x == sorted_str_3x == sorted_str_4x == sorted_str_5x == sorted_str_6x:
        # Print the result and exit the loop
        print(x)
        break

    # Otherwise, increment x and try again
    x += 1