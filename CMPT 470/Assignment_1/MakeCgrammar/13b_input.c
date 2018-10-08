int main()
{
   char fruit;
   printf("Which one is your favourite fruit:\n");
   printf("a) Apples\n");
   printf("b) Bananas\n");
   printf("c) Cherries\n");
   printf("d) Secret Option\n");
   scanf("%c",&fruit);
   switch (fruit)
   {
      case 'a':
         printf("You like apples\n");
         break;
      case 'b':
         printf("You like bananas\n");
         break;
      case 'c':
         printf("You like cherries\n");
         break;
      case 'd':
         printf("You like tomatoes\n");
         printf("You also like carrots\n");
      default:
         printf("You entered an invalid choice\n");
   }

   if(fruit == 'a')
    printf("I also like apples");
   return 0;
}
