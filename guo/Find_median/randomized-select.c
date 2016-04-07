#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #define   DEBUG    0
#if DEBUG
#define   PRINTF(...)    printf(__VA_ARGS__)
#else
#define  PRINTF(...) 
#endif

#define LENGTH  0xffff
#define CHANGE_ELEMENT_NUMBER    (LENGTH>>1)
/* init an array length is LENGHT;
       arr : is  an array that needed init;
       length: is the length of array that needed init;
     */
int InitArray(int arr[],int length);
/*
     use quick sort's idea to find the k_th bigest number in array
     arr: 
     k   :  k_th 
     p  : start  index  of  array to searching the array  
     r   : end   index  of  array to searching the array  
*/
int randomized_select (  int arr[],  int k,   int p,  int r  );
/*
       random partion  in  arr[p:r]
*/
int random_partion (int arr[],int p,int r);

int main()
{
    int  k_th_in_array; 
    int array[LENGTH];
    InitArray(array,LENGTH);
    
    printf("please input you order :");
    while(scanf("%d",&k_th_in_array)!=EOF)
    {
          if(k_th_in_array>LENGTH || k_th_in_array<1)
          {
             printf("your input is worng ! (recommand between 1 ~%d)\n",LENGTH );
             printf("please input you order :");
             continue;
          }
      
          printf("the %dth biger elements in array is %d\n",  k_th_in_array, randomized_select(array,k_th_in_array-1,0,LENGTH-1));
          printf("please input you order :");

    }

    return 0;
}
/*use a special method  ^ operator to swap two element without use extra  space;  
notice!!! when  x  =y   ^ operation will change the value of  (x) to 0;    be careful ~
*/
void swap(int *x ,int *y) 
{
    if(x==y)  //  this condition is  a  must !
        return; 
   *x =*x ^*y;
   *y =*x ^*y;
   *x =*x ^*y;
}
int InitArray(int arr[],int length)
{ 
    int i=0;
    srand(time(NULL));

    for(; i < length; ++i)
    {
        arr[i]=i+1;
    }

  printf("Origin  array  is:");

  #if  DEBUG
   for(i=0;i<length;i++)
   {
       PRINTF(" %d",arr[i]);
   }
   PRINTF("\n");
   #endif

for (i=0; i <CHANGE_ELEMENT_NUMBER ; ++i)
{
         int j,k;
         j= rand()%length;
         k=rand()%length;
         swap(&arr[j],&arr[k]);

}

    PRINTF("After change the order of some elements:");

   for(i=0;i<length;i++)
   {
       printf(" %d",arr[i]);
   }
   printf("\n");

}

int randomized_select (  int arr[],  int k,   int p,  int r  )
{
    int q;

    if(p==r)
        return arr[p];
    q=random_partion(arr,p,r);

    if (k==q)
    {
        return arr[q] ;
    }
    else if (q>k)
    {
        return randomized_select(arr,k,p,q-1) ;
    }
    else
    {
        return randomized_select(arr,k,q+1,r);
    }

}

  int random_partion(int arr[],int p,int r)
  {
    int   i,j;
    int   temp;

    int pivot=r;

     if(p==r)
        return arr[p];
 /*begin  :select   median from  arr[p]   arr[r]   arr[(r+p)/2]  */
    if(arr[p]>arr[r]) /* p > r */
    {
        if(arr[(p+r)/2]>arr[p])   pivot=p;
        else  pivot =  (arr[(p+r)/2]>arr[r] )?  (p+r)/2   :  r;
    }
    else/*  r  > p */
    {
        if(arr[(p+r)/2]>arr[r])  pivot=r;
        else pivot = (arr[(p+r)/2]>arr[p])  ?    (p+r)/2  :  p  ; 
    }
/*  end    : pivot  record  the  index  of  median   of  {  arr[p]    arr[r]    arr[(r+p)/2]  }*/
    

    swap(&arr[pivot],&arr[r]);
    
    i=p-1;
    j=p;
    for (;    j < r ;  ++j)
    { 
         if(arr[j]<arr[r])
         {
            /* change  arr[j] and arr[i+1]*/
            ++i;
            swap(&arr[j],&arr[i]);

         }
    }
   
   ++i;
   swap(&arr[i],&arr[r]);

return i;
}
