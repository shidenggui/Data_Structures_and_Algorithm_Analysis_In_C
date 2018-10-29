import os
import sys


def list_dir(folder, depth):
    print('\t' * depth, os.path.basename(folder))
    if not os.path.isdir(folder):
        return
    for child in os.listdir(folder):
        child_path = os.path.join(folder, child)
        list_dir(child_path, depth + 1)


def list_directory(folder):
    list_dir(folder, depth=0)


list_directory(sys.argv[1])
