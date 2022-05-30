import sys, random, re
import numpy as np
# import generator, utility

def read_file(file):
    try:
        with open(file, "r", encoding='utf-8-sig') as f:
            data = f.read()
            ds, i = data.split("\n"), 0
            size = 3
            numbers = []
            for line in ds:
                line = re.sub(r"[\s\t]+", ' ', line).strip()
                if line != "" and line.strip()[0] != "#":
                    if i == 0:
                        n = line.split()
                        if len(n) != 1:
                            raise ValueError()
                        size = int(n[0])
                        array = np.zeros((size, size))
                    else:
                        check = line.find("#")
                        if check != -1:
                            line = line[:check]
                        app = list(eval(line.replace(" ", ", ")))
                        if len(app) != size:
                            raise ValueError()
                        array[i - 1] = app
                    i += 1
            array = np.round(array.transpose()).astype(int)
            if i != size + 1 or np.array_equal(np.sort(np.concatenate(array)), np.array(range(0, size * size))) == False:
                raise ValueError()
            return array.transpose()
    except:
        print("Error")
        exit()

# def is_solvable(map, verbose) :
#     puzzle = np.concatenate(np.int64(map))
#     solved_full = generator.gen_solution(map.shape[0])
#     solved = np.concatenate(np.int64(solved_full))
#     inversion = 0
#     if verbose == True:
#         print("Puzzle: ")
#         utility.display_puzzle(map)
#         print("\nSolved:")
#         utility.display_puzzle(solved_full)
#     for i in range(len(puzzle) - 1):
#         count = 0
#         for j in range(i + 1, len(puzzle)) :
#             vi = puzzle[i]
#             vj = puzzle[j]
#             if np.where(solved == vi) > np.where(solved == vj):
#                 count += 1
#         inversion += count
#     blank_puzzle = utility.get_empty(map)
#     blank_solved = utility.get_empty(solved_full)
#     if verbose == True:
#         print(f"\nPuzzle: {puzzle}\nSolved: {solved}\nShape : {map.shape[0]}\nNumber of inversions: {inversion}\n")
#     blank = abs(blank_puzzle[1] - blank_solved[1]) + abs(blank_puzzle[0] - blank_solved[0])
#     if blank % 2 == 0 and inversion % 2 == 0:
#         return True
#     if blank % 2 == 1 and inversion % 2 == 1:
#         return True
#     return False