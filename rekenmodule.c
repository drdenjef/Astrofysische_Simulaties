int ggd(int a, int b)
//iterative algorithm for computing the Largest Common Divisor of 2 positive integers 
{
	int temp;
	while (b != 0)
	{
		temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}
