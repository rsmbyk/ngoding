# CODERE4

## Fork: same shape as the second sequence

The first two sequences each use the two terms before them. The second one is `F(n) = 2 * F(n-1) + F(n-2)`. Try that same mix on the third sequence and look at what is left over.

Third sequence, writing the terms as `a1, a2, a3, ...`:

| n | `a(n)` | `2 * a(n-1) + a(n-2)` | leftover to reach `a(n)` |
| --- | --- | --- | --- |
| 3 | 3 | `2 * 1 + 1 = 3` | 0 |
| 4 | 8 | `2 * 3 + 1 = 7` | 1 |
| 5 | 20 | `2 * 8 + 3 = 19` | 1 |
| 6 | 50 | `2 * 20 + 8 = 48` | 2 |
| 7 | 123 | `2 * 50 + 20 = 120` | 3 |

The leftovers are `0, 1, 1, 2, 3`. That is the start of the first sequence, the Fibonacci numbers, lined up under these terms.

Under `n = 7` the leftover is `3`. With Fibonacci written `F(0) = 0`, `F(1) = 1`, `F(2) = 1`, `F(3) = 2`, `F(4) = 3`, that leftover is `F(4)`. The same match for the earlier rows: leftover at `n` is `F(n - 3)`.

So from `n = 3` onward:

`a(n) = 2 * a(n-1) + a(n-2) + F(n - 3)`

with `a(1) = 1`, `a(2) = 1`.

## Fork: a walk to N is too slow

`N` can be `1000000000` and there are up to `1000` tests. Stepping the recurrence one `n` at a time will not finish. The same kind of recurrence is used for Fibonacci, and there the usual jump is matrix exponentiation: pack the last few terms into a short vector, multiply that vector by a fixed matrix once per step, then raise the matrix to the power `N` in about `log N` multiplications. Here the add-on is itself Fibonacci, so the vector has to carry both the `a` terms and the `F` terms that feed them.

## What one step needs

The next third-sequence term is

`a(n + 1) = 2 * a(n) + a(n - 1) + F(n - 2)`

So to write that number you need three known values: `a(n)`, `a(n - 1)`, and `F(n - 2)`. After the step, the new "previous two" are `a(n + 1)` and `a(n)`. The new leftover for the step after that is `F(n - 1)`, and Fibonacci only gives that if you also still have `F(n - 3)`, because `F(n - 1) = F(n - 2) + F(n - 3)`.

One step therefore needs a four-slot vector, for example:

```
[ a(n) , a(n - 1) , F(n - 2) , F(n - 3) ]
```

From those four you can build the next four:

```
[ a(n + 1) , a(n) , F(n - 1) , F(n - 2) ]
```

and a fixed 4×4 matrix multiplies the old vector into the new one.

At `n = 3` the vector is `[3, 1, F(1), F(0)] = [3, 1, 1, 0]`. One step builds `a(4) = 2*3 + 1 + 1 = 8`, which matches the sequence. The new vector is `[8, 3, F(2), F(1)] = [8, 3, 1, 1]`.

For `N = 1` or `N = 2` the answer is `1`. For larger `N`, start from the vector at `n = 3` and raise the step matrix to the power `N - 3`. Each matrix multiply is modulo `1000000007`. That is about `log N` work per test, which fits `T <= 1000` and `N <= 1000000000`.

## Why about `log N` multiplies

Raising the step matrix to the power `P = N - 3` does not multiply it by itself `P` times. Write `P` in binary. Each bit is one squaring of the matrix so far, and when the bit is `1` there is one extra multiply into the answer.

Example: `P = 13 = 1101` in binary, so `13 = 8 + 4 + 1`.

| step | matrix on hand | what it is | used in the answer? |
| --- | --- | --- | --- |
| start | `M` | `M^1` | yes, the `1` bit |
| square | `M^2` | | no, the `2` bit of 13 is off |
| square | `M^4` | | yes, the `4` bit |
| square | `M^8` | | yes, the `8` bit |

That is three squarings and two multiplies into the answer. In general the number of matrix multiplies is about twice the number of bits in `P`, which is about `2 * log2(N)`. A 4×4 multiply is a fixed handful of integer ops, so one test stays far under a second even when `N` is a billion.

## Code notes

The step matrix is

```
| 2  1  1  0 |
| 1  0  0  0 |
| 0  0  1  1 |
| 0  0  1  0 |
```

The first row builds `a(n + 1)`. The second copies `a(n)`. The last two rows advance Fibonacci. `N <= 2` returns `1`. Otherwise the start vector is `[3, 1, 1, 0]` and the answer is the first entry after `N - 3` steps. Every product is taken modulo `1000000007` before it can overflow a 64-bit integer: each factor is below the modulus, so one product fits in 64 bits.

## Insight

The third sequence is the second sequence's recurrence with a Fibonacci leftover glued on. One step needs the last two `a` values and the last two Fibonacci leftovers, so a 4×4 matrix jumps `N` in about `log N` multiplies.

## After AC — what could still improve

Accepted in **0.01s** of a `1s` limit. Memory was not reported.

**Time.** A thousand tests each do a handful of 4×4 multiplies. Precomputing nothing across tests is already fine: `0.01s` does not need a shared cache of powers.

**Memory.** One 4×4 matrix and a four-slot vector. It should sit at the usual one-file baseline.

**Already as tight as it needs to be.** Do not rewrite the accepted file. The bound that mattered was packing Fibonacci into the same step as `a`, not shrinking the matrix further.
