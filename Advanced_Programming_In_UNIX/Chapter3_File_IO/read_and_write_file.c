#include<stdio.h>
#define BUFF_SIZE 10


int main()
{
	int a;
	int buffer[BUFF_SIZE];

	// 0 is stdin
	while( ( a = read(0,buffer,BUFF_SIZE) )> 0 )
	{
		printf("--read %d bytes--",a);

		if( write(1,buffer,a) == -1 )
		{
			perror("");
		}
	}
}
