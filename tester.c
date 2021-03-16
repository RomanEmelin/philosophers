#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int cnt = 50;
	while (cnt--)
		printf("%d\n", cnt);
	return (1);
}

