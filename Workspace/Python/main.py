def count_odd_integers(t, integers_list):
  # Loop through the test cases

  for i in range(t):
    # Get the list of integers for this test case
    integers = integers_list[i]

    # Initialize a counter to keep track of the number of odd integers
    odd_count = 0

    # Loop through the integers in the list
    for integer in integers:
      # If the integer is odd, increment the counter
      if integer % 2 == 1:
        odd_count += 1

    # Print the number of odd integers
    print(odd_count)

def count_odd_integers2():
  # Read the first line of input, which contains the value of t
  t_line = input()
  t = int(t_line)

  # Create a list to store the lists of integers
  integers_list = []

  # Use a loop to read the remaining lines of input
  for i in range(t):
    # Read a line of input
    n = input()
    line = input()

    # Split the line by space to get a list of integers
    integers = list(map(int, line.split()))

    # Add the list of integers to the list of lists
    integers_list.append(integers)

  # Call the count_odd_integers() function to solve the problem
  count_odd_integers(t, integers_list)

# Test the function
count_odd_integers2()