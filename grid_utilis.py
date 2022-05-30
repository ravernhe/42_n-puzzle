import numpy as np

def snail_solution(size):
    A = []
    for i in range (0, size * size) :
        if i == size * size - 1:
            A.append(0)
        else :
            A.append(i + 1)
    top = left = 0
    bottom = right = size - 1
 
    # construct an `M × N` matrix
    mat = np.zeros((size, size), dtype=int)
 
    index = 0
 
    while True:
        if left > right:
            break
        # print top row
        for i in range(left, right + 1):
            mat[top][i] = A[index]
            index = index + 1
        top = top + 1
        if top > bottom:
            break
        # print right column
        for i in range(top, bottom + 1):
            mat[i][right] = A[index]
            index = index + 1
        right = right - 1
        if left > right:
            break
        # print bottom row
        for i in range(right, left - 1, -1):
            mat[bottom][i] = A[index]
            index = index + 1
        bottom = bottom - 1
        if top > bottom:
            break
        # print left column
        for i in range(bottom, top - 1, -1):
            mat[i][left] = A[index]
            index = index + 1
        left = left + 1
 
    return mat