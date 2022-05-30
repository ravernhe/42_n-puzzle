import sys, re
import numpy as np

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
        print("Parsing error")
        exit()