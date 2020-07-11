# Halloween Treats (POJ3370)

**Description:**

Every year there is the same problem at Halloween: Each neighbor is only willing to give a certain total number of sweets on that day, no matter how many children call on him, so it may happen that a child will get nothing if it is too late. To avoid conflicts, the children have decided they will put all sweets together and then divide them evenly among themselves. From last year's experience of Halloween they know how many sweets they get from each neighbor. Since they care more about justice than about the number of sweets they get, they want to select a subset of the neighbors to visit, so that in sharing every child receives the same number of sweets. They will not be satisfied if they have any sweets left which cannot be divided.

Your job is to help the children and present a solution.

**Input:**

The input contains several test cases.
The first line of each test case contains two integers **c** and **n** (*1 ≤ **c** ≤ **n** ≤ 100000*), the number of children and the number of neighbors, respectively. The next line contains **n** space separated integers **a<sub>1</sub> , ... , a<sub>n</sub>**  (*1 ≤ **a<sub>i</sub>** ≤ 100000*), where **a<sub>i</sub>** represents the number of sweets the children get if they visit neighbor **i**.

The last test case is followed by two zeros.

**Output:**

For each test case output one line with the indexes of the neighbors the children should select (here, index **i** corresponds to neighbor **i** who gives a total number of **a<sub>i</sub>** sweets). If there is no solution where each child gets at least one sweet print "no sweets" instead. Note that if there are several solutions where each child gets at least one sweet, you may print any of them.

**Example:**

- Input:

```
4 5
1 2 3 7 5
3 6
7 11 2 5 13 17
0 0
```

- Output:

```
3 5
2 3 4
```



