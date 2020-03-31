# 25. Direction Mark (方向标)

**Description:**

A carpenter has received an order for a wooden directional sign. Each board must be aligned vertically with the previous one, either to the basis of the previous arrowhead or to the opposite side, being fixed there with a specially designed screw. The two boards must overlap. The carpenter wrote down a sequence of integers to encode the sketch sent by the designer but the sequence does not determine a unique model and he has thrown away the original sketch. What looked like a trivial task turned out a big jigsaw to him.

![img](http://lexue.bit.edu.cn/pluginfile.php/197774/mod_programming/intro/1.jpg)

The sequence (with 1 + N elements) encodes the (N) arrows from the bottom to the top of the sign. The first element is the position of the left side of the bottom arrow. The remaining N elements define the positions where the arrowheads start, from bottom to top: the i-th element is the position where the i-th arrowhead basis is. For instance, the two signs depicted (on the left and on the right) could be encoded by 2 6 5 1 4.

Since a board must be aligned vertically with the previous one (either to the basis of the previous arrowhead or to the opposite side), if the sequence was 2 6 5 1 4 3, the fifth arrow could be fixed (in any of the depicted signs) with a screw either at 1 (pointing to the right) or at 4 (pointing to the left), with the arrowhead basis at 3.

If the sequence was 2 3 1, the second arrow could only be fixed with a screw at 3, pointing to the left, because consecutive boards must overlap.

![img](http://lexue.bit.edu.cn/pluginfile.php/197774/mod_programming/intro/2.jpg)

All arrowheads are similar and the designer told the carpenter that their bases stand in different vertical lines, as well as the left side of the bottom arrow, altogether forming a permutation of 1..(N +1). That is why the carpenter overlooked the details and just wrote down the permutation (e.g., 2 6 5 1 4 3).

Given the sequence of numbers the carpenter wrote down, compute the number of directional arrows signs that can be crafted. Since the number can be very large, you must write it modulo 2147483647. The second integer in the sequence is always greater than the first one (the bottom arrow points to the right always).

**Input:**

The first line has one integer N and the second line contains a permutation of the integers from 1 to N + 1. Integers in the same line are separated by a single space.

**Output:**

The output has a single line with the number (**modulo** 2147483647) of distinct signs that can be described by the given permutation.

**Note:**

![1 小於等於 N 小於等於 2000](data:image/svg+xml;charset=utf8,%3Csvg%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%20xmlns%3Awrs%3D%22http%3A%2F%2Fwww.wiris.com%2Fxml%2Fcvs-extension%22%20height%3D%2219%22%20width%3D%2284%22%20wrs%3Abaseline%3D%2215%22%3E%3C%21--MathML%3A%20%3Cmath%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F1998%2FMath%2FMathML%22%20style%3D%22font-family%3A%27Times%20New%20Roman%27%22%3E%3Cmn%3E1%3C%2Fmn%3E%3Cmo%3E%26%23x2264%3B%3C%2Fmo%3E%3Cmi%3EN%3C%2Fmi%3E%3Cmo%3E%26%23x2264%3B%3C%2Fmo%3E%3Cmn%3E2000%3C%2Fmn%3E%3C%2Fmath%3E--%3E%3Cdefs%3E%3Cstyle%20type%3D%22text%2Fcss%22%3E%40font-face%7Bfont-family%3A%27math1a36adbc35e69b22acbf9f834a0%27%3Bsrc%3Aurl%28data%3Afont%2Ftruetype%3Bcharset%3Dutf-8%3Bbase64%2CAAEAAAAMAIAAAwBAT1MvMi7iBBMAAADMAAAATmNtYXDEvmKUAAABHAAAADRjdnQgDVUNBwAAAVAAAAA6Z2x5ZoPi2VsAAAGMAAAAkWhlYWQQC2qxAAACIAAAADZoaGVhCGsXSAAAAlgAAAAkaG10eE2rRkcAAAJ8AAAACGxvY2EAHTwYAAAChAAAAAxtYXhwBT0FPgAAApAAAAAgbmFtZaBxlY4AAAKwAAABn3Bvc3QB9wD6AAAEUAAAACBwcmVwa1uragAABHAAAAAUAAADSwGQAAUAAAQABAAAAAAABAAEAAAAAAAAAQEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACAgICAAAAAg1UADev96AAAD6ACWAAAAAAACAAEAAQAAABQAAwABAAAAFAAEACAAAAAEAAQAAQAAImT%2F%2FwAAImT%2F%2F92dAAEAAAAAAAABVAMsAIABAABWACoCWAIeAQ4BLAIsAFoBgAKAAKAA1ACAAAAAAAAAACsAVQCAAKsA1QEAASsABwAAAAIAVQAAAwADqwADAAcAADMRIRElIREhVQKr%2FasCAP4AA6v8VVUDAAADAID%2FqwKAAqsAAwAHAAsALxgBALEJAD%2BxCAXksQIF9LEBBPSxBgX0sQME5LEFBPSxBAX0sQcBEDyxAAYQPDAxEwcBNRM1ARcBNSEVgQEB%2FwH%2BAAEB%2F%2F4AAatW%2FwBWAapW%2FwBW%2FlZVVQAAAAABAAAAAQAA1XjOQV8PPPUAAwQA%2F%2F%2F%2F%2F9Y6E3P%2F%2F%2F%2F%2F1joTcwAA%2FyAEgAOrAAAACgACAAEAAAAAAAEAAAPo%2F2oAABdwAAD%2FtgSAAAEAAAAAAAAAAAAAAAAAAAACA1IAVQMAAIAAAAAAAAAAKAAAAJEAAQAAAAIAXgAFAAAAAAACAIAEAAAAAAAEAADeAAAAAAAAABUBAgAAAAAAAAABABIAAAAAAAAAAAACAA4AEgAAAAAAAAADADAAIAAAAAAAAAAEABIAUAAAAAAAAAAFABYAYgAAAAAAAAAGAAkAeAAAAAAAAAAIABwAgQABAAAAAAABABIAAAABAAAAAAACAA4AEgABAAAAAAADADAAIAABAAAAAAAEABIAUAABAAAAAAAFABYAYgABAAAAAAAGAAkAeAABAAAAAAAIABwAgQADAAEECQABABIAAAADAAEECQACAA4AEgADAAEECQADADAAIAADAAEECQAEABIAUAADAAEECQAFABYAYgADAAEECQAGAAkAeAADAAEECQAIABwAgQBNAGEAdABoACAARgBvAG4AdABSAGUAZwB1AGwAYQByAE0AYQB0AGgAcwAgAEYAbwByACAATQBvAHIAZQAgAE0AYQB0AGgAIABGAG8AbgB0AE0AYQB0AGgAIABGAG8AbgB0AFYAZQByAHMAaQBvAG4AIAAxAC4AME1hdGhfRm9udABNAGEAdABoAHMAIABGAG8AcgAgAE0AbwByAGUAAAMAAAAAAAAB9AD6AAAAAAAAAAAAAAAAAAAAAAAAAAC5BxEAAI2FGACyAAAAFRQTsQABPw%3D%3D%29format%28%27truetype%27%29%3Bfont-weight%3Anormal%3Bfont-style%3Anormal%3B%7D%3C%2Fstyle%3E%3C%2Fdefs%3E%3Ctext%20font-family%3D%22Times%20New%20Roman%22%20font-size%3D%2216%22%20text-anchor%3D%22middle%22%20x%3D%224.5%22%20y%3D%2215%22%3E1%3C%2Ftext%3E%3Ctext%20font-family%3D%22math1a36adbc35e69b22acbf9f834a0%22%20font-size%3D%2214%22%20text-anchor%3D%22middle%22%20x%3D%2215.5%22%20y%3D%2215%22%3E%26%23x2264%3B%3C%2Ftext%3E%3Ctext%20font-family%3D%22Times%20New%20Roman%22%20font-size%3D%2216%22%20font-style%3D%22italic%22%20text-anchor%3D%22middle%22%20x%3D%2229.5%22%20y%3D%2215%22%3EN%3C%2Ftext%3E%3Ctext%20font-family%3D%22math1a36adbc35e69b22acbf9f834a0%22%20font-size%3D%2214%22%20text-anchor%3D%22middle%22%20x%3D%2243.5%22%20y%3D%2215%22%3E%26%23x2264%3B%3C%2Ftext%3E%3Ctext%20font-family%3D%22Times%20New%20Roman%22%20font-size%3D%2216%22%20text-anchor%3D%22middle%22%20x%3D%2267.5%22%20y%3D%2215%22%3E2000%3C%2Ftext%3E%3C%2Fsvg%3E)

**Example:**

- Input:

```
2
2 3 1
```

- Output:

```
1
```

