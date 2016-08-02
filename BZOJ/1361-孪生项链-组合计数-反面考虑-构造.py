import math

n,m,k = map(int, raw_input().split())

f = [0]*1001
f[1] = 2

for i in range(2, k+1):
    f[i] = 2**i
    for j in range(1, int(math.sqrt(i) + .0001) + 1):
        if (i%j == 0):
            f[i] -= f[j]
            if j*j != i and j != 1:
                f[i] -= f[i/j]
print f[k]/k

s = raw_input();

ans = s

while len(ans) < n:
    ans += s


ans = ans[0:n]

cnt = 0
p = n-1
while 0 <= p and ans[p] == '1':
    p = p-1

print ans[0:p]+'1'


