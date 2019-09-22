#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char filename[] = "file.txt";

typedef struct employee
{
	int empid;
	char name[30];
	int salary;
}emp;

int search(int);
void insert();
void display();
void delete(int);
void modify(int);

int main()
{
	int ch = 0;
	int fd1, fd2;
	int i,n;
	fd1 = open(filename, O_CREAT, 0777);
	close(fd1);
	do
	{
		printf("MENU\n"
			"1) Insert a record \n"
			"2) Display the file \n"
			"3) Search a record \n"
			"4) Modify a record \n"
			"5) Delete a record \n"
			"6) Exit \n");
		printf("\nEnter Your Choice::");
		scanf("%d", &ch);
		switch (ch)
		{
			case 1:
				printf("\nEnter no of records to be inserted : ");
				scanf("%d",&n);
				for(i=0;i<n;i++)
				{
					insert();
				}
				break;
			case 2:
				display();
				break;
			case 3:
				{
					int i;
					printf("Enter empid to search : ");
					scanf("%d", &i);
					int c = search(i);
					if(c == -1)
					{
						printf("Record not found");
					}
				}
				break;
			case 4:
				{
					int id;
					printf("Enter empid to modify : ");
					scanf("%d",  &id);
					modify(id);
				}
				break;
			case 5:
				{
					int id;
					printf("Enter empid to delete : ");
					scanf("%d",  &id);
					delete(id);
				}
				break;
				
			case 6:
				printf("Exit from program\n");
				break;
			default:
			printf("Enter a valid choice\n");
		}
	}while(ch <= 5);
	return 0;
}

int search(int id)
{
	emp e;
	int fd = open(filename, O_RDONLY);
	int count=0;
	while( read(fd, &e, sizeof(emp)) > 0)
	{
		if(e.empid == id)
		{
			close(fd);
			printf("Record is Present\n");
			printf("empid = %d\tname = %s\tsalary = %d\n", e.empid, e.name, e.salary);
			return count;
		}
		count++;
	}
	close(fd);
	return -1; 
}

void insert()
{	
	emp e;
	
	here:
	printf("Enter empid : ");
	scanf("%d", &e.empid);
	if(search(e.empid) >= 0)
	{
		printf("Record already exists\n");
		goto here;
	}
	
	printf("Enter name : ");
	scanf("%s", e.name);
	printf("Enter salary : ");
	scanf("%d", &e.salary);
	
	int fd = open(filename, O_WRONLY | O_APPEND);
	if( write(fd, &e, sizeof(e)) < 0)
	{
		printf("Didnt write to file");
	}
	close(fd);
}

void display()
{
	emp e;
	int fd = open(filename, O_RDONLY);
	
	printf("-----------------------------------------------------------------------\n");
	printf("| empid\t|\tname\t|\tsalary\t|\n");
	
	while( read(fd, &e, sizeof(emp)) > 0)
	{
		printf("| %d \t| %s \t| %d \t|\n", e.empid, e.name, e.salary);
	}
	printf("------------------------------------------------------------------------\n");
	close(fd);
}

void delete(int id)
{
	char tempFilename[] = "temp";
	int fd1 = open(filename, O_RDONLY);
	int fd2 = open(tempFilename, O_WRONLY | O_CREAT, 0777);
	
	emp e;
	
	if(search(id) == -1)
	{
		printf("Record not present\n");
		return;
	}
	
	while( read(fd1, &e, sizeof(emp)) > 0)
	{
		if(e.empid != id)
		{
			write(fd2, &e, sizeof(e));
		}
	}
	
	remove(filename);
	if(rename("temp", "file.txt") == -1)
	{
		printf("Couldn't rename temp file\n");
	}
	
	close(fd1);
	close(fd2);
	printf("Record deleted");
}

void modify(int id)
{
	int fd = open(filename, O_RDWR);
	int count = search(id); 	
	if(count < 0)
	{
		printf("Record not found\n");
		close(fd);
		return;
	}
	else
	{
		emp e;
		e.empid=id;
		printf("Enter name : ");
		scanf("%s", e.name);
		printf("Enter salary : ");
		scanf("%d", &e.salary);
		lseek(fd, count*sizeof(emp), SEEK_SET);
		if( write(fd, &e, sizeof(emp) ) < 0)
		{
			printf("Didnt write to file\n");
		}
		else
		{
			printf("Modified");
		}
		close(fd);
		return;
	}
}

//OUTPUT

/*
@ubuntu:~/SL2$ gcc OS-9.c
@ubuntu:~/SL2$ ./a.out
MENU
1) Insert a record 
2) Display the file 
3) Search a record 
4) Modify a record 
5) Delete a record 
6) Exit 

Enter Your Choice : 1

Enter no of records to be inserted : 3
Enter empid : 1
Enter name : Shivam
Enter salary : 58000
Enter empid : 2
Enter name : Mihir
Enter salary : 27000
Enter empid : 3
Enter name : Aayush
Enter salary : 36000

Enter Your Choice : 2
-----------------------------------------------------------------------
| empid	|	name	|	salary	|
| 1 	| Shivam 	| 58000 	|
| 2 	| Mihir 	| 27000 	|
| 3 	| Aayush	| 36000 	|
------------------------------------------------------------------------
Enter Your Choice : 3
Enter empid tp search : 1
Record Is Present
empid = 1	name = Shivam	salary = 58000

Enter Your Choice : 4
Enter empid to modify : 3
Record Is Present
empid = 3	name = Aayush	salary = 36000
Enter name : Gaurav
Enter salary : 8000 
Modified 
-----------------------------------------------------------------------
| empid	|	name	|	salary	|
| 1 	| Shivam 	| 58000 	|
| 2 	| Mihir 	| 27000 	|
| 3 	| Gaurav	| 8000  	|
------------------------------------------------------------------------

Enter Your Choice : 5
Enter empid to delete : 3
Record Is Present
empid = 3	name = Gaurav	salary = 8000
Record deleted
-----------------------------------------------------------------------
| empid	|	name	|	salary	|
| 1 	| Shivam 	| 58000 	|
| 2 	| Mihir 	| 27000 	|
------------------------------------------------------------------------
Enter Your Choice : 6
Exit from program
*/
