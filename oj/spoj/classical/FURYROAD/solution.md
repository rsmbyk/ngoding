# FURYROAD

## Fork: check every pair

A party is a connected group under the eight-neighbor rule. The obvious pass is: for every boy, look at every other boy, and if they stand on neighboring cells (including diagonally), put them in the same party.

That finds the right links. With `N = 10000` it also tries about `N^2 / 2` pairs per test, and there are up to `50` tests. Most of those pairs are nowhere near each other: two boys are neighbors only when both `|dx|` and `|dy|` are at most `1`.

## Fork: the plane is a small grid

`Xi` and `Yi` only run from `0` to `1000`, so the plane is a `1001 × 1001` grid. Mark every cell that holds a boy. For one boy at `(x, y)`, the only cells that can touch him are the eight around him (and his own cell if another boy stands there).

```
(x-1,y+1) (x,y+1) (x+1,y+1)
(x-1,y)   (x,y)   (x+1,y)
(x-1,y-1) (x,y-1) (x+1,y-1)
```

That is at most nine checks per boy, not `N` of them.

## Fork: paint one party at a time

Pick a boy that is not yet painted. Paint him, then keep painting every marked neighbor of a painted boy, and their neighbors, until that blob is done. That whole blob is one party. Count `1`, then pick the next unpainted boy and repeat.

Sample test 2 on the grid (marks are `*`):

```
y=3:  . * * .
y=2:  . * . .
y=1:  * . . * .
y=0:  . . . . *
      x=0 1 2 3 4 5
```

Start at `(0, 1)`. The paint reaches `(1, 2)`, `(1, 3)`, `(2, 3)` through edge and corner steps. That is party 1. The next unpainted marks are `(4, 1)` and `(5, 0)`, which touch each other — party 2.

## Code notes

A `1001 × 1001` grid marks occupied cells. For each unpainted boy, a queue flood fill paints the whole eight-neighbor blob and adds one party. Boys that share a cell are one mark, so they never start a second party.

## Insight

A party is a connected component on the plane under eight-neighbor adjacency. The coordinate bounds make a dense grid cheap, so each boy only looks at the nine cells around him, and a flood fill counts the blobs.

## After AC — what could still improve

Accepted in **0.16s** of a `1s` limit. Memory was not reported.

**Time.** Allocating a fresh `1001 × 1001` grid every test is simple and already fast. Reusing one static grid and clearing only the used cells would cut the constant. `0.16s` does not need that.

**Memory.** Two grids of about a million flags. It should sit at the usual one-file baseline.

**Already as tight as it needs to be.** Do not rewrite the accepted file. The bound that mattered was the grid flood fill, not a Union-Find over pairs.
