# LOCKER — solution

## Forks

**One cut, at the middle.** Two pieces that add to `n` have product `x * (n - x)`. That is a downward parabola in `x`. The high point is `x = n / 2`. For an odd `n` the integers sit on either side of that point (`2` and `3` for the sample `n = 5`).

This is the best day among sales that use exactly two pieces. Vertu may use any number of pieces.

## The two-piece curve

`n = 10`. Only splits into two positive integers:

| pieces | product |
| --- | --- |
| `1 + 9` | 9 |
| `2 + 8` | 16 |
| `3 + 7` | 21 |
| `4 + 6` | 24 |
| `5 + 5` | 25 |

```
product
  25 |              *
  24 |           *
  21 |        *
  16 |     *
   9 |  *
     +--+--+--+--+-- piece
        1  2  3  4  5
```

The unconstrained product `x * y` has no highest point: either factor can grow forever. The middle shows up because the two pieces have to add to `n`.

## More than two pieces

`n = 8`. The middle cut is `4 * 4 = 16`. Four `2`s are also `16`.

| pieces | product |
| --- | --- |
| `4 + 4` | 16 |
| `2 + 2 + 2 + 2` | 16 |
| `3 + 3 + 2` | 18 |

`3 * 3 * 2 = 18` beats the middle cut. Equal pieces are the best two-piece sale, and they are not always the best day.

## Which single piece is worth cutting

A part `k` survives only when no split of `k` multiplies to more than `k`.

| `k` | a split | that product | leave `k` alone |
| --- | --- | --- | --- |
| 2 | `1 + 1` | 1 | 2 wins |
| 3 | `1 + 2` | 2 | 3 wins |
| 4 | `2 + 2` | 4 | tie |
| 5 | `2 + 3` | 6 | split wins |
| 6 | `3 + 3` | 9 | split wins (`2 + 2 + 2` is 8, still above 6) |

`2` and `3` stay whole. `4` may stay, or become two `2`s, same product. `5` and anything larger get cut, and the cut repeats on any leftover that is still `5` or more. What remains is `2`s, `3`s, and `4`s.

## Prefer 3s

Same 6 meters, two ways to spend them:

| pieces | product |
| --- | --- |
| `3 + 3` | 9 |
| `2 + 2 + 2` | 8 |

9 wins, so a `3` earns more product per meter than a `2`. The function behind that is `x^(1/x)`: the factor you gain for each meter tied up in a part of size `x`. It peaks near `e ≈ 2.718`. Among integers, `3` sits closer to that peak than `2` does (`3^(1/3) ≈ 1.44`, `2^(1/2) ≈ 1.41`).

Take as many `3`s as the rope allows. The leftover is `n mod 3`: `0`, `1`, or `2` meters. Leftover `0` is all `3`s. Leftover `2` is one `2` beside the `3`s.

## Leftover 1

Those last 4 meters, checked both ways:

| pieces | product |
| --- | --- |
| `3 + 1` | 3 |
| `2 + 2` | 4 |

`2 + 2` wins. A leftover `1` is one `3` plus that `1`. Swap that pair for two `2`s. The other `3`s stay.

`n = 7` (`7 mod 3 = 1`):

| pieces | product |
| --- | --- |
| `3 + 3 + 1` | 9 |
| `3 + 2 + 2` | 12 |

Same trade, with one `3` left in place.

`n = 1` has no `3` to give back. The only sale is `1`.

## The split

| `n mod 3` | pieces | product |
| --- | --- | --- |
| `0` | `n/3` threes | `3^(n/3)` |
| `1` (`n > 1`) | `(n/3 - 1)` threes and two `2`s | `3^(n/3 - 1) * 4` |
| `2` | `n/3` threes and one `2` | `3^(n/3) * 2` |

`n = 2` and `n = 3` are the one-piece answers `2` and `3`, which match the last two rows. Answer modulo `10^9 + 7`. `n` can be almost `10^12` and there can be almost `10^5` tests, so the power of `3` is a fast modular power, not a loop of length `n`.

## Code

`n <= 3` returns `n`. Those are the one-piece answers, and `n = 1` has no `3` to trade away.

`leftover == 1` uses `threes - 1` and multiplies by `4`. That is the swap of one `3` and the leftover `1` for two `2`s. `threes` is at least `1` here, because `n = 1` already returned and the next `n mod 3 = 1` value is `n = 4`.

`mod_pow` squares the base and halves the exponent, folding a factor into the result when the exponent is odd. Each multiply is reduced mod `10^9 + 7`, so the product never needs a big integer. Almost `10^5` tests is why input is untied from stdio.

## Insight

The middle of one cut is only the best two-piece sale. Keep cutting anything `5` or larger and the pieces left are `2`s and `3`s. A `3` earns more product per meter, because `x^(1/x)` peaks near `e` and `3` is the closest integer. A leftover `1` is one `3` plus that `1`, and those 4 meters want two `2`s instead. After that, `n` is only an exponent.

## After AC — what could still improve

Accepted in **0.06s**. Memory was not reported.

**Time.** Binary exponentiation is `O(log (n/3))` modular multiplies per test, and there are fewer than `10^5` tests. A loop of `n/3` multiplies is the thing that would miss the 1s limit. Montgomery multiplication or a hand-rolled `scanf` loop would be chasing a time that is already a small fraction of the limit.

**Memory.** No table. The program holds a few integers. It should sit at the usual one-file baseline.

**Already as tight as it needs to be.** Do not rewrite the accepted file. The bound that mattered was “do not walk the meters.”
