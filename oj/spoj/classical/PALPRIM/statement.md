# PALPRIM — Palindromic Primes (Hard)

A number is **palindromic** if it has no leading zeros and reading its decimal digits backwards gives the same number. `5`, `22`, `12321`, `101101` are palindromes. `10`, `34`, `566`, `123421` are not.

A number is **prime** if it is an integer greater than `1` with no positive divisors besides `1` and itself. `2`, `31`, `97` are prime. `1`, `10`, `25`, `119` are not.

A **palindromic prime** is both: palindrome and prime. `2`, `3`, `131` are palindromic primes. `6`, `17`, `3333` are not.

Given a positive integer `N`, print the **largest palindromic prime that is still ≤ `N`**.

Source: [SPOJ PALPRIM](https://www.spoj.com/problems/PALPRIM/). Added by sgtlaugh, 2016-02-26. Own problem. Time `15s`, memory `1536 MB`, source `50000` bytes. Cluster: Cube (Intel G860). Tagged `#binary-search` `#primality-test` `#precalculation`. Warning: large I/O — use fast input/output.

## Input

- Line 1: `T` — number of test cases.
- Next `T` lines: one integer `N` each, no leading or trailing spaces.

## Output

`T` lines. Line `i` is the largest palindromic prime `≤ N_i`.

## Constraints

- `1 ≤ T ≤ 10^6`
- `2 ≤ N ≤ 10^13`
- Time limit `15s`
- Memory limit `1536 MB`
- Source limit `50000` bytes
- Languages: all except ASM64, GOSU, JS-MONKEY

`T` really is a million. `N` really reaches `10^13` (up to 14 digits: `10000000000000`). Answers themselves are palindromic primes, so they fit in 64-bit integers. Walking every integer down from `N` is `10^13` steps on a single query, and there are a million queries.

Every `N` is at least `2`, so an answer always exists (`2` itself is a palindromic prime).

## Special cases

- `N = 2`: the answer is `2`.
- `N` itself is a palindromic prime: print `N`.
- `N` just below a palindromic prime: jump down to the previous one. Sample `10` is past `7` and short of `11`, so `7`.
- `N` in a long gap between palindromic primes: the answer can sit many orders of magnitude below `N`.
- Even-length vs odd-length palindromes both appear in the examples (`22` is a palindrome but not prime; `2` and `131` are odd-length primes; `11` is the even-length palindromic prime that exists).
- A million copies of the same `N`, including `N = 10^13`, must still finish inside `15s`.

## Sample

Input:

```
3
2
10
666
```

Output:

```
2
7
383
```

`2` is the smallest palindromic prime, so it answers itself.

Between `8` and `10` the palindromic primes are `2, 3, 5, 7`. `11` is the next one and is already larger than `10`, so `10` maps to `7`.

For `666`, `383` is a palindrome (`383` reversed is `383`) and prime. The palindromes sitting between `384` and `666` (`393`, `404`, `414`, …, `656`, `666`) are all composite, so `383` is the largest palindromic prime that still fits.
