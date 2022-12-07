from sympy import isprime, primerange

# generate a list of all primes up to a certain limit
primes = list(primerange(3, 3040))

# try all possible sets of five primes
for i in range(len(primes)):
    for j in range(i+1, len(primes)):
        if (isprime(int(str(primes[i]) + str(primes[j]))) and isprime(int(str(primes[j]) + str(primes[i])))):
            for k in range(j+1, len(primes)):
                if (isprime(int(str(primes[i]) + str(primes[k]))) and 
                    isprime(int(str(primes[k]) + str(primes[i]))) and
                    isprime(int(str(primes[j]) + str(primes[k]))) and
                    isprime(int(str(primes[k]) + str(primes[j])))):                    
                    for l in range(k+1, len(primes)):
                        for m in range(l+1, len(primes)):
                        # check if any two primes concatenate to produce another prime
                            if (isprime(int(str(primes[i]) + str(primes[k]))) and
                                isprime(int(str(str(primes[k]) + str(primes[i])))) and
                                isprime(int(str(primes[i]) + str(primes[l]))) and
                                isprime(int(str(str(primes[l]) + str(primes[i])))) and
                                isprime(int(str(primes[i]) + str(primes[m]))) and
                                isprime(int(str(str(primes[m]) + str(primes[i])))) and
                                isprime(int(str(primes[j]) + str(primes[k]))) and
                                isprime(int(str(str(primes[k]) + str(primes[j])))) and
                                isprime(int(str(primes[j]) + str(primes[l]))) and
                                isprime(int(str(str(primes[l]) + str(primes[j])))) and
                                isprime(int(str(primes[j]) + str(primes[m]))) and
                                isprime(int(str(str(primes[m]) + str(primes[j])))) and
                                isprime(int(str(primes[k]) + str(primes[l]))) and
                                isprime(int(str(str(primes[l]) + str(primes[k])))) and
                                isprime(int(str(primes[k]) + str(primes[m]))) and
                                isprime(int(str(str(primes[m]) + str(primes[k])))) and
                                isprime(int(str(primes[l]) + str(primes[m]))) and
                                isprime(int(str(str(primes[m]) + str(primes[l]))))):
                            # if all concatenations are prime, we found a solution
                                print(primes[i], primes[j], primes[k], primes[l], primes[m])
                                print(primes[i] + primes[j] + primes[k] + primes[l] + primes[m])
                                break