#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct details{
	int roll;
	char fname[20];
	char sname[20];
	char ic250g;
	char cs250g;
	char ee255g;
	char me251g;
	char ce250g;
	int ic250m;
	int cs250m;
	int ee255m;
	int me251m;
	int ce250m;
}det;
int main()
{
	det temp;
	int rolln;
	bool flag=false;
	FILE *fp;
	fp=fopen("master.txt","r");
	if(fp==NULL)
	{
		printf("Error 404 : File not found!\n");
		return -1;
	}
	printf("Enter the roll number of the student : ");
	scanf("%d",&rolln);
	do{
		fscanf(fp,"%d %s %s %d %c %d %c %d %c %d %c %d %c", &temp.roll,temp.fname,temp.sname,&temp.ic250m,&temp.ic250g,&temp.cs250m,&temp.cs250g,&temp.ee255m,&temp.ee255g,&temp.me251m,&temp.me251g,&temp.ce250m,&temp.ce250g);
		if(temp.roll==rolln)
			flag=true;
	}while(!flag);
	printf("\t\t\t\tIndian Institute of Technology Mandi\n\t\t\t\tAcademic Session : (Aug-Dec) 2016\n");
	printf("-------------------------------------------------------------------------------------------\n");
	printf("Name of the student : %s %s\nRoll Number        : %d\n",temp.fname,temp.sname,temp.roll);
	printf("-------------------------------------------------------------------------------------------\n");
	printf("Sr. No.\t|\tSubject Mode\t|\tMaximum\t|\tMarks Obtained\t|\tGrade\n");
	printf("[1]\t\tIC250\t\t\t100\t\t\t%d\t\t%c\n",temp.ic250m,temp.ic250g);
	printf("[2]\t\tCS250\t\t\t100\t\t\t%d\t\t%c\n",temp.cs250m,temp.cs250g);
	printf("[3]\t\tEE255\t\t\t100\t\t\t%d\t\t%c\n",temp.ee255m,temp.ee255g);
	printf("[4]\t\tME251\t\t\t100\t\t\t%d\t\t%c\n",temp.me251m,temp.me251g);
	printf("[5]\t\tCE250\t\t\t50\t\t\t%d\t\t%c\n",temp.ce250m,temp.ce250g);
	printf("-------------------------------------------------------------------------------------------\n");
	int sum=temp.ic250m+temp.cs250m+temp.ee255m+temp.me251m+temp.ce250m;
	double per=(sum/450.0)*100;
	printf("\t\t\t\tTotal 450\t\tTotal %d\n",sum);
	printf("\t\t\tPercentage %lf ",per);
	if(per<30.00)
		printf("Student failed\n");
	else if(per<45.00)
		printf("Student passed with Third division\n");
	else if(per<60.00)
		printf("Student passed with Second division\n");
	else
		printf("Student passed with First division\n");
	printf("-------------------------------------------------------------------------------------------\n");
	fclose(fp);
	return 0;
}