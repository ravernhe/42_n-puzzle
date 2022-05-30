import argparse, parser
import numpy as np

def npuzzle(args):
    grid = args.map
    parser.is_solvable(grid)
    print(grid)
    pass

if __name__ == "__main__":
    argument = argparse.ArgumentParser()
    group = argument.add_mutually_exclusive_group()
    argument.add_argument("-m", "--map", metavar = "file", type=parser.read_file, help="")
    args = argument.parse_args()
    npuzzle(args)