# RRSCHED — solution

Accepted on SPOJ. Time **0.15s**.

## Forks

**Second-by-second queue.** `sum T_i` reaches `5·10^13`. Dead.

**Jump whole rounds, scan the ring each jump.** `O(N)` jumps, `O(N)` per scan → `N²`. Borderline on `0.305s`. Not the path.

**Full-ring formula `(T_i − 1)·N + i`.** Exact only if nobody dies early. Overcounts the sample.

**Per-task pair sum.** `finish(i) = T_i + Σ_{j<i} min(T_j, T_i) + Σ_{j>i} min(T_j, T_i − 1)`. Exact, `N²`. Dead.

**Sort by burst, Fenwick prefix of who is still alive (this path).** Same sum, no pair loop.

## Algorithm

Process tasks **shortest burst first** (same burst: left-to-right in the original queue).

Until the next death, the ring is stable: every still-alive task eats the same number of extra seconds. Jump the clock by

```
delta · (how many are still alive)
```

where `delta = this burst − previous burst`. After that jump, every survivor has received `T` slices of CPU — **as if the round had run to the end**. The task we are finishing did not wait for the people sitting after it. Subtract those still-alive people to its right.

A **Fenwick tree** (binary indexed tree) stores a `1` at every still-alive queue position. Prefix `query(p)` = how many still-alive sit in `1 … p`. Point-delete when a task dies. Same structure as NICEDAY; the aggregate is a **sum** (alive count), not a min.

```
tot  += (T − prevT) · alive
ans  = tot − (alive to the right of me)
     = tot − alive + query(position)
then delete this position
prevT = T
```

`alive` includes the task itself (it is still in the Fenwick when we query).

Work: sort `O(N log N)` plus `N` prefix queries and `N` deletes, each `O(log N)`. Answers in 64-bit.

## Tiny example

Bursts `8, 1, 3, 3, 8`. Sorted order: `B(1,pos2)`, `C(3,pos3)`, `D(3,pos4)`, `A(8,pos1)`, `E(8,pos5)`.

```
positions     1    2    3    4    5
              A    B    C    D    E
start         1    1    1    1    1     tot=0  prevT=0

B, T=1        jump +1·5 → tot=5
              query(2)=2  alive=5  →  5 − 5 + 2 = 2
              delete B    1    0    1    1    1

C, T=3        jump +2·4 → tot=13
              query(3)=2  alive=4  → 13 − 4 + 2 = 11
              delete C    1    0    0    1    1

D, T=3        jump +0·3 → tot=13
              query(4)=2  alive=3  → 13 − 3 + 2 = 12
              delete D    1    0    0    0    1

A, T=8        jump +5·2 → tot=23
              query(1)=1  alive=2  → 23 − 2 + 1 = 22
              delete A    0    0    0    0    1

E, T=8        jump +0·1 → tot=23
              query(5)=1  alive=1  → 23 − 1 + 1 = 23
```

## Code notes

Tie-break the sort by original index so two equal bursts finish left-to-right in the same round. Delete a task from the Fenwick *after* its query, so it still counts in its own prefix. `tot` and the answers are 64-bit; `tot` can reach `5·10^13`.

## Insight

A death only changes the ring size. Between deaths the clock is `delta · alive`. Position only trims the people to your right on the last slice.

## After AC — what could still improve

**0.15s** against `0.305s–1s` has room. The work is one sort plus `N` Fenwick queries and deletes after seeding `N` ones — about `N log N` with a tiny constant. That is not why Cube took 0.15s. The live cost is sorting 50,000 pairs and writing 50,000 lines. Do not rewrite the accepted code unless asked.

**Time.** Seeding the Fenwick with `N` point-adds is the one avoidable `N log N`. Every cell starts at `1`, so the block at index `i` is exactly its length `i & -i` and you can fill the tree in `O(N)`. A custom scanner is the other possible shave; `sync_with_stdio(false)` already went in. A segment tree is the same prefix with more nodes. Jumping rounds with a scan of the ring is the `N²` we walked away from — it would be the thing that misses the 0.305s files.

**Memory.** The judge number was not recorded. A Fenwick of `N` ints, a task array, and the answer array are a few hundred KB. You have to keep original positions after the sort. You do not have to keep the bursts once a task is processed, and that would not show.

**Already as tight as it needs to be.** The bound that mattered was “do not simulate the quantum.” After that the Fenwick is the right size for a prefix count of who is still in the ring.
