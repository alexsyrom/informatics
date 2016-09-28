import random
MIN_INT = -10 ** 1
MAX_INT = 10 ** 1

fout = open('input.txt', 'w')
N = 1000
M = 1000
fout.write("{} {}\n".format(N, M))
for i in range(N):
    for j in range(M):
        #a = random.randint(MIN_INT, MAX_INT)
        a = j
        fout.write("{} ".format(a))
    fout.write('\n')
fout.close()

