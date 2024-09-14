# return ggt and bezout coefficients of two numbers
function eea(a, b)
  a, b = max(a, b), min(a, b)
  r0, r1, q = a, b, div(a, b)
  s0, s1 = 1, 0
  t0, t1 = 0, 1
  while true
    s0, s1 = s1, s0 - (q * s1)
    t0, t1 = t1, t0 - (q * t1)
    r0, r1 = r1, r0 % r1
    if r1 != 0
      q = div(r0, r1)
    else
      break
    end
  end
  return r0, s1, t1
end

function main()
  println(eea(240, 46))
end

if abspath(PROGRAM_FILE) == @__FILE__
  main()
end

