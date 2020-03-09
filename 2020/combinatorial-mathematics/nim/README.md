# Nim

**Description:**

Nim is a 2-player game featuring several piles of stones. Players alternate turns, and on his/her turn, a player’s move consists of removing *one or more stones* from any single pile. Play ends when all the stones have been removed, at which point the last player to have moved is declared the winner. Given a position in Nim, your task is to determine how many winning moves there are in that position.

A position in Nim is called “losing” if the first player to move from that position would lose if both sides played perfectly. A “winning move,” then, is a move that leaves the game in a losing position. There is a famous theorem that classifies all losing positions. Suppose a Nim position contains *n* piles having **k<sub>1</sub>** + **k<sub>2</sub>** + … + **k<sub>n</sub>** stones respectively; in such a position, there are **k<sub>1</sub>** + **k<sub>2</sub>** + … + **k<sub>n</sub>** possible moves. We write each *ki* in binary (base 2). Then, the Nim position is losing if and only if, among all the **k<sub>i</sub>**’s, there are an even number of 1 in each digit position. In other words, the Nim position is losing if and only if the *xor* of the **k<sub>i</sub>**’’s is 0.

Consider the position with three piles given by **k<sub>1</sub>** = 7, **k<sub>2</sub>** = 11, and **k<sub>3</sub>** = 13. In binary, these values are as follows:

<center>
     111<br>
     1011</br>
     1101
</center>

There are an odd number of 1 among the rightmost digits, so this position is not losing. However, suppose **k<sub>3</sub>** were changed to be 12. Then, there would be exactly two 1 in each digit position, and thus, the Nim position would become losing. Since a winning move is any move that leaves the game in a losing position, it follows that removing one stone from the third pile is a winning move when **k<sub>1</sub>** = 7, **k<sub>2</sub>** = 11, and **k<sub>3</sub>** = 13. In fact, there are exactly three winning moves from this position: namely removing one stone from any of the three piles.

**Example:**

- Input:

```
3
7 11 13
2
1000000000 1000000000
0
```

- Output:

```
3
0
```