// stdafx.h : ��� ����

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

// BST ����
typedef struct node {
	int data; // ��忡 ������ ������
	struct node* left; // ���� �ڽ� ����� ������
	struct node* right; // ������ �ڽ� ����� ������
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

//Lever_order�� ���� ����ť �Լ� ����
extern TNode* data[MAX_QUEUE_SIZE];
extern int front; //����
extern int rear; // �Ĵ�

void init_queue();
int is_empty();
int is_full();
void enqueue(TNode* n);
TNode* dequeue();

//���ڿ� �������� �˻��ϴ� �Լ� ����
int numck(char *ch);
int check_error(char *str);