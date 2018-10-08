int main()
{
   int mark;
   char pass;
   char *comment;
   scanf("%d",&mark);
   scanf("%d",&comment);
   if (mark > 40)
      pass = 'y';
   else
      pass = 'n';
   printf("%d", comment);
   return 0;
}
