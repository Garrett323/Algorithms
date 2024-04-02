#!/usr/bin/python
import random
import time

MAX = 20000


def test(alg) -> None:
    array = [random.randint(1, 100) for _ in range(MAX)]
    print(f"Unsorted:\n{array}")
    start_time = time.time()
    array = alg(array)
    elapsed = time.time() - start_time
    print(f"Sorted:\n{array}")
    print(f"Sorting took: {elapsed * 1000000} us")


def main() -> None:
    test(merge_sort)


def merge_sort(array: list) -> list:
    n = len(array)
    if n <= 1:
        return array
    left = merge_sort(array[:n//2])
    right = merge_sort(array[(n+1)//2:])
    return merge(left, right)


def merge(left: list, right: list) -> list:
    merged = []
    n_l = len(left)
    n_r = len(right)
    n = n_r + n_l
    i, j, = 0, 0
    for k in range(n):
        if j >= n_r or (i < n_l and left[i] < right[j]):
            merged.append(left[i])
            i += 1
        else:
            merged.append(right[j])
            j += 1
    return merged


if __name__ == "__main__":
    main()
