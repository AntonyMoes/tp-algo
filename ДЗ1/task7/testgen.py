import random
import string
string.letters

test = []
for j in range(0, 3000):
    length = random.randint(1, 100000)
    s = ''
    for i in range(0, length):
        s += random.choice(string.letters)
    test.append(s)
file = open("test.txt", "w")
file.write('\n'.join(test))
file.close()
