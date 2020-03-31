# 7. Thousand Characters (一夜发白《千字文》)

**Background:**

在古代中国，《三字经》、《百家姓》、《千字文》被合称为三、百、千，都是非常重要的启蒙教育课本，广为流传。而其中问世最早的《千字文》更凭借其优美的文字、华丽的辞藻成为中华传统文化的一个重要组成部分，得到了人们的普遍重视和喜爱。

```
《千字文》的作者，是梁武帝时代官拜散骑员外郎的周兴嗣。历来在正史上的记载，就这样一笔带过，但据私家笔记的野史记载，内容不是这样简单了。周兴嗣同梁武帝本来便是文字之交的朋友，在萧齐时代，还在朝廷上有过同僚之谊。到了梁武帝当了皇帝，那就变成君臣的关系。由朋友变君臣，说是关系不错，其实，伴君如伴虎，反是最糟糕的事，周兴嗣有一次不小心得罪了梁武帝，梁武帝一怒之下，想杀他或很严厉地处分他，到底还是于心不忍，只好下令把先关起来再说。但梁武帝又说了一句话，你不是文才很好吗？你能在一夜之间，把一千个不同的字，写一篇好文章，就赦你无罪。因此，周兴嗣就在一夜之间，挖空心思，写了这篇《千字文》。文章写好了，可是在一夜之间，头发、眉毛、胡子也都白了！大家要注意，用一千个不同的中文字，一夜之间，写出有关宇宙、物理、人情、世故的文间，等于写了一篇非常精简的“中国文化纲领要点”，虽然，只写到南北时期的梁朝为止，实在也太难了。梁武帝本人，才华文学都自命不凡，看了周兴嗣一夜之间之间所写的《千字文》，也不能不佩服。周兴嗣因此得到宽恕，而且还特加赏赐。
                                               ——摘自南怀瑾《原本大学微言》
```

现代人，一生中有机会通读千字文的机会是非常少的，很多理工科的大学生，完全没有听说过这篇神奇的文章，自然也会抱着“怀疑一切”的态度问，真的有这么神吗，真的一个重复的字都没有吗？耳听为虚，眼见为实，我们就来检验一下千字文中是不是真的没有重复的字。

