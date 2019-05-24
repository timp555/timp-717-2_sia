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



/*	удалить	минимальный	элемент	из	поддерева,	корнем	которого является n.	вернуть	значение	удаленного	элемента	*/ 
int removeMin(tree* t, nodeTree*	n)    
{
  while (n->left)
  {
    n = n->left;
  }
  int min = n->value;
  n->root->left = NULL;
  free(n);
  t->nodes --;
  return min;
}


void removeTreeNodePtr(nodeTree* deleted) 
{
  
  //если элемент - не имеет потомков (лист)
    if (deleted->right == NULL && deleted->left == NULL)
    { 
      //цель - чей-то правый потомок
      if (deleted->root->right == deleted)
      {
        deleted->root->right = NULL;
      } 
      else
      {
        //цель - чей-то левый потомок
        deleted->root->left = NULL;
      }
    }
    //если есть только левый потомок
    else if (deleted->right == NULL && deleted->left != NULL)
    {
      if (deleted->root->left == deleted)
      {
        deleted->root->left = deleted->left;
      } 
      else
      {
        deleted->root->right = deleted->left;
      }
    } 
    //только правый потомок
    else if (deleted->right != NULL && deleted->left == NULL)
    {
      if (deleted->root->left == deleted){
        deleted->root->left = deleted->right;
      } else{
        deleted->root->right = deleted->right;
      }
    } 
    //оба потомка есть  
    else if (deleted->right != NULL && deleted->left != NULL)
    {
      //
      nodeTree* substitute;
      if (deleted->right) //if right, ищем минимум в правом поддереве, копируем его значение в целевой ("удаляемый") узел и удаляем его
      {
        substitute = deleted->right;  //min в правом поддереве
        while (substitute->left)
        {
          substitute = substitute->left; 
        }
      }
      else if (deleted->left) 
      {
        substitute = deleted->left; //if нет right и есть left, ищем максимум в левом поддереве 
        while (substitute->right)
        {
          substitute = substitute->right;
        }
      }
      deleted->value = substitute->value;
      removeTreeNodePtr(substitute);
      return;
    }
    free(deleted);
}

 
/* удалить элемент из дерева. вернуть 0 если элемент был удален и 1 если нет элемента с указанным значением */
int removeTreeNode(tree* t, int value)
{
  nodeTree* deleted;
  if(find(t, value, &deleted) == 1)  //элемент не найден
  {
    return 1;
  }
  //deleted = адрес элемента со значением value
  else  //элемент найден
  {
    removeTreeNodePtr(deleted);
    t->nodes --;
    return 0;
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


//удалить все элементы из дерева
void clear(tree* t)                 
{
  list l;    
  initList(&l);
  nodeList* tmp;
  push_back(&l, t->root);
  tmp = l.head;
  nodeTree* removed = NULL; 
  while (!isEmpty(&l))
  {
    if (tmp->ndTree->left)
      push_back(&l, tmp->ndTree->left);
    if (tmp->ndTree->right)
      push_back(&l, tmp->ndTree->right);
    removed = removeFirstListNode(&l);
    tmp = tmp->next;
    free(removed);
  }
  t->root = NULL;
  t->nodes = 0;
}


/*	выполнить	правое	вращение	поддерева.	вернуть	0	при	успешно	выполнение	операции	и	1	в	случае	если	вращение	невозможно	*/ 
int	rotateRight(tree* t)  //если дерево вытянуто влево
{
  
  
  nodeTree *rootPtr = t->root;
  nodeTree *newRoot = rootPtr->left;   //будущий корень
  if (!newRoot) return 1; //вращение невозможно
  
  rootPtr->left = newRoot->right;
  newRoot->right = rootPtr;
  t->root = newRoot;
  return 0;
}



/*	выполнить	левое	вращение	поддерева. вернуть	0	при	успешно	выполнение	операции	и	1	в	случае	если	вращение	невозможно	*/ 
int	rotateLeft(tree* t) //если дерево вытянуто вправо // получаем ссылку на "старый корень"
{
  nodeTree *rootPtr = t->root;
  nodeTree *newRoot = rootPtr->right;   //будущий корень
  if (!newRoot) return 1; //вращение невозможно
  
  rootPtr->right = newRoot->left;
  newRoot->left = rootPtr;
  t->root = newRoot;
  return 0;
}

void printInfAboutNode(tree* t, int value)
{
  nodeTree* found;
  if (find(t, value, &found) == 1)  //элемент не найден
  {
    printf("-");
  }
  else
  {
    if (found->root) printf("%d ", found->root->value);
    else printf("_ ");
    if (found->left) printf("%d ", found->left->value);
    else printf("_ ");
    if (found->right) printf("%d", found->right->value);
    else printf("_");
  }
  printf("\n"); 
}




int main(void) {
  tree t;
  initTree(&t);
  int a;
  for (int i = 0; i<4; i++)
  {
    scanf("%d", &a);
    insert(&t, a);
  }
  printTree(&t);
  for (int i = 0; i<3; i++)
  {
    scanf("%d", &a);
    insert(&t, a);
  }
  printTree(&t);
  int m1, m2, m3;
  scanf("%d", &m1);
  printInfAboutNode(&t, m1);
  scanf("%d", &m2);
  printInfAboutNode(&t, m2);
  scanf("%d", &m3);
  removeTreeNode(&t, m3); 
  printTree(&t);
  int rotFlag;
  do  //вращает влево до упора
  {
    rotFlag = rotateLeft(&t);  //=1 if not rotated
  } while (!rotFlag);
  printTree(&t);
  
  do  //вращает вправо до упора
  {
    rotFlag = rotateRight(&t);  //=1 if not rotated
  } while (!rotFlag);
  printTree(&t);
  printf("%d\n", t.nodes);
  clear(&t);
  printTree(&t);
  return 0;
}
