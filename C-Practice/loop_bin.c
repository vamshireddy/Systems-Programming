			#include <stdio.h>
			 
			 int main()
			 {
			     int i = 1024;
			     int count = 0;
			         for (; i; i >>= 1){
					count++;
					}
					printf("count is %d\n",count);
					return 0;
					     }
