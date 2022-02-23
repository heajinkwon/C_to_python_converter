# C_to_python_converter
<h4> C언어(.c) --> Python 언어(.py) converter프로그램 개발 </h4>
<a> 변환을 원하는 c 소스파일을 converter.cpp 파일 내</a>
	'''c
	FILE* fp = fopen("c-program.c", "r");
	FILE* wp = fopen("py-program.py", "w+");
	'''
<a>c 소스파일명 입력 및 변환될 .py 파일명 입력</a>

// comment

void function1(int a, int b)
{
	print("int two parametric void function\n");
}

void function2(double ab, double bc)
{
	print("double two parametric void function\n");
}

void function3(float sdf, float wer, float xcv)
{
	print("float three parametric void function\n");
}

void function4()
{
	print("not parametric void function\n");
}

int main() {

	int a = 10;
	char b = 'A';
	float c = 5.0;
	double d = 12.8;
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	char name[4] = "my name is heajin kwon";
	boolean bol = true;
	boolean not_bol = false;
	scanf("%d", &a);
	scanf("%f", &c);
	scanf("%s", &name);
	print("Hello converter Program\n");
	printf("int value is %d", a);

	int k = 5;

	if (k % 2 == 0 && k < 10)
	{		
	printf("k is even number and one digit number k : %d",k); 
	}
	else if (k % 2 == 0 && k >= 10)
	{
	printf("k is even number and not one digit number k : %d ",k);
	}
	else if (k % 2 == 0 || k < 10)
	{
	printf("k is even number or one digit number k : %d",k);
	}
	else {
	printf("k : %d ",k);
	}

	for (int i = 2; i < 4; i++)
	{
	printf("%d",i);
	}

	for (int i = 2; i <= 4; i++)
	{
	printf("%d",i);
	}

	for (int i = 4; i > 2; i--)
	{
	printf("%d",i);
	}

	for (int i = 4; i >= 2; i--)
	{
	printf("%d",i);
	}

	return 0;
}
