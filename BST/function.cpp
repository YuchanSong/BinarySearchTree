#include "stdafx.h"

//Binary Search Tree 함수 구현

TNode *root;

void init_tree() { root = NULL; }
int is_empty_tree() { return root == NULL; }
int cnt; // Order를 위한 전역변수 선언
int index;

//트리 데이터 생성
TNode* create_tree(int val, TNode* l, TNode* r)
{
	TNode* n = (TNode*)malloc(sizeof(TNode));
	n->data = val;
	n->left = l;
	n->right = r;
	return n;
}

//탐색 연산 구현
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
	if (n != NULL) return 1; // 원소가 있으면
	else return 0; // 없으면
}

//0) 메인 메뉴 출력 함수
void show_menu(void)
{
	cnt = -1;
	index = -2;
	puts("+----------------------------+");
	puts("|     Binary Search Tree     |");
	puts("+----------------------------+");
	puts("|        1)  노드 삽입       |");
	puts("|        2)  노드 삭제       |");
	puts("|        3)  노드 개수       |");
	puts("|        4)  전위 순회       |");
	puts("|        5)  레벨 순회       |");
	puts("|        6)  다음 값         |");
	puts("|        7)  최대 값         |");
	puts("|        8)  인덱스          |");
	puts("|        9)  자식 관계       |");
	puts("|       10)  종료            |");
	puts("+----------------------------+");
}

//1) Insert
//data를 읽어서 BST에 삽입한다.
//같은 data 값은 없다고 생각한다.(입력 값이 잘못 들어오면 error message를 출력하고 다시 입력받는다.)
int Insert(TNode *r, TNode *n) // r == root, n == new node
{
	if (r->data == n->data) return 0; //노드 n의 키가 루트 노드의 r의 키 값과 같으면 삽입하지 않고 0을 반환한다.
	else if (n->data < r->data) { //노드 n의 키가 루트 노드의 r의 키보다 클 때
		if (r->left == NULL) r->left = n; //루트 노드 r의 왼쪽 자식이 NULL 일 때, 루트 노드의 왼쪽에 노드 n을 대입한다.
		else Insert(r->left, n); //아니면 
	}
	else { //노드 n의 키가 루트 노드의 r의 키보다 작을 때
		if (r->right == NULL) r->right = n;
		else Insert(r->right, n);
	}
	return 1; // 삽입 성공
}

void Insert_BST(int key)
{
	TNode *n = create_tree(key, NULL, NULL);
	if (is_empty_tree()) { // BST가 공백상태이면
		root = n; // root로 설정
		printf("### [삽입 연산] : %d\n", key);
	}
	else if (search_BST(key) == 1 && Insert(root, n) == 0) { // key가 트리에 있고 중복삽입이면
		free(n); // 동적할당 해제
		printf("### 중복 삽입 오류입니다.\n");
	}
	else if (search_BST(key) == 1 && Insert(root, n) == 1) { // key가 트리에 있고 삽입에 성공하면(덮어쓴다)
		free(n); // 동적할당 해제
		printf("### 중복 삽입 오류입니다.\n");
	}
	else if (Insert(root, n) == 1) // insert에 성공하면
		printf("### [삽입 연산] : %d\n", key);
}

