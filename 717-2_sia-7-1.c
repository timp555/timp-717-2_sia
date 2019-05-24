#include <stdio.h>

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void qs(int *arr, int left0, int right0)
{
	int pivot = arr[right0]; //опорный элемент
	int left = left0;
	int right = right0;
	do
	{
		while (arr[left] < pivot)
			++left;
		while (arr[right] > pivot)
			--right;
		if (left <= right)
		{
			swap(&arr[left], &arr[right]);
			++left;
			--right;
		}
	} while (left <= right);
	if (right > left0)
		qs(arr, left0, right);
	if (left < right0)
		qs(arr, left, right0);
}

int quick_sort(int *arr, int arr_len)
{
	int left = 0;
	int right = arr_len - 1;
	qs(arr, left, right); //левая и правая границы
  return 0;
}

//////////функции массива/////////////////////
void print_arr(int *arr, int arr_len)
{
  for(int i = 0; i < arr_len - 1; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("%d\n", arr[arr_len-1]);
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




int main(void) {
  int arr_len;
  scanf("%d", &arr_len);
  int arr[arr_len];
  push_arr(arr, arr_len);
  quick_sort(arr, arr_len);
  print_arr(arr, arr_len);
  return 0;
}

