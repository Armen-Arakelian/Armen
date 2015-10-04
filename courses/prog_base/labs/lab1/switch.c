#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int exec(int op, int a, int b)
{
	char* dt;
	switch (op)
	{
	case 0:
		return -a;
		break;
	case 1:
		return a+b;
		break;
	case 2:
		return a-b;
		break;
	case 3:
		return a*b;
		break;
	case 4:
		return a/b;
		break;
	case 5:
		return abs(a);
		break;
	case 6:
		return pow(a, b);
		break;
	case 7:
	case 13:
	case 77:
		return a%b;
		break;
	case 8:
		if (a > b) return a;
		else
		return b;
		break;
	case 9:
		if (a < b) return a;
		else
			return b;
		break;
	case 10:
		switch (abs(b)%8)
		{
		case 0:
			dt = "char";
			break;
		case 1:
			dt = "signed char";
			break;
		case 2:
			dt = "short";
			break;
		case 3:
			dt = "unsigned int";
			break;
		case 4:
			dt = "long";
			break;
		case 5:
			dt = "unsigned long long";
			break;
		case 6:
			dt = "float";
			break;
		case 7:
			dt = "double";
			break;
		}
		return abs(a)*sizeof(dt);
		break;
	case 11:
		return (int) roundf(pow(a, b + 1) / M_PI);
		break;
	default:
		if (op < 100) return (op % (abs(a + 1)) + op % (abs(b + 1)));
		else
			return -1;
		break;
	}
}

