#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <functional>
using namespace std ;

vector<int> counting_sort_copy(const vector<int> &arr , int max_value)
{
    size_t size = arr.size() ;
    vector<int> count_s(max_value+1 , 0) ;
    for(size_t i = 0 ; i < size ; ++i)
    {
        size_t count_idx = arr[i] ;
        ++count_s[count_idx] ;
    }
    for(size_t i = 1 ; i <= max_value ; ++i) count_s[i] += count_s[i-1] ;
    vector<int> rst(size , 0 ) ;
    for(int i = static_cast<int>(size) - 1; i >= 0 ; --i)
    {
        int ele_value = arr[i] ;
        int output_rst_idx = count_s[ele_value] ;
        --count_s[ele_value] ;
        --output_rst_idx ; // because the idx start from 0 !
        rst[output_rst_idx] = ele_value ;        
    }
    return rst ;
}

vector<int> generate_random_positive_int_array(int arr_size , int max_value)
{
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count() ;
    mt19937 mt_rand(seed) ;
    auto range_generator = bind(uniform_int_distribution<int>(0 , max_value) , mt_rand) ;
    vector<int> arr(arr_size , 0) ;
    for(size_t i = 0 ; i < arr_size ; ++i) arr[i] = range_generator() ;
    return arr ;
}

int main(int argc , char *argv[])
{
    const int max_value = 66 ;
    const int arr_size = 0xFFFF ;
    vector<int> random_int_arr = generate_random_positive_int_array(arr_size , max_value) ;
    vector<int> rst = counting_sort_copy(random_int_arr , max_value) ;
    return 0 ;
}
