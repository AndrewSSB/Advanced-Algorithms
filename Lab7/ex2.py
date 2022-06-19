def intersectie(semiplans, point):
    x1,y1,x2,y2 = float('inf'), float('inf'), -float('inf'), -float('inf')

    for semiplan in semiplans:
        if semiplan[0] == 0:  # vertical
            if (semiplan[2]+ semiplan[1] * point[1] ) >= 0:
                continue
        else:  # horizontal
            if (semiplan[2] + semiplan[0] * point[0] ) >= 0:
                continue

        if semiplan[0] == 0:  # vertical
            if -1 * semiplan[2] / semiplan[1] < point[1]:
                y2 = max(y2, -1 * semiplan[2] / semiplan[1])
            else:
                y1 = min(y1, -1 * semiplan[2] / semiplan[1])
        else:  # horizontal
            if -1 * semiplan[2] / semiplan[0] < point[0]:
                x2 = max(x2, -1 * semiplan[2] / semiplan[0])
            else:
                x1 = min(x1, -1 * semiplan[2] / semiplan[0])

    if x1 == float('inf') or y1 == float('inf') or x2 == -float('inf') or y2 == -float('inf'):
        return 0
    return (x1 - x2) * (y1 - y2) # surface

listaSemiplanuri = []
n = int(input())
for i in range(n):
    line = [int(x) for x in input().split()]
    semiplan = (line[0], line[1], line[2])
    listaSemiplanuri.append(semiplan)

m = int(input())
for i in range(m):
    line = [float(x) for x in input().split()]
    point = (line[0], line[1])
    output = intersectie(listaSemiplanuri, point)
    if output == 0:
        print("NO")
    else:
        print("YES")
        print(output)