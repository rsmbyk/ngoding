# RRSCHED — Round-Robin Scheduling

A processor is given `N` tasks, numbered `1` to `N` in the order they sit in the queue. Task `i` needs `T_i` seconds of CPU. All of them are ready at time `0`.

The scheduler is round-robin with a **1-second quantum**:

1. Walk the queue from task `1` to task `N`.
2. Give the next unfinished task one second.
3. If that second finishes the task, drop it. It never comes back.
4. When the walk falls off the end, start again at the first unfinished task.

Idle time does not exist. Every second, some still-alive task runs.

For each task, print the wall-clock time at the instant it uses its last second. That is the completion time, not the remaining burst.

Source: [SPOJ RRSCHED](https://www.spoj.com/problems/RRSCHED/). Added by Neal Wu, 2008-07-02. Resource: TopCoder High School SRM 52 (raised constraints). Time `0.305s–1s`, memory `1536 MB`, source `50000` bytes. Cluster: Cube (Intel G860). Tagged `#simulations`. Warning: large I/O. One test only — do not read until EOF. Answers need 64-bit.

## Input

- Line 1: `N` — number of tasks.
- Next `N` lines: one integer `T_i` each, the burst of task `i` (1-based in the output).

## Output

`N` lines. Line `i` is the completion time of task `i`.

## Constraints

- `1 ≤ N ≤ 50,000`
- `1 ≤ T_i ≤ 1,000,000,000`
- Time is tight: `0.305s` on some files, `1s` on others
- Completion times can reach `sum T_i ≤ 5·10^4 · 10^9 = 5·10^13`, so 32-bit integers overflow
- One test case

A second-by-second walk of the CPU is `sum T_i` steps. That does not finish. Even one step per remaining slot of every task is the same bound.

## Special cases

- `N = 1`: the answer is just `T_1`.
- Every burst is `1`: the queue never wraps. Completions are `1, 2, …, N`.
- Every burst is the same `T`: nobody drops until round `T`. Task `i` finishes at `(T − 1) · N + i`.
- Two tasks with the same burst: the one earlier in the original order finishes first, in that last shared round.
- A short task in the middle of long ones: it drops on its last round, and later rounds skip it.
- The last task to die can finish at `sum T_i` (the CPU is busy the whole time).

## Sample

Input:

```
5
8
1
3
3
8
```

Output:

```
22
2
11
12
23
```

Tasks in order: `A=8`, `B=1`, `C=3`, `D=3`, `E=8`. Remaining after each second:

```
time  who  remaining after the second          done?
  1    A   A7 B1 C3 D3 E8
  2    B   A7 B0 C3 D3 E8                       B at 2
  3    C   A7    C2 D3 E8
  4    D   A7    C2 D2 E8
  5    E   A7    C2 D2 E7
  6    A   A6    C2 D2 E7
  7    C   A6    C1 D2 E7
  8    D   A6    C1 D1 E7
  9    E   A6    C1 D1 E6
 10    A   A5    C1 D1 E6
 11    C   A5    C0 D1 E6                       C at 11
 12    D   A5       D0 E6                       D at 12
 13    E   A5          E5
 14    A   A4          E5
 15    E   A4          E4
 ...
 22    A   A0          E1                       A at 22
 23    E               E0                       E at 23
```

`B` dies in the first pass. `C` and `D` die together on the third pass (`C` first, because it sits earlier). `A` and `E` share the rest of the ring until round 8.
