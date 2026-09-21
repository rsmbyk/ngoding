# NPC2015D — Eefun is not so Fun

Eefun has a positive integer `N`. Split it into **one or more positive integers** that add up to `N`. Among all such splits, take the one whose **product** is as large as possible, and print that product modulo `1000000007` (`10^9 + 7`).

A split of one part is allowed: just `N` itself, product `N`. Order does not matter. The number of parts is not fixed.

Zeros are not allowed (a zero in the split makes the product `0`). Negative parts are not allowed either: if they were, you could drive the product to infinity (`N = (−a) + (−a) + (N + 2a)` for large `a`). The page never says “positive,” but without that the answer is unbounded. Comments on the page confirm both gaps.

Source: [SPOJ NPC2015D](https://www.spoj.com/problems/NPC2015D/). NPC Schematics 2015. Time limit `1s`, memory `1536 MB`, source limit `50000` bytes.

## Input

One test. A single integer `N`.

## Output

One integer: the maximum product, modulo `1000000007`.

## Constraints

The page prints `1 ≤ N ≤ 10 18`. Lost superscript: `1 ≤ N ≤ 10^18`.

The product before the modulo can be far larger than a 64-bit integer. The modulo is `10^9 + 7`, a prime.

`N` itself fits in 64 bits. A loop of length `N` does not finish in `1s`.

## Special cases

- `N = 1`: the only split is `[1]`, product `1`.
- `N = 2`: `[2]` beats `[1, 1]` (`2 > 1`). Sample 1.
- `N = 3`: `[3]` beats `[1, 2]` (`3 > 2`).
- `N = 4`: `[2, 2]` and `[4]` both give `4`; `[1, 3]` gives `3`.
- `N = 5`: `[2, 3]` gives `6`, which beats `[5]`, `[1, 4]`, and `[1, 2, 2]`. Sample 2.
- A leftover `1` is wasteful: `1 + k` has product `k`, while `(k + 1)` as a single part is larger. So an optimal split never contains a `1`, except when `N = 1`.

## Sample

Two separate runs on the page, not a `T`-block.

Input 1:

```
2
```

Output 1:

```
2
```

Input 2:

```
5
```

Output 2:

```
6
```

For `5`, the splits of positive integers and their products:

| split | product |
| --- | --- |
| `5` | `5` |
| `1 + 4` | `4` |
| `2 + 3` | `6` |
| `1 + 1 + 3` | `3` |
| `1 + 2 + 2` | `4` |
| `1 + 1 + 1 + 2` | `2` |
| `1 + 1 + 1 + 1 + 1` | `1` |

The winner is `2 + 3`.
