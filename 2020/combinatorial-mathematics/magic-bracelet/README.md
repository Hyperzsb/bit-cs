# Magic Bracelet

**Description:**

Ginny’s birthday is coming soon. Harry Potter is preparing a birthday present for his new girlfriend. The present is a magic bracelet which consists of *n* magic beads. The are *m* kinds of different magic beads. Each kind of beads has its unique characteristic. Stringing many beads together a beautiful circular magic bracelet will be made. As Harry Potter’s friend Hermione has pointed out, beads of certain pairs of kinds will interact with each other and explode, Harry Potter must be very careful to make sure that beads of these pairs are not stringed next to each other.

There infinite beads of each kind. How many different bracelets can Harry make if repetitions produced by rotation around the center of the bracelet are neglected? Find the answer taken modulo 9973.

**Input:**

The first line of the input contains the number of test cases.

Each test cases starts with a line containing three integers *n* (1 ≤ *n* ≤ 10<sup>9</sup>, *gcd*(*n*, 9973) = 1), *m* (1 ≤ *m* ≤ 10), *k* (1 ≤ *k* ≤ *m*(*m* − 1) ⁄ 2). The next k lines each contain two integers *a* and *b* (1 ≤ *a*, *b* ≤ *m*), indicating beads of kind *a* cannot be stringed to beads of kind *b*.

**Output:**

Output the answer of each test case on a separate line.

**Example:**

- Input:

```
4
3 2 0
3 2 1
1 2
3 2 2
1 1
1 2
3 2 3
1 1
1 2
2 2
```

- Output:

```
4
2
1
0
```

**Source:**

POJ Monthly--2006.07.30, cuiaoxiang