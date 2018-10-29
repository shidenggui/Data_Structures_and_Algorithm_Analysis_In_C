import os


def list_dir_size(folder):
    total_size = os.path.getsize(folder)
    if not os.path.isdir(folder):
        return total_size

    for child in os.listdir(folder):
        child_path = os.path.join(folder, child)
        total_size += list_dir_size(child_path)
    return total_size
