#期望为线性时间的排序算法
##算法思想：
> 根据快速排序的算法思想，每次划分将会确定一个元素的位置；因而可以利用此特点来寻找一个无序数组中第ｋ大的元素。
> 当划分时候返回的数组的index等于k时候认为找到了第ｋ大的元素。
##[randomized-select.c] (https://github.com/GXNandXWLearningGroup/ITAL/blob/master/guo/Find_median/randomized-select.c)算法实线的基本步骤描述
1.首先生成一个数组。
>由于算法要求只局限在数组元素互补相同，所以首先生成一个有序数组大小为: 1～LENGTH。
2.random-select 
>对数组中进行划分。
*如果划分的数值下标正好为k，那么找到了第k大的元素。
*如果划分的数值下标大于k,那么必然在　划分位置之前　递归从数组开始到本次划分的位置继续寻找。
*如果划分的数值下标小于k,那么一定在　划分位置之后到数组结尾的位置，递归从本次划分的位置到数组结尾的位置继续寻找。

-------------
#线性时间寻找中位数算法
** 在上边的算法中其实已经能够保证在线性时间找到任意第k大的数，所以当然也能在线性时间找到中位数。**
##算法思想：
> 首先将数组成[5/n],每组5个元素; 
> 对各组组内进行插入排序;
> 如果
