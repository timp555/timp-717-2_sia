#include <stdio.h>
#include <stdlib.h>


typedef struct nodeTree
{
    struct nodeTree* right; //прав. потомок - больше    
    struct nodeTree* left;  //лев. потомок - меньше
    struct nodeTree* root; //предок
    int value;
} nodeTree;
/*	структура	для	хранения	дерева.	хранит	ссылку	на	корень	дерева	и	количество	элементов	в	дереве	*/
 typedef struct	tree
{
     nodeTree* root;    //ссылка на корень
     int  nodes;    //к-во эл-тов
} tree;
//	инициализация	пустого	дерева 
void initTree(tree*	t)
{
    t->root = NULL;
    t->nodes = 0;
}

/*	поиск	элемента	по	значению.	вернуть	0	если	элемент	найден	и	ссылку	на	найденный	элемент	в	переменную	n	если	n	!=	NULL.	в	случае	если	элемент	не	найден	вернуть	1*/ 
int	find(tree*	t,	int	value,	nodeTree**	n)    //1       
{
    nodeTree* tmp = t->root;
    while (tmp != NULL)
    {
        if (tmp->value == value)   //эл-т найден
        {
            *n = tmp;    
            return 0;
        }
        else    
        {
            value > tmp->value ? (tmp = tmp->right) : (tmp = tmp->left);
        }
    }
    return 1;   //не найден
}


//поиск подходящего узла в дереве t для вставки элемента после него; даёт ссылку на нужный корень (после которого вставлять) 
nodeTree* findPredElem(tree* t, int value)  //1
{
    nodeTree* tmp = t->root;
    nodeTree* predElem;
    while(tmp!=NULL)
    {
        predElem = tmp;
        value > tmp->value ? (tmp = tmp->right) : (tmp = tmp->left);
    }
    return predElem;
}
//вставка потомка p в дерево t
void insertAfterNode(tree* t, nodeTree* p, int value)   //1
{
    p->value = value;
    nodeTree* predElem = findPredElem(t, value);
    p->value > predElem->value ? (predElem->right = p) : (predElem->left = p);
    p->root = predElem;
    p->right = NULL;
    p->left = NULL;
}






/*	вставка	значения	в	дерево.	вернуть	0,	если	вставка	выполнена	успешна; 1,	если элемент уже существует; 2 если	не	удалось	выделить	память	для	нового	элемента */ 
int	insert(tree* t,	int	value)    //10
{   
    nodeTree* newNode; 
    if (find(t, value, &newNode) == 0)    //если элемент существует 
    {
        return 1;
    }
    else
    {
        nodeTree* newNode = (nodeTree*)malloc(sizeof(nodeTree)); 
        if (newNode == NULL)    //если не удалось выделить память
        {
            return 2;
        }
        else            //вставка успешна
        {
            if (t->root == NULL)  //дерево было пусто
            {
                t->root = newNode;
                newNode->value = value;
                newNode->right = NULL;
                newNode->left = NULL;
            }
            
            else               //дерево не пусто
            {
                insertAfterNode(t, newNode, value);
            }
            t->nodes += 1;
            return 0;
        }
    }
}

//////////Очередь//////////

typedef struct nodeList //
{
  nodeTree* ndTree;
  struct nodeList* next;
} nodeList;


