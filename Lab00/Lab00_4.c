/*input
sachin
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	printf("Please enter the string to be checked as a palindrome : \n");
	char s[100];
	scanf("%s",s);
	int c;
	for(c=0;s[c]!='\0';++c);
	int i;
	for(i=0;i<c/2;++i)
	{
		if(s[i]!=s[c-i-1])
			break;
	}
	if(i==c/2)
		printf("%s is a Palindrome string\n",s);
	else
		printf("%s is NOT a Palindrome string\n",s);
	return 0;
}