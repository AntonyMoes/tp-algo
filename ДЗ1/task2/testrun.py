import os
def find_peak(length, list):
    for i in range (0, length):
        if i == length - 1 or list[i] > list[i + 1]:
            return i

os.system(" echo > testresult.txt")
for i in range(0, 1000):
    os.system("./cmake-build-debug/task2 < tests/" + str(i) + ".txt >> testresult.txt")

results = open("testresult.txt", "r")
for i in range(0, 1000):
    file = open("tests/" + str(i) + ".txt", "r")
    length = int(file.readline())
    raw = file.readline()
    lst = [" ".split(raw)]
    if (find_peak(len(lst), lst) != int(results.readline())):
        print "error in test " + str(i) + "\n"
    file.close()
results.close()