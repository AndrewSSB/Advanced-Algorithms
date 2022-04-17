from scipy.optimize import linprog
import math

# max 180x + 200y
# 5x + 4y ≤ 80
# 10x + 20y ≤ 200
# x ≥ 0
# y ≥ 0

obj = [-180, -200]  # cu minim pt a maximiza

ineq_left = [[5, 4],
             [10, 20]]

ineq_right = [80,
              200]

boundsXY = [(0, float('inf')),  # x
            (0, float('inf'))]  # y

opt = linprog(c=obj, A_ub=ineq_left, b_ub=ineq_right, bounds=boundsXY, method='revised simplex')

lista = opt.x
lista = [math.floor(x) for x in opt.x]

print(lista)

# 3-CNF Problem
# Pentru (x1 ∨ x2 ∨ x4) ∧ (x1 ∨ x3 ∨ x5) ∧ (x2 ∨ x4 ∨ x5)
# Programul liniar:
# * min x1 + x2 + x3 + x4 + x5
# * x1 + x2 + x4 ≥ 1
# * x1 + x3 + x5 ≥ 1
# * x2 + x4 + x5 ≥ 1
# * 0 ≤ x1 ≤ 1
# * 0 ≤ x2 ≤ 1
# * 0 ≤ x3 ≤ 1
# * 0 ≤ x4 ≤ 1
# * 0 ≤ x5 ≤ 1


obj = [1, 1, 1, 1, 1]  # cand fac minim e ok sa le las cu 1, la max le vreau negate

ineq_left = [[-1, -1, 0, -1, 0],  # negate pt ca el aplica less than
             [-1, 0, -1, 0, -1],
             [0, -1, 0, -1, -1]]

ineq_right = [-1,
              -1,
              -1]

boundsXY = [(0, 1),  # x1
            (0, 1),  # x3
            (0, 1),  # x3
            (0, 1),  # x4
            (0, 1)]  # x5

rez = linprog(c=obj, A_ub=ineq_left, b_ub=ineq_right, bounds=boundsXY, method='revised simplex')
rez = [False if x < 1 / 3 else True for x in rez.x]

print(rez)  # Solutie 3-aproximativa