# ngoding

A study archive. Not a trophy case.

I come back to online-judge problems I could not solve (and new ones I hit later) to learn how they are *supposed* to be solved. An AI agent walks the thought process with me. I am not here to farm Accepted verdicts or take credit for work I did not do.

A solution is right only when **both** are true:

1. I understand the idea.
2. The judge returns AC.

Understanding without AC is an unproven guess. AC without understanding is credit I do not want. A session is not done until both land.

The old flat `.cpp` files (UVa, CodeChef, …) are history. Leave them. New problems use the folder layout below.

SPOJ solved sources that have not been restudied live as code-only folders until a session adds `statement.md` and `solution.md`. They sit under `oj/spoj/{classical,tutorial,basics,challenge,partial,riddle}/<ID>/`.

## How a session feels

I name a problem (id, URL, or pasted statement). We do **not** dump a finished solution.

The agent restates the problem (constraints included) and asks how I would try it. We start from my approach. The agent then guides that thinking toward the process that actually solves it — questions, the gap in the model, the next fork — instead of dumping the finished path first. When a named theory, algorithm, or data structure shows up, the agent also gives a quick explanation of what it is and why it fits — not a textbook dump, enough that I am not left with a label I do not own.

The algorithm has to survive a tiny example before any real code. When a picture would make the idea easier — a time line, a DP table, a graph, a shrinking search range — draw it (Mermaid, a compact ASCII figure, or a small table). Skip decoration. Code is written only after I say go.

I submit to the judge. The agent never submits. After I have a verdict, the agent asks for the result — AC, WA, TLE, and time and memory when I have them (optional). If the judge says WA or TLE, we debug the *idea* first (wrong model, off-by-one, complexity), then the implementation. The miss stays in `solution.md`: what we tried, what the judge said, what that taught, and how the next fork fixed it. Do not erase a failed attempt when the accepted write-up lands — the path is part of the study.

We close by naming the one insight that makes the problem collapse. That is the thing worth remembering.

After AC, one more pass: how this could still improve. Time and memory, yes — also simpler bounds, clearer structure, less work per check, kinder I/O, fewer allocations, anything that is actually an improvement. Write those insights down. Do not rewrite the accepted code unless I ask — the point is to see the next level, not to churn a second submission.

## Per-problem folder

When a new problem lands, create a directory under the matching judge. Keep an existing contest subfolder if one already exists (for example `oj/codechef/APRIL17/`).

```
oj/<judge>/<PROBLEM_ID>/
  statement.md
  solution.md
  <PROBLEM_ID>.cpp
```

Example: `oj/spoj/classical/LCS0/statement.md`, `oj/spoj/classical/LCS0/solution.md`, `oj/spoj/classical/LCS0/LCS0.cpp`.

**`statement.md`** — a full restatement in our own words. Not a summary. Not a paste of the original. Keep every essential: story/task, input format, output format, constraints, special cases, sample inputs, sample outputs. If the original had it, the restatement has it.

**`solution.md`** — the written solution(s): forks we considered, the algorithm, the tiny example that proves it, the key insight, and an explanation of the **non-trivial** parts of the code (why that loop exists, what the state means, where the off-by-one lives). Skip the obvious. If a named theory, algorithm, or data structure is used, a short explanation lives here too. If a visual made the idea click, keep it here. If a submission was not AC, keep that attempt in the file too — the discussion and the fix — not only the final accepted path. If more than one approach AC'd, they all live here. After AC, a short section on what could still improve: time, memory, and any other optimization worth seeing. Note what is already as tight as it needs to be.

**`<PROBLEM_ID>.cpp`** — the implementation. Do not mimic the old contest-golf / `scanf` style in this repo. Write clear code. Comments only on non-trivial bits (the *why*, not the *what*). Code only after I say go.

New work does not land as a lone `.cpp` at the judge root.

## Git

One problem per branch, named `<judge>/<PROBLEM_ID>` (judge name or short code, then the problem code). Examples: `spoj/LCS0`, `uva/10453`, `codechef/CLIQUED`. Never a second problem on the same branch.

When a problem is done — I understand it, the judge has AC, and the post-AC notes are written — squash-merge that branch into `main` locally, push `main`, and delete the problem branch immediately (local, and remote if it exists). No pull requests in this repo.
