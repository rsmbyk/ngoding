# NAGAY — Joseph’s Problem

Joseph knows the classic **Josephus** survivor problem: `n` people in a circle, every `k`-th remaining person is removed, find who is left. The usual one-line recurrence is

```
r := 0
for i from 1 to n:
    r := (r + k) mod i
return r
```

He remembered the loop wrong. His version **adds** the remainder instead of folding it back into `r`:

```
r := 0
for i from 1 to n:
    r := r + (k mod i)
return r
```

That is not Josephus. It is still a function of `n` and `k`. Compute it: the sum of `k mod i` for every `i` from `1` to `n`.

`x mod y` is the remainder of `x` divided by `y` (so `0 ≤ (k mod i) < i`).

The original contest is ACM ICPC 2005–2006, Northeastern European Regional (NEERC 05), problem J. This SPOJ copy is the same story with a larger bound.

Source: [SPOJ NAGAY](https://www.spoj.com/problems/NAGAY/). Time limit `1s`, memory `1536 MB`, source limit `50000` bytes. Cluster: Cube (Intel G860).

## Input

One test. A single line with two integers `n` and `k`.

## Output

One integer: `∑_{i=1}^{n} (k mod i)`.

No modulo on the output. The sum is the answer.

## Constraints

The page prints `1 ≤ n, k ≤ 10^18`.

The original NEERC / POJ 2800 / UVa 1363 versions use `10^9`. Here both variables go to `10^18`.

A loop of length `n` does not finish in `1s`.

A bound on the answer, not printed on the page: `k mod i < i`, and for `i > k` the remainder is `k` itself, so

- if `n ≤ k`, the sum is at most `n(n − 1)/2`
- if `n > k`, the sum is at most `k(k − 1)/2 + k(n − k)`

At the high end that is about `5 · 10^35`. A 64-bit integer tops out near `9 · 10^18`. A comment on the page asks whether the answer fits in `long long`; another comment answers yes. That yes matches a `10^9` bound, not this one.

UVa 1363 uses several tests until EOF. This page is one pair `(n, k)`.

## Special cases

- `i = 1`: `k mod 1 = 0` always.
- `k = 1`: the sum is `0` if `n = 1`, and `n − 1` otherwise (`1 mod i` is `0` only at `i = 1`).
- `n = 1`: the sum is `0`.
- `i > k`: `k mod i = k`. If `n > k`, the tail `i = k+1 … n` contributes `k · (n − k)`.
- `n = k`: no tail; every remainder is a true `k mod i` with `i ≤ k`.

## Sample

Input:

```
5 3
```

Output:

```
7
```

The five remainders:

| `i` | `3 mod i` |
| --- | --- |
| `1` | `0` |
| `2` | `1` |
| `3` | `0` |
| `4` | `3` |
| `5` | `3` |

`0 + 1 + 0 + 3 + 3 = 7`.
