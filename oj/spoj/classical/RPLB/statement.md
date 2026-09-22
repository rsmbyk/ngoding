# RPLB — Blueberries

Teresa is done with strawberries. She is picking blueberries from a row of magical bushes in Rainbowland. There is a limit `K`: the total she carries home must be at most `K`.

The bushes are in a line. If she picks bush `i`, she cannot pick bush `i + 1`. The first and the last are neighbors only when they actually sit next to each other. She may skip a bush, and she may pick nothing.

Among every allowed set of bushes, she wants the largest total that is still at most `K`.

Source: [SPOJ RPLB](https://www.spoj.com/problems/RPLB/). The Luogu mirror of this problem reports time `0.439s` and memory `1536 MB`.

## Input

The first line is `T`, the number of test cases. Each case is two lines. The first line of a case is `N` and `K`: `N` bushes, and `K` the most blueberries she may carry. The second line is `N` integers, the blueberry count on bush `1` through bush `N`.

## Output

For each case, one line:

```
Scenario #i: X
```

`i` is the case number starting at `1`. There is a single space after the colon. `X` is the largest total she can carry.

## Constraints

The constraint block on the page is:

- `1 <= N <= 1000`
- `1 <= K <= 1000`

It does not print a separate bound on `T`, or on the count of one bush. A bush with more than `K` berries cannot be part of any allowed pick, because taking it alone already breaks the limit. The answer itself is at most `K`.

## Sample

```
2
5 100
50 10 20 30 40
5 87
21 45 30 12 14
```

```
Scenario #1: 90
Scenario #2: 65
```

Case 1, bushes `50 10 20 30 40`, limit `100`.

| pick | total | allowed? |
| --- | --- | --- |
| `50` and `40` | 90 | yes, they are not neighbors |
| `50`, `20`, and `40` | 110 | over the limit |
| `50` and `30` | 80 | yes, and smaller than 90 |
| `20` and `40` | 60 | yes, and smaller than 90 |

`90` is the best.

Case 2, bushes `21 45 30 12 14`, limit `87`.

| pick | total |
| --- | --- |
| `21`, `30`, and `14` | 65 |
| `45` and `14` | 59 |
| `45` and `12` | 57 |

`21`, `30`, and `14` are pairwise non-neighbors (`1` with `3`, `3` with `5`). `65` is the best of these.
