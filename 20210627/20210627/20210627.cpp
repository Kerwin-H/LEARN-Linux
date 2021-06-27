//前序遍历
int* preorderTraversal(struct TreeNode* root, int* returnSize){

	int sz = getSize(root);
	int* arr = malloc(sizeof(int)*sz);
	stack st;
	stackInit(&st);
	int idx;
	//当前遍历的节点不为空,或栈不为空
	while (root || !stackEmpty(&st)){

		//1.访问左边路径
		while (root){

			arr[idx++] = root->val;
			//当前节点入栈
			stackPush(&st, root);
			root = root->left;
		}
		//2.获取栈顶元素,访问右子树
		root = stackTop(&st);
		stackPop(&st);
		root = root->right;
	}
	*returnSize = idx;
	return arr;
}
//=========================================3.中序遍历 非递归
int* inorderTraversal(struct TreeNode* root, int* returnSize){

	int sz = getSize(root);
	int* arr = malloc(sizeof(int)*sz);
	stack st;
	stackInit(&st);
	int idx = 0;

	while (root || !stackEmpty(&st)){

		//1.先遍历左边
		while (root){

			stackPush(&st, root);
			root = root->left;
		}
		//2.获取栈顶元素

		root = stackTop(&st);
		stackPop(&st);
		arr[idx++] = root->val;

		//3.访问右子树
		root = root->right;
	}
	*returnSize = idx;
	return arr;
}
//===========================================4.后序遍历 非递归
int* postorderTraversal(struct TreeNode* root, int* returnSize){

	int sz = getSize(root);
	int* arr = (int*)malloc(sizeof(int)*sz);
	stack st;
	stackInit(&st);
	int idx = 0;
	//prev:上次访问记得节点位置
	struct TreeNode* prev = NULL;
	while (root || !stackEmpty(&st)){

		//1.遍历左路径
		while (root){

			stackPush(&st, root);
			root = root->left;
		}
		//top:栈顶的节点
		struct TreeNode* top = stackTop(&st);
		//这里要进行判断是否能访问栈顶
		//条件:没有右子树或者右子树访问完毕
		if (top->right == NULL || top->right == prev){

			//访问栈顶元素
			arr[idx++] = top->val;
			stackPop(&st);

			prev = top;
		}
		else
			//访问右子树
			root = top->right;
	}
	*returnSize = idx;
	return arr;
}