# DISTANCE — solution

Accepted on SPOJ (0.63s, 5.4M).

## Forks

**Pair every pair.** `N` is `10^5`. About `N²/2` pairs, each a loop of `d` abs. On the order of `10^10`. Dead.

**Keep the abs, stay geometric.** In 2-D the usual move is a 45° change of coordinates, then a bounding box. That is the fork we took. `d` goes up to 6, so the live question is what those two axes become in higher D.

## 2-D: rotate, then read the box

Map

```
u = x + y
v = x - y
```

L1 in `(x, y)` is Chebyshev in `(u, v)`:

```
|Δx| + |Δy| = max(|Δu|, |Δv|)
```

The farthest Chebyshev pair of a set is the longer side of the axis-aligned bounding box. No pair search: `max(u_max - u_min, v_max - v_min)`.

```mermaid
flowchart LR
  xy["points in x y"] --> rot["u = x+y, v = x-y"]
  rot --> box["AABB in u v"]
  box --> ans["L1 diameter = longer side"]
```

`u = x+y` and `v = x-y` are the two independent ways to attach ± to the coordinates. The other two (`-x-y`, `-x+y`) are just negations — same span.

## The lift (same geometry, more axes)

In `d`-D the “rotated axes” are all signed sums

```
s_ε(p) = ε1 p1 + ε2 p2 + … + εd pd
```

with each `εi = ±1`. There are `2^d` of them (`64` when `d = 6`), or `2^{d-1}` if we drop negations.

Same identity as 2-D:

```
|Δx1| + … + |Δxd| = max over ε of |s_ε(p) - s_ε(q)|
```

so the L1 diameter is the longest side of the AABB in that `2^d`-axis space: for each sign pattern `ε`, track `max s_ε - min s_ε`; the answer is the max of those.

Work: `N × 2^d × d` ≈ `10^5 × 64 × 6` ≈ `4·10^7`. Comfortable. Store `N × d` ints (~2.4 MB).

This is not a different trick from “brute the signs.” It is the 2-D rotation written so it still has a meaning when `d` is 6.

## Tiny example

The official sample. Transformed:

- `(0, 0)` → `(u, v) = (0, 0)`
- `(-5, 0)` → `(-5, -5)`
- `(1, 1)` → `(2, 0)`

`u` span = `2 - (-5) = 7`. `v` span = `0 - (-5) = 5`. Answer 7.

The same numbers as four signed-sum masks (`+` when the bit is set):

```
mask   εx εy    (0,0)  (-5,0)  (1,1)   max   min   span
  00    -  -       0      5     -2      5    -2      7
  01    +  -       0     -5      0      0    -5      5
  10    -  +       0      5      0      5     0      5
  11    +  +       0     -5      2      2    -5      7
```

Masks `00` and `11` are negations of each other; same span. The longest side is 7, matching the pair `(-5, 0)` and `(1, 1)`.

## Why the code is careful

The idea does not fail. Starting min/max and the sign bit do.

- **Seed min/max from empty.** Before any point, `min` has to be `+∞` and `max` `-∞`. Zero is a legal signed sum, so seeding both at `0` is wrong on an all-negative (or all-positive) projection.
- **A bit is a sign, not a coordinate.** Mask bit `j` set means `+p_j`, unset means `-p_j`. Flipping that convention still works — it only swaps a mask with its negation.
- **64-bit is house style, not a requirement.** A signed sum is at most `d × 10^6 = 6·10^6`; the span at most twice that. 32-bit holds. We still use `i64` like CURDPROD.

## Insight

L1 diameter is the longest side of the axis-aligned bounding box after you project every point onto the diagonals of the unit hypercube. In 2-D those diagonals are `x+y` and `x-y`. In 6-D there are 64 of them, and `N` is still linear.

## After AC — what could still improve

The accepted code is already in the right complexity class. The judge ran it in **0.63s / 5.4M** against a 1s–4.4s limit. What is left is polish, not a new algorithm. Do not rewrite the accepted code unless asked.

**Time.** The inner loop is `N × 2^d × d` signed adds, about `4·10^7` at the worst case. That is the work. `sync_with_stdio(false)` is already on; a custom scanner would shave the `N × d` reads, not the projections.

Still on the table:

- **Half the masks.** `ε` and `-ε` give the same span. Looping `2^{d-1}` instead of `2^d` cuts the projections in half. On a 0.63s run that is the one constant factor that would actually show.
- **Drop the inner branch.** For each mask, build a `±1` table of length `d` once, then `sum += sign[j] * p[j]`. Or keep `int` in the inner loop: signed sums fit in 32-bit, and `i64` is house style, not speed.
- **Layout.** `array<int, 6>` wastes a few ints when `d < 6`. At the tight case `d = 6` it is exact. A flat `vector<int>` of `n * d` would pack the lower-`d` tests and might scan a little hotter. Invisible next to the mask count.

**Memory.** 5.4M is the process, not just the points. The `vector` of `N` `array<int,6>` is `N × 24` bytes ≈ 2.4 MB; the rest is the binary, iostream, and allocator slack. You need every coordinate on every mask, so you have to store them. Rereading the file once per mask would trade memory for I/O and lose. Packing to `n * d` ints only helps when `d < 6`.

**Clarity.** A `signed_sum(point, mask, d)` helper would make `main` “for each mask, max − min” instead of a triple loop that also contains the geometry. Seeding min/max from `numeric_limits` is already the right empty-set start.

None of this is worth a second submission. The bound that mattered was “do not pair every pair.” After that, the judge is no longer the bottleneck.
