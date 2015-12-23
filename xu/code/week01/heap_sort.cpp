#include <iostream>
#include <ctime>

using namespace std ;

/**************
* 基于《算法导论》实现的基本 堆排序
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

void max_heapify(int arr[] , size_t target_idx , size_t heap_size )
{
    size_t parent_idx = target_idx ;
    while( parent_idx < heap_size )
    {
        // find the idx with the max value from ( parent , left_child , right_child ) 
        size_t largest_idx = parent_idx ;
        size_t left_child_idx = (parent_idx << 1) + 1 ;
        size_t right_child_idx = (parent_idx << 1) + 2 ; 
        if( left_child_idx < heap_size && arr[left_child_idx] > arr[largest_idx] )
            largest_idx = left_child_idx ;
        if( right_child_idx < heap_size && arr[right_child_idx] > arr[largest_idx])
            largest_idx = right_child_idx ;
        if( largest_idx != parent_idx )
        {
            swap(arr[parent_idx] , arr[largest_idx]) ;
            parent_idx = largest_idx ;
        }
        else break ;
    }
}

void build_max_heap(int arr[] , size_t arr_size )
{
    size_t largest_non_leaf_node_idx = ( arr_size >> 1 ) - 1 ; // idx count from 0
    int start_idx = static_cast<int>(largest_non_leaf_node_idx) ; // must be converted to int !
    while(start_idx >= 0) max_heapify(arr , start_idx-- , arr_size) ;
}

void heap_sort(int arr[] , size_t arr_size)
{
    build_max_heap(arr , arr_size ) ;
    size_t heap_size = arr_size ;
    while(heap_size > 1) // at least 2 elements !
    {
        swap(arr[0] , arr[heap_size-1]) ;
        --heap_size ;
        max_heapify(arr , 0 , heap_size) ;
    }
}

int main(int argc , char *argv[])
{
    const int ARRAY_SIZE = 0xFFFF ;
    const size_t MAX_NUM = 0xFFFFFF ;
    int arr[ARRAY_SIZE] = { 0 } ;
    fill_array_with_random_value(arr , ARRAY_SIZE , MAX_NUM , false) ;
    //print_array(arr , ARRAY_SIZE) ;
    heap_sort(arr , ARRAY_SIZE) ;
    //print_array(arr , ARRAY_SIZE) ;
    if(is_array_increasing(arr , ARRAY_SIZE))
        cout << "heap sort implementation is right" << endl ;
    else 
        cout << "heap sort implementation is wrong" << endl ;
    return 0 ;
}

