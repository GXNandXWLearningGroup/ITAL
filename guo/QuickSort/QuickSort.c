#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ARRAR_LENGHT 18
int PartionArray(int arr[],int p,int r);
int QuickSort(int arr[],int p,int r);
int InitArray(int arr[],int length);

int main()
{
   int array[ARRAR_LENGHT];
   int i=0;

   InitArray(array,ARRAR_LENGHT);
   QuickSort(array,0,17);
   printf("After QuickSort:");
   for(;i<ARRAR_LENGHT;i++)
   {
       printf("%d ",array[i]);
   }
   printf("\n");
  return  0;
}

int PartionArray(int arr[],int p,int r)
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
	int q=PartionArray(arr,p,r);
	if(p<r)
	{
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
     printf("Init array     :");
     for(i=0;i<length;i++)
     {
	  printf("%d ",arr[i]);
     }
     printf("\n");
}
