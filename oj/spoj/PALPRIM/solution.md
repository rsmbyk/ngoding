# PALPRIM — solution

Accepted on SPOJ. Time **18.87s**, memory **9.4M**.

## Forks

**Count down from `N`, test palindrome and prime.** One query is `10^13` steps. A million queries. Dead.

**Sieve every integer up to `10^13`.** Same shape as APS / MOHIBTREE: an array of size `L` after a linear pass. `L = 10^13` does not fit in memory or time.

**Walk palindromes down from each `N`, Miller–Rabin until a hit.** The search space is right, the *sharing* is wrong. `T = 10^6` repeats the same walks. A 13-digit `N` whose previous palindromic prime sits far below it is a long hunt, a million times.

**Generate every palindrome, trial-divide each up to `√n`.** About `10^7` palindromes, `√(10^13) ≈ 3·10^6` trials. `~3·10^13` checks. Dead.

**Generate palindromes, keep primes, binary-search per query (this path).** Even length dies for free (divisible by 11, except `11`). Odd length, first digit in `{1,3,7,9}`, Miller–Rabin, one sorted list.

## Why even length dies

A number is divisible by 11 iff the alternating sum of its digits is a multiple of 11. On an even-length palindrome the pairs cancel:

```
a  b | b  a
+  -   +  -
a − b + b − a  =  0
```

Always `0`, so always `11 × something`. The only even-length palindromic prime is `11` itself.

Odd length does not cancel (`131`: `1 − 3 + 1 = −1`). Those can be prime.

Last digit equals first digit, so a palindromic prime `> 5` cannot start with `2,4,6,8` (even) or `5` (divisible by `5`). First digit is `1, 3, 7, or 9`. Add `2`, `5`, and `11` by hand.

## Generating palindromes

`N ≤ 10^13` fits in 64 bits. No strings. Enumerate the first half `h` as an integer, glue on the reverse.

Odd length — drop the last digit of `h` before reversing, that digit is the middle:

```
h = 12  →  121
h = 123 →  12321
```

`p = h · 10^{⌊digits(h)/2⌋} + reverse(h / 10)`.

Lengths `1, 3, 5, …, 13`. (`10^13` is 14 digits and even, so the largest candidates are 13-digit.) About `4·10^6` thirteen-digit survivors after the first-digit filter, plus the smaller odd lengths.

## Miller–Rabin

A **sieve** decides primality for every integer in a range. **Miller–Rabin** decides it for *one* `n`, with a handful of modular exponentiations (the same `a^k mod n` as `FASTPOW.cpp`).

Write `n − 1 = 2^s · d` with `d` odd. For a base `a`, compute `a^d mod n`, then square up to `s` times. A prime is only allowed `1` immediately, or `-1` after some squaring. Any other outcome → composite.

If `n` fails a base, it is composite. If `n ≤ 10^13` **passes** the fixed bases `2, 3, 5, 7, 11, 13, 17`, it is prime. Those seven are known to suffice for every `n < 341,550,071,728,321`.

One 13-digit palindrome: ~7 modexps, not `3·10^6` divisions. A few million candidates fit in `15s`. Multiply `a · b % n` in 128-bit so the product of two 64-bit words does not wrap.

## Queries

The kept palindromes form a sorted list `P`. Each query is the last entry `≤ N`.

**Binary search** on a sorted array: look at the middle, throw away half, repeat. `O(log |P|)` comparisons, here about 20. A million queries are ~`2·10^7` looks, not `|P| · T`.

`upper_bound(N)` then one step left. `N ≥ 2` and `P[0] = 2`, so that entry always exists.

```
P:  2  3  5  7  11  101  131  …  383  727  …
             ↑                    ↑
            N=10                N=666
```

## Tiny example

3-digit palindromes from `h = 10 … 38` (first digit `1` or `3`). `p = h · 10 + reverse(h / 10)`.

```
h     p      first  MR
10   101     1      prime
11   111     1      3×37
12   121     1      11²
13   131     1      prime
…
18   181     1      prime
38   383     3      prime
39   393     3      3×131
40   404     4      skip (even)
```

List so far: `2, 3, 5, 7, 11, 101, 131, …, 383`. Next 3-digit palindromic prime is `727 > 666`.

```
N=2    →  2
N=10   →  7     (11 is already larger)
N=666  →  383
```

## Insight

The integers are the wrong tape. Palindromes are generated from the first half; even length is `11 × something`; the rest are few enough to Miller–Rabin once; queries are a binary search on that list.

## Code notes

- Build odd palindromes only. Seed `{2, 3, 5, 7, 11}`: one-digit primes plus the even-length exception. The first-digit filter would drop `2` and `5`.
- `mul_mod` through `__int128`. `a * b % n` on `unsigned long long` wraps.
- Fast I/O. `T` is a million lines in and a million lines out.

## After AC — what could still improve

Accepted **18.87s**, **9.4M**. Best on the ranklist is **2.79s**. Cube sums files; the `15s` cap is per file. The idea is the same as rank 1. The gap is the inner multiply. Do not rewrite the accepted code unless asked.

**Time.** Queries and I/O are noise. The live cost is Miller–Rabin on the odd palindromes that survive `{2,3,5,7,11,13,17}`. Each of those pays ~40 modular multiplies per witness. Ours is

```
(a * b) % n    via __int128 divide
```

A 128-bit divide on the G860 is the tax. A 13-digit modulus, a few million survivors, seven witnesses: that is the 18s.

The 3s codes keep the same list and replace the divide. **Montgomery multiplication** does `(a · b) mod n` with 64-bit multiplies and a shift, after a one-time setup for that `n`. Miller–Rabin hits the same `n` ~40 times in a row, so the setup is paid once and every later mul is cheap. A `long double` reduction of `a*b/n` is the same idea with the FPU, slightly dirtier.

Second shave: trial-divide by primes up to a few hundred with ordinary 64-bit `%` *before* any `modexp`. Those `%` are cheap; most remaining composites die there and never enter Montgomery. We already kill `3,7,11,13,17`. Extending that wheel is linear and small. Splitting first halves into `1…, 3…, 7…, 9…` avoids a `continue`; it does not move the clock. Fewer witnesses for `n < 4.8·10^9` only helps the short palindromes; the 13-digit ones still need a 64-bit-complete set.

Some ACs dump a giant table (one ranklist entry is **505M**). The setter’s note: the table is not required. Min_25’s **83M** is extra sieve room, not a different problem.

**Memory.** **9.4M** is the vector plus the C++ runtime. 13-digit values need 64 bits. A bitset of all palindromes is the wrong tape again.

**Already as tight as it needs to be.** The bound that mattered was “do not walk integers.” After even length dies to `11` and the rest are generated from the first half, the list is the right size. Sub-10s is a faster `mul_mod`, not a new search.
