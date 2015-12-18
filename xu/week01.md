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

3. 保持最大堆性质——MAX-HEAPIFY

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
 
                    



