#include <stdio.h>
#include <stdlib.h>

char *test(void)
{
	static char* line;
	char *ret;
	if (!line)
	{
		line = (char*)malloc(sizeof(char) * 10);
		for (int i = 0; i < 10; i++)
			line[i] = 'a' + i;
		line[4] = 0;
		ret = line;
		line = &line[5];
		printf("line %s\n", line);
		return (ret);
	}
	printf("line %s\n", line);
	return line;
}

//gnl:
//if remainder contains \n replace it with \0, return and move pointer to beginning, othervise
//malloc a big buf of size 1000 + BUF_SIZE - 1000 % BUF_SIZE + sizeof remainder. remember size / BUF_SIZE
//copy remainder into this buf
//read into a big static bufer by parts with moving pointer
//if not enough place - double the buf size, copy and continue reading
//if met \n: replace it with \0 and return
//save the remainder pointer into static var

int main(void)
{
	char *ret = test();
	printf("%s\n", ret);
	free(ret);
	ret = test();
	printf("%s\n", ret);
	return 0;
}