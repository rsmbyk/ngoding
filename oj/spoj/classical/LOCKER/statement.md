# LOCKER — Magic of the locker

Vertu sells rope at 1 rupee per meter, and he only sells whole meters. He also owns a locker that multiplies. If the locker currently holds `x` rupees and he puts in `y` more, the locker does not add them. It replaces the total with `x * y`.

He starts the day with `n` meters of rope and with 1 rupee already in the locker, "for good luck." Every time he sells a piece, those rupees go into the locker immediately. He cannot take money out until the day is over, and by then he has sold every meter. The pieces are positive integers that add up to `n`. The money he earns is whatever the locker holds at the end.

Because the locker starts at 1, that starting rupee does not change the product. Selling lengths `y1, y2, ..., yk` with `y1 + ... + yk = n` leaves `y1 * y2 * ... * yk` in the locker. One piece of length `n` is allowed: the locker ends at `n`. Order of the pieces does not matter.

Print the maximum possible ending amount, modulo `1000000007` (`10^9 + 7`).

Source: [SPOJ LOCKER](https://www.spoj.com/problems/LOCKER/). Time limit `1s`, memory `1.46 GB`.

## Input

The first line is `t`, the number of test cases. Each of the next `t` lines is one positive integer `n`.

## Output

For each test case, one line: the maximum ending amount, modulo `1000000007`.

## Constraints

- `t < 10^5` (so `t` is at most `99999`)
- `0 < n < 10^12` (so `n` is from `1` through `10^12 - 1`)

`n` does not fit in a 32-bit signed integer. The product, before the modulo, is far larger than a 64-bit integer. The modulo `10^9 + 7` is prime.

A loop of length `n`, once per test, does not finish in `1s`. There can be almost `10^5` tests.

## Sample

```
2
4
5
```

```
4
6
```

For `n = 4`, the locker starts at 1:

| pieces | locker ends at |
| --- | --- |
| `4` | `4` |
| `1 + 3` | `3` |
| `2 + 2` | `4` |
| `1 + 1 + 2` | `2` |
| `1 + 1 + 1 + 1` | `1` |

Both `4` and `2 + 2` reach `4`. That is the maximum.

For `n = 5`:

| pieces | locker ends at |
| --- | --- |
| `5` | `5` |
| `1 + 4` | `4` |
| `2 + 3` | `6` |
| `1 + 2 + 2` | `4` |
| `1 + 1 + 1 + 1 + 1` | `1` |

The winner is `2 + 3`.