typedef struct list
{
    nodeList* head;
    nodeList* tail;
    int elements;     //количество элементов 
} list;
// инициализация пустого списка
void initList(list* l)  //1
{
    l->head = NULL;
    l->tail = l->head;
    l->elements = 0;  
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
int push_back(list* l, nodeTree* ndTree)   //1
{
    nodeList* newNode = (nodeList*)malloc(sizeof(nodeList));
    if (newNode == NULL)  //не удачно, 
    {
      return 1;
    }
    else  //вставка успешна
    {
      newNode->ndTree = ndTree;
      newNode->next = NULL;
      if (isEmpty(l))         
      {
          l->head = l->tail = newNode;
      }
      else
      {
          l->tail->next = newNode;
          l->tail = newNode;
      }
      l->elements += 1;
      return 0;
    }
}

nodeTree* removeFirstListNode(list* l)  //возвращает адрес узла дерева, хранящегося в узле очереди
{
	nodeList* hd = l->head;
  l->head = l->head->next;
  nodeTree* ndTree = hd->ndTree;
  free(hd);
  if (l->head == NULL) l->tail = NULL;
  l->elements --;
  return ndTree;
}

void printList (list* l)
{
  nodeList* hd = l->head;
  while (hd != NULL)
  {
    if (hd->ndTree == NULL)
    {
      printf("_");
    }
    else
    {
      printf("%d", hd->ndTree->value);
    }

    if (hd->next != NULL)
    {
      printf(" ");
    }
    hd = hd->next;
  }
  printf("\n");

}

///////////////////////////////////////////////////////////////////////////



/////////stack///////////////////


typedef struct nodeStack
{
    int value;
    nodeTree* ndTree;
    struct nodeStack* next;
    struct nodeStack* prev;
} nodeStack;


typedef struct stack
{
    nodeStack* head;
    nodeStack* tail;
} stack;





// инициализация пустого списка
void init(stack* s)  //1
{
    s->head = NULL;
    s->tail = s->head;
}


// проверка на пустоту списка
int isEmpty_stack(stack* s)    //
{
    if (s->head == NULL)
    {
        return 1;
    }
    else return 0;
}



// вставка значения в конец списка, вернуть 0 если успешно
int push_back_stack(stack* s, nodeTree* ndTree)   //1
{
    nodeStack* newNode = (nodeStack*)malloc(sizeof(nodeStack));
    if (!newNode) return 1;
    newNode->ndTree = ndTree;
    if (isEmpty_stack(s))         //qw
    {
        s->head = newNode;
        s->tail = newNode;
    }
    else
    {
        newNode->prev = s->tail;
        newNode->next = NULL;   //qw
        s->tail->next = newNode;
        s->tail = newNode;
    }
    return 0;
}



// вставка значения в начало списка, вернуть 0 если успешно
int push_front_stack(stack* s, nodeTree* ndTree)  //1
{
    nodeStack* newNode = (nodeStack*)malloc(sizeof(nodeStack));
    if (!newNode) return 1;
    newNode->ndTree = ndTree;
    if (isEmpty_stack(s))       
    {
        s->head = newNode;
        s->tail = newNode;
    }
    else
    {
        newNode->next = s->head;
        newNode->prev = NULL;   //qw
        s->head->prev = newNode;
        s->head = newNode;
    }
    return 0;
}



// вывести все значения из списка в прямом порядке, через
//пробел, после окончания вывода перейти на новую строку
void printStack(stack* s) //1
{
  nodeStack *tmp = s->head;
    if (!isEmpty_stack(s))  //если не пуст
    {
      while (tmp)
      {
        printf("%d", tmp->ndTree->value);
  	    if (tmp->next) printf(" ");
        tmp = tmp->next;
      }
    }
    else  //пуст
    {
      printf("-");
    }
    printf("\n");
}



// вывести все значения из списка в обратном порядке, 
//через пробел, после окончания вывода перейти на новую строку
void print_invers_stack(stack* s)  //1
{
    
  nodeStack *tmp = s->tail;
    if (!isEmpty_stack(s))  //если не пуст
    {
      printf("%d", tmp->ndTree->value);
	    if (tmp->prev) printf(" ");
      tmp = tmp->prev;
    }
    else  //пуст
    {
      printf("-");
    }
    printf("\n");
}


nodeTree *removeLastStackNode (stack* s)
{
  nodeStack *tmp = s->tail;
  nodeTree *ndTree = tmp->ndTree;
  s->tail = tmp->prev;
  free(tmp);
  if (s->tail == NULL) s->head = NULL; //qw
  return ndTree;
}


void delete_stack(stack *s)
{
  nodeStack *tmp = s->head, *tmp1;
  while (tmp)
  {
    tmp1 = tmp;
    tmp = tmp->next;
    free(tmp1);
  }
  s->head = s->tail = NULL;
}


//////////////////////stack end/////////////////////////////



/////////продолжение дерева/////////////////////////
int nodeTreeInListIsNULL(list* l)   
{
  nodeList* tmp = l->head;
  while (tmp != NULL)
  {
    if (tmp->ndTree != NULL)
    {
      return 0;
    }
    tmp = tmp->next;
  }
  return 1;
}


void print (nodeTree* n)
{
  if (n == NULL)
  {
    printf("-\n");
    return;
  }
  list l1;
  initList(&l1);

  nodeTree* rt = n;
  push_back(&l1, rt); 
  printList(&l1);    //выводим корень

  list l2;
  initList(&l2);
  //принтуем остальное
  while(1)
  {
    while (!isEmpty(&l1))  //
    {
      rt = removeFirstListNode(&l1);
      push_back(&l2, rt);
    }
    
    while (!isEmpty(&l2))
    {
      rt = removeFirstListNode(&l2);
      if (rt == NULL) //
      {
        push_back(&l1, NULL);
        push_back(&l1, NULL);
      }
      else
      {
        push_back(&l1, rt->left);
        push_back(&l1, rt->right);
      }
    }
    if (nodeTreeInListIsNULL(&l1))
    {
      while (!isEmpty(&l1))
        removeFirstListNode(&l1);
      break;
    }
    printList(&l1);
  }
}

//	вывести	все	значения	дерева	t,	аналогично	функции	print 
void printTree(tree* t)
{
  print(t->root);
}


void func(nodeTree *ndTree, stack *st)
{
  if (ndTree == NULL) return;
  func(ndTree->left, st);
  func(ndTree->right, st);
  push_back_stack(st, ndTree);
}


//обратный обход дерева в глубину : сначала обрабатываем левое поддерево, затем правое, затем узел
void ReverseTreeDepthPostOrderSearh(tree* t)
{
  stack *s = malloc(sizeof(stack));
  func(t->root, s);
  printStack(s);
  delete_stack(s);
}

int main(void) {
  tree *t = malloc(sizeof(tree));
  int value;
  for (int i = 0; i < 7; i++)
  {
    scanf("%d", &value);
    insert(t, value);
  }
  ReverseTreeDepthPostOrderSearh(t);
  return 0;
}
