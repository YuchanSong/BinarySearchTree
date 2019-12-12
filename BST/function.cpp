#include "stdafx.h"

//Binary Search Tree �Լ� ����

TNode *root;

void init_tree() { root = NULL; }
int is_empty_tree() { return root == NULL; }
int cnt; // Order�� ���� �������� ����
int index;

//Ʈ�� ������ ����
TNode* create_tree(int val, TNode* l, TNode* r)
{
	TNode* n = (TNode*)malloc(sizeof(TNode));
	n->data = val;
	n->left = l;
	n->right = r;
	return n;
}

//Ž�� ���� ����
TNode* search(TNode *n, int key)
{
	if (n == NULL) return NULL;
	else if (key == n->data) return n;
	else if (key < n->data) return search(n->left, key);
	else return search(n->right, key);
}

int search_BST(int key)
{
	TNode *n = search(root, key);
	if (n != NULL) return 1; // ���Ұ� ������
	else return 0; // ������
}

//0) ���� �޴� ��� �Լ�
void show_menu(void)
{
	cnt = -1;
	index = -2;
	puts("+----------------------------+");
	puts("|     Binary Search Tree     |");
	puts("+----------------------------+");
	puts("|        1)  ��� ����       |");
	puts("|        2)  ��� ����       |");
	puts("|        3)  ��� ����       |");
	puts("|        4)  ���� ��ȸ       |");
	puts("|        5)  ���� ��ȸ       |");
	puts("|        6)  ���� ��         |");
	puts("|        7)  �ִ� ��         |");
	puts("|        8)  �ε���          |");
	puts("|        9)  �ڽ� ����       |");
	puts("|       10)  ����            |");
	puts("+----------------------------+");
}

//1) Insert
//data�� �о BST�� �����Ѵ�.
//���� data ���� ���ٰ� �����Ѵ�.(�Է� ���� �߸� ������ error message�� ����ϰ� �ٽ� �Է¹޴´�.)
int Insert(TNode *r, TNode *n) // r == root, n == new node
{
	if (r->data == n->data) return 0; //��� n�� Ű�� ��Ʈ ����� r�� Ű ���� ������ �������� �ʰ� 0�� ��ȯ�Ѵ�.
	else if (n->data < r->data) { //��� n�� Ű�� ��Ʈ ����� r�� Ű���� Ŭ ��
		if (r->left == NULL) r->left = n; //��Ʈ ��� r�� ���� �ڽ��� NULL �� ��, ��Ʈ ����� ���ʿ� ��� n�� �����Ѵ�.
		else Insert(r->left, n); //�ƴϸ� 
	}
	else { //��� n�� Ű�� ��Ʈ ����� r�� Ű���� ���� ��
		if (r->right == NULL) r->right = n;
		else Insert(r->right, n);
	}
	return 1; // ���� ����
}

void Insert_BST(int key)
{
	TNode *n = create_tree(key, NULL, NULL);
	if (is_empty_tree()) { // BST�� ��������̸�
		root = n; // root�� ����
		printf("### [���� ����] : %d\n", key);
	}
	else if (search_BST(key) == 1 && Insert(root, n) == 0) { // key�� Ʈ���� �ְ� �ߺ������̸�
		free(n); // �����Ҵ� ����
		printf("### �ߺ� ���� �����Դϴ�.\n");
	}
	else if (search_BST(key) == 1 && Insert(root, n) == 1) { // key�� Ʈ���� �ְ� ���Կ� �����ϸ�(�����)
		free(n); // �����Ҵ� ����
		printf("### �ߺ� ���� �����Դϴ�.\n");
	}
	else if (Insert(root, n) == 1) // insert�� �����ϸ�
		printf("### [���� ����] : %d\n", key);
}

