// BST.cpp : main

#include "stdafx.h"

void main(void)
{
	init_tree(); // Ʈ�� �ʱ�ȭ
	int choice = 0; // menu ���� ����
	char temp[20] = ""; // �Է¹��� ���� �ӽ÷� ������ char�� ����
	int data = 0; // �Է°��� ��ȿ���� �� ���� ���� ����

	do {
		show_menu(); // �޴�ȣ��
		while (1) {
			printf("�� Menu Choice => ");
			rewind(stdin);
			scanf("%s", temp); //char�� �迭 temp�� �켱 �Է� �� ����
			data = check_error(temp); //temp���� ���ڸ� ��� �ִ��� Ȯ�� ��, ���ڸ� 1 �ƴϸ� 0(+���� �޽��� ��ȯ)
			if (data && data > 0 && data <= 11) { // �Է°�(check)�� ���ڸ� �ְ� ���� 1~11 ���� �� ��
				choice = data;
				break;
			}
		}

		switch (choice) {

		case 11: // 0�� ���ý� test data input
			Insert_BST(35); Insert_BST(18);
			Insert_BST(7); Insert_BST(26);
			Insert_BST(12); Insert_BST(3);
			Insert_BST(68); Insert_BST(22);
			Insert_BST(30); Insert_BST(99);
			printf("### �׽�Ʈ�� ������ �Է¿Ϸ�\n\n");
			break;

		case 1: // 1�� ���ý� data insert
			while (1) {
				puts("\n### 1~100���� �� ������ �Է����ּ���!");
				printf("���� Input data => ");
				rewind(stdin);
				scanf("%s", temp); //char�� �迭 temp�� �켱 �Է� �� ����
				data = check_error(temp); //temp���� ���ڸ� ��� �ִ��� Ȯ�� ��, ���ڸ� 1 �ƴϸ� 0(+���� �޽��� ��ȯ)
				if (data && data > 0 && data < 101) { // �Է°�(check)�� ���ڸ� �ְ� ���� 1~100 ���� �� ��
					Insert_BST(data); // Insert ����
					puts("");
					break;
				}
			}
			break;

		case 2: // 2�� ���ý� data delete
			while (1) {
				puts("\n### ������ ���� �Է����ּ���! (1~100)");
				printf("���� Input data => ");
				rewind(stdin);
				scanf("%s", temp); //char�� �迭 temp�� �켱 �Է� �� ����
				data = check_error(temp); //temp���� ���ڸ� ��� �ִ��� Ȯ�� ��, ���ڸ� 1 �ƴϸ� 0(+���� �޽��� ��ȯ)
				if (data && data > 0 && data < 101) { // �Է°�(check)�� ���ڸ� �ְ� ���� 1~100 ���� �� ��
					Delete_BST(data); // Delete ����
					break;
				}
			}
			break;

		case 3: // 3�� ���� �� ��� ���� count
			printf("### ����� ���� : [%d]��\n\n", Count(root));
			break;

		case 4: // 4�� ���� �� ���� ��ȸ
			printf("### Pre-Order : "); Preorder(root);
			puts("\n");
			break;

		case 5: // 5�� ���� �� Level_order
			printf("### Level-order : "); Level_order(root);
			puts("\n");
			break;

		case 6: // 6�� ���� �� Next
			while (1) {
				puts("\n### �Է°��� �� �ܰ� ū ���� ����մϴ�! (1~100)");
				printf("���� Input data => ");
				rewind(stdin);
				scanf("%s", temp); //char�� �迭 temp�� �켱 �Է� �� ����
				data = check_error(temp); //temp���� ���ڸ� ��� �ִ��� Ȯ�� ��, ���ڸ� 1 �ƴϸ� 0(+���� �޽��� ��ȯ)
				if (data && data > 0 && data < 101) { // �Է°�(check)�� ���ڸ� �ְ� ���� 1~100 ���� �� ��
					int ck = Next(root, data); // Next ����
					if (ck == 1) printf("### �˻��� ���� �������� �ʽ��ϴ�.\n\n");
					break;
				}
			}
			break;

		case 7: // 7�� ���� �� �ִ� �� ���
			if (Max(root) == 0) {
				printf("### ���� Ʈ�������� �õ��Դϴ�.\n\n");
				break;
			}
			printf("### ����� �ִ� �� : %d\n\n", Max(root));
			break;

		case 8: // 8�� ���� �� Order
			while (1) {
				puts("\n### �Է� ���� �� ��°�� ���� �������� �˷��帳�ϴ�! (1~100)");
				printf("���� Input data => ");
				rewind(stdin);
				scanf("%s", temp); //char�� �迭 temp�� �켱 �Է� �� ����
				data = check_error(temp); //temp���� ���ڸ� ��� �ִ��� Ȯ�� ��, ���ڸ� 1 �ƴϸ� 0(+���� �޽��� ��ȯ)
				if (data && data > 0 && data < 101) { // �Է°�(check)�� ���ڸ� �ְ� ���� 1~100 ���� �� ��
					int orderck = Order(root, data); // Order ����
					if (orderck == 0) printf("### ���� Ʈ�������� �õ��Դϴ�.\n\n");
					else Order_BST(data);
					break;
				}
			}
			break;

		case 9: // 9�� ���� �� Children
			while (1) {
				puts("\n### �ڽĳ�尡 �ñ��� ��带 �Է����ּ���! (1~100)");
				printf("���� Input data => ");
				rewind(stdin);
				scanf("%s", temp); //char�� �迭 temp�� �켱 �Է� �� ����
				data = check_error(temp); //temp���� ���ڸ� ��� �ִ��� Ȯ�� ��, ���ڸ� 1 �ƴϸ� 0(+���� �޽��� ��ȯ)
				if (data && data > 0 && data < 101) { // �Է°�(check)�� ���ڸ� �ְ� ���� 1~100 ���� �� ��
					Children(root, data); // Children ����
					break;
				}
			}
			break;

		case 10: // 10�� ���� �� ����
			Quit();
			break;
		}

	} while (choice != 10); // 10 �Է½� Quit

}
