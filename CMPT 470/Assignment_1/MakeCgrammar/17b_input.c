int main()
{
   int i, j;

   j = 10;
   i = 5 + j;
   while (i < 100)
   {
      i += 15;
      if (i == 5)
         break;
   }
   return 0;
}