//2) Delete
//data ���� �����Ѵ�. data ���� ���� ��� ���ٰ� ����Ѵ�.
//case 1 : terminal node - �θ�� ���� ����
//case 2 : �ڽ�1 - �θ�� �ڽ� ����
//case 3 : �ڽ�2 - ���ʼ���Ʈ���� ���� ū���� ��ġ�Ѵ�
void Delete(TNode *parent, TNode *node)
{
	TNode *child, *succ, *succp;

	//case1 (�����ϴ� ��尡 �ܸ� ����� ���)
	if (node->left == NULL && node->right == NULL) {
		if (parent == NULL) root = NULL; // node�� Ʈ���� ��Ʈ�̸� Ʈ���� ��Ʈ�� NULL�� �ǰ� ����Ʈ���� ��
		else {
			if (parent->left == node) // node�� parent�� ���� �ڽ��ΰ�?
				parent->left = NULL; // Yes => parent�� ���� �ڽ��� ��带 NULL�� ����
			else parent->right = NULL; // No => parent�� ������ �ڽ��� ��带 NULL�� ����
		}
	}
	//case2 (�����ϴ� ��忡 �����̳� �����ʿ� �ڽ��� �ϳ� ���� ���)
	else if (node->left == NULL || node->right == NULL) {
		child = (node->left != NULL) ? node->left : node->right; // child�� node�� �����̳� ������ �ڽ� �ּҸ� ����
		if (node == root) root = child; // node�� ��Ʈ ����̸� child�� ��Ʈ��尡 ��
		else {
			if (parent->left == node) //node�� parent�� ���� �ڽ��̸� 
				parent->left = child; // child�� parent�� ���� �ڽ��� �ǰ�
			else parent->right = child; // node�� ������ �ڽ��̸� child�� ������ �ڽ��� ��
		}
	}
	//case3 (�����ϴ� ��尡 �ΰ��� �ڽ��� �ִ� ���)
	else {
		//�İ���� ���� �θ��� ������ �ʱ�ȭ
		succp = node;
		succ = node->left; //���� ����Ʈ���� �̵�
		while (succ->right != NULL) { //���� ����Ʈ���� ���� ū ���(���������� ����)�� ã�ư��� ��ġ��Ŵ
			succp = succ;
			succ = succ->right;
		}
		if (succp->left == succ) //succ�� succp�� ���� �ڽ��̸� 
			succp->left = succ->right; //succp�� ���� �ڽ����� succ�� ������ �ڽ��� ������.
		else succp->right = succ->right; //�׷��� ������ succp�� ������ �ڽ����� succ�� ������ �ڽ��� ������(succ�� ���� �ڽ�x)

		node->data = succ->data; //������ ��� node�� �İ� ��� succ�� ������ ����� ������
		node = succ;
	}
	free(node);
}

void Delete_BST(int key)
{
	TNode *parent = NULL;
	TNode *node = root;

	//if (node == NULL) return;
	while (node != NULL && node->data != key) {
		parent = node; //root�������� key�� ���� ���� �θ� ��带 ã��, ������ delete ����, ������ ���� �޽��� ���
		node = (key < node->data) ? node->left : node->right;
	}
	if (node == NULL) printf("### Delete�� ���� �������� �ʽ��ϴ�. �ٽ� �õ����ּ���.\n\n");
	else {
		Delete(parent, node);
		printf("### [���� ����] : %d\n\n", key);
	}
}

//3) Count
//������ ������ ����Ѵ�.
int Count(TNode *n)
{
	if (n == NULL) return 0; // ���� Ʈ���̸� 0��ȯ
	return 1 + Count(n->left) + Count(n->right); // root + left subtree + right subtree
}

//4) Preorder
//���� ��ȸ ���� ���
void Preorder(TNode *n)
{
	if (n != NULL) {
		printf("[%d] ", n->data);
		Preorder(n->left);
		Preorder(n->right);
	}
}

//5-1) Level_orde�� ���� ����ť ����
TNode* data[MAX_QUEUE_SIZE];
int front;
int rear;

void init_queue() { front = rear = 0; }
int is_empty() { return front == rear; }
int is_full() { return front == (rear + 1) % MAX_QUEUE_SIZE; }

//������ ���� ����
void enqueue(TNode* n)
{
	if (is_full())
		printf("### ť ��ȭ ����");
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	data[rear] = n;
}

//������ ���� ����
TNode* dequeue()
{
	TNode *n = NULL;

	if (is_empty())
		printf("### ť ���� ����");
	front = (front + 1) % MAX_QUEUE_SIZE;
	n = data[front];
	return n;
}

//5-2) Level_order
//���� ��ȸ ������� �湮�� ���Ҹ� ����Ѵ�.
void Level_order(TNode *root) 
{
	TNode *n;

	if (root == NULL) return; // ���� Ʈ����� return
	init_queue(); // ť �ʱ�ȭ
	enqueue(root); // ť�� root ����
	while (!is_empty()) { // ť�� ������ �ƴҵ��� �ݺ�
		n = dequeue(); // �ϳ��� dequeue����
		if (n != NULL) { // n�� NULL�� �� ������ �ݺ�
			printf("[%d] ", n->data);
			enqueue(n->left);
			enqueue(n->right);
		}
	}
}

//6) Next
//data �� ���� ū ���� ���� ���� �� ���� ���� ���� ����Ѵ�.
int Next(TNode *n, int key)
{
	int buf[20]; //data�� ������ �迭 buf
	TNode* r = root; //r�� ��� ������ ���ϱ� ���� ����

	if (n != NULL) {
		Next(n->left, key);
		cnt++; // ������ȸ�Ҷ����� cnt(index)�� ����������
		buf[cnt] = n->data; // �迭 buf�� 0 ~ n���� ����� �����͸� ����
		if (key == n->data && cnt != Count(r)-1) index = cnt; // ����� �����Ϳ� key�� ���� �ִ밪�� �ƴϸ� ���� cnt�� index�� ����
		else if (key == n->data && cnt == Count(r) - 1) { // ����� �����Ϳ� key�� ���� �ִ밪�̸� cnt�� index�� ���� �� ���� ���
			index = cnt;
			printf("### �ִ밪�Դϴ�.\n\n");
		}
		else if (index == cnt - 1) printf("### Next Value [%d]\n\n", buf[index + 1]); // �� �ܰ� ū �� ���
		Next(n->right, key);
	}
	if (index == -2) return 1; // ã�� ��尡 ������ return 1
	return 2; // ��ġ�ϴ� ���� ã������ return 2
}

