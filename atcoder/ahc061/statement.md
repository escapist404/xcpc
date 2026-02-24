## A - Multi-Player Territory Game

Time Limit: 2 sec / Memory Limit: 1024 MiB

### Story

Takahashi has decided to play a territory-capturing game in which multiple players compete against each other. Compete against AI opponents for control of the land, and aim to win by as large a margin as possible.


### Problem Statement
There is a land represented by an $n \times n$ grid. Let $(0,0)$ be the coordinates of the top-left cell, and $(i,j)$ be the coordinates of the cell located $i$ cells down and $j$ cells to the right from there.

On this land, $M$ players play a territory-capturing game. The players are numbered from $0$ to $M−1$. The other $M−1$ players besides Takahashi (player $0$) are controlled by AI.

Each player $p$ initially owns one cell $(sx_p,sy_p)$ as their **initial territory**, and places a **piece** on that cell.

Each cell $(i,j)$ has a **value** $V_{i,j}$ and a **level** $L_{i,j}$​. The value does not change throughout the game, while the level changes as the game progresses. In the initial state, the level of each player’s initial territory is $1$, and the level of cells that belong to no player is $0$.

The game consists of $T$ turns. Each turn proceeds according to the following steps.

* **Decision of Move Destination**: All players simultaneously decide the destination of their piece. The destination must satisfy the following conditions.

    Define the **reachable territory** as the set of cells that can be reached from the current position of the player’s piece by traversing adjacent (up, down, left, right) cells that belong to the player. The destination must either be included in the reachable territory or be adjacent to at least one cell in the reachable territory.

    The destination must not contain another player’s piece.

* **Conflict Resolution**: After all pieces have been moved simultaneously, the following process is applied to each cell that contains two or more pieces.

    If the cell contains the piece of the owner of that cell, only that piece remains on the board and all other pieces on that cell are removed.

    If the cell belongs to no player, or if it does not contain the piece of the owner of that cell, then all pieces on that cell are removed.

* **Territory Update**: For each player’s piece that was not removed, apply the following process according to the condition of the destination cell.

    * **Occupation**: If the cell belongs to no player, it becomes the player’s territory and its level becomes $1$.

    * **Reinforcement**: If the cell is already the player’s territory, increase its level by $1$. However, the maximum level is the constant $U$ given in the input; if the level is already $U$, it does not change.

    * **Attack**: If the cell belongs to another player, decrease its level by $1$. If the level becomes $0$ as a result, the cell becomes the attacking player’s territory and its level becomes $1$. If the level does not become $0$, the attacking player’s piece is removed.

* **Piece Restoration**: All pieces removed during this turn are returned to the cells where they were located at the beginning of this turn (before movement).

    Note that a player’s piece always exists on their own territory, and a cell containing a piece is not subject to attack by other players. Therefore, a player’s territory never becomes empty.

After $T$ turns, the score $S_p$​ of each player $p$ is defined as the sum of $V_{i, j} \times L_{i, j}$ over all cells $(i,j)$ that belong to player $p$ (including territories that are not reachable).

Takahashi aims to **maximize the ratio of his score to that of the highest-scoring AI player**. That is, let $S_0$ be the score of Takahashi (player $0$), and let $S_A$ be the score of the highest-scoring AI player. Your task is to choose the actions of player $0$ in each turn so as to maximize $S_0/S_A$.

### AI Action Policy

Each AI player $p \space (1 \le p \le M−1)$ has internal parameters $wa_p, wb_p, wc_p, wd_p$, and $\varepsilon_p$, and determines its move destination according to the following algorithm.

For each cell $(i,j)$, define the evaluation value $A_{p,i,j}$ for player $p$ as follows.

* If the cell belongs to no player: $A_{p, i, j} = V_{i, j} \times wa_p$
* If the cell belongs to player $p$ and its level is less than $U$: $A_{p, i, j} = V_{i, j} \times wb_p$
* If the cell belongs to player $p$ and its level is $U$: $A_{p, i, j} = 0$
* If the cell belongs to another player and its level is $1$: $A_{p, i, j} = V_{i, j} \times wc_p$
* If the cell belongs to another player and its level is at least $2$: $A_{p, i, j} = V_{i, j} \times wd_p$
 
