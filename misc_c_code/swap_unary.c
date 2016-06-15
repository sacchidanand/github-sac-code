main()
{

  int    	One = 20;
  int		Two = 12;

  printf("One = %d Two = %d\n", One, Two);

  One ^= Two;
  Two ^= One;
  One ^= Two;

  printf("One = %d Two = %d\n", One, Two);
}
