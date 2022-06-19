nr = int(input())
x1,y1,x2,y2 = float('inf'), float('inf'), -float('inf'), -float('inf')
for _ in range(nr):
    a, b, c = [float(i) for i in input().split()]
    if(a == 0):
        if (b>0):
            if y1 > -c/b:
                y1 = -c/b
        else:
            if y2 < -c/b:
                y2 = -c/b
    else:
        if (a>0):
            if x1 > -c/a:
                x1 = -c/a
        else:
            if x2 < -c/a:
                x2 = -c/a
if (x2 > x1):
    print("VOID")
elif (x1 == float('inf')  or y1 == float('inf') or x2 == -float('inf') or y2 == -float('inf')):
    print("UNBOUNDED")
else:
    print("BOUNDED")


