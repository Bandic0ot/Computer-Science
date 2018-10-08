int main()
{
   int i = 0;
   int j = 0;
   for (; i < 10; i++) {
    printf("%d", i);
    for (; j < 10; j++) {
      printf("%d", j);
    }
   }
      
   return 0;
}
