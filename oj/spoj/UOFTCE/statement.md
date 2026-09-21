# UOFTCE — A Brief Expedition

Alice is dragging Bob through `M` malls. She will hit **every store** in every mall. Bob wants it over quickly. Alice promised to minimise the time on her stopwatch.

Each mall is a grid of `R` rows by `C` columns. A cell is one of:

- `#` — wall (blocked)
- `.` — open floor
- `S` — a store (at least one)
- `C` — Bob's car (exactly one)

They walk in the four directions, one cell per minute, and cannot step on a wall. Stores and the car are walkable. Walking through a store does **not** count as shopping there.

The loop at one mall:

1. Start at the car.
2. Walk to a store they have not shopped at yet (other stores may sit on the path; ignore them).
3. Shop for **60 minutes**.
4. Because of how much they bought, walk **back to the car** and drop it off.
5. Repeat from step 2 until every store has been shopped.

Every store is reachable from the car. The order of stores is theirs to choose.

Alice's stopwatch is the twist. It starts when they **begin shopping at the first store**, not when they leave the car. It stops when the **last** load is dropped at the car. So the opening walk from car to first store is free. Everything after that is timed: first shop, first return, later walks, later shops, and the final return.

For each mall, print that stopwatch time, minimised.

Source: [SPOJ UOFTCE](https://www.spoj.com/problems/UOFTCE/). Own problem by SourSpinach, used in U of T ACM tryouts (2014-02-18). Time `3s`, memory `1536 MB`, source `50000` bytes. Cluster: Cube (Intel G860). Tagged `#bfs`. Same statement lives on DMOJ as [acmtryouts3e](https://dmoj.ca/problem/acmtryouts3e).

## Input

- Line 1: `M` — number of malls.
- Then `M` malls. Each mall:
  - Line 1: two integers `R` and `C`.
  - Next `R` lines: `C` characters each, the grid. The original writes `i = 1..H` for the row index; that `H` is `R`.

Malls are independent.

## Output

One integer per mall: the minimum stopwatch minutes for that mall. One line each.

## Constraints

- `1 ≤ M ≤ 100`
- `1 ≤ R, C ≤ 100`
- At least one `S`, exactly one `C`
- Every store is reachable from the car
- Time `3s`, so `M · R · C` up to `10^6` cells is comfortable for a linear scan of each mall
- Number of stores is not capped separately: a mall can be almost all `S`, so up to about `R · C − 1` stores
- A walk between two cells is at most `R · C` minutes (a path cannot revisit a cell on a shortest route)

Shopping time is `60` per store and cannot be avoided, so the answer is at least `60 · (number of stores)` plus the walking that the stopwatch still sees.

## Special cases

- One store: walk there free, shop `60`, walk back. Answer is `60 + dist(car, that store)`.
- A store next to the car: that round trip is `2` minutes of walking (or `1` if it is the first store, because the outbound is free).
- Passing through an unvisited store on the way to another does not shop it. They still have to come back for it later (car in between).
- Walls can make the walk much longer than Manhattan. The sample's top store is two cells from the car on the map and eight minutes away on foot.
- The car cell can be walked onto later. Stores are not walls.

## Sample

Input:

```
2
4 4
..S#
.##C
....
S.#S
1 5
SSCSS
```

Output:

```
202
250
```

### Mall 1

```
  c0 c1 c2 c3
r0 .  .  T  #
r1 .  #  #  C
r2 .  .  .  .
r3 BL .  #  BR
```

Car `C` at `(1,3)`. Stores: top `T` `(0,2)`, bottom-left `BL` `(3,0)`, bottom-right `BR` `(3,3)`.

Shortest walks from the car: `T = 8`, `BL = 5`, `BR = 2`. One shortest path to `T` goes down and around the left, because the cells above and left of the car are walls.

The sample order is `T`, then `BL`, then `BR`:

| step | minutes | on the clock? |
| --- | ---: | --- |
| car → `T` | 8 | no |
| shop `T` | 60 | yes |
| `T` → car | 8 | yes |
| car → `BL` | 5 | yes |
| shop `BL` | 60 | yes |
| `BL` → car | 5 | yes |
| car → `BR` | 2 | yes |
| shop `BR` | 60 | yes |
| `BR` → car | 2 | yes |

Timed total `60+8+5+60+5+2+60+2 = 202`.

### Mall 2

One row `S S C S S`. Distances from the car: `2, 1, 1, 2`. Left-to-right shopping:

`60 + 2 + 1 + 60 + 1 + 1 + 60 + 1 + 2 + 60 + 2 = 250`.
