//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>  // standard library 헤더 파일. malloc(), free() 등

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;   			// 노드의 값
	struct _listnode *next; // 다음 노드의 주소를 가리키는 포인터 변수 *next
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;   	 // 리스트의 길이
	ListNode *head;  // ListNode 타입의 *head 포인터 변수 선언
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
// *ll:  LinkedList타입의 구조체 포인터 변수.
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");     // 1: 정수 삽입
	printf("2: Print the index of the most recent input value:\n");  // 2: 가장 최근에 삽입한 값의 인덱스 출력
	printf("3: Print sorted linked list:\n");						 // 3: 정렬된 연결리스트 원소 출력
	printf("0: Quit:");												 // 0: 종료

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
// 1. 이미 존재하는 값은 삽입이 안됨.
// 2. 삽입한 원소의 인덱스를 반환해야됨.
int insertSortedLL(LinkedList *ll, int item)
{	
	// cur, pre, tmp 변수 필요
	ListNode *pre, *cur, *tmp;

	// 3번. 빈 리스트
	if (ll->head == NULL)
	{
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = item;
		ll->head->next = NULL;
		ll->size++;
		return 0;
	}
	
	int index = 1;
	pre = NULL;
	cur = ll->head;

	while (cur != NULL)
	{
		// 1. 이미 값이 존재할 경우
		if (cur->item == item)
			return -1;

		if (cur->item > item && pre == NULL)
		{
			tmp = cur;
			ll->head = malloc(sizeof(ListNode));
			ll->head->item = item;
			ll->head->next = tmp;
			ll->size ++;
			return 0;
		}
		else if (cur->item > item)
		{
			tmp = cur;
			pre->next = malloc(sizeof(ListNode));
			pre->next->item = item;
			pre->next->next = tmp;
			ll->size ++;
			return index;
		}
		else if (cur->item < item)
		{
			pre = cur;
			cur = cur->next;
			index ++;
		}
	}
	// cur == NULL인 경우, 즉 배열의 끝에 도달한 경우
	pre->next = malloc(sizeof(ListNode));
	pre->next->item = item;
	ll->size ++;
	index = ll->size - 1;
	
	return index;
}
///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	// 연결리스트 구조체 자체가 존재하지않을 경우
	if (ll == NULL)
		return;
	// cur(현재 노드)에 ll의 head노드의 주소를 저장
	cur = ll->head;

	// 연결리스트가 비어있을 경우
	if (cur == NULL)
		printf("Empty");
	// cur 가 NULL이 아니라면 반복
	while (cur != NULL)
	{	
		printf("%d ", cur->item);   // cur의 item 출력
		cur = cur->next;			// cur를 다음노드로 업데이트
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;   // cur에 ll의 첫 번째 노드 주소 할당
	ListNode *tmp;

	// cur가 NULL이 아닐때까지 반복
	while (cur != NULL){
		tmp = cur->next;	// curr(현재)의 다음 노드를 tmp(임시)에 저장
		free(cur);			// 현재 노드(curr)를 메모리에서 제거
		cur = tmp;			// 현재 노드를 다음 노드로 업데이트
	}
	// 노드들을 전부 메모리에서 제거 후 ll을 초기 상태로 변환
	ll->head = NULL;		
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;
	// ll이 비었거나, 인덱스값이 0보다 작은 값을 인자로 받았거나, 인덱스값이 연결리스트 길이 이상이거나
	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;  // 첫 번째 노드를 가리킴

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){		// index <= 0이 될때까지 반복. 즉, index가 0이 될 때 index에 해당하는 원소에 도달함.
		temp = temp->next;	// 다음 노드를 가리킴
		if (temp == NULL)	
			return NULL;
		index--;
	}

	return temp;  // index에 해당하는 원소의 노드 주소값 반환
}

int insertNode(LinkedList *ll, int index, int value){
	// ListNode 타입의 pre, cur 포인터 변수
	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	// head == NULL: 리스트가 비어있는 경우, index == 0: 첫 번째 원소에 삽입하려는 경우
	// ll은 구조체 포인터 변수
	if (ll->head == NULL || index == 0){
		cur = ll->head;  // cur = NULL
		ll->head = malloc(sizeof(ListNode)); // ListNode를 만들기 위한 메모리 공간 할당
		ll->head->item = value;   // head가 가리키는 노드의 item에 value 할당
		ll->head->next = cur;     // head가 가리키는 노드의 next값을 NULL로 설정. 첫 원소기 때문에 다음 노드를 가리킬 노드가 없음.
		ll->size++;			      // size +1
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	// pre = index(삽입하려는 자리) - 1의 노드 주소값이 NULL이 아니라면
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;  					   // cur는 pre다음 노드의 주소
		pre->next = malloc(sizeof(ListNode));  // pre 다음 노드 새로 생성
		pre->next->item = value;  			   // 생성한 노드에 값 대입
		pre->next->next = cur;				   // 생성한 노드의 다음 노드를 cur로 연결
		ll->size++;							   // size +1
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	// 첫 번째 노드를 삭제하는 경우
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	// 첫 번째 이후의 노드를 삭제하는 경우
	// pre=삭제하려는 노드의 전 노드
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;   		  // cur=삭제하려는 노드의 인덱스
		pre->next = cur->next;    // pre 다음 노드를 삭제하려는 노드의 다음 노드 인덱스로 업데이트
		free(cur);				  // 노드 삭제
		ll->size--;
		return 0;
	}

	return -1;
}
