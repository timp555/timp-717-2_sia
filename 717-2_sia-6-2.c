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



int shell_sort (int *arr, int arr_len) {
    int h, temp;
    int i, j;
    for (h = arr_len; h /= 2;) 
    {
        for (i = h; i < arr_len; i++) 
        {
            temp = arr[i];
            for (j = i; j >= h && temp < arr[j - h]; j -= h) 
            {
                arr[j] = arr[j - h];
            }
            arr[j] = temp;
        }
    }
    return 0;
}




int main(void) {
  int arr_len;
  scanf("%d", &arr_len);
  int arr[arr_len];
  push_arr(arr, arr_len);
  shell_sort(arr, arr_len);
  print_arr(arr, arr_len);
  printf("\n");
  return 0;
}
