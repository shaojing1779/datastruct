#include "avl_tree.h"
#include <time.h>
  
int main() 
{ 
  struct Node *root = NULL; 
  
  do{
	static int i = 0;

	srand(time(NULL));
	root = insert(root, rand());
	if(i >= 10000000) break;

  }while(1);
  
  preOrder(root); 

  printf("\n");
  
  return 0; 
}
