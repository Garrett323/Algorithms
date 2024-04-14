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

## Quick Sort
The _Quick Sort_ algorithm is an example of a divide & conquer algorithm.
It sorts a given list of numbers by recursively partitioning an array of numbers around a _pivot_ element. The pivot element maybe choosing at random or as the median. Both result on average in the same runtime, iff the median is choosen in $\mathcal{O}(n)$.
If an array has the length $n \leq 1$ then it returns the array without modification.
After obtaining two sorted arrays via the recurive calls it _merges_ the two arrays back together.

**_Runtime:_** $\mathcal{O}(n \log n)$

**_Note:_** While asymptotically the runtime is the same as Merge Sort the constants involved are smaller and it can be implemented in-place. Thus requires less extra memory.
