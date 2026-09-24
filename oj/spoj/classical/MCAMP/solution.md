# MCAMP

## Fork: one block, one inequality

The forcefield is always a contiguous block of camps. For a block from camp `L` to camp `R` (inclusive), it pays for itself when

`d[L] + d[L+1] + ... + d[R] >= x[R] - x[L]`

and its gold is `g[L] + ... + g[R]`. The answer is the largest gold among blocks that pass that test. A single camp always passes: length `0`, energy at least `1`.

Sample block `L = 0`, `R = 2`:

```
x:  0 ---- 1 ---- 4 ---- 7
d:  1      2      1      1
g:  5      7      4     15
         [=======]
         length 4
         energy 1+2+1 = 4
```

`4 >= 4`, so the block is legal, gold `16`.

## Fork: sliding window

The block is contiguous, so a sliding window is a natural try: grow the right end, and move the left end when the block stops paying for itself.

Check whether that "broken" signal is safe. Sample, start at `L = 0`, grow `R`:

| `R` | length `x[R]-x[0]` | energy `d[0]+…+d[R]` | pays? |
| --- | --- | --- | --- |
| 0 | 0 | 1 | yes |
| 1 | 1 | 3 | yes |
| 2 | 4 | 4 | yes |
| 3 | 7 | 5 | no |

At `R = 3` the window `[0, 3]` breaks. If the left end then moves forward, gold `16` from `[0, 2]` is already behind the window. A usual grow-until-broken pass only keeps one live window and can forget an earlier best.

`[0, 2]` pays (`4 >= 4`). Add camp `3` and the same left end fails: length becomes `7`, energy becomes `5`. So a legal block can become illegal when the right end grows. The usual sliding-window promise — “once it breaks, keep shoving left” — needs that kind of growth to be nested. Here it is not.

## Fork: split the inequality

Write `S[i]` for the total energy of camps `0 .. i`. Then

`d[L] + … + d[R] = S[R] - S[L - 1]`

(with `S[-1] = 0`). The pay test is

`S[R] - S[L - 1] >= x[R] - x[L]`

Move every `R` term to one side and every `L` term to the other:

`S[R] - x[R] >= S[L - 1] - x[L]`

Call the left side `A[R]` and the right side `B[L]`. A block `[L, R]` pays for itself exactly when `B[L] <= A[R]`.

Sample, `S = [1, 3, 4, 5]`:

| camp `i` | `A[i] = S[i] - x[i]` | `B[i] = S[i-1] - x[i]` |
| --- | --- | --- |
| 0 | `1 - 0 = 1` | `0 - 0 = 0` |
| 1 | `3 - 1 = 2` | `1 - 1 = 0` |
| 2 | `4 - 4 = 0` | `3 - 4 = -1` |
| 3 | `5 - 7 = -2` | `4 - 7 = -3` |

`[0, 2]`: `B[0] = 0` and `A[2] = 0`, so `0 <= 0`, pays. `[0, 3]`: `B[0] = 0` and `A[3] = -2`, so `0 <= -2` fails.

## Plain: fix the right end

Pick the rightmost camp of the forcefield first, say camp `2` on the sample. Then the left end can be `0`, `1`, or `2`. Only the choices with `B[L] <= A[2]` are legal.

`A[2] = 0`, so:

| left `L` | `B[L]` | `B[L] <= 0`? | gold in `[L, 2]` |
| --- | --- | --- | --- |
| 0 | 0 | yes | `5+7+4 = 16` |
| 1 | 0 | yes | `7+4 = 11` |
| 2 | -1 | yes | `4` |

The best gold for this right end is `16`. For every other right end, do the same and keep the global best.

Gold in `[L, R]` is “prefix gold up to `R`” minus “prefix gold before `L`”. So for a fixed `R`, a bigger gold means a smaller “prefix gold before `L`”. Among legal left ends, you want the one whose camps before it have the smallest gold total.

## Fork: walk right ends left to right

Walk `R` from left to right. When you pass a camp, it becomes a possible left end for this `R` and for later ones. Each possible left end `L` stores two numbers: its `B[L]`, and the gold sitting before it.

Standing at `R`, you need the smallest “gold before” among left ends with `B[L] <= A[R]`. Then the gold for this right end is “gold up to `R`” minus that smallest before-gold. The answer is the best of those.

`N` is `100000`, so scanning the whole list of left ends at every `R` is too slow. The ask is always “minimum among keys up to `A[R]`” — a prefix minimum on the `B` values.

## Sample walk

Prefix gold before camp `i` is `0, 5, 12, 16`. Gold up to `R` is `5, 12, 16, 31`.

Walk `R` left to right. First insert this camp as a left end: key `B[R]`, value = gold before it. Then ask for the minimum value among keys `<= A[R]`. Gold for this `R` is “gold up to `R`” minus that minimum.

| step | insert (`B`, gold before) | store after insert | `A[R]` | keys with `B <= A` | min gold before | gold for this `R` |
| --- | --- | --- | --- | --- | --- | --- |
| `R = 0` | `(0, 0)` | `(0, 0)` | 1 | `0` | 0 | `5 - 0 = 5` |
| `R = 1` | `(0, 5)` | `(0, 0)`, `(0, 5)` | 2 | both | 0 | `12 - 0 = 12` |
| `R = 2` | `(-1, 12)` | those plus `(-1, 12)` | 0 | all three | 0 | `16 - 0 = 16` |
| `R = 3` | `(-3, 16)` | those plus `(-3, 16)` | -2 | only `-3` (`0` and `-1` are too big) | 16 | `31 - 16 = 15` |

The best is `16`. At `R = 3` the earlier left ends are shut out because their `B` is larger than `A[3]`, so the broken long blocks never get counted.

## Code notes

`B` values are compressed to ranks for the Fenwick tree. A raise is a `lower`: store the minimum gold-before at that rank. A query is `upper_bound` on `A[R]` in the sorted keys, then a prefix minimum through that rank. Insert the current camp as a left end before the query so a single-camp forcefield is always available. Gold and energy prefixes use 64-bit integers.

## Insight

A legal forcefield is a contiguous block whose energy covers its length. That inequality splits into `B[L] <= A[R]`. For each right end, the best gold is “gold up to `R`” minus the smallest “gold before `L`” among legal left ends. A Fenwick tree of prefix minima on compressed `B` answers that ask in about `log N` per camp. A plain sliding window fails because a legal block can become illegal when the right end grows.

## After AC — what could still improve

Accepted in **0.69s** of a `1s` limit. Memory was not reported.

**Time.** `0.69s` is comfortable but not tiny. A monotone deque on candidates ordered by `B` can replace the Fenwick tree if the inserts stay sorted by something stronger; the compression-plus-tree path already clears the limit. Do not rewrite for that.

**Memory.** One Fenwick of `N` minima and a few prefix arrays. It should sit at the usual one-file baseline.

**Already as tight as it needs to be.** Do not rewrite the accepted file. The bound that mattered was the split `B[L] <= A[R]` plus a prefix minimum, not squeezing the tree constant.
