# DISTANCE — Manhattan

You are given `N` distinct points in `d`-dimensional space. The distance between two points is **L1** (Manhattan): the sum of absolute coordinate differences.

For points `x` and `y`:

```
|x1 - y1| + |x2 - y2| + … + |xd - yd|
```

Find a pair whose L1 distance is as large as it can be, and print that distance. (The statement says “in the plane,” then immediately gives `d` up to 6. The space is `d`-dimensional, not necessarily 2-D.)

Source: [SPOJ DISTANCE](https://www.spoj.com/problems/DISTANCE/)

## Input

One test.

- First line: two integers `N` and `d` — number of points and dimension.
- Then `N` lines. Line `i` is `d` space-separated integers, the coordinates of the `i`-th point.

All points are distinct.

## Output

One integer: the farthest L1 distance between any pair of input points, followed by a newline.

## Constraints

- `2 ≤ N ≤ 100000`
- `1 ≤ d ≤ 6`
- Each coordinate is an integer with absolute value at most `1000000`
- Time limit about `1s`–`4.4s`

A pair’s distance is at most `d * 2 * 10^6 = 1.2 * 10^7`.

## Special cases

- `d = 1` is just `max(x) - min(x)` on a line.
- Points are distinct, so the answer is at least `1`.
- Coordinates can be negative. L1 does not care about origin — only differences.
- Extra dimensions can only make a pair farther or leave it the same, never closer.

## Sample

Input:

```
3 2
0 0
-5 0
1 1
```

Output:

```
7
```

The three pairs:

| pair | L1 |
| --- | --- |
| `(0, 0)` and `(-5, 0)` | `5 + 0 = 5` |
| `(0, 0)` and `(1, 1)` | `1 + 1 = 2` |
| `(-5, 0)` and `(1, 1)` | `6 + 1 = 7` |

The farthest is 7.
