#include <stdio.h>


void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

//////////////////array////////////////////
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
///////////////////////////////////////////


////////////////////////////////heap///////////////////////////////////
/* куча - дерево, для которого:
- Значение в любой вершине не меньше, чем значения её потомков[К 1].
- Глубина всех листьев (расстояние до корня) отличается не более чем на 1 слой.
- Последний слой заполняется слева направо без «дырок».*/

//arr[0] - корень кучи
//для каждого элемента с индексом i индекс левого потомка = 2i + 1, правого = 2i+2
//индекс родителя = (i-1)/2

//восстановление свойств кучи

//просеивание вниз (if эл-т меньше своих потомков)
void SiftDown(int *arr, int arr_len, int i)  //i - индекс просеиваемого элемента
{
  int left = 2*i + 1;
  int right = 2*i + 2;
  int max = i; //определяем максимум (его индекс) среди корня и его потомков
  if (left < arr_len && arr[left] > arr[max])
    max = left;
  if (right < arr_len && arr[right] > arr[max])
    max = right;
  //если потомок оказался больше корня, меняем их местами
  if (max != i)
  {
    swap(&arr[i], &arr[max]); //qw
    SiftDown(arr, arr_len, max);
  }
}


//построение кучи из массива
void BuildHeap(int *arr, int arr_len)
{
  //просеиваем вниз, начиная от предков листьев и так вверх
  //индекс последнего элемента кучи = arr_len-1, тогда индекс его предка = ((arr_len-1)-1)/2 = arr_len/2-1
  for (int i = arr_len/2-1; i >= 0; i--)
  {
    SiftDown(arr, arr_len, i);
  }
}

int HeapSort(int *arr, int arr_len)
{
  int heap_size = arr_len;
  BuildHeap(arr, arr_len); //строим кучу из массива
  while (heap_size > 1) //когда р-р кучи станет = 1, в ней останется только один элемент, к-й будет сам. мал - т.о. массив будет отсортирован
  {
    //массив = куча (уменьшается с итерациями) + отсортированная часть (увеличивается), куда последовательно кладём максимумы из кучи
    swap(&arr[0], &arr[heap_size - 1]); //ставим максимум в конец кучи и уменьшаем её размер на 1 (увеличиваем р-р отсорт. массива на 1), а затем восстанавливаем свойства кучи
    heap_size--;
    SiftDown(arr, heap_size, 0);
  }
    return 0;
}

int main(void) {
  int arr_len;
  scanf("%d", &arr_len);
  int arr[arr_len];
  push_arr(arr, arr_len);
  HeapSort(arr, arr_len);
  print_arr(arr, arr_len);
  return 0;
}
