int main()
{
   int i,times;
   scanf("%d",&times);
   i = 0;
   do
   {
      i++;
      printf("%d\n",i);
      for(int j = 0; j < 10; j++) {
        printf("Hello.\n");
      }
   }
   while (i <= times);
   return 0;
}
