# ROADS

## Fork: plain Dijkstra

Dijkstra grows outward from city 1 and always expands the route with the smallest length so far. Its usual promise is that the first time a city is settled, that arrival is the best one, so the city is never opened again.

Sample, budget 5. Edge labels are `length/toll`.

```
        2/3          3/3         2/1
   1 --------> 2 --------> 4 --------> 6
   |                      ^
   | 4/1              2/4 |
   v                 /    |
   3 --------> 5 ---3/2---
        2/0
```

Two arrivals at city 4:

| route into 4 | length | coins spent |
| --- | --- | --- |
| `1 → 2 → 4` | 5 | 6 |
| `1 → 3 → 5 → 4` | 9 | 3 |

Length-first search settles `1 → 2 → 4` and drops the longer arrival. That dropped arrival is the one that can still pay for `4 → 6` (total length 11, coins 4). The settled one reaches 6 at length 7 after spending 7 coins, which is over the budget.

## Fork: one minimum-coin arrival per city

Coins spent are the missing fact. Keeping only the arrival that spent the fewest coins still drops a useful route.

Budget 5. Edge labels are `length/toll`.

```
1 --100/0--> 2 --1/0--> 3
1 ---1/3---> 2
```

| arrival at 2 | length | coins |
| --- | --- | --- |
| the free road | 100 | 0 |
| the paid road | 1 | 3 |

Fewest coins keeps length 100. City 3 is then length 101. The paid arrival reaches 3 at length 2 after 3 coins, which the budget allows. One number per city cannot keep both: one arrival is shorter, the other spent fewer coins.

## Fork: throw away the longer arrival

On the map above, dropping the free road leaves the right answer (length 2). A later toll can make that drop illegal.

Budget 5.

```
1 --10/0--> 2 --1/4--> 3
1 ---1/3---> 2
```

| arrival at 2 | length | coins | can pay the toll-4 road? |
| --- | --- | --- | --- |
| free | 10 | 0 | yes, total coins 4, length 11 |
| paid | 1 | 3 | no, 3 + 4 = 7, over the budget |

Dropping the free arrival leaves no route to 3. Dropping the paid arrival was the mistake on the previous map. Neither arrival is better on both length and coins, so neither is safe to drop when you first reach the city.

## Place the search settles

One place is a city plus the coins already spent, and only while that total is still within `K`. Dijkstra still expands the place with the smallest length first, and it settles that place once. For the same city and the same coin total, only the smaller length is kept: the coins match, so the longer road is worse on both.

On the sample, budget 5, the places come out in this order:

| settled | length | opens |
| --- | --- | --- |
| city 1, 0 coins | 0 | city 2 with 3 coins at length 2; city 3 with 1 coin at length 4 |
| city 2, 3 coins | 2 | the road into 4 costs 3 more coins, total 6, over budget |
| city 3, 1 coin | 4 | city 4 with 5 coins at length 6; city 5 with 1 coin at length 6 |
| city 4, 5 coins | 6 | the road into 6 costs 1 more coin, total 6, over budget |
| city 5, 1 coin | 6 | city 4 with 3 coins at length 9 |
| city 4, 3 coins | 9 | city 6 with 4 coins at length 11 |

City 4 is settled twice, once at 5 coins and once at 3. The second of those is the arrival the plain search had thrown away. The first time city 6 is settled, the length is 11.

`N <= 100` and `K <= 10000`, so there are at most about a million such places. Each road is tried from each coin total that can still pay its toll.

## Code notes

`best[city][coins]` is the smallest length seen for that place. The heap may still hold an older, longer trip to the same place; that entry is skipped because a longer trip with the same coins is worse on both. Roads that would push the coin total past `K` are never opened. The first time city `N` comes off the heap, that length is the answer: every still-waiting place is at least that long.

## Insight

The shortest road to a city can be the one that already spent more coins, so settling the city once drops the arrival that can still pay for what comes next. One place in the search is the city plus the coins already spent. The same coins keep only the smaller length. A different coin total stays, as long as it is still within `K`.

## After AC — what could still improve

Accepted in **0.02s** of a `7s` limit. Memory was not reported.

**Time.** The heap still holds a trip that is both longer and more expensive than some other trip already stored for the same city. Dropping that trip before it is pushed would shrink the heap. `0.02s` does not need that.

**Memory.** One length per city per coin total: `N` is at most `100` and `K` is at most `10000`, so the table is a few megabytes plus the heap's older trips. It should sit at the usual one-file baseline.

**Already as tight as it needs to be.** Do not rewrite the accepted file. The bound that mattered was keeping a separate place for each coin total, not squeezing the heap.

## Fork: keep every arrival that is not worse on both

Both arrivals stay. An arrival is safe to drop only when some other arrival at the same city is no longer and spent no more coins.

On the second map, city 2 starts with (length 10, coins 0) and (length 1, coins 3).

| new arrival | length | coins | compared with the two kept | drop? |
| --- | --- | --- | --- | --- |
| same coins, longer road | 10 | 3 | (1, 3) is shorter, same coins | yes |
| longer and more expensive | 50 | 4 | (1, 3) is shorter and cheaper | yes |
| a bit longer, a bit cheaper | 2 | 2 | loses length to (1, 3), loses coins to (10, 0) | no |
