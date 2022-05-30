import sys, re, grid_utilis
import numpy as np

def is_solvable(puzzle):
    solution = grid_utilis.snail_solution(len(puzzle[0]))
    solution = np.concatenate(np.int64(solution))
    puzzle = np.concatenate(np.int64(puzzle))

    inversion = 0
    # print("Solution : ", solution, " && Puzzle : ", puzzle)

    for i in range(len(puzzle) - 1):
        vi = puzzle[i]
        for j in range(i + 1, len(puzzle)) :
            vj = puzzle[j]
            if np.where(solution == vi) > np.where(solution == vj):
                inversion += 1

    for i in range(len(solution)):
        if solution[i] == 0:
            pos_x_y = i

    # print("Inversion : ", inversion, " && Pos_x_y : ", pos_x_y)
    if (inversion % 2 != pos_x_y % 2):
        print("Non solvable")
        exit(0)

def error_list(puzzle, size):
    values = np.unique(puzzle)
    if len(values) != size or values[0] != 0 or values[-1] != size - 1:
        raise ValueError()

def catch_error(lines):
    puzzle_size = 0
    values = []
    for each in lines:
        each = each.split('#')[0].split()
        if each :
            if puzzle_size == 0:
                puzzle_size = int(each[0])
            else :
                values.append(each)
    # check doublon
    puzzle = np.array(values, dtype=int)
    error_list(puzzle, puzzle_size * puzzle_size)
    return puzzle


def read_file(file_name):
    try:
        with open(file_name, "r", encoding='utf-8-sig') as file:
            lines = file.read().split("\n")
            return catch_error(lines)
    except:
        print("Error while parsing.")
        exit()