import Queue
import sys

def check(a):
    global CNT
    global S
    global Q
    a.sort()
    for i in range(len(a)):
        if a[i] <= 0 or len(str(a[i])) >= 100:
            return
    Q.put(a)
    for i in range(len(a)):
        if a[i] in S:
            return
    for i in range(len(a)):
        S.add(a[i])
    print '%d %d %d' % (a[0],a[1],a[2])
    CNT -= 1
    if CNT == 0:
        sys.exit(0)

k , n = map(int,raw_input().split())
CNT = n
S = set()
Q = Queue.Queue()
Q.put([0,1,k])
while not Q.empty():
    a = Q.get()
    x = [(a[1] + a[2]) * k - a[0] , a[1] , a[2]]
    y = [a[0] , (a[0] + a[2]) * k - a[1] , a[2]]
    check(x)
    check(y)
