#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkSearchHead.h"

int main(void) {
	struct Student *head = (struct Student*) malloc(sizeof(struct Student));
	struct Student *ptr;

	head->next = NULL; // 초기값으로 NULL을 할당
	ptr = head;

	readList(ptr);
	findList(ptr, head);

	ptr = head->next;
	while(ptr != NULL) {
		struct Student *next = ptr->next;  // 임시적인 next 포인터를 생성
		free(ptr);
		ptr = next;
	}
	free(head);
	// malloc 함수를 해제한다.

	printf("\n");
	system("pause");
	return 0;
}

