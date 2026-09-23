# NDIV — n-divisors

A number is an `n`-divisors number when it has exactly `n` positive divisors. For example, `1` is a 1-divisor number, every prime is a 2-divisors number, `4` is a 3-divisors number (`1, 2, 4`), and `8` is a 4-divisors number (`1, 2, 4, 8`).

Given `a`, `b`, and `n`, count how many integers in the closed range `[a, b]` have exactly `n` positive divisors.

Source: [SPOJ NDIV](https://www.spoj.com/problems/NDIV/). Time limit `1s`, memory `1536 MB`, source limit `50000 B`. The Vietnamese mirror redirects away from this problem; the live statement is on `www.spoj.com`.

## Input

One line with three integers `a`, `b`, and `n`.

## Output

One line: the count of integers `x` with `a <= x <= b` that have exactly `n` positive divisors.

## Constraints

- `1 <= a, b <= 10^9`
- `0 <= b - a <= 10^4`
- `1 <= n <= 100`

The page does not say that `a` is at most `b`. If `a > b`, the closed range is empty and the count is `0`.

## Sample

```
1 7 2
```

```
4
```

`n = 2` means primes. Between `1` and `7` the primes are `2`, `3`, `5`, and `7`, so the answer is `4`.
