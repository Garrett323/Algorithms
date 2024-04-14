#!/usr/bin/julia

function merge_sort(array)
  n = size(array, 1)
  half = trunc(Int, n / 2)
  if n <= 1
    return array
  end
  left = merge_sort(array[1:half])
  right = merge_sort(array[half+1:n])
  return merge(left, right)
end

function merge(left, right)
  l, r = size(left, 1), size(right, 1)
  n = l + r
  merged = Vector{Int}(undef, n)
  i, j = 1, 1
  for k in 1:n
    if j > r || (i <= l && left[i] < right[j])
      merged[k] = left[i]
      i += 1
    else
      merged[k] = right[j]
      j += 1
    end
  end
  return merged
end

array = rand(1:100, 30)

println("Merge Sort")
println("Unsorted:")
println(array)
println("Sorted:")
println(merge_sort(array))