Let $B_p$ be the set of all cells to which player $p$ can move. The move destination of player $p$ is determined as follows.

* With probability $\varepsilon_p$​, perform a random action.
    Choose one cell uniformly at random from $B_p$.
* With probability $1 - \varepsilon_p$, perform a greedy action.
    Choose a cell in $B_p$ that maximizes $A_{p, i, j}$. 
    If multiple such cells exist, choose one uniformly at random from among them.


### Scoring

Let $S_0$​ be the score of Takahashi (player $0$), and let $S_A = \max_{1 \le p \le M−1} S_p$ be the highest score among the AI players. The absolute score for a test case is defined as

$$
\mathrm{round} \left( 10^5 \times \log_2{\left(1 + \frac{S_0}{S_A}\right)} \right) 
$$

The higher the absolute score, the better.

For each test case, we compute the **relative score** $\mathrm{round}\left(10^9 \times \frac{\textrm{YOUR}}{\textrm{MAX}}\right)$, where YOUR is your absolute score and MAX is the highest absolute score among all competitors obtained on that test case. The score of the submission is the sum of the relative scores.

The final ranking will be determined by the system test with more inputs which will be run after the contest is over. In both the provisional/system test, if your submission produces illegal output or exceeds the time limit for some test cases, only the score for those test cases will be zero, and your submission will be excluded from the MAX calculation for those test cases.

The system test will be performed only for **the last submission which received a result other than CE**. Be careful not to make a mistake in the final submission.

#### Number of test cases

Provisional test: 100
System test: 3000. We will publish seeds.txt (sha256=24432b101519407fc0e5c2f92f3b939089115b79fd2e71ab3ee737ebc53e0601) after the contest is over.

#### About relative evaluation system

In both the provisional/system test, the standings will be calculated using only the last submission which received a result other than CE. Only the last submissions are used to calculate the MAX for each test case when calculating the relative scores.

The scores shown in the standings are relative, and whenever a new submission arrives, all relative scores are recalculated. On the other hand, the score for each submission shown on the submissions page is the sum of the absolute score for each test case, and the relative scores are not shown. In order to know the relative score of submission other than the latest one in the current standings, you need to resubmit it. If your submission produces illegal output or exceeds the time limit for some test cases, the score shown on the submissions page will be 0, but the standings show the sum of the relative scores for the test cases that were answered correctly.

#### About execution time

Execution time may vary slightly from run to run. In addition, since system tests simultaneously perform a large number of executions, it has been observed that execution time increases by several percent compared to provisional tests. For these reasons, submissions that are very close to the time limit may result in TLE in the system test. Please measure the execution time in your program to terminate the process, or have enough margin in the execution time.

### Input and Output

First, the board size $N$, the number of players $M$, the number of turns $T$, the level cap $U$, the value $V_{i, j}$ of each cell $(i, j)$, and the initial territory $(sx_p, sy_p)$ of each player $p$ are given from Standard Input in the following format.

```
N M T U
V_{0,0} ... V_{0,N-1}
...
V_{N-1,0} ... V_{N-1,N-1}
sx_{0} sy_{0}
...
sx_{M-1} sy_{M-1}
```
 
Each value satisfies the following constraints.

* $N = 10$
* $2 \le M \le 8$
* $T = 100$
* $1 \le U \le 5$
* $1 \le V_{i, j}$
* $\sum_{i, j} V_{i, j} = 1000 \times N^2$
* $0 \le sx_p, sy_p \le N-1$
* The initial territories $(sx_p​, sy_p​)$ of all players $p$ are pairwise distinct.

After reading the above information, repeat the following input/output for each turn $t \space (1 \le t \le T)$.

In each turn, output the destination $(tx_0,ty_0)$ of player $0$'s piece in one line to Standard Output in the following format. The destination must satisfy the conditions described in the problem statement.

