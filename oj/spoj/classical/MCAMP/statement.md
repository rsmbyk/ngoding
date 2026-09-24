# MCAMP — Mining Camps

Mansur has mining camps on a straight line. Each camp gives some gold and some energy. He may build one forcefield that covers a contiguous block of camps. The forcefield needs energy equal to its length: if the leftmost covered camp is at `X1` and the rightmost is at `X2`, the cost is `|X1 - X2|`.

The energy of the camps inside the forcefield must be at least that cost. Among every block that pays for itself, he wants the largest total gold. The answer is that gold total. He builds exactly one forcefield; the page does not ask about the empty choice of building none, and every `gi` is at least `1`, so a single camp always has gold at least `1` and length `0`.

Source: [SPOJ MCAMP](https://www.spoj.com/problems/MCAMP/). Time limit `1s`, memory `1536 MB`, source limit `50000 B`. From an APIO 2014 training session.

## Input

- one integer `N`, the number of camps
- `N` lines of `xi gi di`: position, gold, and energy of that camp

The positions are all different and already sorted in increasing order.

## Output

One integer: the largest gold total of a contiguous block whose energy sum is at least the distance between its ends.

## Constraints

- `N <= 10^5`
- `0 <= xi <= 10^9`
- `1 <= gi, di <= 10^9`
- all `xi` distinct and given in increasing order

The page does not print a lower bound on `N`. A single camp is a legal block of length `0`.

## Sample

```
4
0 5 1
1 7 2
4 4 1
7 15 1
```

```
16
```

| camps covered (0-based) | length | energy | gold | pays? |
| --- | --- | --- | --- | --- |
| `0..2` (`0` to `4`) | 4 | `1 + 2 + 1 = 4` | `5 + 7 + 4 = 16` | yes |
| `0..3` (`0` to `7`) | 7 | `1 + 2 + 1 + 1 = 5` | 31 | no |
| `1..3` (`1` to `7`) | 6 | `2 + 1 + 1 = 4` | 26 | no |
| `3` alone | 0 | 1 | 15 | yes |

The best paying block in the table is gold `16`. A note on the page points at that same block.
