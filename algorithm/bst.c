//��������������ֵ����Сֵ��ǰ������̣����ң����룬ɾ��
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

struct __bst_node{
    int key;
    struct __bst_node* parent;
    struct __bst_node* left;
    struct __bst_node* right;
};

typedef struct __bst_node bst_node;
// preassume that the root is not null
bst_node* max_node(bst_node * root)
{
    /* if (root-> right == NULL) */
    /* { */
    /* 	return root; */
    /* } */
    /* return max_node(root->right); */
    bst_node* max = root;
    while(max->right)
    {
	max = max->right;
    }
    return max;
}
bst_node* min_node(bst_node * root)
{
    bst_node* min = root;
    while(min->left)
    {
        min = min->left;
    }
    return min;
}
// preassume that the root is not null
bst_node* precursor_node(bst_node* current)
{
    bst_node* parent = current->parent;
    // ����������ӣ���ǰ��Ϊ��ǰ����������������Ǹ����
    if(current->left)
    {
	return max_node(current->left);
    }
    else if(parent)
    {
	// �����ǰ������丸�׵��Һ��ӣ���ø�������ǰ��
	while(parent && parent->right != current)
	{
	    current = parent;
	    parent = parent->parent;
	}
	if(parent)
	    return parent;
	else
	    return NULL;
    }
    else
    {
	return NULL;
    }

}
// preassume that the root is not null
bst_node* successor_node(bst_node* current)
{
    bst_node* parent = current->parent;
    // ��������Һ��ӣ�����Ϊ��ǰ�������������С���Ǹ����
    if(current->right)
    {
	return min_node(current->right);
    }
    else if(parent)
    {
	while(parent && parent->left != current)
	{
	    current = parent;
	    parent = parent->parent;
	}
	if (parent)
	    return parent;
	else 
	    return NULL;
    }
    else
    {
	return NULL;
    }
}
// preassume that the current is not null
bst_node* delete_node(bst_node* current)
{
    // ɾ�����������
    // Ҷ��㣬ֱ��ɾ��
    // ��һ�������Ľ�㣬�������ĸ��滻�ý��
    // �����������Ľ�㣬�ҵ��ý��ĺ�̣��ú�̵�key�滻�ý���key��ɾ�����,
    // ���̱ض�Ϊ���������������Ǹ���㣬�Ҹýڵ�����ֻ�е�һ����,�Ҹõ�һ������������
    // x��Ǵ�ɾ���Ľ�㣬y��Ǵ����ӵ�����
    // ����ɾ������������ĸ�
    // Ҫϰ���Ե��ж�y�Ƿ���Ч
    bst_node* root = current;
    bst_node* x = current;
    bst_node* y = NULL;
    while(root->parent)
    {
	root = root->parent;
    }
    if(x->left == NULL)
    {
	y = x->right;
    }
    else if(x->right == NULL)
    {
	y = x->left;
    }
    else
    {
	x = successor_node(x);
	current->key = x->key;
	y = x->right;
    }
    if(x->parent == NULL)
    {
	root = y;
	// y maybe null
	if(y)
	{
	    y->parent = NULL;
	}
    }
    else if(x->parent->right == x)
    {
	x->parent->right = y;
	if(y)
	{
	    y->parent = x->parent;
	}
    }
    else // x->parent->left == x
    {
	x->parent->left = y;
	if(y)
	{
	    y->parent = x->parent;	
	}
    }
    free(x);
    return root;    
}
bst_node*  insert_node(bst_node* root, bst_node* x)
{
    // ���root ΪNULL,ȷ��root ��ָ���Ԫ�ز�Ϊ��
    if(root == NULL)
    {
	root = x;
	return root;
    }
    else if(x->key < root->key)
    {
	root->left = insert_node(root->left, x);
	// �ж�x->parent�Ƿ�Ϊ�գ����Ϊ�գ���ô�ѭ������˶Խ��Ĳ��룬ָ���丸�ڵ�
	if(!x->parent)
	{
	    x->parent = root;
	}
    }
    else
    {
	root->right = insert_node(root->right, x);
	// �ж�x->parent�Ƿ�Ϊ�գ����Ϊ�գ���ô�ѭ������˶Խ��Ĳ��룬ָ���丸�ڵ�
	if(!x->parent)
	{
	    x->parent = root;
	}
    }
    return root;
}
bst_node* search_node(bst_node* root, int key)
{
    if(root == NULL)
    {
	return NULL;
    }
    if(root->key == key)
    {
	return root;
    }
    else if (key > root->key)
    {
	search_node(root->right, key);
    }
    else 
    {
	search_node(root->left, key);
    }
}
void print_node(bst_node* x)
{
    if (x == NULL)
    {
	printf("no value\n");
	fflush(stdout);
	return ;
    }
    printf("%d\n", x->key);
    fflush(stdout);
}
// ����������������
void mid_traverse_node(bst_node* root)
{
    if(root)
    {
	mid_traverse_node(root->left);
	print_node(root);
	mid_traverse_node(root->right);
    }
}
void construct_node(bst_node* x, int value)
{
    // error here!!!
    //x = (bst_node*)malloc(sizeof(bst_node));
    x->parent = NULL;
    x->left = NULL;
    x->right = NULL;
    x->key = value;
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
    int i;
    bst_node* root = NULL;
    // ����ԭ������������������
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = sizeof(array)/sizeof(int);
    /* srand(GetTickCount()); */
    randomize_in_place(array, length);  
    print_array(array, length);  
    for (i = 0; i < length; i++)
    {
	bst_node* y = (bst_node*)malloc(sizeof(bst_node));
    	construct_node(y, array[i]);
    	root = insert_node(root, y);
	/* printf("%x\n", (unsigned int)root); */
    }
    mid_traverse_node(root);
    print_node(max_node(root));
    print_node(min_node(root));
    int s_value;
    scanf("%d", &s_value);
    fflush(stdin);
    while(s_value != -1)
    {
	bst_node* s_node = search_node(root, s_value);
	if (s_node)
	{
	    root = delete_node(s_node);
	}
	else
	{
	    printf("not in the bst tree\n");
	    fflush(stdout);
	}
	length--;
	mid_traverse_node(root);
	scanf("%d", &s_value);
	/* for(i = 0; i<length; i++) */
	/* { */
	/*     int search_key = random(0, length-1); */
	/*     bst_node* current_node = search_node(root, search_key); */
	/*     /\* bst_node* precursor = precursor_node(current_node); *\/ */
	/*     /\* bst_node* successor = successor_node(current_node); *\/ */
	/*     printf("the search key is %d\n", search_key); */
	/*     if(current_node->parent) */
	/* 	printf("the parent of %d is %d\n",current_node->key, current_node->parent->key); */
	/*     fflush(stdout); */
	/*     /\* if(precursor) *\/ */
	/*     /\*     printf("the precursor of %d is %d\n", current_node->key, precursor->key); *\/ */
	/*     /\* if(successor) *\/ */
	/*     /\*     printf("the successor of %d is %d\n", current_node->key, successor->key); *\/ */
	/* } */
    }
    return 0;
}
    
