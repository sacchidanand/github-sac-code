main(){
  int n = 0;

  printf("\n\nEnter n : ");
  scanf("%d",&n);
  int count =0;
  printf("\nBefore n = %d \t count =%d \n\n", n, count);
  while(n){
    n &= (n -1);
    count++;
  }
  printf("\nAfter n = %d \t count = %d\n\n", n,count);

}