//2) Delete
//data 값을 삭제한다. data 값이 없을 경우 없다고 출력한다.
//case 1 : terminal node - 부모와 관계 끊기
//case 2 : 자식1 - 부모와 자식 연결
//case 3 : 자식2 - 왼쪽서브트리의 가장 큰값을 대치한다
void Delete(TNode *parent, TNode *node)
{
	TNode *child, *succ, *succp;

	//case1 (삭제하는 노드가 단말 노드인 경우)
	if (node->left == NULL && node->right == NULL) {
		if (parent == NULL) root = NULL; // node가 트리의 루트이면 트리의 루트가 NULL이 되고 공백트리가 됨
		else {
			if (parent->left == node) // node가 parent의 왼쪽 자식인가?
				parent->left = NULL; // Yes => parent의 왼쪽 자식의 노드를 NULL로 만듦
			else parent->right = NULL; // No => parent의 오른쪽 자식의 노드를 NULL로 만듦
		}
	}
	//case2 (삭제하는 노드에 왼쪽이나 오른쪽에 자식이 하나 있을 경우)
	else if (node->left == NULL || node->right == NULL) {
		child = (node->left != NULL) ? node->left : node->right; // child에 node의 왼쪽이나 오른쪽 자식 주소를 복사
		if (node == root) root = child; // node가 루트 노드이면 child가 루트노드가 됨
		else {
			if (parent->left == node) //node가 parent의 왼쪽 자식이면 
				parent->left = child; // child가 parent의 왼쪽 자식이 되고
			else parent->right = child; // node가 오른쪽 자식이면 child가 오른쪽 자식이 됨
		}
	}
	//case3 (삭제하는 노드가 두개의 자식이 있는 경우)
	else {
		//후계노드와 그의 부모노드 포인터 초기화
		succp = node;
		succ = node->left; //왼쪽 서브트리로 이동
		while (succ->right != NULL) { //왼쪽 서브트리의 가장 큰 노드(오른쪽으로 진행)를 찾아가서 대치시킴
			succp = succ;
			succ = succ->right;
		}
		if (succp->left == succ) //succ가 succp의 왼쪽 자식이면 
			succp->left = succ->right; //succp의 왼쪽 자식으로 succ의 오른쪽 자식을 연결함.
		else succp->right = succ->right; //그렇지 않으면 succp의 오른쪽 자식으로 succ의 오른쪽 자식을 연결함(succ는 왼쪽 자식x)

		node->data = succ->data; //삭제할 노드 node에 후계 노드 succ의 데이터 멤버를 복사함
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
		parent = node; //root에서부터 key를 가진 노드와 부모 노드를 찾고, 있으면 delete 연산, 없으면 오류 메시지 출력
		node = (key < node->data) ? node->left : node->right;
	}
	if (node == NULL) printf("### Delete할 값이 존재하지 않습니다. 다시 시도해주세요.\n\n");
	else {
		Delete(parent, node);
		printf("### [삭제 연산] : %d\n\n", key);
	}
}

//3) Count
//원소의 개수를 출력한다.
int Count(TNode *n)
{
	if (n == NULL) return 0; // 공백 트리이면 0반환
	return 1 + Count(n->left) + Count(n->right); // root + left subtree + right subtree
}

//4) Preorder
//전위 순회 원소 출력
void Preorder(TNode *n)
{
	if (n != NULL) {
		printf("[%d] ", n->data);
		Preorder(n->left);
		Preorder(n->right);
	}
}

//5-1) Level_orde를 위한 원형큐 구현
TNode* data[MAX_QUEUE_SIZE];
int front;
int rear;

void init_queue() { front = rear = 0; }
int is_empty() { return front == rear; }
int is_full() { return front == (rear + 1) % MAX_QUEUE_SIZE; }

//데이터 삽입 구현
void enqueue(TNode* n)
{
	if (is_full())
		printf("### 큐 포화 에러");
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	data[rear] = n;
}

//데이터 삭제 구현
TNode* dequeue()
{
	TNode *n = NULL;

	if (is_empty())
		printf("### 큐 공백 에러");
	front = (front + 1) % MAX_QUEUE_SIZE;
	n = data[front];
	return n;
}

//5-2) Level_order
//레벨 순회 방식으로 방문한 원소를 출력한다.
void Level_order(TNode *root) 
{
	TNode *n;

	if (root == NULL) return; // 공백 트리라면 return
	init_queue(); // 큐 초기화
	enqueue(root); // 큐에 root 삽입
	while (!is_empty()) { // 큐가 공백이 아닐동안 반복
		n = dequeue(); // 하나씩 dequeue해줌
		if (n != NULL) { // n이 NULL이 될 때까지 반복
			printf("[%d] ", n->data);
			enqueue(n->left);
			enqueue(n->right);
		}
	}
}

//6) Next
//data 값 보다 큰 값을 갖는 원소 중 가장 작은 값을 출력한다.
int Next(TNode *n, int key)
{
	int buf[20]; //data를 저장할 배열 buf
	TNode* r = root; //r의 노드 개수를 구하기 위해 선언

	if (n != NULL) {
		Next(n->left, key);
		cnt++; // 중위순회할때마다 cnt(index)를 증가시켜줌
		buf[cnt] = n->data; // 배열 buf에 0 ~ n까지 노드의 데이터를 삽입
		if (key == n->data && cnt != Count(r)-1) index = cnt; // 노드의 데이터와 key가 같고 최대값이 아니면 현재 cnt를 index에 저장
		else if (key == n->data && cnt == Count(r) - 1) { // 노드의 데이터와 key가 같고 최대값이면 cnt를 index에 저장 후 오류 출력
			index = cnt;
			printf("### 최대값입니다.\n\n");
		}
		else if (index == cnt - 1) printf("### Next Value [%d]\n\n", buf[index + 1]); // 한 단계 큰 값 출력
		Next(n->right, key);
	}
	if (index == -2) return 1; // 찾는 노드가 없으면 return 1
	return 2; // 일치하는 값을 찾았으면 return 2
}

