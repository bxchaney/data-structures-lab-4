import os
import random
import sys

import numpy as np

def main(argv: list[str]):
    make_files(argv[1])

def make_files(parent_folder: str) -> None:
    sizes = [
        50,
        500,
        1000,
        2000,
        5000,
        10_000,
        20_000,
    ]

    for n in sizes:
        write_file(sorted_list(n), "asc", parent_folder)
        write_file(reverse_list(n), "desc", parent_folder)
        write_file(random_list(n), "rand", parent_folder)
        write_file(random_with_dupes(n), "dupe", parent_folder)


def sorted_list(n) -> list[str]:
    return [str(i+1) for i in range(n)]

def reverse_list(n) -> list[str]:
    return [str(i) for i in range(n,0,-1)]

def random_list(n) -> list[str]:
    l = [str(i +1) for i in range(n)]
    random.shuffle(l)
    return l

def random_with_dupes(n: int) -> list[str]:
    return [str(i + 1) for i in  np.random.choice(n,n, replace=True)]

def write_file(data: list[str], type: str, parent_folder: str) -> None:
    filename = f"{type}{len(data)}.dat"
    with open(os.path.join(parent_folder, filename), "w") as f:
        f.write("\n".join(data))

if __name__ == '__main__':
    main(sys.argv)
    