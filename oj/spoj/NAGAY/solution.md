# NAGAY — solution

Accepted on SPOJ. Time **0.02s**, memory **5.2M**.

## Forks

**Loop `i = 1 … n`.** `n ≤ 10^18`. Dead.

**Rewrite.** `k mod i = k − i · ⌊k/i⌋`, so `S = n·k − ∑ i · ⌊k/i⌋` up to `min(n, k)`. True, and a good check. Still `10^18` terms unless `⌊k/i⌋` is constant on stretches we can skip.

**Watch the remainders.** Same stretches, seen from `k mod i` instead of the quotient. That is the path below.

## Remainders as `i` grows

Fix `k = 10`, run `i` from 1 to 15 (`n > k` so the tail shows up):

```
i      1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
k%i    0  0  1  2  0  4  3  2  1  0 10 10 10 10 10
⌊k/i⌋ 10  5  3  2  2  1  1  1  1  1  0  0  0  0  0
              └──┘  \──────────/  \────────────/
              −2       −1              stuck at k
```

Three shapes, nothing else:

- **`i > k`.** Remainder is `k` forever. Tail sum `k · (n − k)`.
- **Quotient frozen at `p ≥ 1`.** Each next `i` subtracts `p` from the remainder: `k = p·i + r` becomes `k = p·(i+1) + (r−p)`. The terms are an **arithmetic series** — constant difference, here `−p`. The series dies when the next term would be negative.
- **A one-term blip** is the same rule: `r < p`, so the series has length 1.

The last `i` of a `p`-block is the last index where remainder stays non-negative under that countdown: from current `(i, r, p)`, you can take `⌊r/p⌋` further steps, so **`⌊r/p⌋ + 1` terms**, capped by `n`. Then jump.

That jump is also `⌊k/p⌋`: `r = k − p·i`, so `i + ⌊r/p⌋ = ⌊k/p⌋`. Same right endpoint the rewrite would have used for “`⌊k/i⌋` stays `p`”.

## Arithmetic series

Terms `r`, `r−p`, `r−2p`, …, `r−(cnt−1)p`. Count `cnt`. Sum is `cnt · (first + last) / 2`, i.e. `cnt · (2r − (cnt−1)·p) / 2`. One closed form per block, not one add per `i`.

## Tiny example

Sample `n = 5`, `k = 3`.

| start `i` | `r` | `p` | `cnt` | terms | add |
| --- | --- | --- | --- | --- | --- |
| 1 | 0 | 3 | 1 | `0` | 0 |
| 2 | 1 | 1 | 2 | `1, 0` | 1 |
| 4 | 3 | 0 | 2 | `3, 3` | 6 |

Total `7`. The `p = 0` row is the tail `i > k`.

`k = 10`, `n = 15`, same walk: `0 + 0 + 1 + (2+0) + (4+3+2+1+0) + 5·10 = 63`. Rewrite check: `15·10 − ∑_{i=1}^{10} i⌊10/i⌋ = 150 − 87 = 63`.

## Why the code is careful

- **Cap `n` to `k` first.** The tail `i > k` is `k · (n − k)`. After the cap, `⌊k/i⌋ ≥ 1` on the loop, so `rem / p` is never a divide by zero.
- **`__int128`.** `k · (n − k)` and `cnt · (2r − (cnt−1)p)` reach `~10^36`. 64-bit wraps. `__int128` holds it (`2^127 ≈ 1.7 · 10^38`). `iostream` will not print it; write digits by hand.
- **`/ 2` is exact.** `cnt · (2r − (cnt−1)p)` is always even: `2r` is even, so if `(cnt−1)p` is odd then `cnt` is even.
- **`last = i + rem/p`.** That is `⌊k/p⌋`, already in 64 bits (`≤ k`). No `i + extra` overflow.

Number of blocks is the number of distinct `⌊k/i⌋` for `i ≤ min(n,k)`, which is `O(√k)`. That is **number-theoretic blocking** (also called divisor blocking): for a fixed `n`, `⌊n/i⌋` stays constant on contiguous ranges of `i`, there are `O(√n)` such ranges, and the right end of the range that starts at `L` is `min(n, ⌊n / ⌊n/L⌋⌋)`. The remainder countdown is the same partition, seen from `k mod i` instead of from the quotient. At `k = 10^18` that is about `2·10^9` jumps. The tests did not go there.

## Insight

When the quotient is frozen, remainders just count down by that quotient. The countdown tells you how far to jump, and the jump’s sum is one arithmetic series.

## After AC — what could still improve

**0.02s** answers the live worry. Locally `n = k = 10^15` already took `0.75s`. Cube finishing in `0.02s` means the tests sit near the original NEERC `10^9` (about `2√k ≈ 6·10^4` jumps), not the `10^18` printed on the page. Blue.Mary’s “`O(√k)` CAN pass” was about this judge. A comment also says the judge solution cannot handle many cases — the bound on the page is not what ran.

**Time.** These jumps are `Θ(√k)` blocks. You cannot keep this loop and survive a real `k = 10^18` in `1s` on Cube; `2·10^9` iterations do not fit. The next level is a sub-`√k` floor-sum: batch many consecutive quotients in one shot (the practical `O(k^{1/3})` algorithms for `∑ ⌊k/i⌋` and friends), not a tighter inner arithmetic series. The rewrite `S = n·k − ∑ i·⌊k/i⌋` is the same blocks with a different formula per block. Neither would move `0.02s`.

**Memory.** **5.2M** is the one-file baseline. No array.

**Width.** For `n, k ≤ 10^9` the sum fits in signed 64-bit (`≤ n(n−1)/2 ≈ 5·10^17`). `__int128` is the right width for the printed `10^18` bound even if the tests never filled it.

Already as tight as this judge needs. Do not rewrite the accepted file.
