// stdafx.h : 헤더 파일

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

// BST 구현
typedef struct node {
	int data; // 노드에 저장할 데이터
	struct node* left; // 왼쪽 자식 노드의 포인터
	struct node* right; // 오른쪽 자식 노드의 포인터
} TNode;
extern TNode *root;

void init_tree();
int is_empty_tree();
TNode* search(TNode *n, int key);
int search_BST(int key);
void show_menu(void);
int Insert(TNode *r, TNode *n);
void Insert_BST(int key);
void Delete(TNode *parent, TNode *node);
void Delete_BST(int key);
int Count(TNode *n);
void Preorder(TNode *n);
void Level_order(TNode *root);
int Next(TNode *n, int data);
int Max(TNode* n);
int Order(TNode* n, int key);
void Order_BST(int key);
void Children(TNode* n, int key);
void Quit();

//Lever_order를 위한 원형큐 함수 정의
extern TNode* data[MAX_QUEUE_SIZE];
extern int front; //전단
extern int rear; // 후단

void init_queue();
int is_empty();
int is_full();
void enqueue(TNode* n);
TNode* dequeue();

//문자열 정수인지 검사하는 함수 정의
int numck(char *ch);
int check_error(char *str);