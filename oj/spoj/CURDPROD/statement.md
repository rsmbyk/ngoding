# CURDPROD — Curd Producers

A factory owns `n` curd-producing machines. Each machine has a quality `q`. A machine of quality `q` finishes **one** unit of curd every `q` units of time, and only at those instants: at time `q`, `2q`, `3q`, and so on.

So a quality-5 machine has produced 1 unit at time 5, another at time 10, and so on. At time 9 it has produced **1** unit, not 1.8. Production is discrete; partial units do not count.

Given the qualities of all machines and a target amount `T`, find the **minimum time** at which the factory has finished at least `T` units of curd. Machines run in parallel.

Source: [SPOJ CURDPROD](https://www.spoj.com/problems/CURDPROD/)

## Input

The first line is an integer `t`, the number of test cases.

Each test case:

- One line with two integers `n` and `T` — the number of machines and the target amount of curd.
- Then `n` integers, the qualities of the machines. The original statement puts them on the next `n` lines; reading `n` integers is enough either way.

## Output

For each test case, one line: the minimum time required to produce at least `T` units of curd.

## Constraints

The statement prints `1 ≤ t ≤ 102`, `1 ≤ n ≤ 104`, `1 ≤ T ≤ 109`, `1 ≤ quality ≤ 109`. Those are the usual lost superscripts:

- `1 ≤ t ≤ 10^2`
- `1 ≤ n ≤ 10^4`
- `1 ≤ T ≤ 10^9`
- `1 ≤ quality of each machine ≤ 10^9`

The answer can be as large as `min(quality) * T`, which reaches `10^18`.

## Special cases

- A quality-`q` machine at time `t` has produced exactly `floor(t / q)` units.
- `T ≥ 1`, so the answer is never 0.
- Extra machines can only make the answer smaller. An upper bound on the time is the fastest machine working alone.

## Sample (handmade)

The official page has no sample we could fetch. This case is the tiny example used while solving.

Input:

```
1
3 10
2
3
5
```

Output:

```
10
```

At time 9 the three machines have made `floor(9/2) + floor(9/3) + floor(9/5) = 4 + 3 + 1 = 8` units. At time 10 they have made `5 + 3 + 2 = 10`. Time 10 is the first moment the target is met.
