#include<stdlib.h>
#include<time.h>
#include <stdio.h>

#define DEBUG  0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

#define ARRAR_LENGHT 0xffff
int PartionArray(int arr[],int p,int r);
int PartionArray2(int arr[],int p,int r);

int JudgeSortedArray(int arr[],int length);
int QuickSort(int arr[],int p,int r);

int InitArray(int arr[],int length);
int main()
{
   int array[ARRAR_LENGHT];
   int i=0;
   long int timeusage;

   InitArray(array,ARRAR_LENGHT);
   timeusage=time(NULL);

   QuickSort(array,0,ARRAR_LENGHT-1);

   timeusage=time(NULL)-timeusage;

   PRINTF("After QuickSort:");
   for(;i<ARRAR_LENGHT;i++)
   {
       PRINTF("%d ",array[i]);
   }
   PRINTF("\n");

  if(JudgeSortedArray(array,ARRAR_LENGHT))
      printf("yes sorted using time %lu\n",timeusage);
  else
      printf("no somthing wrong\n");
  return  0;
}

int PartionArray(int arr[],int p,int r) // 两个游标　指向两侧　同时向中间移动
{
     int pivot=arr[p];
       while(p<r)
       {
  while(p<r  &&  arr[r] >= pivot )  --r;
    arr[p]=arr[r];
  while(p<r  &&  arr[p] <= pivot )  ++p;
    arr[r]=arr[p];
       }
       arr[p]= pivot;
       return p;
}

int QuickSort(int arr[],int p,int r)
{

  if(p<r)
  {
      int q=PartionArray2(arr,p,r);
        QuickSort(arr,p,q-1);
      QuickSort(arr,q+1,r);
  }

}

int InitArray(int arr[],int length)
{
     int i=0;
     srand((unsigned int)time(NULL));
     for(;i<length;i++)
     {
          arr[i]=rand()%100;

     }
     PRINTF("Init array     :");
     for(i=0;i<length;i++)
     {
    PRINTF("%d ",arr[i]);
     }
     PRINTF("\n");
}
int PartionArray2(int arr[],int p,int r)// 单个游标的　划分方法
{
    int i=p-1;
    int j=p;
    int temp;
    for(;j<r;j++)
    {
       if(arr[j]<arr[r])
  {
      temp=arr[++i];
      arr[i]=arr[j];
      arr[j]=temp;
  }

    }
   temp=arr[++i];
   arr[i]=arr[r];
   arr[r]=temp;
   return i;
}
int JudgeSortedArray(int arr[],int length)
{
  int i =0;
  for (;i<length-1;i++)
  {
       if(arr[i]>arr[i+1])
    return 0;

  }
  return 1;
}
