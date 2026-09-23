# NDIV

## Fork: the range is short

`a` and `b` can sit near `10^9`, but `b - a` is at most `10000`. So at most about ten thousand integers need a divisor count. The whole range `1 .. 10^9` does not.

The sample range `[1, 7]` is tiny. A larger window of the same shape looks like `[10^9 - 5, 10^9]`: still only six numbers to inspect, even though each one is huge.

## Fork: divisors come in pairs

Checking every candidate from `1` through `x` finds every divisor, and for `x` near `10^9` that is a billion checks on one number. Divisors come in pairs: if `d` divides `x`, so does `x / d`. One of the two is at most `sqrt(x)`. Walking only up to `sqrt(x)` is enough.

For `x = 8`, `sqrt(8)` is a bit under `3`:

| `d` | divides `8`? | pair |
| --- | --- | --- |
| 1 | yes | `8 / 1 = 8` |
| 2 | yes | `8 / 2 = 4` |
| 3 | no | |

That finds `1, 8, 2, 4` — four divisors, which matches the statement.

## First attempt: pair counting (TLE)

Walk every `x` from `a` to `b`. For each `x`, walk every integer `d` from `1` while `d * d <= x`. When `d` divides `x`, count two divisors if `d` and `x / d` differ, and one if they are the same (perfect square). If the tally equals `n`, keep `x`.

Sample `a = 1`, `b = 7`, `n = 2`:

| `x` | divisor count | keep? |
| --- | --- | --- |
| 1 | 1 | no |
| 2 | 2 | yes |
| 3 | 2 | yes |
| 4 | 3 (`1, 2, 4`) | no |
| 5 | 2 | yes |
| 6 | 4 | no |
| 7 | 2 | yes |

Four keeps, which matches the sample. That version was submitted and the judge returned TLE.

About `10001 * 31623` is roughly `3 * 10^8` trial divisions on a worst window. The idea of the window was right. The inner walk was too heavy: most of those `d` are composite and can never be the next new prime factor of `x`.

## Accepted: peel primes only

If `x` factors as `p1^e1 * p2^e2 * ...`, the number of positive divisors is `(e1 + 1) * (e2 + 1) * ...`. For `8 = 2^3` that is `4`. For `12 = 2^2 * 3^1` that is `6`.

Only primes need to be tried when peeling `x` apart. There are about `3400` primes up to `sqrt(10^9)`, so the same window is closer to `10001 * 3400` tries. Sieve those primes once up to `31623`. For each `x` in the window, divide out each prime, multiply `(exponent + 1)` into the tally, and if a leftover bigger than `1` remains, multiply by `2` (one last prime). `x = 1` has count `1` with no peels. If `a > b`, the answer is `0`.

## Code notes

Primes up to `31623` are sieved once. The factor loop stops when `prime * prime > leftover`. Every product for the divisor tally stays small because `n` is at most `100` and we only care whether the tally equals `n`.

## Insight

The range is short, so each `x` can be handled on its own. Counting divisors by walking every integer up to `sqrt(x)` is the right shape and the wrong constant. Peeling only primes, then using `(e + 1)` products, is the same factorization idea with a thin enough inner loop.

## After AC — what could still improve

Accepted in **0.29s** of a `1s` limit. Memory was not reported.

**Time.** A segmented smallest-prime-factor sieve over `[a, b]` would factor each `x` in fewer random mods. `0.29s` already clears the limit. Do not rewrite for that.

**Memory.** One prime list of a few thousand integers. It should sit at the usual one-file baseline.

**Already as tight as it needs to be.** Do not rewrite the accepted file. The bound that mattered was dropping composite trial divisors, not a heavier sieve over the window.
