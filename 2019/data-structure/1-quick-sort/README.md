# 1. Quick Sort (快速排序) <font color=Red>(Buggy)</font>

**Description:**

 要求根据给定输入，按照课堂给定的快速排序算法进行排序。在划分时，以当前序列的首位元素、中间位置元素和最末元素的中间值为枢轴，记为median3。注意，如median3不在首尾，需要和首位元素交换位置。

要求输出排序结果和median3的返回值。

注：cutoff值为5，不足cutoff使用插入排序。

**Example:**

- Input:

```
41
17
34
0
19
#
```

- Output:

```
After Sorting:
0 17 19 34 41 
Median3 Value:
none
```
