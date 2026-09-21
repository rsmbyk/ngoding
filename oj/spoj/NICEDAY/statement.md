# NICEDAY — The day of the competitors

The Vietnamese IOI coaches have `N` strong contestants, numbered `1` to `N`. They ran **three** contests. Every contestant sat all three. On any one contest, **no two people tied** — the ranks `1 … N` are a permutation for that contest.

Rank `1` is first (best). Smaller rank number means “ranked before.”

Contestant `A` is **better than** contestant `B` when `A` is ranked before `B` in **all three** contests. So if the ranks are `(a, b, c)` and `(a′, b′, c′)`:

```
A better than B  ⇔  a < a′  and  b < b′  and  c < c′
```

`A` is **excellent** if nobody is better than `A`. Count the excellent contestants.

Being first in one contest is not enough. Someone else can still beat you on the other two *and* on that one. You fail to be excellent only if there is a person who beats you on every contest at once.

Source: [SPOJ NICEDAY](https://www.spoj.com/problems/NICEDAY/). Added by Nguyen Minh Hieu, 2006-01-20. Based on a BOI problem. Time limit on the page is `0.109s`; a note on the page says there are **4 input files** and the total time used to be advertised as `4s` rather than `1s`. Memory `1536 MB`. Source limit `10000` bytes. Cluster: Cube (Intel G860). Tagged `#tree`.

## Input

- Line 1: `t` — number of tests.
- Then `t` tests. Each test:
  - Line 1: `N` — number of contestants.
  - Next `N` lines: three integers `ai bi ci` — ranks of one contestant in contests 1, 2, and 3.

Tests are independent.

## Output

One integer per test: the number of excellent contestants. One line each.

## Constraints

- `1 ≤ t ≤ 10`
- `3 ≤ N ≤ 100000`
- `1 ≤ ai, bi, ci ≤ N`
- On any one contest, ranks are unique (so each of `(ai)`, `(bi)`, `(ci)` is a permutation of `1 … N`)
- Time is tight: `N · t` reaches `10^6` people, and the displayed limit is `0.109s` per file
- Source must stay under `10000` bytes

A pair check is `N²` ≤ `10^{10}` per test. That does not finish.

The answer is an integer in `1 … N`. At least one excellent person always exists (a 3-D “first” in the partial order). All `N` can be excellent (nobody dominates anybody).

## Special cases

- Someone ranked `1 1 1` is excellent, and they dominate anyone whose ranks are all larger.
- A total chain `1 1 1`, `2 2 2`, …, `N N N`: only the first person is excellent.
- Rock-paper-scissors cycle (the sample): each person is first in one contest and last in another. Nobody dominates anybody. Answer `N`.
- Dominated on two contests but winning the third: still excellent. The third contest is a shield.
- `N = 3` is the smallest allowed size.

## Sample

Input:

```
1
3
1 2 3
2 3 1
3 1 2
```

Output:

```
3
```

Call them `P1`, `P2`, `P3`. Pairwise:

| pair | contest 1 | contest 2 | contest 3 | dominate? |
| --- | --- | --- | --- | --- |
| `P1` vs `P2` | `1 < 2` | `2 < 3` | `3 > 1` | neither (third contest blocks) |
| `P1` vs `P3` | `1 < 3` | `2 > 1` | `3 > 2` | neither |
| `P2` vs `P3` | `2 < 3` | `3 > 1` | `1 < 2` | neither |

No arrow `A → B` meaning “better than.” All three are excellent.
