# RPLB — solution

## Forks

**Sliding window.** A window keeps one contiguous stretch of the row and moves the ends. The best pick in case 1 is bush 1 and bush 5 (`50 + 40 = 90`). Those two are not a contiguous stretch: bushes 2, 3, and 4 are skipped, and bush 3 (`20`) is left out even though it is not a neighbor of either pick. The kept bushes are a subset with gaps, under a sum cap.

**Dynamic programming.** Each bush is a yes-or-no, and a later bush only needs a summary of the earlier choices. Solve each smaller prefix of the row once and reuse it. The number in a cell is the higher total for that one situation. One running best for the whole prefix is too coarse: a lighter basket can still win later.

Case 1, limit `100`. After bush 3, two legal baskets:

| path so far | basket | bush 4 taken? |
| --- | --- | --- |
| `50 + 20` | 70 | no |
| `50`, skip `20` | 50 | no |

The higher number is `70`. Bush 5 is `40`. `70 + 40 = 110` breaks the limit, so that path stays at `70`. The lighter path takes `40` and reaches `90`, which is the answer. Same adjacency, different fill. The cell has to know how full the basket already is.

**Two totals, took-previous and not.** That splits the neighbor fact. Walking case 1 with only those two numbers, and refusing any total over `100`:

| after bush | took it | left it |
| --- | --- | --- |
| `50` | 50 | 0 |
| `10` | 10 | 50 |
| `20` | 70 | 50 |
| `30` | 80 | 70 |
| `40` | — (`70 + 40` is over) | 80 |

The answer `90` is `50` (left the `20` and the `30`) plus the last `40`. That `50` sat in “left it” next to `70`, and a single number would replace it. Keep every fill that is still legal. The slot label is the fill itself, so `50` and `70` are different cells on the same “left it” side.

After the bush of `30`, the “left it” side still holds both:

```
fill     50      70
left    [50]    [70]
          |
          +40 → 90     70+40 = 110, over the limit, no write
```

Taking a bush of `a` reads a “left it” slot `s` and, when `s + a ≤ K`, writes slot `s + a` on the “took it” side. Leaving the bush copies every slot forward onto “left it”. `K ≤ 1000`, so the slots are `0 .. K` on each side.

## Code

The slot index is the total already carried, so the cell is a yes-or-no: that total is reachable. The answer is the highest slot that is on, on either side. Two ways to make the same total share a slot, because the total is the score.

Taking reads only the “left it” side, so two neighbors cannot both be on. A bush of `a ≤ 0` is never taken: it adds nothing and blocks the next bush. A bush bigger than the room left in the limit writes nothing.

`N` and `K` are at most `1000`, so one pass over the bushes and the slots is enough for the `0.439s` limit. The arrays are rebuilt from the previous bush, so a bush cannot be counted twice.

## Insight

The kept bushes are a subset with gaps, so one running best throws away a lighter basket that still fits a later bush. The slot label is the fill itself, and both `50` and `70` stay. Taking reads only the “left it” side, which is what keeps two neighbors from both being on.

## After AC — what could still improve

Accepted in **0.05s** of a `0.439s` limit. Memory was not reported.

**Time.** One pass over `N` bushes and `K + 1` slots, and both are at most `1000`. The inner loop is already a scan of reachable fills. A bitset would turn “leave the bush” into an OR and “take `a`” into a shift by `a`, which cuts the constant. `0.05s` does not need that.

**Memory.** Two rows of `K + 1` flags. No table of paths. It should sit at the usual one-file baseline.

**Already as tight as it needs to be.** Do not rewrite the accepted file. The bound that mattered was keeping every fill, not squeezing the scan.
