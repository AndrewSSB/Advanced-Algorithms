def createMatrix(xA, yA, xB, yB, xC, yC, xD, yD):
  return [
          [xA, yA, xA**2 + yA**2,  1],
          [xB, yB, xB**2 + yB**2,  1],
          [xC, yC, xC**2 + yC**2,  1],
          [xD, yD, xD**2 + yD**2,  1]
          ]

def determinant_recursive(A, total=0):
    indices = list(range(len(A)))
    if len(A) == 2 and len(A[0]) == 2:
        val = A[0][0] * A[1][1] - A[1][0] * A[0][1]
        return val
    for fc in indices: 
        As = A 
        As = As[1:] 
        height = len(As) 
 
        for i in range(height): 
            As[i] = As[i][0:fc] + As[i][fc+1:] 
 
        sign = (-1) ** (fc % 2) # F) 
        sub_det = determinant_recursive(As)
        total += sign * A[0][fc] * sub_det 
 
    return total

xA, yA = input().split()
xB, yB = input().split()
xC, yC = input().split()
xD, yD = input().split()

xA, yA = int(xA), int(yA)
xB, yB = int(xB), int(yB)
xC, yC = int(xC), int(yC)
xD, yD = int(xD), int(yD)

det1 = determinant_recursive(createMatrix(xA, yA, xB, yB, xC, yC, xD, yD))
det2 = determinant_recursive(createMatrix(xB, yB, xC, yC, xD, yD, xA, yA))

if det1 > 0:
  print("AC: ILLEGAL")
else:
  print("AC: LEGAL")

if det2 > 0:
  print("BD: ILLEGAL")
else:
  print("BD: LEGAL")