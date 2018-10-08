int main()
{
   int i,times;
   char a = 'A';
   scanf("%d",&times);
   i = 0;
   while (i <= times && i != 0)
   {
      ++i;
      printf("%d\n",i);
      printf("%d", a);
   }
   return 0;
}
