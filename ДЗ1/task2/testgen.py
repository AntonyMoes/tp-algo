import random
for j in range(0, 1000):
    length = random.randint(1, 10000)
    peak = random.randint(0, length)

    test = [i for i in range(0, peak + 1)]
    test += [peak - (i - peak) for i in range(peak + 1, length)]
    test_s = [str(i) for i in test]
    file = open("tests/" + str(j) + ".txt", "w")
    file.write(str(length) + "\n")
    file.write(' '.join(test_s))
    file.close()