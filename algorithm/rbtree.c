//implement the red-black tree
//���������ɣ��ȴ����ɾ������
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef enum { RED, BLACK } EColor;
typedef struct tag_rbtree
{
  struct tag_rbtree* left;
  struct tag_rbtree* right;
  struct tag_rbtree* parent;
  int key;
  EColor color;
}rbtree, *prbtree, *prbt_node, rbt_node;

// ����һ����Ԫ
prbtree nil;
//preassume that the x has a right child
prbtree rbt_left_rotate(prbtree T, prbtree x)
{
  prbtree y = x->right;
  x->right = y->left;
  // ע���ж�ÿ��ָ���Ƿ�Ϊnil
  if (y->left != nil)
    {
      y->left->parent = x;    
    }
  y->parent = x->parent;
  if (x->parent != nil)
    {
      if (x->parent->left == x)
	{
	  x->parent->left = y;
	}
      else
	{
	  x->parent->right = y;
	}
    }
  else
    {
      T = y;
    }
  y->left = x;
  x->parent = y;
  return T;
}
//preassume that the y has a left child
prbtree rbt_right_rotate(prbtree T, prbtree y)
{
  // �ȴ���߽��������ٴ����м������y->parent Ҫ y��ָ��
  // ͬʱx->right Ҫx��ָ��������ȴ��������������
  // ÿ������ʶ�ж�ָ���Ƿ�Ϊ�գ�����ʹ��assert�����ж�
  prbtree x = y->left;
  // ���� x->right with y
  y->left = x->right;
  if(x->right != nil)
    {
      x->right->parent = y;
    }
  // ���� y->parent with x
  x->parent = y->parent;
  if (y->parent != nil)
    {
      if (y->parent->left == y)
	{
	  y->parent->left = x;
	}
      else
	{
	  y->parent->right = x;
	}
    }
  else
    {
      T = x;
    }
  // ���� x with y
  x->right = y;
  y->parent = x;
  return T;
}
/*���ֺ����������
 * ���������Щ���ʿ��ܱ��ƻ���
 * ����2�����ڵ��Ǻڵģ��������Ľ���Ǹ��ڵ㣬��δ����ǰ������ǿ�����
 * ������2���ƻ�
 * ����4�����һ������Ǻ�ɫ��������Ů���Ǻڵġ����������󣬸ý��
 * �ĸ��׽��Ҳ�Ǻ�ɫ�����ƻ�������4.
 */