不过在动手之前，先让我们花上几分钟的时间，读读《千字文》吧：[简体中文版](http://online.bit.edu.cn/moodle/mod/page/view.php?id=85586)、[正体中文版](http://online.bit.edu.cn/moodle/mod/page/view.php?id=85587)。

**Description:**

编写一个程序，从输入中读取一篇中文文章，并统计出该文章中 ASCII 字符以外的重复出现的每一个字重复出现的次数。

文章使用 UTF-8 编码，可能会出现任何可以用 UTF-8 编码表示的字符（不限于中文）。

文章中所有的字符在 UCS-2 能够表示的范围内，即字符的 Unicode 值用两个字节就可以表示。

**Input:**

一篇文章，总字数不限、每行字符数不限。每个字重复出现的次数不超过 ![60000 空格](data:image/svg+xml;charset=utf8,%3Csvg%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%20xmlns%3Awrs%3D%22http%3A%2F%2Fwww.wiris.com%2Fxml%2Fcvs-extension%22%20height%3D%2219%22%20width%3D%2245%22%20wrs%3Abaseline%3D%2215%22%3E%3C%21--MathML%3A%20%3Cmath%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F1998%2FMath%2FMathML%22%20class%3D%22wrs_chemistry%22%20style%3D%22font-family%3A%27Times%20New%20Roman%27%22%3E%3Cmn%3E60000%3C%2Fmn%3E%3Cmo%3E%26%23xA0%3B%3C%2Fmo%3E%3C%2Fmath%3E--%3E%3Cdefs%3E%3Cstyle%20type%3D%22text%2Fcss%22%2F%3E%3C%2Fdefs%3E%3Ctext%20font-family%3D%22Times%20New%20Roman%22%20font-size%3D%2216%22%20text-anchor%3D%22middle%22%20x%3D%2220.5%22%20y%3D%2215%22%3E60000%3C%2Ftext%3E%3C%2Fsvg%3E) 次。

**Output:**

按照 Unicode 编码从小到大的顺序，输出文章中 ASCII ![左括号 0 雙點 127 右括号](data:image/svg+xml;charset=utf8,%3Csvg%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%20xmlns%3Awrs%3D%22http%3A%2F%2Fwww.wiris.com%2Fxml%2Fcvs-extension%22%20height%3D%2220%22%20width%3D%2259%22%20wrs%3Abaseline%3D%2215%22%3E%3C%21--MathML%3A%20%3Cmath%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F1998%2FMath%2FMathML%22%20class%3D%22wrs_chemistry%22%20style%3D%22font-family%3A%27Times%20New%20Roman%27%22%3E%3Cmo%3E%28%3C%2Fmo%3E%3Cmn%3E0%3C%2Fmn%3E%3Cmo%3E~%3C%2Fmo%3E%3Cmn%3E127%3C%2Fmn%3E%3Cmo%3E%29%3C%2Fmo%3E%3C%2Fmath%3E--%3E%3Cdefs%3E%3Cstyle%20type%3D%22text%2Fcss%22%3E%40font-face%7Bfont-family%3A%27math1d4ea5dacfff2d8a35c09522917%27%3Bsrc%3Aurl%28data%3Afont%2Ftruetype%3Bcharset%3Dutf-8%3Bbase64%2CAAEAAAAMAIAAAwBAT1MvMi7iBBMAAADMAAAATmNtYXDEvmKUAAABHAAAADRjdnQgDVUNBwAAAVAAAAA6Z2x5ZoPi2VsAAAGMAAAAm2hlYWQQC2qxAAACKAAAADZoaGVhCGsXSAAAAmAAAAAkaG10eE2rRkcAAAKEAAAACGxvY2EAHTwYAAACjAAAAAxtYXhwBT0FPgAAApgAAAAgbmFtZaBxlY4AAAK4AAABn3Bvc3QB9wD6AAAEWAAAACBwcmVwa1uragAABHgAAAAUAAADSwGQAAUAAAQABAAAAAAABAAEAAAAAAAAAQEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACAgICAAAAAg1UADev96AAAD6ACWAAAAAAACAAEAAQAAABQAAwABAAAAFAAEACAAAAAEAAQAAQAAIjz%2F%2FwAAIjz%2F%2F93FAAEAAAAAAAABVAMsAIABAABWACoCWAIeAQ4BLAIsAFoBgAKAAKAA1ACAAAAAAAAAACsAVQCAAKsA1QEAASsABwAAAAIAVQAAAwADqwADAAcAADMRIRElIREhVQKr%2FasCAP4AA6v8VVUDAAABAIAAqwMAAlUABwBJGAGwCBCxBwP2sQYD9rABPLAHELAD1bEJA%2BaxAgP2sAU8ALEAABMQsQMG5bEDARMQsQYF9rEBBeawAxCxBwX1sQIF9rEFBeYxMBM2ADcVBgAHgIABgICA%2FoCAAauq%2FqurVqoBVasAAAEAAAABAADVeM5BXw889QADBAD%2F%2F%2F%2F%2F1joTc%2F%2F%2F%2F%2F%2FWOhNzAAD%2FIASAA6sAAAAKAAIAAQAAAAAAAQAAA%2Bj%2FagAAF3AAAP%2B2BIAAAQAAAAAAAAAAAAAAAAAAAAIDUgBVA1YAgAAAAAAAAAAoAAAAmwABAAAAAgBeAAUAAAAAAAIAgAQAAAAAAAQAAN4AAAAAAAAAFQECAAAAAAAAAAEAEgAAAAAAAAAAAAIADgASAAAAAAAAAAMAMAAgAAAAAAAAAAQAEgBQAAAAAAAAAAUAFgBiAAAAAAAAAAYACQB4AAAAAAAAAAgAHACBAAEAAAAAAAEAEgAAAAEAAAAAAAIADgASAAEAAAAAAAMAMAAgAAEAAAAAAAQAEgBQAAEAAAAAAAUAFgBiAAEAAAAAAAYACQB4AAEAAAAAAAgAHACBAAMAAQQJAAEAEgAAAAMAAQQJAAIADgASAAMAAQQJAAMAMAAgAAMAAQQJAAQAEgBQAAMAAQQJAAUAFgBiAAMAAQQJAAYACQB4AAMAAQQJAAgAHACBAE0AYQB0AGgAIABGAG8AbgB0AFIAZQBnAHUAbABhAHIATQBhAHQAaABzACAARgBvAHIAIABNAG8AcgBlACAATQBhAHQAaAAgAEYAbwBuAHQATQBhAHQAaAAgAEYAbwBuAHQAVgBlAHIAcwBpAG8AbgAgADEALgAwTWF0aF9Gb250AE0AYQB0AGgAcwAgAEYAbwByACAATQBvAHIAZQAAAwAAAAAAAAH0APoAAAAAAAAAAAAAAAAAAAAAAAAAALkHEQAAjYUYALIAAAAVFBOxAAE%2F%29format%28%27truetype%27%29%3Bfont-weight%3Anormal%3Bfont-style%3Anormal%3B%7D%40font-face%7Bfont-family%3A%27round_brackets18549f92a457f2409%27%3Bsrc%3Aurl%28data%3Afont%2Ftruetype%3Bcharset%3Dutf-8%3Bbase64%2CAAEAAAAMAIAAAwBAT1MvMjwHLFQAAADMAAAATmNtYXDf7xCrAAABHAAAADxjdnQgBAkDLgAAAVgAAAASZ2x5ZmAOz2cAAAFsAAABJGhlYWQOKih8AAACkAAAADZoaGVhCvgVwgAAAsgAAAAkaG10eCA6AAIAAALsAAAADGxvY2EAAARLAAAC%2BAAAABBtYXhwBIgEWQAAAwgAAAAgbmFtZXHR30MAAAMoAAACOXBvc3QDogHPAAAFZAAAACBwcmVwupWEAAAABYQAAAAHAAAGcgGQAAUAAAgACAAAAAAACAAIAAAAAAAAAQIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACAgICAAAAAo8AMGe%2F57AAAHPgGyAAAAAAACAAEAAQAAABQAAwABAAAAFAAEACgAAAAGAAQAAQACACgAKf%2F%2FAAAAKAAp%2F%2F%2F%2F2f%2FZAAEAAAAAAAAAAAFUAFYBAAAsAKgDgAAyAAcAAAACAAAAKgDVA1UAAwAHAAA1MxEjEyMRM9XVq4CAKgMr%2FQAC1QABAAD%2B0AIgBtAACQBNGAGwChCwA9SwAxCwAtSwChCwBdSwBRCwANSwAxCwBzywAhCwCDwAsAoQsAPUsAMQsAfUsAoQsAXUsAoQsADUsAMQsAI8sAcQsAg8MTAREAEzABEQASMAAZCQ%2FnABkJD%2BcALQ%2FZD%2BcAGQAnACcAGQ%2FnAAAQAA%2FtACIAbQAAkATRgBsAoQsAPUsAMQsALUsAoQsAXUsAUQsADUsAMQsAc8sAIQsAg8ALAKELAD1LADELAH1LAKELAF1LAKELAA1LADELACPLAHELAIPDEwARABIwAREAEzAAIg%2FnCQAZD%2BcJABkALQ%2FZD%2BcAGQAnACcAGQ%2FnAAAQAAAAEAAPW2NYFfDzz1AAMIAP%2F%2F%2F%2F%2FVre7u%2F%2F%2F%2F%2F9Wt7u4AAP7QA7cG0AAAAAoAAgABAAAAAAABAAAHPv5OAAAXcAAA%2F%2F4DtwABAAAAAAAAAAAAAAAAAAAAAwDVAAACIAAAAiAAAAAAAAAAAAAkAAAAowAAASQAAQAAAAMACgACAAAAAAACAIAEAAAAAAAEAABNAAAAAAAAABUBAgAAAAAAAAABAD4AAAAAAAAAAAACAA4APgAAAAAAAAADAFwATAAAAAAAAAAEAD4AqAAAAAAAAAAFABYA5gAAAAAAAAAGAB8A%2FAAAAAAAAAAIABwBGwABAAAAAAABAD4AAAABAAAAAAACAA4APgABAAAAAAADAFwATAABAAAAAAAEAD4AqAABAAAAAAAFABYA5gABAAAAAAAGAB8A%2FAABAAAAAAAIABwBGwADAAEECQABAD4AAAADAAEECQACAA4APgADAAEECQADAFwATAADAAEECQAEAD4AqAADAAEECQAFABYA5gADAAEECQAGAB8A%2FAADAAEECQAIABwBGwBSAG8AdQBuAGQAIABiAHIAYQBjAGsAZQB0AHMAIAB3AGkAdABoACAAYQBzAGMAZQBuAHQAIAAxADgANQA0AFIAZQBnAHUAbABhAHIATQBhAHQAaABzACAARgBvAHIAIABNAG8AcgBlACAAUgBvAHUAbgBkACAAYgByAGEAYwBrAGUAdABzACAAdwBpAHQAaAAgAGEAcwBjAGUAbgB0ACAAMQA4ADUANABSAG8AdQBuAGQAIABiAHIAYQBjAGsAZQB0AHMAIAB3AGkAdABoACAAYQBzAGMAZQBuAHQAIAAxADgANQA0AFYAZQByAHMAaQBvAG4AIAAyAC4AMFJvdW5kX2JyYWNrZXRzX3dpdGhfYXNjZW50XzE4NTQATQBhAHQAaABzACAARgBvAHIAIABNAG8AcgBlAAAAAAMAAAAAAAADnwHPAAAAAAAAAAAAAAAAAAAAAAAAAAC5B%2F8AAY2FAA%3D%3D%29format%28%27truetype%27%29%3Bfont-weight%3Anormal%3Bfont-style%3Anormal%3B%7D%3C%2Fstyle%3E%3C%2Fdefs%3E%3Ctext%20font-family%3D%22round_brackets18549f92a457f2409%22%20font-size%3D%2216%22%20text-anchor%3D%22middle%22%20x%3D%223.5%22%20y%3D%2215%22%3E%28%3C%2Ftext%3E%3Ctext%20font-family%3D%22Times%20New%20Roman%22%20font-size%3D%2216%22%20text-anchor%3D%22middle%22%20x%3D%229.5%22%20y%3D%2215%22%3E0%3C%2Ftext%3E%3Ctext%20font-family%3D%22math1d4ea5dacfff2d8a35c09522917%22%20font-size%3D%2214%22%20text-anchor%3D%22middle%22%20x%3D%2221.5%22%20y%3D%2215%22%3E%26%23x223C%3B%3C%2Ftext%3E%3Ctext%20font-family%3D%22Times%20New%20Roman%22%20font-size%3D%2216%22%20text-anchor%3D%22middle%22%20x%3D%2241.5%22%20y%3D%2215%22%3E127%3C%2Ftext%3E%3Ctext%20font-family%3D%22round_brackets18549f92a457f2409%22%20font-size%3D%2216%22%20text-anchor%3D%22middle%22%20x%3D%2255.5%22%20y%3D%2215%22%3E%29%3C%2Ftext%3E%3C%2Fsvg%3E) 字符以外的每一个重复出现过的字重复出现的次数。每行包含三项内容，首先是重复的字符（以 UTF-8 编码输出），然后是该字符的 Unicode 编码值（十六进制输出，字母均使用小写，长度不足 ![4](data:image/svg+xml;charset=utf8,%3Csvg%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%20xmlns%3Awrs%3D%22http%3A%2F%2Fwww.wiris.com%2Fxml%2Fcvs-extension%22%20height%3D%2219%22%20width%3D%229%22%20wrs%3Abaseline%3D%2215%22%3E%3C%21--MathML%3A%20%3Cmath%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F1998%2FMath%2FMathML%22%20class%3D%22wrs_chemistry%22%20style%3D%22font-family%3A%27Times%20New%20Roman%27%22%3E%3Cmn%3E4%3C%2Fmn%3E%3C%2Fmath%3E--%3E%3Cdefs%3E%3Cstyle%20type%3D%22text%2Fcss%22%2F%3E%3C%2Fdefs%3E%3Ctext%20font-family%3D%22Times%20New%20Roman%22%20font-size%3D%2216%22%20text-anchor%3D%22middle%22%20x%3D%224.5%22%20y%3D%2215%22%3E4%3C%2Ftext%3E%3C%2Fsvg%3E) 位数的用 ![0](data:image/svg+xml;charset=utf8,%3Csvg%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%20xmlns%3Awrs%3D%22http%3A%2F%2Fwww.wiris.com%2Fxml%2Fcvs-extension%22%20height%3D%2219%22%20width%3D%229%22%20wrs%3Abaseline%3D%2215%22%3E%3C%21--MathML%3A%20%3Cmath%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F1998%2FMath%2FMathML%22%20class%3D%22wrs_chemistry%22%20style%3D%22font-family%3A%27Times%20New%20Roman%27%22%3E%3Cmn%3E0%3C%2Fmn%3E%3C%2Fmath%3E--%3E%3Cdefs%3E%3Cstyle%20type%3D%22text%2Fcss%22%2F%3E%3C%2Fdefs%3E%3Ctext%20font-family%3D%22Times%20New%20Roman%22%20font-size%3D%2216%22%20text-anchor%3D%22middle%22%20x%3D%224.5%22%20y%3D%2215%22%3E0%3C%2Ftext%3E%3C%2Fsvg%3E) 补齐），最后输出该字符的重复次数。

如果文章中没有出现重复的字，则输出`No repeat!`。

**Example:**

- Input:

```
Qianzi wen in Simplified Chinese↵
天地玄黄 宇宙洪荒 日月盈昃 辰宿列张 寒来暑往 秋收冬藏 闰馀成岁 律吕调阳
云腾致雨 露结为霜 金生丽水 玉出昆冈 剑号巨阙 珠称夜光 果珍李柰 菜重芥姜
海咸河淡 鳞潜羽翔 龙师火帝 鸟官人皇 始制文字 乃服衣裳 推位让国 有虞陶唐
吊民伐罪 周发殷汤 坐朝问道 垂拱平章 爱育黎首 臣伏戎羌 遐迩一体 率宾归王
鸣凤在竹 白驹食场 化被草木 赖及万方 盖此身发 四大五常 恭惟鞠养 岂敢毁伤
女慕贞洁 男效才良 知过必改 得能莫忘 罔谈彼短 靡恃己长 信使可复 器欲难量
墨悲丝染 诗赞羔羊 景行维贤 克念作圣 德建名立 形端表正 空谷传声 虚堂习听
祸因恶积 福缘善庆 尺璧非宝 寸阴是竞 资父事君 曰严与敬 孝当竭力 忠则尽命
临深履薄 夙兴温凊 似兰斯馨 如松之盛 川流不息 渊澄取映 容止若思 言辞安定
笃初诚美 慎终宜令 荣业所基 籍甚无竟 学
```

- Output:

```
云 0x4e91 2
发 0x53d1 2
巨 0x5de8 2
戚 0x621a 2
昆 0x6606 2
资 0x8d44 2
```

