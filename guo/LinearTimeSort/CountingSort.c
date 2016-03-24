#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...) 
#endif

#define LENGTH  0xff
#define RANDOM_RANGE 100
void CountingSort(int arr[],int length);
void initArray(int arr[],int length);
void PrintArray(int arr[],int length);
int JudgeSortedArray(int arr[],int length);

int main()
{
  int Array[LENGTH]; 
  
  initArray(Array,LENGTH);

  CountingSort(Array,LENGTH);
  if(JudgeSortedArray(Array,LENGTH))
  {
	 printf("Ｏ（∩＿∩）Ｏ～ yes, counting sort is right\n");
     PrintArray(Array,LENGTH);
  }
  else
  {
	 printf(" ╮（╯▽╰）╭　something wrong~\n");
  }
  return 0;
}

void PrintArray(int arr[],int length)
{
	int i=0;
	for(;i<length;i++)
	{
		PRINTF("%d ",arr[i]);
	}
	PRINTF("\n");
}

void initArray(int arr[],int length)
{
   int i=0;
   srand(time(NULL));

   PRINTF("Init Aarray Done\n");
   for(;i<length;i++)
   {
	   arr[i]= rand()%RANDOM_RANGE;
	   PRINTF("%d ",arr[i]);
   }
   PRINTF("\n");
}

void CountingSort(int arr[],int length)
{
   int Temp[RANDOM_RANGE]={0};
   int Result[LENGTH]={0};
   int i=0;
   int j=0;
//counting the intger
   for(;j<length;j++)
   {
      ++Temp[arr[j]];
   }

   for(j=1;j<length;j++)
   {
	  Temp[j]+=Temp[j-1]; 
   }
   PRINTF("counting array:");
   PrintArray(Temp,RANDOM_RANGE);
   
   for(j=length-1;j>=0;j--)
   {
 //NOTICE the element of Temp[j] recording number of integer larger or equal to j among the array arr 
 //for example length of arr is 255 and its elment is [0~99] ;the temp[99]=255 ,so arr[j]-1 is index. 
	  Result[Temp[arr[j]]-1]=arr[j];   
	  --Temp[arr[j]];
   }
  // write the sorting result into array arr; 
   for(j=0;j<length;j++)
   {
	   arr[j]=Result[j];
   }

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