prbtree rbt_insert_fixup(prbtree T, prbtree z)
{
  prbtree y;
  while(z->parent->color == RED)
    {
      assert(z->parent != nil);
      // ���z�ĸ��ڵ������游��������Ů
      assert(z->parent->parent != nil);
      if (z->parent == z->parent->parent->left)
	{
	  //y ��¼���常���
	  y = z->parent->parent->right;
	  // ������ ���y��ָ��Ľ�����ɫ�Ǻ�ɫ��case 1
	  if (y->color == RED)
	    {
	      // ����z��ͬʱ����y���
	      // ��z->parent �� y Ⱦ�ɺ�ɫ
	      // z->parent->parentȾ�ɺ�ɫ
	      // z����������㣬ָ�����游��
	      // Ҫ����y����� �����Զ�������һѭ��
	      z->parent->color = BLACK;
	      y->color = BLACK;
	      z->parent->parent->color = RED;
	      z = z->parent->parent;
	      // ������z����	      
	    }
	  // ���y��ָ��Ľ�����ɫ�Ǻ�ɫ��case 2 or case3
	  else 
	    {
	      // ���� ���z��ָ��Ľ�����丸�ڵ���Ҷ��� case 2
	      // ��z�ĸ��ڵ�Ϊ�ᣬ������һ������������ת��Ϊcase 3
	      if (z == z->parent->right)
		{
		  // ��ת�����»�ø��ڵ��ָ��
		  z = z->parent;
		  T = rbt_left_rotate(T,z);
		}
	      // ���z��ָ��Ľ�����丸�ڵ������� case 3
	      // �ı�z->parent����ɫΪ��ɫ��z->parent->parent��ɫΪ��ɫ�������游�ڵ�Ϊ�ᣬ������ѭ������
	      if (z == z->parent->left)
		{
		  z->parent->color = BLACK;
		  z->parent->parent->color = RED;
		  T = rbt_right_rotate(T, z->parent->parent);
		}
	    }
	}
      // ���z�ĸ��ڵ������游��������Ů
      else // z->parent == z->parent->parent->right
	{
	  // ����������Ů�����д���
	  // ��¼���常���
	  y = z->parent->parent->left;
	  // ���y�Ǻ�ɫ case 1
	  if (y->color == RED)
	    {
	      z->parent->color = BLACK;
	      y->color = BLACK;
	      z->parent->parent->color = RED;
	      z = z->parent->parent;
	    }
	  else // ���y�Ǻ�ɫ case 2 ���� case 3
	    {
	      // ���z���丸�׵����ӣ�����ת��Ϊ�Һ��� case 2
	      if (z == z->parent->left)
		{
		  z = z->parent;
		  T = rbt_right_rotate(T, z);
		}
	      // ����z���丸�׵��Һ����ˣ�case 3
	      // ���丸��ȾΪ��ɫ�����游ȾΪ��ɫ������
	      z->parent->color = BLACK;
	      z->parent->parent->color = RED;
	      T = rbt_left_rotate(T, z->parent->parent);
	    }
	}
    }
  T->color = BLACK;
  return T;
}
/* ����һ�����
 * TΪ�յ����
 * T��Ϊ�յ����
 * ����λ��
 * �������
 * ��ɫ
 * ���ֺ������
 */
prbtree rbt_insert_node(prbtree T, prbtree z)
{
  prbtree y = nil;
  prbtree x = T;
  while(x != nil){
    // y���游�ڵ��λ��
    y = x;
    if (z->key < x->key)
      {
	x = x->left;
      }
    else
      {
	x = x->right;
      }
  }
  z->parent = y;
  // ��� yΪ�ڱ�����z�Ǹ����
  if (y == nil)
    {
      T = z;
    }
  else
    {
      // �������
      if (z->key < y->key)
	{
	  y->left = z;
	}
      else
	{
	  y->right = z;
	}
    }
  //��ɫ
  z->left = nil;
  z->right = nil;  
  z->color = RED;
  // ���ֺ������
  T = rbt_insert_fixup(T, z);
  return T;  
}
/**
 * ��ȡ������н������ֵ
 */
prbt_node rbt_maximum(prbt_node root)
{
     prbt_node max = root;
     while(max->right != nil)
     {
	  max = max->right;
     }
     return max;
}
/**
 * ��ȡ������н�����Сֵ
 */
prbt_node rbt_minimum(prbt_node root)
{
     prbt_node min = root;
     while(min->left != nil)
     {
	  min = min->left;
     }
     return min;
}
/**
 * ��ȡ������н���ǰ��
 */
prbt_node rbt_precursor(prbt_node current)
{
     prbt_node parent = current->parent;
     if (current->left != nil)
     {
	  return rbt_maximum(current->left);
     }
     else if (parent != nil)
     {
	  while(parent != nil && parent->right != current)
	  {
	       current = parent;
	       parent = parent->parent;
	  }
	  if(parent != nil)
	  {
	       return parent;
	  }
	  else
	  {
	       return nil;
	  }
     }
     else
     {
	  return nil;
     }
}
/**
 * ��ȡ������н��ĺ��
 */
