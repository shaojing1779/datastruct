#include "avl_tree.h"
#include <time.h>
#include <unistd.h>

int main() 
{ 
	struct Node *root = NULL; 

	srand(time(NULL));
	root = insert(root, 11);
	root = insert(root, 32);
	root = insert(root, 8);
	root = insert(root, 7);
	root = insert(root, 21);

	print_tree(root);

	int i = 0;
	for(;i<10;i++)
	{
		sleep(1);
		root = insert(root, rand()%100);
		print_tree(root);
	}

	return 0; 
}
