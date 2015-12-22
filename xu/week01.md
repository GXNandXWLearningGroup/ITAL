###堆排序

> date : 2015-12-18

1. 性质

    最大堆，可以表示为一棵完全二叉树；满足父亲节点大于等于孩子节点，且从根节点到任意非叶节点，递归地满足该性质；

    最小堆，与最大堆类似——满足父亲节点小于等于孩子节点。

2. 最大堆、最小堆的数组表示

    因为是完全二叉树，所以树的节点一层一层排下来，可以表示为一个数组的形式。

    满足关系：

        对任意结点i（下标从1计数），如果存在父亲节点或左孩子或右孩子，则它们的下标满足：
        PARENT(i) = floor(i/2)
        LEFT(i) = 2*i
        RIGHT(i) = 2*i + 1
        如果下标从0开始计数，有:
        PARENT(i) = ceil(i/2) - 1 // floor( (i-1) /2 )
        LEFT(i) = 2*i + 1
        RIGHT(i) = 2*i + 2

    > 满二叉树： 除了叶结点外每一个结点都有左右子叶且叶结点都处在最底层的二叉树。（来自[csdn](http://blog.csdn.net/hytdsky/article/details/4783707) ）即是说，全满的一棵二叉树，设高度为h，则节点数为 2^h -1

    > 完全二叉树：只有最下面的两层结点度小于2，并且最下面一层的结点都集中在该层最左边的若干位置的二叉树。即是，相对满二叉树，在最后一层，只能从右往左缺节点。

> 2015-12-19

保持最大堆性质——MAX-HEAPIFY

前提：其余部分满足最大堆性质。

A数组是一个最大堆数组，i是需要需要维持的位置（除i节点及其直接子节点外，其余位置均满足最大堆性质）。

保证最大堆性质的算法：

    MAX-HEAPIFY(A , i)
        left_idx = LEFT(i) 
        right_idx = RIGHT(i)
        // 找父亲、左孩子、右孩子中最大的元素（对应的下标）
        IF left_idx <= heap-size(A) AND A[left_idx] > A[i]
        THEN largest_idx = left_idx 
        ELSE largest_idx = i
        IF right_idx <= heap-size(A) AND A[right_idx] > A[largest]
        THEN largest_idx = right_idx
        // 保证父亲节点应该大于孩子节点，即将最大的元素拿到父亲节点的位置（i）
        IF largest_idx != i 
        THEN 
            exchange(A[i] , A[largest_idx])
            // 由于交换了i与largetst_idx(左孩子或右孩子)的位置，其子树可能也需要更新
            // 递归调用即可
            MAX-HEAPiFY(A , largest_idx)


一些问题：

1. 时间复杂度

    调整一步，自然是O(1) (或者 \theta(1)) , 关键是要调整多少步（递归调用的上限）？

    算法导论上这么考虑的——调整父亲节点所在的局部区域后，下一步递归调用的就是孩子节点——将该孩子节点作为下次调整的父亲节点。其剩下的元素极端情况下最多有 `2n/3` 个。 很容易考虑到，由于是二叉树， n / 2 似乎是一个不错的界，那么 2n / 3 是如何达到的呢？ 就是当这棵树最后一层恰是半满时，最后一层有n/3个节点，上面的所有节点，左右各n/3个，如果选择递归调用左孩子，那么剩下的就是2n/3了。

    其实这个不重要。因为，由master定理 , T(n) = T(2n/3) + O(1) ， 只要其中的a是1，那么b不管具体是多少，求出的时间复杂度都是O(lg n ) 。 当然，这种想法是非常不严谨的。

    由上，最多有O(ln n)步递归调用。

    注意到树的高度也是lg n . **所以复杂度为 O(h)**

2. 非递归版本

    转为while循环还是比较简单的。

        MAX-HEAPIFY(A,i)
            WHILE i <= heap-size(A) 
                left_idx = LEFT(i) 
                right_idx = RIGHT(i)
                IF left_idx <= heap-size(A) AND A[left_idx] > A[i]
                THEN largest_idx = left_idx 
                ELSE largest_idx = i
                IF right_idx <= heap-size(A) AND A[right_idx] > A[largest]
                THEN largest_idx = right_idx
                IF largest_idx != i 
                THEN 
                    exchange(A[i] , A[largest_idx])
                    i = largest_idx
                ELSE BREAK // 退出

> 2015-12-20

###建堆

已有结论： 假设有有n个元素的数组构成最大堆，那么下标 floor(n/2) + 1 , floor(n/2) + 2 , ... , n 对应的元素都是堆的叶子节点。

原因：因为满足完全二叉树吧

那么建堆的过程可以表示为：

    BUILD-MAX-HEAP(A)
        start_idx = floor(length(A)/2) // n = length(A)
        WHILE start_idx >= 1 :
            MAX-HEAPIFY(A,start_idx)
            start_idx -= 1

非常简单的过程。

使用循环不变量去证明它：

1. 初始时，由结论可知，floor(n/2)+1 , floor(n/2)+2 , ... , n 都是叶节点，各个节点构成大小为1的树，即必然满足最大堆的，是`平凡最大堆`。

2. 循环从 start_idx = floor(n/2) 开始，每次循环，将以start\_idx为根的子树修正为最大堆。重复直到start\_idx为1，即完成后根节点为1的树是一个最大堆。

3. 可知循环结束时，根节点为1的子树是最大堆。即A已构建为以下标1为根节点的最大堆。

时间复杂度： O(n)

首先想到的上界是O(n lgn)，但是这不是上确界。要证明上确界，首先需要有结论：

*h层的节点数最多为 n / 2^(h+1)*

这个可以用数学归纳法证明...（是这么回事...）

而我们前面知道MAX-HEAPIFY的时间复杂度为O(h)的，那么就是对所有节点，从h=0，到h=floor(lg n)，时间为： 

\sum\_{h=0}^{h=floor(n/2)} \frac{n}{2^{h+1}} O(h) = n \sum\_{h=1}^{h=floor(lg n)}O(\frac{1}{2^h}) = n O(2) = O(n)

> 2015-12-21

###堆排序

堆排序流程：

1. 调用`BUILD-MAX-HEAP`建好最大堆

2. 将A[1]元素与A[heap-size(A)]交换
    
    - 减少堆的大小：heap-size(A) -= 1 .  

    - 对交换后的A[1]调用`MAX-HEAPIFY` : MAX-HEAPIFY(A , 1)

3. 重复2，直到堆中仅含一个元素。此时的A数组就是`由小到大`排序的有序数组。

伪代码：

    HEAPSORT(A) :
        BUILD-MAX-HEAP(A)
        FOR i <- length(A) DOWNTO 2 
            DO  exchange(A[1] , A[i])
                heap-size(A) <- heap-size(A) -1
                MAX-HEAPIFY(A,1)

非常巧妙的算法！

首先说明算法的正确性。

使用循环不变量证明：

起始：由最大堆的性质，根元素必然是最大堆中最大的元素。将其移动到第n个位置，是排序后正确的位置。

循环：移动后，将最后一个元素放到了根的位置，并对其调用MAX-HEAPIFY操作。首先，最后一个元素必然是叶节点，移动它到根位置，不影响除根位置外其他位置的最大堆性质，故可以应用MAX-HEAPIFY操作。而应用该操作后，整个堆又成为了一个最大堆，且此时堆的大小减一，最大的元素在根处，且小于等于上次循环的根元素。接着循环将根放到堆最后一个位置。此时由该位置到数组最后位置，都是满足有小到大有序的。

结束：此时，堆中仅有一个元素，且是最小的元素。此时，数组已经成为由小到大的有序序列。

巧妙之处，就是将根元素与堆最后一个元素交换。好处是：

1. 使移动后从堆最后一个位置到数组最后一个位置，都是有序的。

2. 移动堆最后一个元素，保证了不影响其他位置的最大堆性质，使得MAX-HEAPIFY可行。

时间复杂度： \theta(n lg n)

###优先级队列

书上说，最大堆、最小堆用来做排序虽然很漂亮，但是仍然比不过良好实现的快速排序。

不过，最大堆、最小堆在优先级队列上有独到的应用。

优先级队列，分为最大优先级队列和最小优先级队列。最大优先级队列可以用在计算机中任务调度，最小优先级队列则可用在基于事件驱动的模拟器中（？）。

以最大优先级队列为例，需要包含的操作：

- INSERT(S,x)

- MAXIMUM(S)

- EXTRACT-MAX(S)

- INCREASE-KEY(S,x,k)

以下是相关思想。

最简单的是 MAXMUM(S) , 只需返回堆的第一个个元素（根元素）即可。

EXTRACT-MAX(S) , 与堆排序中的SORT很像，就是单步SORT。取出根元素作为最大值；将堆中最后一个元素放到根元素的位置，减少堆大小；对根元素做MAX-HEAPIFY操作。

INCREASE-KEY , 就是将x位置的元素的优先级（key）*增大* ， 然后再将其放到合适的位置。首先，要保证新的key必须必当前key值大；然后改变key值；改变后，其他位置的元素仍然满足最大堆性质，且以此节点为根的子树也必然是满足最大堆的！只是，以此节点为孩子的子树却可能不再满足了。所以，与MAX-HEAPIFY相反的是，这次要*从下往上*更正元素。

最后讲插入 INSERT ， 直观想法当然是在堆末尾加一个元素，然后再往上更正即可——注意到这和INCREASE-KEY的逻辑是相同的！于是，我们新建一个key为*负无穷*的节点，增加堆的大小；然后对此位置调用INCREASE-KEY，完成加入一个大小为key的元素的操作。初始设为负无穷，是为了保证INCREASE-KEY必然能够被执行。