```
tx_{0} ty_{0}
```

**The output must be followed by a new line, and you have to flush Standard Output.** Otherwise, the submission might be judged as TLE.

Then, as the board information at the end of turn $t$, the cell $(tx_p, ty_p)$ chosen by each player $p$ as the move destination, the position $(ex_p, ey_p)$ of each player $p$'s piece at the end of the turn, and the owner $O_{i, j}$ and level $L_{i,j}$ of each cell $(i, j)$ at the end of the turn are given from Standard Input in the following format.

```
tx_{0} ty_{0}
...
tx_{M-1} ty_{M-1}
ex_{0} ey_{0}
...
ex_{M-1} ey_{M-1}
O_{0,0} ... O_{0,N-1}
...
O_{N-1,0} ... O_{N-1,N-1}
...
L_{N-1,0} ... L_{N-1,N-1}
```

Each value satisfies the following constraints.

* $0 \le tx_p, ty_p \le N - 1$
* $0 \le ex_p, ey_p \le N - 1$
* $-1 \le O_{i, j} \le M - 1$
* If $O_{i, j} = -1$, the cell belongs to no player.
* $0 \le L_{i, j} \le U$

### Input Generation
Let $\mathrm{randint}(L, U)$ denote a function that generates an integer value uniformly at random between $L$ and $U$ (inclusive). Let $\mathrm{randdouble}(L, U)$ denote a function that generates a real value uniformly at random in the range $[L,U)$.

The number of players $M$ is generated by $\mathrm{randint}(2, 8)$.
The level cap $U$ is generated by $\mathrm{randint}(1, 5)$.
The initial positions $(sx_p, sy_p)$ of the players are generated uniformly at random so that no two positions overlap.

#### Generation of $V$

$V_{i,j}$ is generated by the following procedure.

Let $a = \mathrm{randdouble}(0.0, 3.0)$.
For each cell $(i,j)$, initialize $V_{i,j} = (\mathrm{randdouble}(0.5,1.0))^a$.
Let $K = \mathrm{randint}(0, 2)$, and repeat the following procedure $K$ times.
Let $x=\mathrm{randint}(0,N−1), y=\mathrm{randint}(0,N−1), b=\mathrm{randdouble}(1.0,4.0), m=\mathrm{randint}(0,4)$, and $R=\mathrm{randdouble}(1.0,5.0)$.
Depending on the value of $m$, add the following to each cell $(i,j)$.
* $m = 0$: $V_{i,j} \gets V_{i,j} + b \times \exp(−\frac{(i-x)^2 + (j-y)^2}{2R^2})$
* $m = 1$: $V_{i,j} \gets V_{i, j} + \frac{b}{1 + \sqrt{(i-x)^2+(j-y)^2} / R}$
* $m = 2$: For cells satisfying $(i-x)^2+(j-y)^2 \le R^2$, set $V_{i, j} \gets V_{i, j} + b/4$
* $m = 3$: $V_{i, j} \gets V_{i, j} + \frac{b}{1 + \left(| i - x | + | j - y |\right) / R}$
* $m = 4$ : For cells satisfying 
$|i−x|+|j−y| \le R$, set $V_{i, j} \gets V_{i, j} + b/4$

Let $S$ be the sum of all $V_{i,j}$, and set $V_{i, j} \gets \lceil \frac{V_{i, j} \times 1000 \times N^2}{S} \rceil$.

While $\sum_{i, j} V_{i, j} > 1000 \times N^2$, repeatedly choose one cell uniformly at random among those with $V_{i, j} \ge 2$ and decrease $V_{i, j}$ by 1.

#### Generation of AI Internal Parameters
For each AI player $p \space (1 \le p \le M−1)$,
* $wa_p, wb_p, wc_p, wd_p$ are generated independently by $\mathrm{randdouble}(0.3,1.0)$.
* $\varepsilon_p$ is generated by $\mathrm{randdouble}(0.1,0.5)$.
