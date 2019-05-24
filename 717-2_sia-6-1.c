#include <stdio.h> 
//#include <stdlib.h>

void print_arr(int *arr, int arr_len)
{
  for(int i = 0; i < arr_len - 1; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("%d", arr[arr_len-1]);
}



void push_arr(int *arr, int arr_len)
{
  int elem;
  for(int i = 0; i < arr_len; i++)
  {
    scanf("%d", &elem);
    arr[i] = elem;
  }
}



int comb_sort(int *arr, int arr_len)
{
  float fact_um = 1.247;  //factor umensheniya
  int n = arr_len; //rasst m/u el-tami (shag)
  int swap = 1, tmp; 
  
  while(swap == 1 || n > 1) // if step = 1 and there was no swap then quit
  {
    swap = 0;
    n = n/fact_um;
    if (n < 1) n = 1;
    for(int i = 0; i + n < arr_len; i++)
    {
      if(arr[i] > arr[i+n]) //swap condition
      {
        tmp = arr[i];
        arr[i] = arr[i+n];
        arr[i+n] = tmp;
        swap = 1; //sign that a swap took place
      }
    }
  }
  return 0;
}


int main(void) {
  int arr_len;
  scanf("%d", &arr_len);
  int arr[arr_len];
  push_arr(arr, arr_len);
  comb_sort(arr, arr_len);
  print_arr(arr, arr_len);
  printf("\n");
  return 0;
}

