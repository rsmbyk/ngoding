# JPM — Just Primes

You are given a positive integer `N`. Write it as a sum of **distinct primes**, using as few primes as possible. Print that count. If no such set of primes exists, print `-1`.

A **prime** is an integer greater than `1` whose only positive divisors are `1` and itself. The sequence starts `2, 3, 5, 7, 11, 13, 17, 19, 23, 29, …`.

**Distinct** is the whole point: each prime may appear at most once. `2 + 2 = 4` does not count, because `2` is used twice. Order does not matter: `{3, 7}` and `{7, 3}` are the same set.

Source: [SPOJ JPM](https://www.spoj.com/problems/JPM/). Added by sgtlaugh, 2021-02-25. Own problem. Time `3s`, memory `1536 MB`, source `50000` bytes. Cluster: Cube (Intel G860). Tagged `#number-theory` `#dynamic-programming` `#prime-numbers-1`. Languages: all. A harder follow-up exists as [JPM2](https://www.spoj.com/problems/JPM2/).

## Input

- Line 1: `T` — number of test cases.
- Next `T` lines: one integer `N` each.

## Output

`T` lines. Line `i` is:

```
Case i: X
```

where `X` is the size of a smallest set of distinct primes that sum to `N_i`, or `-1` if no such set exists. The case numbers are 1-based. There is a space after the colon.

## Constraints

- `1 ≤ T ≤ 50,000`
- `1 ≤ N ≤ 50,000`
- Time limit `3s`
- Memory limit `1536 MB`
- Source limit `50000` bytes

`T` and `N` both reach fifty thousand. Fifty thousand independent walks over all primes up to fifty thousand is a lot of repeated work: there are a few thousand primes below `50,000`, and a naive search per query can blow the three seconds.

The answer, when it exists, is a small integer (a set of distinct primes summing to at most `50,000` cannot be huge — the smallest `k` primes already grow like `k² log k`). When it does not exist, the output is exactly `-1`.

## Special cases

- `N = 1`: no prime is `≤ 1`. The empty sum is `0`. Impossible. `-1`.
- `N` itself is prime (`2`, `3`, `49999` in the sample): the set is `{N}`. Answer `1`.
- Repeats are illegal. `4 = 2 + 2` is not allowed, and `4` is not prime, so `4` is `-1`. Same story for `6 = 3 + 3`.
- The smallest sum of three distinct primes is `2 + 3 + 5 = 10`, so every `N < 10` that is not prime and not a sum of two distinct primes is impossible.
- Odd `N` that is not prime: two distinct primes that sum to an odd number must be one even and one odd, and the only even prime is `2`. So the only two-prime candidate is `{2, N − 2}`, and that works only when `N − 2` is an odd prime different from `2`.
- Sample `27`: not prime, `27 − 2 = 25` is not prime, so two primes are out. Three work (`3 + 5 + 19`). Answer `3`.
- Sample `4991`: same shape as `27` — not a prime, `4991 − 2 = 4989` is not a prime, three distinct primes do work. Answer `3`.
- A million-scale `T` is not the issue here, but `50,000` copies of `N = 50,000` still have to finish inside `3s`.

## Sample

Input:

```
10
1
2
3
10
27
100
1000
4572
4991
49999
```

Output:

```
Case 1: -1
Case 2: 1
Case 3: 1
Case 4: 2
Case 5: 3
Case 6: 2
Case 7: 2
Case 8: 2
Case 9: 3
Case 10: 1
```

| `N` | why |
| --- | --- |
| `1` | no primes sum to `1` |
| `2` | `{2}` |
| `3` | `{3}` |
| `10` | not prime; `{3, 7}` |
| `27` | not prime; `25` not prime; `{3, 5, 19}` |
| `100` | `{3, 97}` (among others) |
| `1000` | `{3, 997}` (among others) |
| `4572` | two distinct primes |
| `4991` | not prime; `4989` not prime; three distinct primes |
| `49999` | `49999` is itself prime |
