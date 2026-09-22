# ROADS — Roads

Cities `1` through `N` are joined by one-way roads. Each road has a length and a toll, the toll counted in coins. Bob is leaving city `1` for city `N` and wants the smallest total length he can still pay for. He has at most `K` coins. If no route from `1` to `N` costs at most `K` coins, the answer is `-1`.

Two roads may share the same start and the same end. A toll may be `0`.

Source: [SPOJ ROADS](https://www.spoj.com/problems/ROADS/). The Luogu mirror reports time `7s` and memory `1536 MB`.

## Input

The first line is `t`, the number of tests. Each test is:

- one integer `K`, the most coins Bob can spend
- one integer `N`, the number of cities
- one integer `R`, the number of roads
- `R` lines of `S D L T`: a one-way road from `S` to `D`, length `L`, toll `T`

## Output

For each test, one line: the smallest total length of a route from `1` to `N` whose tolls add up to at most `K`. If there is no such route, `-1`.

## Constraints

- `0 <= K <= 10000`
- `2 <= N <= 100`
- `1 <= R <= 10000`
- `1 <= S, D <= N`
- `1 <= L <= 100`
- `0 <= T <= 100`

## Sample

```
2
5
6
7
1 2 2 3
2 4 3 3
3 4 2 4
1 3 4 1
4 6 2 1
3 5 2 0
5 4 3 2
0
4
4
1 4 5 2
1 2 1 0
2 3 1 1
3 4 1 0
```

```
11
-1
```

Test 1, budget `5` coins, cities `1` through `6`.

| route | length | toll |
| --- | --- | --- |
| `1 → 2 → 4 → 6` | `2 + 3 + 2 = 7` | `3 + 3 + 1 = 7` |
| `1 → 3 → 5 → 4 → 6` | `4 + 2 + 3 + 2 = 11` | `1 + 0 + 2 + 1 = 4` |

Length `7` costs `7` coins, over the budget. Length `11` costs `4` coins, which he can pay. That is the answer.

Test 2, budget `0`, cities `1` through `4`. The direct road `1 → 4` costs `2` coins. The long way `1 → 2 → 3 → 4` costs `1` coin. Nothing is free, so the answer is `-1`.
