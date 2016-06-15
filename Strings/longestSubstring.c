#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void uniqueLongestSubString(char s[])
{
  int start=0, end=0, prevStart=0, prevEnd =0, c=0, len=0, flag = 0;
  int hash[27] = {0};  
  int maxLen = 0, currentLen=0;
  int i = 0, j = 0;

  for(i=0;i<27;i++)
    hash[i] = -1;

  len = strlen(s);
  while(end<len)
  {
    c = (s[end]>='a')?(s[end]-'a'):(s[end]-'A');

    while((end < len) && (hash[c] ==-1)){
      hash[c] = end++;
      c = (s[end]>='a')?(s[end]-'a'):(s[end]-'A');
      if(flag==0)
        flag=1;
    }

    //resetting HashSet
    if(flag==1)
    {
      currentLen = end-start;
      if(currentLen > maxLen)
      {
        maxLen = currentLen;
        prevStart = start;
        prevEnd = end-1;
      }
      
      if(end == len)
        break;
      start = end = hash[c] + 1;
      currentLen = 0;

      for(j=0;j<27;j++)
        hash[j] = -1;
      flag = 0;
    }

    end++;
  }

  printf("\n String=%s MaxLen=%d, start=%d, end =%d\n", s, maxLen, prevStart, prevEnd);
}


int main(){

  char *s[] =  {"abc",
    "aabc", 
    "abcc",
    "cabcde",
    "abcdec",
    "abcdefckjhgf",
    "aaaaaaaaaaa" };

  int i =0;
  for(i=0; i<7;i++)
  {
    uniqueLongestSubString(s[i]);
  }

  printf("\n");
  return 0;
}


