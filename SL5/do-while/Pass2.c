#include<stdio.h>
#include<stdlib.h> 
#include<string.h>

int main()
{
	FILE *fp,*fp2,*fp3;
	fp=fopen("IC.txt","r");
	fp2=fopen("Symbol.txt","r");
	
	fp3=fopen("TC.txt","w");
	
	char buff[50],buff2[20],tk[4][10];
	int fcnt,i,j;
	int LC=0;
	char ch;
	char sno[2],symbol[5],line[5];
	int sym_no;
	while(1)
	{
		fgets(buff,50,fp);
		fcnt = sscanf(buff,"%s %s %s %s",tk[0],tk[1],tk[2],tk[3]);
		
		if(strcmp(tk[0],"(AD,1)")==0)
			continue;
		else if(strcmp(tk[1],"(AD,2)")==0)
			break;
		else
		{

			if(tk[1][1]=='I' && tk[1][2]=='S')
			{
				fprintf(fp3,"%s) ",tk[0]);
							
				if(tk[1][5]!=')')	//to extract a 1 digit number or a 2 digit number?
					fprintf(fp3,"\t+%c%c",tk[1][4],tk[1][5]);
				else 
					fprintf(fp3,"\t+%c",tk[1][4]);
			}
	
			
			
			if(tk[2][1]=='R')
				fprintf(fp3,"\t%c",tk[2][3]);
			else fprintf(fp3,"\t%c",'0');
			
			if(tk[2][1]=='S')
			{
				if(tk[2][4]==')') sym_no=(int)(tk[2][3]-48);
				else
					sym_no =(int) ((tk[2][3]-48)*10 + (tk[2][4]-48));	//convert 2 digits to integer by multiplying ten's by 10 and adding to unit's place
				
				goto here;
			}
			else if(tk[3][1]=='S')
			{
				if(tk[3][4]==')') sym_no=(int)(tk[3][3]-48);
				else
					sym_no =(int) ((tk[3][3]-48)*10 + (tk[3][4]-48));	
				
		
	here:	
				for(i=0;i<sym_no;i++) 	//skip the contents of symbol table till correct symbol number is extracted
					fgets(buff2,20,fp2);
				
				sscanf(buff2,"%s %s %s",sno,symbol,line);
				fprintf(fp3,"\t%s",line);
			}	
		}
		fprintf(fp3,"\n");
	
	}
	fclose(fp);
	fclose(fp2);
	fclose(fp3);
	
	return 0;
}
