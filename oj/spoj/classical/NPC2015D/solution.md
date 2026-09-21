# NPC2015D — solution

Accepted on SPOJ. Time **0.09s**, memory **5.2M**.

## Forks

**DP table over the sum.** For each sum `s`, try every last part `k` and keep `k * best(s-k)`. Honest brute force. `N = 10^18` kills the table. Tiny `N` is still how the pattern showed up.

**Enumerate partitions.** Worse.

**Replacement, then a closed form.** If a part `k` can be split into pieces whose product is larger than `k`, an optimum never keeps `k`: swap the part for that split, the sum is still `N`, the product grows. After every bad part is gone, only `2`s and `3`s remain, and the count is forced by `N mod 3`.

## Tiny table

Hand / tiny DP, `N = 1` through `12`. A one-part split is allowed. No zeros.

| `N` | a winning split | product | a worse split |
| --- | --- | --- | --- |
| 1 | `1` | 1 | — |
| 2 | `2` | 2 | `1+1 → 1` |
| 3 | `3` | 3 | `1+2 → 2` |
| 4 | `2+2` (tie with `4`) | 4 | `1+3 → 3` |
| 5 | `2+3` | 6 | `5 → 5` |
| 6 | `3+3` | 9 | `2+2+2 → 8` |
| 7 | `3+2+2` | 12 | `3+4 → 12` (tie), `7 → 7` |
| 8 | `3+3+2` | 18 | `2+2+2+2 → 16` |
| 9 | `3+3+3` | 27 | `3+3+2+1 → 18` |
| 10 | `3+3+2+2` | 36 | `3+3+4 → 36` (tie) |
| 11 | `3+3+3+2` | 54 | `3+3+5 → 45` |
| 12 | `3+3+3+3` | 81 | `2+2+2+3+3 → 72` |

## Replacement

A part that is itself a worse split of its own size cannot survive.

**`k ≥ 5`, even.** Replace `k` by `2 + (k-2)`. Product `2(k-2) = 2k-4`. That beats `k` exactly when `k > 4`. So every even part `≥ 6` is already worse than splitting off a `2`.

**`k ≥ 5`, odd.** Replace `k` by `3 + (k-3)`. Product `3(k-3) = 3k-9`. That beats `k` exactly when `k ≥ 5`. So every odd part `≥ 5` is already worse than splitting off a `3`.

One step is enough to *forbid* keeping `k`. The leftover `k-2` or `k-3` may still be large; repeat. Everything collapses to `2`s and `3`s (and `4`s, next).

```
5  →  2 + 3          6 > 5
6  →  3 + 3          9 > 6
7  →  3 + 4 → 3+2+2  12 > 7
8  →  2 + 6 → 2+3+3  18 > 8
```

**`4`.** `2+2` has product `4`, same as keeping `4`. Never strictly better, never strictly worse. Treat `4` as `2+2` so the next rewrite has a uniform shape.

**Three `2`s.** `2+2+2` sums to `6` with product `8`. `3+3` sums to `6` with product `9`. Never keep three `2`s.

**A leftover `1`.** `3+1` sums to `4` with product `3`. `2+2` sums to `4` with product `4`. So `N = 3m+1` is not `m` threes and a one: drop one three, write two twos.

`2` and `3` themselves cannot be improved (`1+1 < 2`, `1+2 < 3`). Those are the only parts an optimum is allowed to keep.

## Algorithm

After the rewrites, the split is forced by `N mod 3`:

| `N` | residue | split | product |
| --- | --- | --- | --- |
| `3m` | 0 | `m` threes | `3^m` |
| `3m+1` (`N ≥ 4`) | 1 | `m-1` threes and two twos | `3^{m-1} · 4` |
| `3m+2` | 2 | `m` threes and one two | `3^m · 2` |

`N ≤ 3` is just `N` (`N = 1` is `3·0+1`, and `m-1` would be `-1`).

The exponent is about `N/3`, up to `~3·10^17`. Multiplying `3` that many times is dead. **Binary exponentiation** (square-and-multiply): to compute `b^e`, square the base and consume the bits of `e` — if the bit is 1, multiply into the answer. About `log2(e) ≤ 60` modular multiplies, which is why it fits `N = 10^18` and a `1s` limit. Do every multiply modulo `10^9+7`. Two factors each `< 10^9+7` still fit in a 64-bit `long long` before the `%`.

## Tiny example

The table already is the proof of the three residues:

- `12 = 3·4` → `3^4 = 81`
- `10 = 3·3+1` → `3^2 · 4 = 36`
- `11 = 3·3+2` → `3^3 · 2 = 54`

`5 = 3·1+2` → `3^1 · 2 = 6`, sample 2. `2 = 3·0+2` → `2`, sample 1.

## Code notes

`n <= 3` returns `n` before any `n % 3 == 1` branch: that branch does `3^{m-1}`, and `n = 1` has `m = 0`.

The `* 4` is `2 · 2` in one multiply. `r == 2` is `* 2`. Both stay inside `long long` before `%` because each factor is already `< 10^9+7`.

## Insight

An optimum never keeps a part that is a worse split of itself. That kills everything except `2` and `3`, and `N mod 3` then picks the counts. The huge `N` is only an exponent.

## After AC — what could still improve

The accepted code is already the right complexity. About 60 modular multiplies and one integer of I/O. **0.09s** on Cube is the process coming up, not the powering. **5.2M** is the same baseline as other one-file programs here — we allocate nothing.

**Time.** Binary exponentiation is `O(log (N/3))`. A linear loop of `N/3` multiplies is the thing that would TLE; we already did not do that. Fancier modular multiplication (Montgomery, 128-bit words) is for when you do millions of multiplies, not sixty. `scanf` instead of iostream would not move 0.09s on one token.

**Memory.** No array. The `n <= 3` guard is a branch, not a table.

**Already as tight as it needs to be.** Do not rewrite the accepted file. The bound that mattered was “do not walk `1..N`.” After that, the judge is no longer the bottleneck.
