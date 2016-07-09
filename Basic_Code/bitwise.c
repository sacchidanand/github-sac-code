main(){
  int n = 0;

  printf("\n\nEnter n : ");
  scanf("%d",&n);
  printf("\nBefore n = %d\n\n", n);
  n = n & 0177;
  printf("\nAfter n = %d\n\n", n);

}
