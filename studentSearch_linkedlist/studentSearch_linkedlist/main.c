#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkSearchHead.h"

int main(void) {
	struct Student *head = (struct Student*) malloc(sizeof(struct Student));
	struct Student *ptr;

	head->next = NULL; // �ʱⰪ���� NULL�� �Ҵ�
	ptr = head;

	readList(ptr);
	findList(ptr, head);

	ptr = head->next;
	while(ptr != NULL) {
		struct Student *next = ptr->next;  // �ӽ����� next �����͸� ����
		free(ptr);
		ptr = next;
	}
	free(head);
	// malloc �Լ��� �����Ѵ�.

	printf("\n");
	system("pause");
	return 0;
}

