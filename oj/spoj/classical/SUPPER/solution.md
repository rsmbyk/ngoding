# SUPPER

## Fork: one value, cut at its place

There can be many longest increasing subsequences, and `n` is up to `100000`, so listing them is not the way in. A value is a supernumber when at least one longest chain uses it. The row cuts at that value: a chain to its left that ends on it, and a chain to its right that starts on it.

Sample, looking at `4`:

```
index:  1   2   3   4   5
value:  2   1   4   5   3
               ^
          left | right
```

`3` is the other value to try the same cut on. It sits at the end, so its right side is empty.

| value | longest chain ending here, from the left | longest chain starting here, to the right | joined |
| --- | --- | --- | --- |
| `4` | 2, as in `2, 4` or `1, 4` | 2, as in `4, 5` | `2 + 2 - 1 = 3` |
| `3` | 2, as in `2, 3` or `1, 3` | 1, the value alone | `2 + 1 - 1 = 2` |

The value itself is in both counts, so it is subtracted once. The longest chain in this row has length 3. `4` matches that length. `3` falls short.

`5` has a left chain of length 3, for example `2, 4, 5`, and a right chain of length 1, just `5`. Adding `3 + 1` writes `5` twice. The joined chain is `2, 4, 5`, length `3 + 1 - 1 = 3`, so `5` is a supernumber too.

| value | left | right | joined | supernumber? |
| --- | --- | --- | --- | --- |
| `2` | 1 | 3 (`2, 4, 5`) | 3 | yes |
| `1` | 1 | 3 (`1, 4, 5`) | 3 | yes |
| `4` | 2 | 2 | 3 | yes |
| `5` | 3 | 1 | 3 | yes |
| `3` | 2 | 1 | 2 | no |

A value is a supernumber when `left + right - 1` equals the longest chain anywhere in the row. The right lengths are the same idea walked from the other end.

## Fork: left length from earlier smaller values

Walking left to right, the left length at a value is one more than the best left length among earlier values that are strictly smaller. A larger earlier value cannot sit in front of it in an increasing chain.

Arriving at `4`, earlier rows are `2` and `1`, both smaller, both with left length 1. So `4` gets `1 + 1 = 2`.

Arriving at `3`, the earlier left lengths are 1, 1, 2, 3 on values `2, 1, 4, 5`. Only `2` and `1` are smaller than `3`. The 2 and the 3 belong to `4` and `5`, which are too big to prepend. So `3` gets `1 + 1 = 2`.

## The array, indexed by value

The permutation uses each of `1..n` once, so the left lengths can sit in an array whose index is the value. A query is the maximum on the prefix of smaller values. A write puts this value's left length into its own slot, for later bigger values to see.

Empty cells are 0. Sample, one value at a time:

| just reached | prefix queried | max there | left length written |
| --- | --- | --- | --- |
| `2` | value `1` | 0 | `best[2] = 1` |
| `1` | nothing smaller | 0 | `best[1] = 1` |
| `4` | values `1..3` | 1 | `best[4] = 2` |
| `5` | values `1..4` | 2 | `best[5] = 3` |
| `3` | values `1..2` | 1 | `best[3] = 2` |

`best[4]` and `best[5]` stay out of the query for `3`, which is what kept that left length at 2.

Scanning the prefix cell by cell is still too slow at `n = 100000`. A Fenwick tree is this same array with a few stored block-maximums, so a prefix maximum and a single-slot write each take about `log n` steps instead of `n`. It fits because every question is a prefix of the values and every write is one value. A segment tree answers the same two operations; the Fenwick tree is the smaller one for prefixes.

Each index stores the maximum of a block whose width is the lowest `1` in that index written in binary. The blocks for `n = 5`:

| index | binary | lowest 1 | block stored there |
| --- | --- | --- | --- |
| 1 | `0001` | 1 | just `1` |
| 2 | `0010` | 2 | `1..2` |
| 3 | `0011` | 1 | just `3` |
| 4 | `0100` | 4 | `1..4` |
| 5 | `0101` | 1 | just `5` |

A prefix is read by peeling those blocks off the right end. Values `1..3` are block `3` plus block `1..2`. A write at one value climbs to every wider block that contains it: writing value `2` updates index `2`, then index `4`.

After `2` and `1` have been written, the tree holds `1` in the blocks that cover them. The query for `4` reads values `1..3` and gets `1`, so the left length is `2`. That `2` is then written at index `4`, which is the block `1..4`. The later query for `5` reads that one block and gets `2`. The query for `3` stops after block `1..2` and never reads index `4`, so the left length stays `2`.

Raising a block maximum is enough here: each value is written once, and a left length never needs to go back down. The right-hand walk asks for values strictly greater than the current one, which is a suffix. Storing the length at index `n + 1 - value` turns that suffix into a prefix, so the same tree works.

The right lengths are the same walk from the other end. Already-seen values are then to the right, and the query is the values strictly greater than the one just reached.

## Code notes

`from_left` and `from_right` are those two lengths at each position. The tree is cleared between the walks. On the right-hand walk the slot is `n + 1 - value`, so a prefix of that flipped index is exactly the values greater than the current one. A value is kept when `from_left + from_right - 1` equals the longest `from_left` in the row. The printed line is those values sorted, because the walk meets them in position order.

## Insight

A value is on some longest increasing chain when the chain ending there and the chain starting there, counting that value once, match the longest chain in the row. The chains are prefix maximums over values: smaller values on the way forward, greater values on the way back. A Fenwick tree reads each of those prefixes in about `log n` steps.

## After AC — what could still improve

Accepted in **0.04s** of a `2.25s` limit. Memory was not reported.

**Time.** Ten permutations, `n` at most `100000`, and each value does two tree steps of about `log n`. Sorting the answer is smaller than that. `0.04s` does not need a different tree.

**Memory.** Two length rows and one tree of block maximums, each about `n` integers. It should sit at the usual one-file baseline.

**Already as tight as it needs to be.** Do not rewrite the accepted file. The bound that mattered was the two chain lengths, not the constant on the tree.
