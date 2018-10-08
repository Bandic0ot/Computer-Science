#include<stdio.h>

int main()
{
   int i, j, times;
   scanf("%d", &times);
   i = 0;
   j = 10;
   while (i <= times)
   {
     while (j <= times)
     {
       printf("%j\n", j);
       j+=10;
     }

     if (i > 2) {
       printf("%d\n", i);
     }
     i ++;
   }

   return 0;
}
