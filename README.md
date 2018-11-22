# studentSearch_LinkedList  
 Take a .txt file containing the student number and name and save it as a linked list.  
 Then, when you input the name, the student number is printed out.  
   
 학번과 이름이 적힌 .txt 파일을 받아 linked list로 저장합니다.  
 그 후에 이름을 입력받으면 학번을 출력하고, 학번을 입력받으면 이름을 출력합니다.  
 
## 들어가기 전에
 정상적인 프로젝트의 실행을 위해, 프로젝트 또는 .exe파일과 동일한 위치에  
 student.txt 파일과 input.txt 파일이 있어야 합니다.  
 <br />
 student.txt 파일은 학생들의 학번과 이름이 적힌 파일입니다.  
 input.txt 파일은 내가 찾고 싶은 학번 또는 이름이 적힌 파일입니다.  
 <br />
 <br />
 
## Student 구조체  
 ```
 typedef struct Student{
	char name[20];
	unsigned long int studentId;
	struct Student *next;
} S_tudent;
```
 이름을 저장할 name 변수, 학번을 저장할 studentId 변수를 선언합니다.  
 linked list 자료구조를 활용하므로 다음 노드를 가리킬 next 포인터를 선언합니다.   
 <br />
 <br />
 
## main.c
```
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
```
 readList 함수에서 student.txt 파일을 읽어와 linked list 형태로 구현합니다.  
 findList 함수에서 input.txt 파일을 읽어와 linked list를 searching 합니다.  
 Searching 결과는 커맨드라인에 표시합니다.  
 그 후 모든 linked list의 노드들을 free 하고 프로그램을 종료합니다.  
 <br />
 <br />
 
## readList 함수
```
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
```
 student 구조체의 linked list의 헤드포인터를 입력받습니다.  
 student.txt 파일을 읽기전용("r") 으로 읽어서 end of file(feof)이 될 때 까지 읽어서  
 createNewStudent 함수를 이용해 linked list 형태로 저장합니다.  
 createNewStudent 함수는 새로 만든 노드의 주소를 반환합니다.  
 <br />
 <br />
 
## createNewStudent 함수
```
S_tudent *createNewStudent(struct Student *target, char *inputname, unsigned long int id)    // 타겟노드 뒤에 노드를 추가하는 함수
{
    struct Student *newNode = (struct Student*) malloc(sizeof(struct Student));    // 새 노드 생성
    newNode->next = target->next;    // 새 노드의 다음 노드에 타겟노드의 다음 노드를 지정
	strcpy(newNode->name, inputname);
	newNode->studentId = id;	// 데이터 저장

    target->next = newNode;    // *target 은 newNode의 주소를 가리킨다

	return newNode; // newNode 의 주소값을 반환
}
```
 타겟이 되는 노드와 이름, 학번을 입력받아 타겟노드 뒤에 노드를 linked list로 추가합니다.  
 새로 만든 노드의 주소를 반환합니다. 따라서 아래 코드에서 ptr 변수는 새로 만든 노드,    
 즉 linked list의 마지막 노드를 가리키는 것을 알 수 있습니다.  
 >ptr = createNewStudent(ptr, inputName, inputNum);  
 <br />
 <br />

## findList 함수
```
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
```
 이름 또는 학번이 적힌 input.txt 파일을 입력받습니다.  
 input.txt를 한 줄 씩 읽어와 만약 이름이 있다면 학번을 출력합니다.  
 (만약 일치하는 이름이 없다면 없는 학번이라고 출력합니다.)  
 만약 input.txt에서 학번을 읽었다면 이름을 출력합니다.  
 (역시 일치하는 학번이 없다면 없는 학번이라고 출력합니다.)  
 <br />
 <br />

## 실행 결과
![ssearch_result_linked](https://user-images.githubusercontent.com/41851641/48906254-39b65580-eea7-11e8-9c79-75d627b2368a.png)  
 student.txt 파일에 "홍길동" 이 있었기 때문에 해당하는 학번을 찾았습니다.  
 student.txt 파일에 "2017104321" 과 일치하는 학번이 있기 때문에 이름을 찾았습니다.  
 student.txt 파일에 "2014104654" 와 일치하는 학번이 없기 때문에 없는 학번이라고 알려줍니다.  

<br />
