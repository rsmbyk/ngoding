# PT07Z — Longest path in a tree

You are given an **unweighted, undirected tree**: `N` nodes, connected, no cycles. Every edge has the same cost of one. Between any two nodes there is exactly one simple path.

Print the **length of a longest path** in that tree. Length is the **number of edges** on the path, not the number of nodes. A path from a node to itself has length `0`.

Source: [SPOJ PT07Z](https://www.spoj.com/problems/PT07Z/). Added by Thanh-Vy Hua, 2007-03-28. Resource: Co-author Amber. Time `0.5s`, memory `1536 MB`, source `50000` bytes. Cluster: Cube (Intel G860). Tagged `#dfs`. Languages: all except ERL, JS-RHINO, NODEJS, PERL6, VB.NET.

## Input

One test.

- Line 1: `N` — number of nodes.
- Next `N − 1` lines: each line is a pair `u v`, an undirected edge between node `u` and node `v`.

Nodes are numbered `1` to `N`. The input is a tree, so those `N − 1` edges already connect everything and introduce no cycle.

## Output

One integer: the length of a longest path, followed by a newline.

## Constraints

- `0 < N ≤ 10000`
- `1 ≤ u, v ≤ N`
- Time limit `0.5s`
- Memory limit `1536 MB`
- Source limit `50000` bytes

A path’s length is at most `N − 1` (a straight line of `N` nodes). `N` itself is only ten thousand, but half a second is still not a lot if every pair of nodes is walked separately: `N²` is `10⁸` pair-starts, and a walk from each start is another factor of `N`.

## Special cases

- `N = 1`: no edges. The only path is a single node. Length `0`.
- `N = 2`: one edge. Length `1`.
- A **line** (`1–2–…–N`): the unique longest path uses every edge. Length `N − 1`.
- A **star** (one center, `N − 1` leaves): any leaf-to-leaf path has two edges. Length `2` when `N ≥ 3`.
- Length is edges, not nodes. The sample’s three-node line has three nodes and length `2`.
- The graph is a tree, so there are no weights to compare, no extra edges, and no second path between the same pair.

## Sample

Input:

```
3
1 2
2 3
```

Output:

```
2
```

The tree is a line of three nodes:

```
1 — 2 — 3
```

The three simple paths:

| path | edges |
| --- | --- |
| `1–2` | 1 |
| `2–3` | 1 |
| `1–2–3` | 2 |

The longest is `2`.
