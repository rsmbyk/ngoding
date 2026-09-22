# CODERE4 — Coder Express 4

Rahul is shown three sequences. He already knows the rule for the first two. The task is the `N`th term of the third one. The answer can be huge, so print it modulo `1000000007`.

The first sequence is `0 1 1 2 3 5 8 13 ...`. Each term from the third onward is the sum of the two before it.

The second sequence is `1 1 3 7 17 ...`. The first two terms are `1` and `1`. Each later term is twice the previous term, plus the term before that.

The third sequence starts `1 1 3 8 20 50 123 ...`. No rule is given. `N` counts from 1: the 1st term is `1`, the 2nd term is `1`, the 3rd term is `3`.

Source: [SPOJ CODERE4](https://www.spoj.com/problems/CODERE4/). Time limit `1s`, memory `1536 MB`, source limit `50000 B`.

## Input

The first line is `T`, the number of tests. Each of the next `T` lines is one integer `N`, the term to print.

## Output

`T` lines. Each line is the `N`th term of the third sequence, modulo `1000000007`.

## Constraints

- `1 <= T <= 1000`
- `1 <= N <= 1000000000`
- modulo `1000000007`

## Sample

```
3
1
2
3
```

```
1
1
3
```

Those are the first three terms of `1 1 3 8 20 50 123 ...`.
