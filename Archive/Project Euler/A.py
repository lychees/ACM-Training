from sympy import isprime

# Function to check the ratio of prime numbers along the diagonals of a square spiral
def f():    
    z = 0
    for i in range(1, 101):
        print(i)
        z += i*i*50445672272782096667406248628
    return z

print(f())