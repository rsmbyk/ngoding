# LCS0 — Longest Common Subsequence

Two strings `A` and `B`. A **subsequence** is what you get by deleting zero or more characters, keeping the rest in order (gaps allowed). A **common** subsequence is one that can be carved out of both strings. Find the **length** of a longest one. The characters themselves are not required.

Source: [SPOJ LCS0](https://www.spoj.com/problems/LCS0/)

The original page has no story. “No imagination at the moment.”

## Input

One test. Exactly two lines.

- Line 1: string `A`
- Line 2: string `B`

Both strings are lowercase Latin letters (`a`–`z`). No length is given on a separate line; the line is the string.

## Output

One integer: the length of a longest common subsequence of `A` and `B`.

## Constraints

- `|A| ≤ 50000`, `|B| ≤ 50000`
- Alphabet size 26
- Time limit `1s`
- Memory limit `1536 MB`
- Source limit `50000` bytes

`|A| · |B|` reaches `2.5 · 10^9`. A length is at most `min(|A|, |B|) ≤ 50000`.

The setter’s note on the page: `O(NM)` and `O(N²)` will not pass.

## Special cases

- No shared letter: answer `0`.
- One string is a subsequence of the other: answer `min(|A|, |B|)`.
- Both strings are the same letter repeated: answer `min(|A|, |B|)`.
- Empty strings are not forbidden by the wording (“no more than 50000”). If one is empty, the answer is `0`.
- We need the length only, not the subsequence.

## Sample

Input:

```
abababab
bcbb
```

Output:

```
3
```

`B` is `b c b b`. One common subsequence of length 3 is `b b b`, taking the `b`s of `A` in order. There is no common subsequence of length 4: `B` itself is not a subsequence of `A` (`A` has no `c`).
