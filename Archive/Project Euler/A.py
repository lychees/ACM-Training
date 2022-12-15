# Parse the input
s = input()

# Check if the string satisfies the condition
if len(s) != 8 or not s[0].isalpha() or not s[0].isupper() or not s[1:7].isdigit() or int(s[1:7]) < 100000 or int(s[1:7]) > 999999 or not s[7].isalpha() or not s[7].isupper():
  print("No")
else:
  print("Yes")