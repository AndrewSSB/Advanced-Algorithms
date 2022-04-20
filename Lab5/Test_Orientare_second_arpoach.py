def orientare(A, B, C):
    return (A[0] - B[0])*(B[1] - C[1]) - (A[1] - B[1]) * (B[0] - C[0])

t = int(input())

for i in range(t):
    arr = list(map(int, input().split()))
    aux = orientare(arr[0 : 2], arr[2: 4], arr[4: 6])
    if aux == 0:
        print("TOUCH")
    elif aux < 0:
        print("RIGHT")
    else:
        print("LEFT")