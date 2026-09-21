# UOFTCE — solution

Accepted on SPOJ. Time **0.03s**.

## Forks

**TSP on the stores.** Pick an order, walk store to store (maybe via the car). Store count is not capped — a 100×100 mall can be almost all `S`. Held-Karp dies at ~20 stores. The constraint is telling us the order is not a search.

**Independent round-trips.** Read the loop again: shop, **back to the car**, shop, **back to the car**. They never walk store → store without the car in the middle. Each store `s` costs `2 · dist(C, s)` of walking plus `60` shopping, no matter the order.

The stopwatch is the only twist: it starts at the first shop, so the opening car → store walk is free. To throw away the most unpaid walking, that first store is the farthest from the car.

## Algorithm

**BFS** (breadth-first search) from the car. Flood the grid one minute per step; walls are blocked; first time a cell is reached is the shortest walk. One flood gives `dist(C, s)` for every store.

```
answer = 2 * sum dist(C, s)  −  max dist(C, s)  +  60 * (number of stores)
```

The subtracted max is the unpaid first outbound. Later stores still pay both ways.

Work per mall is `O(R C)`. `M · R · C ≤ 10^6`.

## Tiny example

Mall 1, distances `8, 5, 2`:

```
car --8--> T --8--> car --5--> BL --5--> car --2--> BR --2--> car
         ^
         clock starts (shop T)
```

Full walking if everything were timed: `2·(8+5+2) = 30`. Drop the opening `8`. Walking left: `22`. Shopping: `180`. Total **202**.

Mall 2, distances `2, 1, 1, 2`: `2·6 − 2 + 240 = 250`.

Furthest-first is forced by the free walk. Any other first store leaves a shorter unpaid outbound and a longer timed one.

## Code notes

The BFS walks through `S` and `C`. Stepping on a store is not shopping; shopping is counted when the cell is dequeued and the letter is `S`.

`dist[r][c] == -1` is unvisited. First touch is shortest, so later paths are ignored.

## Insight

They always dump at the car, so the mall is not a tour — it is a star from `C`. Alice’s clock deletes one spoke; pick the longest spoke to delete.

## After AC — what could still improve

The accepted code is already the right complexity. One BFS per mall, `O(R C)` cells, and you have to read the grid anyway. **0.03s** against a 3s limit is the process coming up, not the flood. Do not rewrite the accepted code unless asked.

**Time.** `M · R · C ≤ 10^6`. The queue already touches each open cell once. A custom scanner, `scanf`, or marking the grid in place instead of a `dist` matrix would not move 0.03s. Multi-source or store-to-store BFS would only add work we do not need: every path that matters already goes through the car.

**Memory.** A `100 × 100` distance table and a handful of strings. You can carry the distance on the queue and keep a visited flag, or reuse one static buffer across malls. That is layout, not a new bound. The judge’s memory number was not recorded here; the working set is tiny either way.

**Already as tight as it needs to be.** The bound that mattered was “do not search store order.” After that, the judge is no longer the bottleneck.
