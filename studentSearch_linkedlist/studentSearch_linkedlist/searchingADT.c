#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkSearchHead.h"

void readList(struct Student *ptr){
	FILE *flist;
	unsigned long int inputNum;	// student.txt ���� �Է¹޴� �й��� �ӽ÷� ����
	char *inputName = (char*) malloc(sizeof(char)*20); // �� ���� �ѱ� �̸� ������

	flist = fopen("student.txt", "r");
	while (!feof(flist))
	{
		fscanf_s(flist, "%lu %s", &inputNum, inputName, sizeof(char)*20);
		ptr = createNewStudent(ptr, inputName, inputNum);
	} /* student.txt �о linked list ���� �Ϸ� */
	
	fclose(flist);
	return;
}

S_tudent *createNewStudent(struct Student *target, char *inputname, unsigned long int id)    // Ÿ�ٳ�� �ڿ� ��带 �߰��ϴ� �Լ�
{
    struct Student *newNode = (struct Student*) malloc(sizeof(struct Student));    // �� ��� ����
    newNode->next = target->next;    // �� ����� ���� ��忡 Ÿ�ٳ���� ���� ��带 ����
	strcpy(newNode->name, inputname);
	newNode->studentId = id;	// ������ ����

    target->next = newNode;    // *target �� newNode�� �ּҸ� ����Ų��

	return newNode; // newNode �� �ּҰ��� ��ȯ
}

void findList(struct Student *ptr, struct Student *head){
	FILE *fin;
	int result;
	/* result�� ��� ������� 0���� 0�� �ƴ��� T/F�� �����Ҷ� ����Ѵ�. */
	unsigned long int inputNum; // �й��� �޾Ҵٸ� ���⿡ ����
	char buf[20];	// input.txt ���� �Է¹޴� �̸��� �ӽ÷� ����

	fin = fopen("input.txt", "r");
	
	while (!feof(fin))
	{
		ptr = head->next;  // ptr�� ù��° ��带 ����Ų��
		fscanf_s(fin, "%s", buf, sizeof(buf));
		if (buf[0] >= -1 && buf[0] <= 255) {
			inputNum = atoi(buf);
			while(ptr != NULL) {
				result = ptr->studentId - inputNum;
				if (!result) {
					printf("%s \n", ptr->name);
					break;
				} // �ݺ����� �̿��� ���� ���� ã�� �� �̸��� ���
				ptr = ptr->next;
			}
			if(ptr==NULL) {
				printf("���� �й��Դϴ�.\n");
			}
			// �� ã�� �й��� ���ٸ� ����ó��
		}
		else {			/* �Է¹��� ���� ���ڰ� �ƴ� ��� */
			while(ptr != NULL) {
				result = strcmp(buf, ptr->name);
				/* buf[0]�� ���ڶ�� ���ڿ��� ���ؼ� ��ġ�ϸ� 0, ����ġ�ϸ� 1
				��ġ�Ѵٸ� studentId�� ����ϰ� break; */
				if (!result) {
					printf("%d \n", ptr->studentId);
					break;
				}
				ptr = ptr->next;
			}
			if (ptr==NULL) {
				printf("���� �̸��Դϴ�.\n");
			}
			// �� ã�� �̸��� ���ٸ� ����ó��
		}
	}
	/* output.txt�� cmd �� ��� �Ϸ� */

	fclose(fin);
	// ���� �����͸� �ݴ´�.
}