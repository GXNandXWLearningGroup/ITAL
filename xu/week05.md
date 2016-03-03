#快速排序

快速排序是一种基于分治（二分）思想的排序算法，最坏复杂度为O(n^2) ， 最佳复杂度为O(nlgn)，平均复杂度为O(nlogn)

##两种划分方法

1. Lomuto
    
    单索引，从一头开始遍历，将小于主轴元素的往前交换，同时分隔点向前移动。

    易理解、实现，不易有BUG。

    c++实现

    ```C++
    /**
    * 输入： arr ， 整型数组 
    *        h   ， 待排序的起始位置索引
    *        r   ， 待排序的结束位置索引
    * 返回： 划分位置索引，使得左边小于该位置值 ，右边大于等于该位置值。 
    * 前提：h <= r
    */
    int partition(int *arr , int h , int r)
    {
        int split_idx = h - 1 ;
        int pivot_val = arr[r] ;
        for(int pos = h ; pos < r ; ++pos)
        {
            if(arr[pos] < pivot_val)
            { 
                ++split_idx ;
                swap(arr[pos] , arr[split_idx]) ;
            }
        }
        ++split_idx ;
        swap(arr[split_idx] , arr[r]) ;
        return split_idx ;
    }

    ```
    
    解释：

    始终保持如下循环不变式： 

        arr[h , split_idx] < pivot_value
        arr[split_idx + 1 , r -1] >= pivot_value
        arr[r] = pivot_value

    在结束循环后，需要将`split_idx`往后移动一个位置(`++split_idx`)，然后将pivot值移动到此位置，即交换`swap(arr[split_idx] , arr[r])`

    划分位置就是`split_idx`

    考虑极端情况，

    如果数组arr[h , r-1]全都是大于等于arr[r]的，那么就不会发生交换，循环后`split_idx = h-1` ， +1再交换后依然满足要求。

    如果数组arr[h , r-1]全部都是小于arr[r]的，那么全部交换，循环后` split_idx = r-1` , +1再交换，同样没有问题！

2. Hoare

    双索引交换。分别从头部和尾部个开始一个指针，头部找大于主轴元素的，尾部找小于等于主轴元素的。两个都找到后交换元素，继续下次寻找。直到两个指针相遇。

    编码易出现BUG。但效率高。

    ```C++
    int partition(int *arr , int h , int r)
    {
        int pivot_val = arr[r] ;
        int left_pos = h ;
        int right_pos = r - 1 ;
        while( left_pos < right_pos )
        {
            while(left_pos < right_pos && arr[left_pos] < pivot_val) ++left_pos ;
            while(left_pos < right_pos && arr[right_pos] >= pivot_val) --right_pos ;
            swap(arr[left_pos] , arr[right_pos]) ;
        }
        if(arr[left_pos] >= pivot_val) swap(arr[left_pos] , arr[r]) ;
        else ++left_pos ; // 或者  left_pos = r ;
        return left_pos ; 
    }
    ```

    解释：

    双指针版本，左右指针分别找左右两边违反规则的元素，然后交换。

    循环结束的条件，必然是`left_pos >= right_pos` ， 而又由于每次都是++的，所以必然是

    `left_pos == right_pos` ！

    考虑`right_pos`的情况，有两种可能：

    1. right_pos 向前移动过，则必然其指向的值`>=` `pivot\_val` < 此时把二者交换，返回`right\_pos`(也即是`left_pos`)的值即是分割位置。

    2. `right_pos` 从未向前移动过，即`arr[h , r-2]`的值都是小于等于`pivot\_val`的！注意是`r-2`，因为`r-1`位置，即此种情况下`right_pos`的值还没有被比较过呢！所以此时需要比较`right_pos`位置的值和`pivot_val`的大小，如果`right_pos`处的大或等（等其实可以不交换，但是为了统一代码，需要包含等！），就交换；如果依然小于，则r位置就是分割位置，此时应该将`right_pos`+1 (即`left_pos` + 1)，当然，+1后也就是r的值了，所以直接赋值为r更加直观！

    结合上述的考虑，代码写出来却仅仅只是一个`if`判断。

    这段代码暗含玄机，希望没有理解错误！


[比较](http://cs.stackexchange.com/questions/11458/quicksort-partitioning-hoare-vs-lomuto)


最后，快排思想是比较容易理解的，不过始终觉得代码有些诡异。没事多看看，记住比较好。

纠结了很久，最后还照着伪代码和维基百科上的内容写上了代码。有些东西也别太纠结了，记住就好。

##扩展

1. 随机化选择主轴元素

    实现起来非常简单，划分时随机选择一个位置作为主轴元素，然后把该元素和尾部元素交换，后续就是上述的逻辑了！

2. 尾递归？

    似乎就是把处理划分右部分的递归调用变为return + 函数调用；少了压栈的开销！

    不过不是很清楚，这个有些玄乎。

3. 其他选择主轴元素方法

    SGI-STL实现时，取的似乎是首、中、尾三个位置的中位数。

4. 混合方法

    混合`插入排序`以提高效率。
