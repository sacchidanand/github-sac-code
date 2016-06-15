main(){
  int n = 0, i=0;

  printf("\n\nEnter n : ");
  scanf("%d",&n);
  int count =0;
  printf("\nBefore n = %d \t count =%d \n\n", n, count);
  
  for(i=0; n!=0; n>>=1){
    if(n & 1)
      count++;
  }

  printf("\nAfter n = %d \t count = %d\n\n", n,count);

}
