import argparse, parser, grid_utilis
import numpy as np

def is_solvable(puzzle):
    solution = grid_utilis.snail_solution(len(puzzle[0]))
    solution = np.concatenate(np.int64(solution))
    puzzle = np.concatenate(np.int64(puzzle))

    inversion = 0
    print("Solution : ", solution, " && Puzzle : ", puzzle)

    for i in range(len(puzzle) - 1):
        count = 0
        vi = puzzle[i]
        for j in range(i + 1, len(puzzle)) :
            vj = puzzle[j]
            if np.where(solution == vi) > np.where(solution == vj):
                count += 1
        inversion += count
    print("Inversion : ", inversion)


def npuzzle(args):
    grid = args.map
    is_solvable(grid)
    pass

if __name__ == "__main__":
    argument = argparse.ArgumentParser()
    group = argument.add_mutually_exclusive_group()
    argument.add_argument("-m", "--map", metavar = "file", type=parser.read_file, help="")
    args = argument.parse_args()
    npuzzle(args)