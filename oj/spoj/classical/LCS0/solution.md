# LCS0 — solution

Accepted on SPOJ (1.47s, 5.2M).

A **subsequence** may skip letters. It may not reorder. Substring (one solid block) is a different problem; the sample’s `bbb` skips `c` in `B`.

## Forks

**Fill every DP cell.** `dp[i][j]` = LCS of `A[1..i]` and `B[1..j]`. Match → diagonal `+ 1`, else `max(up, left)`. `|A| · |B|` is `2.5 · 10^9` cells in 1s. Dead even with a rolling row.

**Only matching pairs (Hunt–Szymanski / LCS via LIS).** Cost tracks `C` = how many pairs `(i, j)` have `A[i] = B[j]`. Both strings all `a` makes `C` still `Θ(NM)`. Setter said this family fails; no bound on `C`.

**Same table, lamps not numbers.** In a row the value stays or goes up by 1. Store only the houses where it ticks. That is still `O(NM)` if each letter of `A` walks all of `B`, unless a machine updates many houses in one instruction.

## Algorithm

Fix `B` as a street of houses. After reading a prefix of `A`, lamp `k` sits on the **leftmost** house in `B` where some common subsequence of length `k` already ends.

- The number in house `j` in the textbook row is “how many lamps on this house or to the left.”
- The answer is the number of lamps. We never need the actual string.

When `A` shows a letter `x`, every lamp looks at the **old** seats, then they jump together:

```
new seat of lamp k = min(
    old seat of lamp k,
    first house named x that is strictly after lamp k-1’s old seat
)
```

Lamp 1 uses “after the start.” If that `x` exists after the last old lamp, a new lamp appears. Leftmost is better: finishing length `k` earlier leaves more street for `k+1`.

The lamps on one row are finish lines, not one common string. Different lengths may come from different subsequences.

## Tiny example

`A = ccbbb`, `B = bccbbb`.

```
B:  b   c   c   b   b   b
```

After `c`: lamp 1 on the first `c`. After another `c`: lamp 2 on the second `c`.

`A` says `b`. Lamp 1 jumps **left** onto the first `b`. Lamp 2 **stays** on the second `c` (`"cc"` still finishes length 2 earlier than any `"xb"`). Lamp 3 appears on the next `b`:

```
    b   c   c   b   b   b
    1       2   3
```

Those three lamps are not the string `"bcb"` — `"bc"` is not even a subsequence of `A`. They are only earliest finish lines. Two more `b`s add lamps 4 and 5. Score 5: all of `A` sits in `B` if you skip the first `b`.

Official sample `abababab` / `bcbb` ends with three lamps on `B`’s three `b`s. Score 3.

## Bits (same lamps, 64 houses at a time)

Bit `j` of `V` is on iff a lamp sits on house `j`. Precompute 26 masks: bit `j` of `PM[c]` is on iff `B[j] = c`. After each character of `A`, `V` becomes the new lamp row. Answer = number of 1-bits.

The jump-left rule on a whole street is: OR `V` with the match mask (every gap still has its old lamp as a wall), then keep only the **leftmost 1 of each gap**. Subtracting 1 at the start of a gap knocks that first 1 off — all gaps at once, because the old lamps are borrow walls. Allison–Dix / Hyyrö, with bit 0 = first house of `B`:

```
U = V | PM[x]
V = U & ((U - ((V << 1) | 1)) XOR U)
```

`(V << 1) | 1` puts a 1 at house 0 and just after every old lamp — the start of each gap.

Work is `|walk| · ceil(|houses| / 64)`. Walking the shorter string and packing the longer is about `4 · 10^7` word steps when both are `5 · 10^4`, and cheaper when the lengths differ. Comfortable for 1s. `std::bitset` has no minus; the words are `uint64_t` with borrow between them.

## Why the code is careful

- **Last-word mask.** Only `m` houses exist. A left shift can light bit `m`, past the street. That extra 1 would make the big-integer subtract wrong. Mask after the shift and after the update.
- **Borrow, not one `uint64_t`.** `U - ((V << 1) | 1)` is subtraction of a `m`-bit number. Carry/borrow has to walk the words the same way a shift does, low word first (bit 0 = first house).
- **Which string is the street.** LCS is symmetric. Inner work is smaller if the loop is the shorter string. Empty either side is 0 before any words are built.

## Insight

A DP row is a handful of “earliest finish” lamps, not `5 · 10^4` different integers. Encode the lamps as bits and one subtraction slides every lamp at once.

## After AC — what could still improve

The accepted code is the right algorithm. Time is the live number: **1.47s** on Cube (Intel G860, 2011). Memory **5.2M** is already noise against a 1536 MB cap — 26 match masks plus three working arrays of 782 words is a couple of hundred KB; the rest is the binary and iostream.

**Time.** Worst case is still `5·10^4 · ceil(5·10^4 / 64) ≈ 4·10^7` word steps. Each step is several ops, and we currently do **three** passes per letter of `walk` (OR into `united`, build `gap_start`, subtract). Word `w` of the subtract only needs word `w` of those, and the shift-in bit comes from word `w-1`, so one fused pass is the same math with less store/reload. That is the improvement that would actually move 1.47s. Static `u64[782]` instead of `vector` is the same idea, smaller.

128-bit words (`__uint128_t` / SSE2) would cut the word count in half. The G860 has SSE2 and not AVX2, so 256-bit is a later-machine trick, not this cluster. Hyyrö’s addition form (complement encoding) is the same `O(nm / w)` with a different inner op — similar speed, not a new class.

**Already as tight as it needs to be.** I/O of two `5·10^4` strings is not 1.47s. Popcount of 782 words is not 1.47s. Hunt–Szymanski is still `Θ(nm)` on the all-`a` tests. Do not rewrite the accepted file for the fused pass unless we are chasing a tighter time.