prbt_node rbt_successor(prbt_node current)
{
     prbt_node parent = current->parent;
     if (current->right != nil)
     {
	  return rbt_minimum(current->right);
     }
     else if (parent != nil)
     {
	  while(parent != nil && parent->left != current)
	  {
	       current = parent;
	       parent = parent->parent;
	  }
	  if (parent != nil)
	  {
	       return parent;
	  }
	  else
	  {
	       return nil;
	  }
     }
     else
     {
	  return nil;
     }
}
/** 
 * ���Ҹ���key�ĺ�����㣬������ָ��
 */
prbt_node rbt_search(prbt_node root, int key)
{
     // ���õ���ʵ�ָú���
     while(root != nil && root->key != key)
     {
	  if (key < root->key)
	  {
	       root = root->left;
	  }
	  else
	  {
	       root = root->right;
	  }
     }
     return root;
}
/**
 * ɾ�����󱣳ֺ�������ʵĺ���
 */
prbt_node rbt_delete_fixup(prbtree T, prbt_node x)
{
     prbt_node w;
     // ��x!=T��x����ɫΪ��ʱѭ������
     while(x != T && x->color == BLACK)
     {
	  // ���x���丸�������
	  if (x == x->parent->left)
	  {
	       w = x->parent->right;
	       // ���� case 1
	       // ���w����ɫ�Ǻ�ɫ����x->parent����ɫ�ض�Ϊ��ɫ
	       // w�ض�����Ҷ���
	       if (w->color == RED)
	       {
		    // ����w��x->parent����ɫ
		    // ��x->parent����һ������
		    // ʹcase 1 ת���case 2��3��4
		    w->color = BLACK;
		    x->parent->color = RED;
		    T = rbt_left_rotate(T, x->parent);
		    w = x->parent->right;
	       }
	       // case 2
	       // ��ʱw�ض��Ǻ�ɫ
	       // ���w�����Һ��Ӷ��Ǻ�ɫ
	       // �ı���ɫ��ѭ��������xָ������һ��
	       if (w->left->color == BLACK && w->right->color == BLACK)
	       {
		    w->color = RED;
		    x = x->parent;
	       }
	       else 
	       {
		    // ���w���Һ����Ǻ�ɫ����w�������Ǻ�ɫ
		    // case 3
		    // ����w�������ӵ���ɫ����w����һ������
		    // ����ʹw���Һ����Ǻ�ɫ,ת����case 4
		    if (w->right->color == BLACK)
		    {
			 w->color = RED;
			 w->left->color = BLACK;
			 T = rbt_right_rotate(T, w);
			 w = x->parent->right;
		    }
		    // case 4
		    // w���Һ����Ǻ�ɫ��w�����ӵ���ɫδ֪
		    // ����x->parent �� w����ɫ��
		    // ��w���Һ��Ӹ�ֵΪ��ɫ����x->parent����һ������
		    w->color = x->parent->color;
		    x->parent->color = BLACK;
		    w->right->color = BLACK;
		    T = rbt_left_rotate(T, x->parent);
		    x = T;		    
	       }
	  }
	  // ���x��x->parent���Һ��ӣ��Գƴ���
	  else
	  {
	       w = x->parent->left;
	       // case 1
	       if (w->color == RED)
	       {
		    w->color = BLACK;
		    x->parent->color = RED;
		    T = rbt_right_rotate(T, x->parent);
		    w = x->parent->left;
	       }
	       // case 2
	       if (w->right->color == BLACK && w->left->color == BLACK)
	       {
		    w->color = RED;
		    x = x->parent;
	       }
	       else
	       {
		    // case 3
		    if (w->left->color == BLACK)
		    {
			 w->color = RED;
			 w->right->color = BLACK;
			 T = rbt_left_rotate(T, w);
			 w = x->parent->left;
		    }
		    // case 4
		    w->color = x->parent->color;
		    x->parent->color = BLACK;
		    w->left->color = BLACK;
		    T = rbt_right_rotate(T, x->parent);
		    x = T;		    
	       }
	  }
     }
     x->color = BLACK;
     return T;
}
// ɾ��һ�����
// ���ǵ����
// ����:����������ܳ��֣���Ϊy�Ѿ�ָ�����е�ĳһ���
// ֻ��һ�����ڵ����
// �ж��������
prbtree rbt_delete_node(prbtree T, prbt_node z)
{
     // yָ��Ҫɾ���Ľ��
     prbt_node y;
     prbt_node x;
     if (z->left == nil || z->right == nil)
     {
	  y = z;
     }
     else
     {
	  y = rbt_successor(z);
     }
     // x ָ��Ҫ���ӵ�����
     if (y->left != nil)
     {
	  x = y->left;
     }
     else
     {
	  x = y->right;
     }
     x->parent = y->parent;
     if (y->parent == nil)
     {
	  T = x;
     }
     else if (y->parent->left == y)
     {
	  y->parent->left = x;
     }
     else
     {
	  y->parent->right = x;
     }
// ���y != z ��yΪz�ĺ�̽�㣬��z��key��ֵΪy��key
     if (y != z)
     {
	  z->key = y->key;
	  // ��z���������ݸ�ֵΪy����������
	  // ...
     }
     if (y->color == BLACK)
     {
	  T = rbt_delete_fixup(T, x);
     }
     return T;
}
void print_node(prbt_node x)
{
  if (x == nil)
    {
      printf("no value\n");
      fflush(stdout);
      return ;
    }
  printf("value = %d\n", x->key);
  switch(x->color)
    {
    case RED:
      printf ("COLOR = RED\n");
      break;
    case BLACK:
      printf ("COLOR = BLACK\n");
      break;
    default:
      printf ("NO COLOR\n");
    }
  fflush(stdout);
}
void mid_traverse_node(prbt_node root)
{
  if(root != nil)
    {
      mid_traverse_node(root->left);
      print_node(root);
      mid_traverse_node(root->right);
    }
}
void swap(int* a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
int random(int i, int length)
{
    //ȡi �� n ֮���һ������� [i, n] ������
    return (double)rand()/RAND_MAX * (length - i) + i;
}
void randomize_in_place(int array[], int length)
{
    int i;
    for(i = 0; i < length; i++)
    {
	swap(&array[i], &array[random(i, length-1)]);
    }    
}

void construct_node(prbt_node x, int value)
{
    // error here!!!
    //x = (bst_node*)malloc(sizeof(bst_node));
    x->parent = NULL;
    x->left = NULL;
    x->right = NULL;
    x->key = value;
    x->color = RED;
}
void print_array(int array[], int length)
{
    int i;
    for(i = 0; i < length; i++)
    {
	printf("array[%d] = %d\n", i, array[i]);
    }
}
int main()
{
  // ���Է�����
  // ����10��Ԫ�أ�������Ԫ�أ���ӡ
  int i;
  prbtree root;
  nil =(prbtree)malloc(sizeof(rbtree));
  nil->color = BLACK;
  root = nil;
  int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int length = sizeof(array)/sizeof(int);
  /* srand(GetTickCount()); */
  randomize_in_place(array, length);  
  print_array(array, length);  
  fflush(stdout);
  for (i = 0; i < length; i++)
    {
      prbtree y = (prbtree)malloc(sizeof(rbt_node));
      construct_node(y, array[i]);
      // print_node(y);
      root = rbt_insert_node(root, y);
      printf ("the %dth iteration\n",i + 1);
      mid_traverse_node(root);
      /* print_node(root); */
      /* printf("%x\n", (unsigned int)root); */
    }
  // mid_traverse_node(root);
  // ����ɾ������
  randomize_in_place(array, length);
  print_array(array, length);
  fflush(stdout);
  for (i = 0; i < length; ++i)
  {
       prbt_node x = rbt_search(root, array[i]);
       root = rbt_delete_node(root, x);
       printf ("the number %d deleted\n",array[i]);
       printf ("the %dth iteration\n",i + 1);
       mid_traverse_node(root);
  }
  return 0;
}
