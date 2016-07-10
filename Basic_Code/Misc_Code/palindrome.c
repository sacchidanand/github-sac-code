/*
all we need to do is to perform a modified palindrome checking.
consider the string "ABCDEFGHDCBAIJK"
*/

	maxlength=0;
	//have two positions start and end.
	for i=0 to A.length-1
	{
		start=i;
		end=A.length();
		length=0;
		if(A[start]==A[end])
		{
			while(A[start]==A[end] && start <=end)
			{
				increment length;
				start++;
				end--;
			}
			if(maxlength<length)
			{
				maxlength=length;
				// mark positions of the array.
			}
		}
	}
