int main()
{
   char mark = 'A';
   int percent;
   scanf("%d", &percent);

   if (mark < 40)
      mark = 'F';

   printf("Mark: %d", mark);
   return 0;
}
