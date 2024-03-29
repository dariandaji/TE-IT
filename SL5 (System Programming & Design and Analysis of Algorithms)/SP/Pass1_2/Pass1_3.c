#include<stdio.h>
#include<stdlib.h> 
#include<string.h>

typedef struct
{
	int sno;
	char name[5];
	int add;
}symbol;

int sym_no=1;
int LC=100;
char *mot[10]={"MOVER","MOVEM","ADD","SUB"};
char *pot[10]={"START","END"};
char *DL[10]={"DS","DC"};
char *Reg[10]={"AREG","BREG","CREG","DREG"};
char *Sym[10];

void search(char*);
int search2(char*,int);
int main()
{
	FILE *fp;
	FILE *fp2;
	
	fp = fopen("Input.txt","r");
//	fp2 = fopen("IC.txt","a");
	char buff[50];
	int fcnt;
	char tk[4][10];
	int x;
	int i;
	while(1)
	{
		fgets(buff,50,fp);
	
		fcnt=sscanf(buff,"%s %s %s %s",tk[0],tk[1],tk[2],tk[3]);
		
		if(strcmp(tk[0],"START")==0)
		{
			if(fcnt==1)
				search(tk[0]);
			else if(fcnt==2)
			{
				LC = atoi(tk[1]);
				search(tk[0]);
				search(tk[1]);
			}
			fp2 = fopen("IC.txt","a");
			fprintf(fp2,"\x0A");
			fclose(fp2);
			continue;
		}
			
		if(strcmp(tk[0],"END")==0)
		{
			strcpy(tk[1],"");strcpy(tk[2],"");strcpy(tk[3],"");
			search2("LC",LC++);
			search(tk[0]);
			break;
		}
		//printf("%d %s %s %s %s",fcnt,tk1,tk2,tk3,tk4);
		
		fp2 = fopen("IC.txt","a");
		fprintf(fp2,"\x0A");
		search2("LC",LC++);
		
		for(i=0;i<fcnt;i++)
			search(tk[i]);
		
		fclose(fp2);
		
		if(strcmp(tk[1],"DS")==0)
			LC+=atoi(tk[2])-1;
		
	}
	fclose(fp);
	return 0;
}

void search(char token[10])
{
	int i;
	int flag=0; 
	if(token[0]>='0'&&token[0]<='9')
		flag=search2("C",atoi(token));
	
	for(i=0;i<4;i++)
		if(strcmp(token,mot[i])==0)
			flag=search2("IS",i);
	for(i=0;i<2;i++)		
		if(strcmp(token,pot[i])==0)
			flag=search2("AD",i);
	for(i=0;i<2;i++)		
		if(strcmp(token,DL[i])==0)
			flag=search2("DL",i);
		
	for(i=0;i<4;i++)
		if(strcmp(token,Reg[i])==0)
			flag=search2("R",i);
			
	if(flag==0)
	{
		FILE *fp3 = fopen("Symbol.txt","r");
		FILE *fp4 = fopen("Symbol.txt","a");
		symbol s;
		int flag2=0,cnt=0;
		char buff2[30];
		while(fscanf(fp3,"%d %s %d",&s.sno,s.name,&s.add)>0)
		{
			if(strcmp(s.name,token)==0)
			{
				flag2=1;
				s.add=LC;
				fseek(fp4,cnt*sizeof(s),SEEK_SET);
				fprintf(fp4,"->%d",LC);
				break;
			}
			cnt++;
		}

		if(flag2==0)
		{
			s.sno=sym_no++;
			strcpy(s.name,token);
			s.add=-1;
			fprintf(fp4,"%d %s %d\n",s.sno,s.name,s.add);
		}		
		fclose(fp3);
		fclose(fp4);
		search2("S",s.sno);
	}
}

int search2(char s[10],int i)
{
	FILE *fp2 = fopen("IC.txt","a");
    if(strcmp(s,"LC")==0)
    	fprintf(fp2,"%d ",i);
	else fprintf(fp2,"(%s,%d) ",s,i);
	fclose(fp2);
	return 1;
}
	
	
