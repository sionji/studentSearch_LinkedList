#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkSearchHead.h"

void readList(struct Student *ptr){
	FILE *flist;
	unsigned long int inputNum;	// student.txt 에서 입력받는 학번을 임시로 저장
	char *inputName = (char*) malloc(sizeof(char)*20); // 새 노드로 넘길 이름 포인터

	flist = fopen("student.txt", "r");
	while (!feof(flist))
	{
		fscanf_s(flist, "%lu %s", &inputNum, inputName, sizeof(char)*20);
		ptr = createNewStudent(ptr, inputName, inputNum);
	} /* student.txt 읽어서 linked list 구현 완료 */
	
	fclose(flist);
	return;
}

S_tudent *createNewStudent(struct Student *target, char *inputname, unsigned long int id)    // 타겟노드 뒤에 노드를 추가하는 함수
{
    struct Student *newNode = (struct Student*) malloc(sizeof(struct Student));    // 새 노드 생성
    newNode->next = target->next;    // 새 노드의 다음 노드에 타겟노드의 다음 노드를 지정
	strcpy(newNode->name, inputname);
	newNode->studentId = id;	// 데이터 저장

    target->next = newNode;    // *target 은 newNode의 주소를 가리킨다

	return newNode; // newNode 의 주소값을 반환
}

void findList(struct Student *ptr, struct Student *head){
	FILE *fin;
	int result;
	/* result는 계산 결과값이 0인지 0이 아닌지 T/F를 결정할때 사용한다. */
	unsigned long int inputNum; // 학번을 받았다면 여기에 저장
	char buf[20];	// input.txt 에서 입력받는 이름을 임시로 저장

	fin = fopen("input.txt", "r");
	
	while (!feof(fin))
	{
		ptr = head->next;  // ptr이 첫번째 노드를 가리킨다
		fscanf_s(fin, "%s", buf, sizeof(buf));
		if (buf[0] >= -1 && buf[0] <= 255) {
			inputNum = atoi(buf);
			while(ptr != NULL) {
				result = ptr->studentId - inputNum;
				if (!result) {
					printf("%s \n", ptr->name);
					break;
				} // 반복문을 이용해 같은 값을 찾은 후 이름을 출력
				ptr = ptr->next;
			}
			if(ptr==NULL) {
				printf("없는 학번입니다.\n");
			}
			// 다 찾고도 학번이 없다면 예외처리
		}
		else {			/* 입력받은 값이 숫자가 아닐 경우 */
			while(ptr != NULL) {
				result = strcmp(buf, ptr->name);
				/* buf[0]가 문자라면 문자열을 비교해서 일치하면 0, 불일치하면 1
				일치한다면 studentId를 출력하고 break; */
				if (!result) {
					printf("%d \n", ptr->studentId);
					break;
				}
				ptr = ptr->next;
			}
			if (ptr==NULL) {
				printf("없는 이름입니다.\n");
			}
			// 다 찾고도 이름이 없다면 예외처리
		}
	}
	/* output.txt와 cmd 에 출력 완료 */

	fclose(fin);
	// 파일 포인터를 닫는다.
}