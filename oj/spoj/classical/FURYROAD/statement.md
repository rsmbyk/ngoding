# FURYROAD — Fury Road

War boys stand on the Cartesian plane at integer points. A war party is a group of boys that stand together: any two boys that share an edge or a corner (the eight neighbors: horizontally, vertically, or diagonally) belong to the same party, and that relation chains through other boys. Boys that never connect that way are different parties. Count how many parties there are.

Source: [SPOJ FURYROAD](https://www.spoj.com/problems/FURYROAD/). Time limit `1s`, memory `1536 MB`, source limit `50000 B`.

## Input

The first line is `T`, the number of tests. Each test is:

- one integer `N`, the number of war boys
- `N` lines of `Xi Yi`, the position of one boy

## Output

For each test, one line:

```
Case X: P
```

`X` is the test number starting at `1`, and `P` is the number of war parties. There is a space after the colon.

## Constraints

- `1 <= T <= 50`
- `1 <= N <= 10000`
- `0 <= Xi, Yi <= 1000`

The page does not say whether two boys can share the same point. If they do, they stand together and count as one party.

## Sample

```
3
2
5 5
3 2
6
1 3
0 1
1 2
2 3
4 1
5 0
1
0 0
```

```
Case 1: 2
Case 2: 2
Case 3: 1
```

Test 1: `(5, 5)` and `(3, 2)` are far apart, so two parties.

Test 2: the four points `(0, 1)`, `(1, 2)`, `(1, 3)`, `(2, 3)` touch through diagonal or edge steps, and `(4, 1)` touches `(5, 0)` diagonally. Those are two parties.

Test 3: one boy, one party.
