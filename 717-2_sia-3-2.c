#include <stdio.h>
#include <stdlib.h> //qw


typedef struct node
{
    int value;
    struct node* next;
    struct node* prev;
} node;


typedef struct list
{
    node* head;
    node* tail;
} list;





// инициализация пустого списка
void init(list* l)  //1
{
    l->head = NULL;
    l->tail = l->head;
}


// проверка на пустоту списка
int isEmpty(list* l)    //
{
    if (l->head == NULL)
    {
        return 1;
    }
    else return 0;
}



// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list* l, int value)   //1
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value = value;
    if (isEmpty(l) /*l->head == NULL*/)         //qw
    {
        l->head = newNode;
        l->tail = newNode;
    }
    else
    {
        newNode->prev = l->tail;
        newNode->next = NULL;   //qw
        l->tail->next = newNode;
        l->tail = newNode;
    }
    
}



// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list* l, int value)  //1
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value = value;
    if (isEmpty(l) /*l->head == NULL*/)         //qw
    {
        l->head = newNode;
        l->tail = newNode;
    }
    else
    {
        newNode->next = l->head;
        newNode->prev = NULL;   //qw
        l->head->prev = newNode;
        l->head = newNode;
    }
}



// вывести все значения из списка в прямом порядке, через
//пробел, после окончания вывода перейти на новую строку
void print(list* l) //1
{
    if (isEmpty(l) == 0)
    {
        node* tmp = l->head;
	    while (tmp != NULL)
	    {
		    if (tmp->next == NULL)
		    {
			    printf("%d", tmp->value);
			    tmp = tmp->next;
		    }
		    else
		    {
		    	printf("%d ", tmp->value);
		    	tmp = tmp->next;
		    }
    	}
	    printf("\n");
    }
//	else printf("Список пуст!\n");	//qw

}



//удалить все элементы из списка
void clear(list* l)         //1
{
    node *tmp1 = l->head;
	node *tmp2;
    while (tmp1 != NULL)
	{
		tmp2 = tmp1;
		tmp1 = tmp1->next;
		free(tmp2);
    }
	l->head = NULL;
	l->tail = NULL;
}



// вставка значения после указанного узла, вернуть 0 если успешно
int insertAfter(node* n, int value)     //1
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value = value;
    newNode->next = n->next;
    n->next = newNode;
    newNode->prev = n;
    newNode->next->prev = newNode;      //qw
}



// вставка значения перед указанным узлом, вернуть 0 если успешно
int insertBefore(node* n, int value)    //1
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value = value;
    newNode->prev = n->prev;
    newNode->next = n;
    n->prev = newNode;
    newNode->prev->next = newNode;
}





// поиск элемента по значению. вернуть NULL если элемент не найден
node* findFromBeginning(list* l, int value)
{
    node* tmp = l->head;
	while (tmp != NULL)
	{
		if (tmp->value == value)
		{
			return tmp; //нашёл
		}
		tmp = tmp->next;
	}
	return NULL;   //не нашёл
}

node* findFromEnd(list* l, int value)
{
    node* tmp = l->tail;
	while (tmp != NULL)
	{
		if (tmp->value == value)
		{
			return tmp;
		}
		tmp = tmp->prev;
	}
	return NULL;
}




// удалить первый элемент из списка с указанным значением,
//вернуть 0 если успешно
int removeFirst(list* l, int value)
{
    node* found = findFromBeginning(l, value);
    if (found != NULL)  // если найден
    {
        if (found == l->head)
        {
            l->head = l->head->next;
            l->head->prev = NULL;   //qw
        }
        else if (found == l->tail)
        {
            l->tail = l->tail->prev;
            l->tail->next = NULL;
        }
        else
        {
            found->prev->next = found->next;
            found->next->prev = found->prev;
        }
        free(found);
        return 0;
    }
    
}



// удалить последний элемент из списка с указанным значением, вернуть 0 если успешно
int removeLast(list* l, int value)  //1
{
    node* found = findFromEnd(l, value);
    if (found != NULL)  // если найден
    {
        if (found == l->head)
        {
            l->head = l->head->next;
            l->head->prev = NULL;   //qw
        }
        else if (found == l->tail)
        {
            l->tail = l->tail->prev;
            l->tail->next = NULL;
        }
        else
        {
            found->prev->next = found->next;
            found->next->prev = found->prev;
        }
        free(found);
        return 0;
    }

}


node* findJ(list* l, int j)   //находит j-й узел
{
    node* tmp = l->head;
	int count = 1;
	while (count != j)
	{
		tmp = tmp->next;
		count++;
	}
    return tmp;
}


void insertAfterJ(list* l, int j, int value)    //1~
{
    insertAfter(findJ(l, j), value);
}



void insertBeforeJ(list* l, int j, int value)
{
    insertBefore(findJ(l, j), value);
}





// вывести все значения из списка в обратном порядке, 
//через пробел, после окончания вывода перейти на новую строку
void print_invers(list* l)  //1
{
    node* tmp = l->tail;
    while (tmp != NULL)
    {
        if (tmp->prev == NULL) 
        {
            printf("%d", tmp->value);
        }
        else
        {
            printf("%d ", tmp->value);
        }
        
        tmp = tmp->prev;
    }
    printf("\n");
}




int main()
{
    list* l = (list*)malloc(sizeof(list));
    init(l);
    int n, a, k, m, t, j, x, u, y, z, r;
    scanf("%d", &n);    //к-во эл-тов
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &a);
        push_back(l, a);
    }
    print(l);
    for(int i = 0; i < 3; i++)
    {
        scanf("%d", &k);
        if (findFromBeginning(l, k) != NULL)
        {
            printf("%d", 1);
		}
		else 
        {
			printf("%d", 0);
		}
    }
    printf("\n");
    scanf("%d", &m);
    push_back(l, m);
    print_invers(l);
    scanf("%d", &t);
    push_front(l, t);
    print(l);
    scanf("%d%d", &j, &x);  //qw
    insertAfterJ(l, j, x);
    print_invers(l);
    scanf("%d%d", &u, &y);
    insertBeforeJ(l, u, y);
    print(l);
    scanf("%d", &z);
    removeFirst(l, z);
    print_invers(l);
    scanf("%d", &r);
    removeLast(l, r);
    print(l);
    clear(l);
    return 0;
}
