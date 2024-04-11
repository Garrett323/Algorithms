# Sorting
### Definition:
**_Input:_** An array of $n$ integers (unordered)\
**_Output:_** An array of $n$ integers (sorted)

## Merge Sort
The _Merge Sort_ algorithm is a classical example of a divide & conquer algorithm.
It sorts a given list of numbers by recursively splitting the array of $n$ numbers into two arrays of length $\frac{n}{2}$ and then calls itself on those arrays.
If an array has the length $n \leq 1$ then it returns the array without modification.
After obtaining two sorted arrays via the recurive calls it _merges_ the two arrays back together.

**_Runtime:_** $\mathcal{O}(n \log n)$
