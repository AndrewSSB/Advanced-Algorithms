nrPuncte = int(input())
puncte = []

for _ in range(nrPuncte):
  x, y = input().split()

  puncte.append((int(x), int(y)))

def inorder(arr, i, j, poz):
  return (arr[i][poz] < arr[j][poz]) or (arr[i][poz] == arr[j][poz] and i < j)

X = 0
for i in range(nrPuncte):
  if inorder(puncte, i, (i + 1) % nrPuncte, 0) and inorder(puncte, i, i - 1, 0):
    X += 1

Y = 0
for i in range(nrPuncte):
  if inorder(puncte, i, (i + 1) % nrPuncte, 1) and inorder(puncte, i, i - 1, 1):
    Y += 1

print("YES" if X == 1 else "NO")
print("YES" if Y == 1 else "NO")