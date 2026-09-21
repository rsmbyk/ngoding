# CURDPROD — solution

Accepted on SPOJ.

## Forks

**Tick the clock.** For `time = 1, 2, 3, …` add up production until it hits `T`. The clock can run to `10^18`. Dead.

**Simulate each unit.** Keep a heap of “next finish time per machine,” pop the earliest, count one curd, repeat `T` times. `T` is `10^9`. Dead.

**Check one time in linear time.** The statement already gives a closed form: at a fixed time `t`, machine `q` has made `floor(t / q)` units. Summing that over `n ≤ 10^4` machines is cheap. That answers “is time `t` enough?”, not “what is the smallest `t`?”

## Algorithm

`produced(t)` is non-decreasing. On the time line the answers to “do we have at least `T` units?” only flip once:

```
time     1  2  3  ...  8  9  10 11 ... 20
enough?  n  n  n       n  n   Y  Y      Y
                          ^
                     first yes = answer
```

Binary search the smallest `t` with `produced(t) ≥ T`. Everything left of the first yes is short; everything right already works. Each check throws away half of what is left.

Bounds: `low = 1`, `high = min(q) * T` (fastest machine working alone; extra machines only help). Each check is `O(n)`. About 60 checks cover a `10^18` range. With `t ≤ 100` tests that is comfortable.

If the check is enough, `high = mid` (`mid` might already be the answer). If it is short, `low = mid + 1`. Loop while `low < high`.

## Tiny example

Machines `2, 3, 5`, target `T = 10`. High bound `2 * 10 = 20`.

The boundary that proves the answer is 10:

```
 t   floor(t/2)  floor(t/3)  floor(t/5)  produced  enough?
 9       4           3           1           8      no
10       5           3           2          10      yes (first)
```

Binary search does not walk time in order. Visit order with `mid = low + (high - low) / 2`. The bar is the live range; `*` is the midpoint we asked:

```
[1 --------------------*-------------------- 20]  mid 10, enough → high = 10
[1 --------*-------- 10]                       mid  5, short  → low  =  6
      [6 --*-- 10]                             mid  8, short  → low  =  9
          [9 * 10]                             mid  9, short  → low  = 10
           [10]                                answer 10
```

Times 6 and 7 are never asked. After 8 is already short, everything left of 8 is short too.

## Why the code is careful

The idea does not fail. 64-bit arithmetic and the search update do.

- **High bound.** `min(q) * T` is a 64-bit multiply (`10^9 * 10^9 = 10^18`). A 32-bit `int` wraps and the search runs in the wrong range.
- **The check is yes/no.** At a huge `mid` with many fast machines, summing every `mid / q` overflows even 64-bit (`10^22`). Stop as soon as `count ≥ T`.
- **Midpoint.** `low + high` near `2 * 10^18` overflows signed 64-bit. Use `low + (high - low) / 2`.
- **Keep a time that already works.** `high = mid`, not `high = mid - 1`. Never `low = mid` (no progress when `mid == low`).

## Insight

You are not simulating the factory. You are asking “is this time enough?” and the answers only flip from no to yes, so you can throw away half the clock each time.

## After AC — what could still improve

The accepted code is already in the right complexity class. What is left is polish, not a new algorithm.

**Time.** Each test binary-searches a range up to `10^18` (`~60` midpoints) and each check walks `n ≤ 10^4` machines. A hundred tests is on the order of `6·10^7` divisions. Fine for SPOJ.

You cannot beat “look at every machine” for a single check when the `q_i` are arbitrary. The harmonic-sum `O(√t)` trick is for `floor(t/1) + floor(t/2) + … + floor(t/t)`, not for `floor(t/q_i)` with random `q_i`. Early-exit in `enough` is both correctness (avoid 64-bit overflow) and a time win when fast machines appear early. `low + (high - low) / 2` is also correctness, not speed.

Still on the table:

- **Better `low`.** Production is at most `n * floor(t / min(q))`. So a time that can possibly work is at least about `T * min(q) / n`. Starting there instead of `1` shrinks the search by up to a factor of `n` — a handful of iterations, not a new big-O.
- **Fastest machines first.** Sort `q` ascending once. Then `enough` hits `T` sooner (and can stop when `q > time`, because slower machines produce nothing yet). Helps most when qualities are mixed and the input happens to list slow machines first. Worst case — all `q` similar — you still scan everyone.
- **Group duplicate qualities.** If many machines share a `q`, `count[q] * (time / q)` is one division instead of many. Only pays if the input actually repeats.

**Memory.** A `vector` of `n` ints — tens of kilobytes. You need every quality on every check, so you have to store them. Reusing one vector across tests (`resize` instead of a new `vector` each time) would shave allocations. Invisible at this `n`.

**Clarity.** `fastest = 0` plus `i == 0 || …` works, but it is a tiny trap: if the `i == 0` guard were dropped, quality `10^9` would lose to `0`. Seed from the first machine, or use `min_element` after the read. Pulling the search into `first_time_enough(quality, target)` would make `main` a loop over tests instead of a loop that also contains the algorithm.

**I/O.** `sync_with_stdio(false)` is already the right call. Fast custom scanners would not move the needle; the work is the divisions, not the `10^4` reads.

None of this is worth a second submission unless a tighter limit or a reread for clarity shows up. The bound that mattered was “do not simulate `T` events.” After that, the judge is no longer the bottleneck.
