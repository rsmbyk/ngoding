# MIDEARTH

## Fork: weak vs strong

A village is strong when `Ai > Bi` — after a success, coins go down. Otherwise it is weak: coins stay the same or go up (`Ai <= Bi`).

Weak villages never hurt the bank in the long run. Strong ones spend net coins. The statement caps the strong villages that can matter at `15`, while `N` can be `100000`, so the hard choices live in a tiny set.

## Fork: order among the weak

Richest loot among what you can afford sounds natural, but for weak villages the binding fact is the **cost**. After a weak pillage, coins only stay or rise, so unlocking the next village is about having enough `Ai`, not about grabbing the biggest `Bi` first.

Tiny case, start with `5` coins, only weak villages:

| village | `A` | `B` |
| --- | --- | --- |
| cheap | 3 | 3 |
| gate | 6 | 20 |
| shiny | 5 | 100 |

`shiny` is the richest you can afford at the start. Take it: coins become `5 - 5 + 100 = 100`, then `cheap`, then `gate`. That works here.

Change `shiny` to `A = 5`, `B = 5` (still weak, no real growth). Richest under budget is still `shiny` (loot `5` beats `cheap`’s `3`). Take it: coins stay `5`. You never reach `gate` at cost `6`. Cheapest first: take `cheap`, coins stay `5` — still stuck. Bad example.

Better case — start with `5`:

| village | `A` | `B` |
| --- | --- | --- |
| seed | 5 | 8 |
| wall | 10 | 10 |

Only `seed` is affordable. You must take it (coins become `8`) before `wall` is possible. There is no “richest under budget” choice. Among several weak villages you *can* afford, sorting them by **increasing `A`** is the safe rule: cheaper doors open first, and weak loot never lowers the bank for later doors.

## Fork: order among the strong

Lowest `Ai - Bi` (smallest net loss) cares about how hard the bank is hit after success. You still have to pay `Ai` up front.

Tiny case, start with `10` coins, only strong villages:

| village | `A` | `B` | net loss `A - B` |
| --- | --- | --- | --- |
| steep | 10 | 9 | 1 |
| short | 5 | 0 | 5 |

Lowest loss first: `steep` (need `10`) → coins `9`, then `short` (need `5`) → coins `4`. Both fall. Short first: coins `5`, then `steep` needs `10` → only one village.

So on that map, lowest loss was the better order. The door cost still decided who could go first.

For a **fixed set** of strong villages, the usual safe order is the same door rule as the weak ones: increasing `A`. Which set to take is the remaining puzzle — and that set has size at most `15`.

## Fork: try every strong subset

`15` strong villages means at most `2^15 = 32768` subsets. That is small enough to try each one.

Sorting **every** chosen village by `A` is wrong here: the sample pillages `(2, 10)` and `(10, 23)` before the strong `(1, 0)`, even though that strong has the smallest door. Strong villages drain the bank, so they never help unlock a later weak village. For a fixed strong subset:

1. Take every weak village first, in increasing `A`.
2. Then take the chosen strong villages in decreasing `B` (highest loot first).
3. Remember the best count over every subset.

Cheapest strong door first fails on an all-strong map where the high-door village has to go early. Highest loot first matches brute force on those cases.

## Plain: what went wrong, and what we do instead

Think of two piles.

**Pile W — weak villages** (`A <= B`). After you beat one, your coins stay the same or go up. So take every weak door you can, cheapest first. That only helps later doors.

**Pile S — strong villages** (`A > B`). After you beat one, your coins go down. Which ones to take, and in which order, is the hard part.

### Why the first code failed

It said: “never keep more than 15 strong villages; keep the ones with the biggest loot.”

Counterexample:

- start with `16` coins
- sixteen strong villages, each `A = 1`, `B = 0`

You can beat them one after another: coins go `16 → 15 → 14 → … → 0`. That is **16** villages. If you only keep 15, you answer **15**. Wrong.

So we do **not** throw strong villages away just to make a short list. We only drop a strong village if its door `A` is already bigger than all the coins we have after the weak pass — then it can never be paid.

### How the strong part works (tiny picture)

Suppose after the weaks you have `25` coins, and three strong villages:

| village | door `A` | loot `B` |
| --- | --- | --- |
| short | 5 | 0 |
| mid | 15 | 11 |
| tall | 21 | 15 |

Empty set: coins `25`, taken `0`.

Add one village as “the last one you beat”:

- last = short: need `5`, have `25` → OK, coins become `20`, set `{short}`
- last = mid: need `15` → OK, coins `21`, set `{mid}`
- last = tall: need `21` → OK, coins `19`, set `{tall}`

Grow those sets by appending another last village the same way. One path that gets all three:

1. start `25`
2. beat **tall** last among `{tall}` → coins `19`
3. beat **mid** last among `{tall, mid}` → coins `15`
4. beat **short** last among all three → coins `10`

So the set of all three is possible, size `3`.

The DP is exactly that: for every set you can already finish, try every missing village as a new last door. Money after a finished set does not depend on order — only on which villages are in the set — so the only question is whether the new last door is cheap enough.

Answer = (how many weaks you took) + (size of the biggest finishable strong set).

## Code notes

Weak villages are sorted by increasing `A` and taken once. Strong villages with `A <=` that purse feed a subset DP: `money_after[mask]` is the purse after finishing every village in `mask`, and a new village may be appended as last when that money pays its door. The DP allows up to 20 strong villages so a case like sixteen `(1, 0)` still fits.

## Insight

Weak villages never drain the bank, so take them all first. Strong villages do drain it, so the question is which full set you can finish. Money after a finished set depends only on the set; reachability is “can this village be last?” The first WA came from deleting strong villages to force a size-15 list — the statement’s “15” is a hint about difficulty, not a license to drop input.

## After AC — what could still improve

Accepted in **0.07s** of a `2s` limit after the WA fix. Memory was not reported.

**Time.** `2^k` with `k <= 20` is at most about a million states. `0.07s` does not need a tighter cap.

**Memory.** One array of `2^k` purse values. It should sit at the usual one-file baseline.

**Already as tight as it needs to be.** Do not rewrite the accepted file. The bound that mattered was keeping every payable strong door in the DP, not the first loot-based trim.
