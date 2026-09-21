# NICEDAY — solution

Accepted on SPOJ. Time **0.09s**, memory **5.2M**.

## Forks

**Pair every pair.** `N` is `10^5`. Dead.

**Sort by contest 1, scan left.** Anyone who can dominate you is already behind you. Correct. The left side can be all `N` excellent people, so the scan is still `N²`. Dead on time, not on the idea.

**Same sort, one prefix query (this path).** After the sort, “does anyone on the left beat me on both leftover contests?” is: among people with a better contest-2 rank, is the **best** contest-3 rank also better than mine?

## Algorithm

Sort contestants by contest 1, best first. Process in that order.

Person `P` with contest-2 rank `b` and contest-3 rank `c` is dominated iff

```
min { c_j  |  j already processed and b_j < b }  <  c
```

If that min does not exist (nobody has a better contest-2 rank yet), `P` is excellent. Then record `P`: at index `b`, store `c`.

Contest-2 ranks are a permutation of `1 … N`, so each index is written once. Query is always a **prefix** `[1, b)`.

A **Fenwick tree** (binary indexed tree) fits that shape. It is an array where index `i` stores an aggregate of a contiguous block ending at `i`, length = the lowest set bit of `i`. Walking `i += i & -i` updates a point; walking `i -= i & -i` reads a prefix. Usually the aggregate is a sum. Here it is **min**. We only ever lower a cell from “empty” to `c`, never raise it, so min is a legal aggregate.

Segment tree also answers it. The query is a prefix, so Fenwick is enough and smaller.

Work: sort `O(N log N)` (or place by contest-1 rank in `O(N)`, since that rank is a permutation) plus `N` queries and `N` updates, each `O(log N)`.

## Tiny example

Already sorted on contest 1:

| id | contest 1 | contest 2 | contest 3 |
| --- | --- | --- | --- |
| A | 1 | 2 | 3 |
| B | 2 | 1 | 4 |
| C | 3 | 3 | 1 |
| D | 4 | 4 | 2 |

Fenwick index = contest 2. Value = contest 3. Empty = `∞`.

```
contest 2 →   1        2        3        4
              ┌─────────────────────────────────┐
after A       ∞        3        ∞        ∞       query [1,1] = ∞  → A in
after B       4        3        ∞        ∞       query [1,0] = ∞  → B in
after C       4        3        1        ∞       query [1,2] = 3  → 3 ≮ 1, C in
after D       4        3        1        …       query [1,3] = 1  → 1 < 2, D out
              └──────── prefix for D ────────┘
```

Count 3. Same sample as the statement, plus `D` so a real knockout shows up.

## Why the code has to be careful

- **Query before update.** Index `b` is `P` themselves. Including it would compare `c` with `c`.
- **Empty prefix.** Contest-2 rank `1` has no one better on that contest. Treat `query(0)` as `∞`, not as a tree walk at 0.
- **Insert even the dominated.** Transitivity says a dominated person is a redundant witness, so skipping the update is still correct. Inserting everyone is simpler and still right: a stronger witness is already in some earlier index.
- **Reset per test.** Fill the tree with `∞` again. `N` can change.

## Insight

Three ranks look like a 3-D search. Sort one axis and it becomes a running prefix-minimum on the other two.

## After AC — what could still improve

**0.09s** against a displayed **0.109s** is close. The Fenwick work is `N log N` per test, about `1.7·10^6` min-updates when `N = 10^5`, times `t ≤ 10`. That is not 0.09s on Cube. The live cost is reading `3N` integers per test, across four input files. A custom scanner is the one change that would actually move the time. `sync_with_stdio(false)` already got us under the wire; comments on the page say a segment tree without fast I/O TLEs.

**Time.** Contest-1 ranks are a permutation, so the code never sorts: person `a` sits in slot `a` and we walk `1 … N`. That is already the cheap order. Skipping Fenwick writes for dominated people is legal (a stronger witness is already to their left) and would not show next to the I/O. A segment tree is the same query with more nodes; Fenwick is the right size for a prefix.

**Memory.** **5.2M** is the process baseline. Two rank arrays plus a Fenwick of `N` ints is about 1.2 MB at the cap. You have to store the leftover two ranks after the order is fixed. You do not have to store contest 1.

Already in the right complexity class. Do not rewrite the accepted file.
