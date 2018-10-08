#include<stdio.h>

int main()
{
   int i;
   scanf("%d", i);
   do
   {
      ++i;
      continue;
      printf("Hello\n");
   } while (i < 10);
   return 0;
}
