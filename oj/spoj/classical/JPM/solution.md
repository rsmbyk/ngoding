# JPM — solution

Accepted on SPOJ. Time **0.03s**.

## Forks

**List every subset of primes.** Correct, and it is what “distinct” *means*. `π(50000) ≈ 5000` primes, `2^5000` handfuls. Dead.

**0-1 table, one prime at a time.** Slot `n` = fewest distinct primes that sum to `n`. Each prime is used 0 or 1 times, so a new prime `p` may only be added onto answers that were computed *without* `p`. That works (`T` then becomes a lookup), but the inner pass is `π(N) · N ≈ 2.5·10^8` updates, and the 0-or-1 rule is easy to get backwards. The sample answers never use `4` or more primes, so the table is doing a lot of work for a value in `{−1, 1, 2, 3}`.

**Classify by parity after one sieve (this path).** After the primes are known, an `N` is either impossible, itself prime, two primes, or three. No table of min-counts.

## Goldbach

**Goldbach’s conjecture:** every even integer greater than `2` is a sum of two primes. There is no proof for every even number, but it has been checked far past `50,000`. Here `N ≤ 50,000`, so after the sieve it is a fact we can use.

**Distinct.** `4 = 2+2` and `6 = 3+3` are Goldbach and still illegal. `10 = 5+5` is the same trap, but `10 = 3+7` saves it. From `8` up, every even number in range has a pair of **different** odd primes. (An even `N ≥ 6` cannot be `2 + (N−2)`: `N−2` is even and at least `4`, so not prime.)

A **sieve** (Eratosthenes) marks every composite as a multiple of a smaller prime. Survivors in `2 … 50000` are exactly the primes we need for “is `N` prime?” and “is `N−2` prime?”

## Algorithm

Sieve once. Then each `N`:

1. `1`, `4`, `6` → `-1`
2. `N` is prime → `1`
3. `N` is even (`≥ 8`) → `2` — two odd primes, Goldbach
4. `N` is odd and `N−2` is prime → `2` — only possible pair: `{2, N−2}`
5. otherwise → `3` — peel `3`, leftover `N−3` is even and `≥ 8`, Goldbach splits it into two primes different from `3`

Odd `N` cannot be two odd primes (odd+odd=even). A triple that includes `2` is `2+odd+odd` = even, so an odd that needs three uses three odd primes.

The program never lists the primes in the handful. It only prints the size.

## Tiny example

```
        1  2  3  4  5  6  7  8  9 10  …  27
prime?  n  Y  Y  n  Y  n  Y  n  n  n      n
N-2?                   5     7  8         25
even?                  Y     n  Y         n
ans    -1  1  1 -1  1 -1  1  2  2  2      3
```

`10` even, not `4`/`6` → `2` (`3+7`).

`9` odd, `7` prime → `{2,7}` → `2`.

`27` odd, not prime, `25` not prime → peel `3`, leftover `24 = 5+19` → `3`.

Sample `4991`: not prime, `4989 = 3×1663` not prime → `3`. Leftover `4988` even.

## Insight

The only even prime is `2`, so parity decides the handful size. Even (except `4`, `6`) is two odds. Odd is either the number itself, `2` plus an odd prime, or three odds. You never need a fourth.

## Why the code is careful

- **Special-case `1`, `4`, `6` first.** Otherwise `4` and `6` fall into “even → `2`.”
- **Odd pair is only `N−2`.** Do not scan every prime `p` asking whether `N−p` is prime. One lookup.
- **Do not emit the actual primes.** Goldbach guarantees a pair exists; the judge only wants the count.
- **Sieve to `50000` inclusive.** Query `49999` is prime; the array must contain that slot.
- **Output is `Case i: X`.** 1-based, space after the colon.

## After AC — what could still improve

**0.03s** against `3s` is already in the right class: one sieve, then a handful of lookups per query. Cube is not waiting on us. Do not rewrite the accepted code unless asked.

**Time.** A linear sieve, a bitset, or a precomputed `ans[n]` array is the same `O(N log log N)` setup plus `O(1)` queries, not a faster class. `T = 50,000` lines of `Case i: X` is a small write; `sync_with_stdio(false)` already went in. Scanning primes to *find* a Goldbach pair would be slower and the judge does not ask for the pair.

**Memory.** The judge number was not recorded. A `char` array of length `50,001` is tens of KB against `1536 MB`. You have to store the sieve.

**Already as tight as it needs to be.** The bound that mattered was “do not fill a min-count table, do not search pairs.” After that, the judge is no longer the bottleneck.
