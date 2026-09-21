# EXPOR — expected pairwise OR

You are given an array of `N` integers `A1, A2, …, AN`. Pick two distinct indices uniformly at random, `1 ≤ i < j ≤ N`. What is the expected value of the bitwise OR `Ai | Aj`?

The answer is a rational. Print it as an irreducible fraction `p/q`.

Source: [SPOJ EXPOR](https://www.spoj.com/problems/EXPOR/)

## Input

`T` tests. `T` is on the first line.

Each test is two lines:

- size of the array, `N`
- `N` integers, the array

`N` is per test, not shared across tests.

## Output

One line per test: the irreducible fraction `p/q` for that array, no extra spaces.

A fraction `p/q` is irreducible when `p ≥ 0`, `q > 0`, and no integer `d > 1` divides both.

## Constraints

- `1 ≤ T ≤ 10`
- `2 ≤ N ≤ 100000`
- `0 ≤ Ai < 2^31`
- Time limit `0.55s`
- Memory limit `1536 MB`

There are `C(N, 2) = N(N-1)/2` unordered pairs. The expected value is the sum of `Ai | Aj` over those pairs, divided by `C(N, 2)`.

`Ai | Aj` is at most `2^31 - 1`. The numerator of the unreduced fraction is at most `(2^31 - 1) * C(100000, 2) ≈ 1.07 × 10^19`.

## Special cases

- `N = 2` is a single pair: print `(A1 | A2)/1` after reducing (already a whole number).
- All zeros: every OR is `0`, so `0/1`.
- Every pair can OR to the same value (the official second sample: all three pairs give `3`). Then the answer is that value over `1`.
- The fraction need not be a whole number. Three numbers `[1, 0, 0]` give pairs `1, 1, 0`, so `2/3`.
- `|` is bitwise OR, not logical or.
- Indices are unordered (`i < j`). `(i, j)` and `(j, i)` are not two different samples.

## Sample

Input:

```
2
2
0 0
3
1 2 3
```

Output:

```
0/1
3/1
```

First test: the only pair is `0 | 0 = 0`.

Second test: three pairs.

| pair | OR |
| --- | --- |
| `1 | 2` | `3` |
| `1 | 3` | `3` |
| `2 | 3` | `3` |

Average `3`, already irreducible as `3/1`.
