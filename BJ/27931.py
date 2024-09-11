import sys
input= sys.stdin.readline
n = int(input())
pointlist = input().split(' ')

pointlist = list(int(i) for i in pointlist)

pointlist.sort()

pointer_odd = -1
pointer_even = -1

minvalue_odd = 2*10**9 + 1
minvalue_even = 2*10**9 + 2

for i in range(0, n):
    if pointlist[i] % 2 == 0:
        #even
        if pointer_odd >= 0:
            minvalue_odd = min(minvalue_odd, abs(pointlist[i]-pointlist[pointer_odd]))
        if pointer_even >= 0:
            minvalue_even = min(minvalue_even, abs(pointlist[i]-pointlist[pointer_even]))
        pointer_even = i
    else:
        #odd
        if pointer_odd >= 0:
            minvalue_odd = min(minvalue_odd, abs(pointlist[i]-pointlist[pointer_even]))
        if pointer_even >= 0:
            minvalue_even = min(minvalue_even, abs(pointlist[i]-pointlist[pointer_odd]))
        pointer_odd = i

if minvalue_odd == 2*10**9 + 1:
    minvalue_odd = -1
if minvalue_even == 2*10**9+2:
    minvalue_even = -1
print('%d %d' % (minvalue_even, minvalue_odd))
