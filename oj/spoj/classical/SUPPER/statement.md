# SUPPER — Supernumbers in a permutation

An `n`-element permutation is a sequence of `n` distinct numbers taken from `{1, 2, ..., n}`. For example, `2 1 4 5 3` is a permutation of length 5.

A supernumber is a value that sits on at least one longest increasing subsequence of that permutation. Increasing means each next value is larger than the one before it. The subsequence does not have to be a contiguous block.

In `2 1 4 5 3` the longest increasing subsequences have length 3, and there are two of them: `2, 4, 5` and `1, 4, 5`. The supernumbers are `1, 2, 4, 5`. The value `3` is on no subsequence of length 3, so it is not a supernumber.

Source: [SPOJ SUPPER](https://www.spoj.com/problems/SUPPER/). The page reports time `2.25s`, memory `1536 MB`, and a source limit of `50000 B`. It also warns that the input and output are large.

## Input

There are exactly ten tests, one after another. There is no separate line that says how many tests there are. Each test is two lines:

- `n`, the length of the permutation
- `n` integers, the permutation, separated by single spaces

## Output

For each test, two lines:

- the count of supernumbers
- those supernumbers, separated by single spaces, in increasing order

## Constraints

- `1 <= n <= 100000`
- the second line is a permutation of `1 .. n`

## Sample

The judge prints one test and says the other nine follow the same shape.

```
5
2 1 4 5 3
```

```
4
1 2 4 5
```

| subsequence | length | values used |
| --- | --- | --- |
| `2, 4, 5` | 3 | 2, 4, 5 |
| `1, 4, 5` | 3 | 1, 4, 5 |

Nothing longer exists. `3` never appears, so the increasing list of supernumbers is `1 2 4 5`.
