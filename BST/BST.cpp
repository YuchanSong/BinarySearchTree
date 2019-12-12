// BST.cpp : main

#include "stdafx.h"

void main(void)
{
	init_tree(); // 트리 초기화
	int choice = 0; // menu 구분 변수
	char temp[20] = ""; // 입력받은 값을 임시로 저장할 char형 변수
	int data = 0; // 입력값이 유효수일 때 값을 담을 변수

	do {
		show_menu(); // 메뉴호출
		while (1) {
			printf("▶ Menu Choice => ");
			rewind(stdin);
			scanf("%s", temp); //char형 배열 temp에 우선 입력 값 저장
			data = check_error(temp); //temp값에 숫자만 들어 있는지 확인 후, 숫자면 1 아니면 0(+오류 메시지 반환)
			if (data && data > 0 && data <= 11) { // 입력값(check)에 숫자만 있고 값이 1~11 사이 일 때
				choice = data;
				break;
			}
		}

		switch (choice) {

		case 11: // 0번 선택시 test data input
			Insert_BST(35); Insert_BST(18);
			Insert_BST(7); Insert_BST(26);
			Insert_BST(12); Insert_BST(3);
			Insert_BST(68); Insert_BST(22);
			Insert_BST(30); Insert_BST(99);
			printf("### 테스트용 데이터 입력완료\n\n");
			break;

		case 1: // 1번 선택시 data insert
			while (1) {
				puts("\n### 1~100까지 중 정수를 입력해주세요!");
				printf("▶▶ Input data => ");
				rewind(stdin);
				scanf("%s", temp); //char형 배열 temp에 우선 입력 값 저장
				data = check_error(temp); //temp값에 숫자만 들어 있는지 확인 후, 숫자면 1 아니면 0(+오류 메시지 반환)
				if (data && data > 0 && data < 101) { // 입력값(check)에 숫자만 있고 값이 1~100 사이 일 때
					Insert_BST(data); // Insert 실행
					puts("");
					break;
				}
			}
			break;

		case 2: // 2번 선택시 data delete
			while (1) {
				puts("\n### 삭제할 값을 입력해주세요! (1~100)");
				printf("▶▶ Input data => ");
				rewind(stdin);
				scanf("%s", temp); //char형 배열 temp에 우선 입력 값 저장
				data = check_error(temp); //temp값에 숫자만 들어 있는지 확인 후, 숫자면 1 아니면 0(+오류 메시지 반환)
				if (data && data > 0 && data < 101) { // 입력값(check)에 숫자만 있고 값이 1~100 사이 일 때
					Delete_BST(data); // Delete 실행
					break;
				}
			}
			break;

		case 3: // 3번 선택 시 노드 개수 count
			printf("### 노드의 개수 : [%d]개\n\n", Count(root));
			break;

		case 4: // 4번 선택 시 전위 순회
			printf("### Pre-Order : "); Preorder(root);
			puts("\n");
			break;

		case 5: // 5번 선택 시 Level_order
			printf("### Level-order : "); Level_order(root);
			puts("\n");
			break;

		case 6: // 6번 선택 시 Next
			while (1) {
				puts("\n### 입력값의 한 단계 큰 값을 출력합니다! (1~100)");
				printf("▶▶ Input data => ");
				rewind(stdin);
				scanf("%s", temp); //char형 배열 temp에 우선 입력 값 저장
				data = check_error(temp); //temp값에 숫자만 들어 있는지 확인 후, 숫자면 1 아니면 0(+오류 메시지 반환)
				if (data && data > 0 && data < 101) { // 입력값(check)에 숫자만 있고 값이 1~100 사이 일 때
					int ck = Next(root, data); // Next 실행
					if (ck == 1) printf("### 검색한 노드는 존재하지 않습니다.\n\n");
					break;
				}
			}
			break;

		case 7: // 7번 선택 시 최대 값 출력
			if (Max(root) == 0) {
				printf("### 공백 트리에서의 시도입니다.\n\n");
				break;
			}
			printf("### 노드의 최대 값 : %d\n\n", Max(root));
			break;

		case 8: // 8번 선택 시 Order
			while (1) {
				puts("\n### 입력 값이 몇 번째로 작은 원소인지 알려드립니다! (1~100)");
				printf("▶▶ Input data => ");
				rewind(stdin);
				scanf("%s", temp); //char형 배열 temp에 우선 입력 값 저장
				data = check_error(temp); //temp값에 숫자만 들어 있는지 확인 후, 숫자면 1 아니면 0(+오류 메시지 반환)
				if (data && data > 0 && data < 101) { // 입력값(check)에 숫자만 있고 값이 1~100 사이 일 때
					int orderck = Order(root, data); // Order 실행
					if (orderck == 0) printf("### 공백 트리에서의 시도입니다.\n\n");
					else Order_BST(data);
					break;
				}
			}
			break;

		case 9: // 9번 선택 시 Children
			while (1) {
				puts("\n### 자식노드가 궁금한 노드를 입력해주세요! (1~100)");
				printf("▶▶ Input data => ");
				rewind(stdin);
				scanf("%s", temp); //char형 배열 temp에 우선 입력 값 저장
				data = check_error(temp); //temp값에 숫자만 들어 있는지 확인 후, 숫자면 1 아니면 0(+오류 메시지 반환)
				if (data && data > 0 && data < 101) { // 입력값(check)에 숫자만 있고 값이 1~100 사이 일 때
					Children(root, data); // Children 실행
					break;
				}
			}
			break;

		case 10: // 10번 선택 시 종료
			Quit();
			break;
		}

	} while (choice != 10); // 10 입력시 Quit

}
