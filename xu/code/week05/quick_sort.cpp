#include <iostream>
#include <ctime>

using namespace std ;

/**************
* 基于《算法导论》实现的基本 快速排序
* 仅以实现逻辑为主。
* 输入：int类型的数组
* 输出：由小到大排序完成的数组
**************/

const int STATIC_SEED = 1234 ;

void fill_array_with_random_value(int * arr , size_t array_size , int value_max=100 , bool is_static_random=true)
{
    if(is_static_random) srand(STATIC_SEED) ;
    else srand(time(0)) ;
    for(size_t i = 0 ; i < array_size ; ++i)
    {
        *(arr + i) = rand() % value_max ;
    }
}

void print_array(int *arr , size_t arr_size)
{
    if(arr != nullptr && arr_size > 0) cout << *arr ;
    for(size_t i = 1 ; i < arr_size ; ++i)
    {
        cout << " " << *(arr + i) ;
    }
    cout << endl ;
}

bool is_array_increasing(int *arr , size_t arr_size)
{
    for(size_t i = 0 ; i < arr_size -1 ; ++i)
    {
        if(arr[i+1] < arr[i]) return false ;
    }
    return true ;
}

int partition(int *arr , int h , int r)
{
    /* Partition for Quick Sort
     * Params : arr , pointer to the array 
     *          h , r , [index] for head and rear of the array
     * Returns : Index for pivot elements after partition
     */
    // generate a random pivot index
    int range = r - h + 1 ;
    int pivot_idx = rand() % range + h ;
    swap(arr[pivot_idx] , arr[r]) ;
    int split_idx = h - 1 ;
    int pivot_val = arr[r] ;
    for(int pos = h ; pos <= r - 1 ; ++pos)
    {
        if(arr[pos] <= pivot_val)
        {
            ++split_idx ;
            swap(arr[split_idx] , arr[pos]) ;
        }
    }
    // swap pivot 
    swap(arr[r] , arr[split_idx + 1]) ;
    return split_idx + 1  ;
}

int partition_hoare(int *arr , int h , int r)
{
    // generate a random pivot index
    int range = r - h + 1 ;
    int pivot_idx = rand() % range + h ;
    swap(arr[pivot_idx] , arr[r]) ;
    int split_idx = h - 1 ;
    int pivot_val = arr[r] ; 
    --r ;
    while( h < r )
    {
        

    }
}

void _quick_sort(int *arr , int h , int r)
{
    if(h < r)
    {
        int pivot_idx = partition(arr , h , r) ;
        _quick_sort(arr , h , pivot_idx - 1) ;
        _quick_sort(arr , pivot_idx + 1 , r ) ;
    }
}

void quick_sort(int *arr , int arr_sz )
{
    if(arr_sz < 1 ) return ;
    _quick_sort(arr , 0 , arr_sz - 1) ;
}



int main(int argc , char *argv[])
{
    const int ARRAY_SIZE = 0xFFFF ;
    const size_t MAX_NUM = 0xFFFFFF ;
    int arr[ARRAY_SIZE] = { 0 } ;
    fill_array_with_random_value(arr , ARRAY_SIZE , MAX_NUM , false) ;
    //print_array(arr , ARRAY_SIZE) ;
    quick_sort(arr , ARRAY_SIZE) ;
    //print_array(arr , ARRAY_SIZE) ;
    if(is_array_increasing(arr , ARRAY_SIZE))
        cout << "heap sort implementation is right" << endl ;
    else 
        cout << "heap sort implementation is wrong" << endl ;
    return 0 ;
}

