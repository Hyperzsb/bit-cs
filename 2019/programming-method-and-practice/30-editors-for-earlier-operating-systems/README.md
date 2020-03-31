# 30. Editors for Earlier Operating Systems (早期操作系统的编辑器)

**Description:**

早期的操作系统均是字符操作界面，那时只能采用简单的行编辑器进行文字处理，于是也只能使用行命令来编辑文本文件。

假设现在要开发一个字符界面的编辑器，对文本的编辑操作是通过输入一个一个的“行编辑命令”完成的。

- **系统约定：** 行编辑命令由`命令关键字 命令参数`组成。其中，命令关键字都是单一的字母，命令与参数之间使用一个空格进行分割，当命令参数为多个时采用`/`作为参数的分隔符，如果在命令的参数中间出现符号`/`，则用`\/`表示。**我们将`\`定义为转义符。**

现在，行编辑器具有如下编辑命令：

- **行插入**：`i %d/串`

  在指定行号（> 0）插入一个新行，新行的内容就是命令中给出的`串`。若插入的行超过了已有的行数，则在最后一行的后面插入一个新行。

- **文本替换**：`c 被替换串/替换串`

  将整个文本中全部`被替换串`替换为`替换串`。

- **行删除**：`d #`

  其中`#`为指定的行号

- **行合并**：`f %d1/%d2/%d3...`

  将行号为 `%d2` 和 `%d3...` 的行连接到行号为 `%d1` 的行的后面，取消原来的 `%d2` 行和 `%d3` 等，合并后 `%d2` 行和 `%d3` 等原来的内容不存在了，被后面的行抵补替代。若指定行号超出正文的范围，则放弃操作。

- **查找串：** `q #%d/串`

  查询行号为`%d`是否出现`串`，如果出现请输出`Yes`，否则输出`No`，保证行号合法，且查询操作在最后出现 。

**Input & Output:**

输入首先是用`[Text]......[/Text]`的形式描述的编辑器初始内容，接下来会有若干插入、修改、删除查询操作。

请根据描述处理所有操作，并输出最终编辑器内容。然后对于每个查询操作，请按时间轴顺序输出查询结果，注意格式和换行。

**Hint:**

假设，我们已经得到了一段文本，这段文本用`[Text]......[/Text]`的形式描述，之后是一串操作命令。

```
[Text]
1 222 33 44
2 333 45 d b g 3 
3 444 56 333 54
[/Text]
c 333/zhang
d 1
i 1/This is a new line 1.
i 4/This is a new line 4.
f 3/4
i 100/new line.
```

**以上命令的执行过程如下：**

[Result：`c 333/zhang`]

```
1 222 33 44
2 zhang 45 d b g 3 
3 444 56 zhang 54
```

[Result：`d 1`]

```
2 zhang 45 d b g 3 
3 444 56 zhang 54
```

[Result：`i 1/This is a new line 1.`]

```
This is a new line 1.
2 zhang 45 d b g 3 
3 444 56 zhang 54
```

[Result：`i 4/This is a new line 4.`]

```
This is a new line 1.
2 zhang 45 d b g 3 
3 444 56 zhang 54
This is a new line 4.
```

[Result：`f 3/4`]

```
This is a new line 1.
2 zhang 45 d b g 3 
3 444 56 zhang 54This is a new line 4.
```

[Result：`i 100/new line.`]

```
This is a new line 1.
2 zhang 45 d b g 3 
3 444 56 zhang 54This is a new line 4.
new line.
```

**Example:**

- Input:

```
[Text]
ab cdefghij klmn20abcedf
ab
a a bb  ccd e
[/Text]
c ab/12345
q #1/def
q #2/0
```

- Output:

```
12345 cdefghij klmn2012345cedf
12345
a a bb  ccd e
Yes
No
```