//7) Max
//원소 중 가장 큰 원소 출력
int Max(TNode* n)
{
	if (n == NULL) return 0; // 공백 트리라면 0 반환
	if(n->right == NULL) return n->data; // 노드의 오른쪽이 가리키는 것이 NULL(가장 큰 값)일 때 data 반환
	return Max(n->right); // 가장 오른쪽으로 이동
}

//8) Order
//data 값을 갖는 원소가 몇 번째로 작은 원소인지 출력한다.
//원소가 없을 경우에는 0을 출력한다.
int Order(TNode* n, int key)
{
	if (n == NULL) return 0;
	if (n != NULL) {
		Order(n->left, key);
		cnt++; // 중위 순회 할때마다 cnt값 ++해줌
		if (key == n->data)
			printf("### Value [%d] => [%d]번 째 작은 원소\n\n", key, cnt + 1);
		Order(n->right, key);
	}
	return 1; // 작은 값 찾기 성공
}

void Order_BST(int key)
{
	TNode *parent = NULL;
	TNode *node = root;

	while (node != NULL && node->data != key) {
		parent = node; //root에서부터 key를 가진 노드와 부모 노드를 찾고, 있으면 delete 연산, 없으면 오류 메시지 출력
		node = (key < node->data) ? node->left : node->right;
	}
	if (node == NULL) printf("### 노드가 존재하지 않습니다. 다시 시도해주세요.\n\n");
}

//9) Children
//data 값을 갖는 원소의 자식 원소 값들을 출력한다.
//자식이 없을 경우 없다고 출력한다.
void Children(TNode* n, int key)
{
	if (n == NULL) { // 트리가 공백 일 때
		printf("### 공백트리이거나 노드가 존재하지 않습니다.\n\n");
		return;
	}
	if (key == n->data) { // key값과 노드의 데이터와 같다면
		if (n->left == NULL && n->right == NULL) // 자식이 없을 때
			printf("### Value [%d] => 자식 노드가 없습니다.\n\n", key);
		else if (n->left != NULL && n->right == NULL) // 왼쪽 자식이 있을 때
			printf("### Value [%d]의 자식 => [%d],[NULL]\n\n", key, n->left->data);
		else if (n->left == NULL && n->right != NULL) // 오른쪽 자식이 있을 때
			printf("### Value [%d]의 자식 => [NULL], [%d]\n\n", key, n->right->data);
		else // 자식이 둘 일 때
			printf("### Value [%d]의 자식 => [%d],[%d]\n\n", key, n->left->data, n->right->data);
		return;
	}
	else if (key < n->data) Children(n->left, key); //키가 node의 데이터보다 작을 때, 왼쪽 서브트리로 이동	
	else Children(n->right, key); // 키가 node의 데이터보다 클 때, 오른쪽 서브트리로 이동

	return;
}

//10) Quit
//프로그램을 종료한다
void Quit()
{
	printf("### ByeBye~\n\n");
	exit(1);
}

// 아스키코드를 검사해서, 문자열에 숫자가 아닌 값이 포함되어 있으면 1을 반환
int numck(char *ch)
{
	int str = strlen(ch); // 문자열의 길이 저장

	for (int i = 0; i < str; i++) { // 문자열의 길이만큼 반복
		if ((0x30 <= ch[i] && ch[i] <= 0x39)) continue; //문자열에 0~9만 있으면 continue한다
		else return 1; // 문자열에 0~9 이외에 값이 있으면 return 1
	}
	return 0; // 숫자만 있을 때 return 0
}

// numck가 1일 때(문자 값일 때) 오류 메세지 출력, numck이 0일 때(숫자일 때) 문자열을 정수로 캐스팅하여 반환
int check_error(char *str)
{
	if (numck(str)) {
		puts("형식에 맞지않습니다. 다시 입력해주세요."); return 0;
	}
	else return atoi(str); // 문자열을 정수로 변환하여 반환
}