#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int min(int a, int b, int c)
{
	int min;
	if (a < b || a < c) min = a;
	if (b < a || b < c) min = b;
	if (c < a || c < b) min = c;
	return min;
}
int max(int a, int b, int c)
{
	int max;
	if (a > b || a > c) max = a;
	if (b > a || b > c) max = b;
	if (c > a || c > b) max = c;
	return max;
}
int satisfies(int a, int b, int c)
{
	int modmin, sum2, check, i;
	if (a < 0 && b < 0 && c < 0) modmin = abs(min(a, b, c));
	if (a == modmin) sum2 = b + c;
	if (b == modmin) sum2 = a + c;
	if (c == modmin) sum2 = a + b;
	for (i = 0; i < 9; i++)
	{
		if (modmin == pow(2, i)) check = 1;
		else
			check = 0;
	}
	if (sum2 < -256 && check && modmin != 256 || sum2 > -256 && abs(sum2) > modmin) return 1;
	else
		return 0;
	if (a < 0 && b > 0 && c > 0)
	{
		if (a > -256) return 1;
		else
			return 0;
	}
	if (a > 0 && b < 0 && c > 0)
	{
		if (b > -256) return 1;
		else
			return 0;
	}
	if (a > 0 && b > 0 && c < 0)
	{
		if (c > -256) return 1;
		else
			return 0;
	}


	if (a < 0 && b < 0 && c > 0)
	{
		if (a+b > -256) return 1;
		else
			return 0;
	}
	if (a < 0 && b > 0 && c < 0)
	{
		if (a+c > -256) return 1;
		else
			return 0;
	}
	if (a > 0 && b < 0 && c < 0)
	{
		if (c+b > -256) return 1;
		else
			return 0;
	}
	if (a > 0 && b > 0 && c > 0)
	{
		if (max(a, b, c) + min(a, b, c) < 256) return 1;
		else
			return 0;
	}
    
}

