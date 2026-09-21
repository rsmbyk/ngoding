# PT07Z — solution

Accepted on SPOJ. Time **0.04s**.

## Forks

**Walk every pair.** From each node, search the whole tree. `N = 10000` and `0.5s` makes `N` searches × `N` edges too fat, and most of that work repeats.

**Height from an arbitrary root.** Root anywhere, report the deepest down-chain. A line rooted in the middle reports about `N/2`. The longest path does not have to touch the root.

**Keep only the longest path inside each child.** Recurse, send that number up, parent takes the max. A star then answers `0`: every child is a leaf. The real path is two leaves glued at the center.

**Add every child’s chain.** A path has two ends. Three arms at a node are not a path.

The live fork is: each node returns a chain the parent can still grow, and separately remembers the best path that already peaked here.

## Algorithm

This is **tree DP**: root the tree (node `1` is fine), and let every node answer a question about its subtree. The children’s answers combine in one pass, `O(N)`, because a tree has `N-1` edges and each is seen twice.

At node `u`, after every child `v` has returned:

- `down[v]` = longest chain that **starts at `v` and goes down**. Then `u` can walk into that child for `1 + down[v]` edges.
- `down[u]` = the best of those one-child walks (or `0` if `u` is a leaf). That is what `u` sends **up**. The parent can extend only one chain through `u`, not a finished two-sided path.
- `through[u]` = sum of the **two** best one-child walks (or just the best, if `u` has fewer than two children). That is the longest path that uses `u` as the peak.

The answer is `max through[u]` over every node. Paths that never touch the root still show up: they peak at some descendant.

## Tiny example

```
      2
     /|\
    1 3 5
       \
        4
```

Leaves `1`, `4`, `5` send `down = 0`.

| node | offers from children (`1 + down`) | `down` (best one) | `through` (best two) |
| --- | --- | --- | --- |
| `1` | — | 0 | 0 |
| `4` | — | 0 | 0 |
| `5` | — | 0 | 0 |
| `3` | `1` from `4` | 1 | 1 |
| `2` | `1` from `1`, `2` from `3`, `1` from `5` | 2 | `2 + 1 = 3` |

`through[2] = 3` is `1–2–3–4` (or `5–2–3–4`). Adding all three offers would invent length `4`, which is not a simple path.

If `2` had a parent, that parent would receive `down[2] = 2` (`2–3–4`), not the `3`. The `3` already used two directions.

A path that misses the root still wins here if we root at a leaf instead. Root at `1`: `through[2]` is still `3`, and `through[1]` is only the single chain `1–2–3–4` of length `3`. The max is the same.

Official sample `1—2—3`, rooted at `1`: `through[2] = 1`, `through[1] = 2`. Answer `2`.

## Insight

The longest path in a tree is the best place where two down-chains meet. One number per subtree is not enough: you send the longest **single** chain up, and you keep the **sum of the two longest** as a candidate answer.

## Why the code is careful

- **Two slots, not a running sum.** `best` and `second` are the only arms that may glue. A third child can replace `second` if it is longer, but it never joins the peak. `through[u] = best + second` even when `u` has one child or none: the missing arm is `0`.
- **Send `best`, not `best + second`.** The recursive return is `down[u]`. Adding the peak into the return would let the parent grow a path that already used two directions.
- **Skip the parent, not a visited array.** The graph is stored undirected, so each edge appears twice. The one neighbor that is `parent` is the way we came; everything else is a child.
- **Nodes are `1..N`.** The adjacency vector is size `N + 1`. A line of `N = 10000` is a legal tree, so the walk is depth `N`; the frame is a handful of ints, which fits.

## After AC — what could still improve

**0.04s** against `0.5s` is already in the right class: one walk, every edge twice. Cube is not waiting on us. Do not rewrite the accepted code unless asked.

**Time.** Another linear walk of the same tree is the same `O(N)`, not a faster `O(N)`. `sync_with_stdio(false)` already went in, and `N ≤ 10000` edges is a small read. Flattening the adjacency list or reserving per-node vectors would not show next to process startup.

**Memory.** The judge number was not recorded. `2(N-1)` adjacency ints plus a recursion of depth `N` with a handful of ints per frame is a couple of hundred KB against `1536 MB`. You have to store the tree.

**Already as tight as it needs to be.** The bound that mattered was “do not walk every pair.” After that, the judge is no longer the bottleneck.