//7) Max
//���� �� ���� ū ���� ���
int Max(TNode* n)
{
	if (n == NULL) return 0; // ���� Ʈ����� 0 ��ȯ
	if(n->right == NULL) return n->data; // ����� �������� ����Ű�� ���� NULL(���� ū ��)�� �� data ��ȯ
	return Max(n->right); // ���� ���������� �̵�
}

//8) Order
//data ���� ���� ���Ұ� �� ��°�� ���� �������� ����Ѵ�.
//���Ұ� ���� ��쿡�� 0�� ����Ѵ�.
int Order(TNode* n, int key)
{
	if (n == NULL) return 0;
	if (n != NULL) {
		Order(n->left, key);
		cnt++; // ���� ��ȸ �Ҷ����� cnt�� ++����
		if (key == n->data)
			printf("### Value [%d] => [%d]�� ° ���� ����\n\n", key, cnt + 1);
		Order(n->right, key);
	}
	return 1; // ���� �� ã�� ����
}

void Order_BST(int key)
{
	TNode *parent = NULL;
	TNode *node = root;

	while (node != NULL && node->data != key) {
		parent = node; //root�������� key�� ���� ���� �θ� ��带 ã��, ������ delete ����, ������ ���� �޽��� ���
		node = (key < node->data) ? node->left : node->right;
	}
	if (node == NULL) printf("### ��尡 �������� �ʽ��ϴ�. �ٽ� �õ����ּ���.\n\n");
}

//9) Children
//data ���� ���� ������ �ڽ� ���� ������ ����Ѵ�.
//�ڽ��� ���� ��� ���ٰ� ����Ѵ�.
void Children(TNode* n, int key)
{
	if (n == NULL) { // Ʈ���� ���� �� ��
		printf("### ����Ʈ���̰ų� ��尡 �������� �ʽ��ϴ�.\n\n");
		return;
	}
	if (key == n->data) { // key���� ����� �����Ϳ� ���ٸ�
		if (n->left == NULL && n->right == NULL) // �ڽ��� ���� ��
			printf("### Value [%d] => �ڽ� ��尡 �����ϴ�.\n\n", key);
		else if (n->left != NULL && n->right == NULL) // ���� �ڽ��� ���� ��
			printf("### Value [%d]�� �ڽ� => [%d],[NULL]\n\n", key, n->left->data);
		else if (n->left == NULL && n->right != NULL) // ������ �ڽ��� ���� ��
			printf("### Value [%d]�� �ڽ� => [NULL], [%d]\n\n", key, n->right->data);
		else // �ڽ��� �� �� ��
			printf("### Value [%d]�� �ڽ� => [%d],[%d]\n\n", key, n->left->data, n->right->data);
		return;
	}
	else if (key < n->data) Children(n->left, key); //Ű�� node�� �����ͺ��� ���� ��, ���� ����Ʈ���� �̵�	
	else Children(n->right, key); // Ű�� node�� �����ͺ��� Ŭ ��, ������ ����Ʈ���� �̵�

	return;
}

//10) Quit
//���α׷��� �����Ѵ�
void Quit()
{
	printf("### ByeBye~\n\n");
	exit(1);
}

// �ƽ�Ű�ڵ带 �˻��ؼ�, ���ڿ��� ���ڰ� �ƴ� ���� ���ԵǾ� ������ 1�� ��ȯ
int numck(char *ch)
{
	int str = strlen(ch); // ���ڿ��� ���� ����

	for (int i = 0; i < str; i++) { // ���ڿ��� ���̸�ŭ �ݺ�
		if ((0x30 <= ch[i] && ch[i] <= 0x39)) continue; //���ڿ��� 0~9�� ������ continue�Ѵ�
		else return 1; // ���ڿ��� 0~9 �̿ܿ� ���� ������ return 1
	}
	return 0; // ���ڸ� ���� �� return 0
}

// numck�� 1�� ��(���� ���� ��) ���� �޼��� ���, numck�� 0�� ��(������ ��) ���ڿ��� ������ ĳ�����Ͽ� ��ȯ
int check_error(char *str)
{
	if (numck(str)) {
		puts("���Ŀ� �����ʽ��ϴ�. �ٽ� �Է����ּ���."); return 0;
	}
	else return atoi(str); // ���ڿ��� ������ ��ȯ�Ͽ� ��ȯ
}