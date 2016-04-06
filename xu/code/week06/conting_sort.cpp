#include <iostream>
#include <vector>
using namespce std ;

int counting_sort_copy(const vector<int> &arr , int max_value)
{
    size_t size = arr.size() ;
    vector<int> count_s(max_value+1 , 0) ;
    for(size_t i = 0 ; i < size ; ++i)
    {
        size_t count_idx = arr[i] ;
        ++count_s[cont_idx] ;
    }
    for(size_t i = 1 ; i <= max_value ; ++i) count_s[i] += count_s[i-1] ;
    vector<int> rst(size , 0 ) ;
    for(int i = static_cast<int>(size) - 1; i >= 0 ; --i)
    {
        
    }

}

int main(int argc , char *argv[])
{
    return 0 ;
}
