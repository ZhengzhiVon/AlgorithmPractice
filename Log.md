# 算法练习日志

- 记录当天练习内容，前期可能会优先一次性上传一部分积攒于本地未上传的学习笔记。

# 日志

- 20230411_力扣76 最小覆盖字串	滑动窗口git

  摘要：滑动窗口，最小长度的应用。

  `vector<int>need(128,0)`统计字符串t中每个字符出现的次数，并存储到一个长度为128的数组`need`中。这里的128是ASCII码表中字符的数量，因此`need`可以看作是一个哈希表，用于快速查找每个字符出现的次数。

- 20230412_力扣59 螺旋数组

  摘要：矩阵循环模拟

  边界一致性原则。：需要保证每一条边的遍历过程中边界正确，所以需要同一循环边界标准：左闭右开。

- 20230413_KWIC问题

  摘要：用C++且采用主程序子程序的的思路实现KWIC问题，其中尝试运用`STL`的`vector`、`set`容器；在文件操作方面尝试使用C++中的`stream`类中的`ifstream`和`ofstream`。

- 20230414_KWIC_管道过滤器风格
  
  摘要：用C++且采用管道过滤器的的思路实现KWIC问题，不过此次KWIC_pipe.cpp写的并不完善，之后将会重新研究修改。

- 20230416_力扣203&707_移除链表元素&设计链表

  摘要：学习链表的基本类型、定义、操作。在移除链表元素的过程中，最好定义一个虚拟头节点。

- 20230417_力扣19&14&206_删除倒数第N个结点&交换结点&翻转链表

  摘要：虚拟头节点的应用，双指针（快慢指针）的应用，链表结点交换、删除过程中临时变量tmp所储存的值。

- 20230417

  摘要：

  力扣160_链表相交
  末尾对齐，然后移动curA到curB的位置再进行比较是否相同。

  git错误 error: failed to push some refs to 'https://github.com/...

  问题原因：远程库与本地库不一致造成的

  解决方法：git pull --rebase origin master   #把远程库中的更新合并到（pull=fetch+merge）本地库中，–-rebase的作用是取消掉本地库中刚刚的commit，并把他们接到更新后的版本库之中。

  [参考]: https://blog.csdn.net/qq_30152625/article/details/90404727?ops_request_misc=&amp;request_id=&amp;biz_id=102&amp;utm_term=error:%20failed%20to%20push%20some%20ref&amp;utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-90404727.142^v84^control,239^v2^insert_chatgpt&amp;spm=1018.2226.3001.4187