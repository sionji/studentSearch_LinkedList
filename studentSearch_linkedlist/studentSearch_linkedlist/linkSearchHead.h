typedef struct Student{
	char name[20];
	unsigned long int studentId;
	struct Student *next;
} S_tudent;

S_tudent *createNewStudent(struct Student *, char *, unsigned long int);
void readList(struct Student *);
void findList(struct Student *ptr, struct Student *headnode);