#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#define MaxSize 100
#define j2h(x) (3.1415926*(x)/180.0)
using namespace std;

class Pre_treatment
{
public:
	Pre_treatment(char* s) {
		strcpy(infix, s);
	}
	int SkipNumber(char* s, int i);
	char* Sin_pre_treatment(char* ssin, int n, int end);
	char* Cos_pre_treatment(char* scos, int n, int end);
	char* Tan_pre_treatment(char* stan, int n, int end);
	char* Square_pre_treatment(char* ssquare, int n, int end);
	char* Sqroot_pre_treatment(char* ssqroot, int n, int end);
	char* CalculateSpecialChar(char* str);
private:
	char infix[100];//infix expression 中缀表达式
};

class Stack {
private:
	typedef struct CharStack				//字符栈 
	{
		char data[MaxSize];
		int top;
	}cStack;

	typedef struct DoubleStack				//数据栈 
	{
		double data[MaxSize];
		int top;
	}dStack;

	char s2[MaxSize];
public:
	Stack(char *s1) {
		Trans(s1, s2);
		cout << "计算结果为: " << Calculate(s2) << endl;
	}
	char* GetS2() {
		return s2;
	}
private:
	int Isop(char);				//当前扫描元素优先级 
	int Inop(char);				//栈顶元素优先级 

	void Initc(cStack*);				//初始化字符栈 
	int Pushc(cStack*, char);			//字符栈压栈 
	char Gettopc(cStack*);				//返回栈顶元素 
	char Popc(cStack*);				//出栈 

	void Initd(dStack*);				//初始化数据栈 
	int Pushd(dStack*, double);			//数据压栈 
	double Popd(dStack*);				//出栈 

	void Trans(char* s1, char* s2);		        //转化为后缀表达式 

	double Calculate(char* s2);			//后缀表达式求值 
};

class Format
{
private:
	char char_format[MaxSize];
	int num;
	int ws=0;
public:
	Format(char* str) {
		strcpy(char_format, str);
	}
	Format() {};
	void Show();
	void Choose(int choose);
	void DtoOB(int n);//transfer Decimal to Octal or binary
	void szsl(int n);//十进制转换成十六进制
	void OBtoD(int m);
};
int main() {
	char s1[MaxSize], stemp[MaxSize];
	cout << "请选择功能：" << endl;
	cout << "1.计算器 2.进制转换" << endl;
	int a;
	cin >> a;
	if (a == 1) {
		cout << "注：请用英文符号输入(尤其是括号),以“=”结束输入" << endl;
		cout << "s(90),c(-180),t(45),q(-2),r(4),分别表示" << endl;
		cout << "sin（90°），cos(-180°)，tan(45°)，(-2)的平方，4的平方" << endl;
		cout << "正确的例子：-5+(7-t(-135)*2)+20/r(4)=" << endl;
		cout << "错误的例子：2*(1+3）"<<endl;
		cout << "请输入计算表达式：" << endl;
		cin >> s1;
		cout << "该计算式转化四则运算表达式为：" << endl;
		Pre_treatment A(s1);
		strcpy(stemp, A.CalculateSpecialChar(s1));
		cout << stemp << endl;
		Stack B(stemp);
	}
	else if (a == 2) {
		Format C;
		C.Show();
		cout << "已退出" << endl;
	}
}


int Pre_treatment::SkipNumber(char* s, int i)
{
	int n = 0;
	i++;
	if (s[i++] == '(') {
		while (s[i++] != ')')
			n++;
		return n;
	}
	else {
		cout << "左括号匹配失败" << endl;
		return 0;
	}
}

char* Pre_treatment::Sin_pre_treatment(char* ssin, int n, int end)
{
	int i = n;
	int flag;
	int flag2 = 1;//sin（x）中的x是否为负数，默认为正数
	double sum = 0, divider = 1;
	i = i + 2;
	//判断sin(x)中的x是否为负数
	if (ssin[i] == '-'){
		i++;
		flag2 = 0;
	}
	//将s()字符串sin括号中的部分转化为小数

	while (i < end)
	{
		flag = 0;
		if (ssin[i] == '.')
		{
			flag = 1;
			i++;
			continue;
		}
		if (flag == 0)
		{
			sum = sum * 10 + (double)(ssin[i] - '0');
		}
		else {
			divider = divider * 10;
			sum = sum + ((double(ssin[i] - '0')) / divider);
		}
		i++;
	}
	//sum为负数的情况，并对sum做周期变换
	if (flag2 == 0) {
		sum = -sum;
		while (sum < 0)
			sum = sum + 360;
	}
	int j=0, k = 0;
	int flag1 = 0;
	double dsin;
	while (sum >= 360) {
		sum = sum - 360;
	}
	if (sum == 90)
		dsin = 1.0;
	else if (sum == 180 || sum == 0)
		dsin = 0.0;
	else if (sum == 270)
		dsin = -1.0;
	else
		dsin = sin(j2h(sum));
	char* s2 = (char*)malloc(10);
	if (dsin < 0) {
		s2[k++] = '(';
		s2[k++] = '-';
		flag1 = 1;
		dsin = -dsin;
	}
	j = i = dsin;
	//sin的值整数部分只有一位，所以不用把倒序换成正序
	if (j == 0) {
		s2[k++] = '0';
	}
	while (j > 0)
	{
		s2[k++] = j % 10 + '0';
		j /= 10;
	}
	if (dsin - i > 0)//如果dsin不是整数
	{
		s2[k++] = '.';//补上小数点
	}
	//d2是dsin的小数部分
	double d2 = dsin - i;
	while (d2 > (1e-10))//d2>0.0000000001
	{
		if (k >= 8)
			break;
		d2 *= 10;
		i = d2;
		s2[k++] = i + '0';
		d2 -= i;
	}
	//如果sin是负值
	if (flag1)
	{
		s2[k++] = ')';
	}
	s2[k] = '\0';
	return s2;
}

char* Pre_treatment::Cos_pre_treatment(char* scos, int n, int end)
{
	int i = n;
	int flag;
	double sum = 0, divider = 1;
	i = i + 2;
	//将s()字符串cos括号中的部分转化为小数
	//cos是偶函数，可以把负数当成正数处理
	if (scos[i] == '-') {
		i++;
	}
	while (i < end)
	{
		flag = 0;
		if (scos[i] == '.')
		{
			flag = 1;
			i++;
			continue;
		}
		if (flag == 0)
		{
			sum = sum * 10 + (double)(scos[i] - '0');
		}
		else {
			divider = divider * 10;
			sum = sum + ((double(scos[i] - '0')) / divider);
		}
		i++;
	}
	int j, k = 0;
	int flag1 = 0;
	double dcos;
	while (sum >= 360) {
		sum = sum - 360;
	}
	if (sum == 0)
		dcos = 1.0;
	else if (sum == 90)
		dcos = 0.0;
	else if (sum == 180)
		dcos = -1.0;
	else if (sum == 270)
		dcos = 0.0;
	else
		dcos = cos(j2h(sum));
	char* s2 = (char*)malloc(10);
	if (dcos < 0) {
		s2[k++] = '(';
		s2[k++] = '-';
		flag1 = 1;
		dcos = -dcos;
	}
	j = i = dcos;
	//cos的值整数部分只有一位，所以不用把倒序换成正序
	if (j == 0) {
		s2[k++] = '0';
	}
	while (j > 0)
	{
		s2[k++] = j % 10 + '0';
		j /= 10;
	}
	if (dcos - i > 0)//如果dcos不是整数
	{
		s2[k++] = '.';//补上小数点
	}
	double d2 = dcos - i;
	while (d2 > (1e-10))//d2>0.0000000001
	{
		if (k >= 8)
			break;
		d2 *= 10;
		i = d2;
		s2[k++] = i + '0';
		d2 -= i;
	}
	//如果cos是负值
	if (flag1)
	{
		s2[k++] = ')';
	}
	s2[k] = '\0';
	return s2;
}

char* Pre_treatment::Tan_pre_treatment(char* stan, int n, int end)
{
	int i = n;
	int flag;
	int flag2 = 1;//默认正数
	double sum = 0, divider = 1;
	i = i + 2;
	//将s()字符串tan括号中的部分转化为小数
	if (stan[i] == '-') {
		i++;
		flag2 = 0;
	}
	while (i < end)
	{
		flag = 0;
		if (stan[i] == '.')
		{
			flag = 1;
			i++;
			continue;
		}
		if (flag == 0)
		{
			sum = sum * 10 + (double)(stan[i] - '0');
		}
		else {
			divider = divider * 10;
			sum = sum + ((double(stan[i] - '0')) / divider);
		}
		i++;
	}
	int flag1 = 1;
	double dtan;
	if (flag2 == 0) {
		sum = -sum;
		while (sum < 0)
			sum = sum + 180;
	}
	while (sum >= 180) {
		sum = sum - 180;
	}
	if (sum == 0 || sum == 180)
		dtan = 0.0;
	else if (sum == 45)
		dtan = 1.0;
	else if (sum == 90) {
		cout << "tan≠kΠ/2（k∈N*）" << endl;
		cout << "无效输入";
		return NULL;
	}
	else if (sum == 135)
		dtan = -1.0;
	else
		dtan = sin(j2h(sum)) / cos(j2h(sum));
	char* s2 = (char*)malloc(10);
	if (dtan < 0) {
		flag1 = 0;
	}
	//字符串化为小数
	sprintf(s2, "%lf", dtan);
	//如果tan是负值
	if (flag1==0)
	{
		int k = 0;
		int s2len = strlen(s2);
		for (k = s2len - 1; k > 0; k--) {
			s2[k] = s2[k - 1];
		};
		s2[0] = '(';
		s2[s2len-1] = ')';
	}
	return s2;
}

char* Pre_treatment::Square_pre_treatment(char* ssquare, int n, int end)
{
	int i = n;
	int flag;
	double sum = 0, divider = 1;
	i = i + 2;
	//将s()字符串square括号中的部分转化为小数
	//因为负数的平方等于其绝对值的平方，所以可以跳过负号
	if (ssquare[i] == '-')
		i++;
	while (i < end)
	{
		flag = 0;
		if (ssquare[i] == '.')
		{
			flag = 1;
			i++;
			continue;
		}
		if (flag == 0)
		{
			sum = sum * 10 + (double)(ssquare[i] - '0');
		}
		else {
			divider = divider * 10;
			sum = sum + ((double(ssquare[i] - '0')) / divider);
		}
		i++;
	}
	double dsquare;
	dsquare = sum * sum;
	char* s2 = (char*)malloc(10);
	sprintf(s2, "%lf", dsquare);
	//dsquare不可能是负值
	return s2;
}

char* Pre_treatment::Sqroot_pre_treatment(char* ssqroot, int n, int end)
{
	int i = n;
	int flag;
	double sum = 0, divider = 1;
	i = i + 2;
	//将s()字符串sqroot括号中的部分转化为小数
	if (ssqroot[i] == '-') {
		cout << "无效输入！不能对负数开平方" << endl;
		i++;
		cout << "以下为忽略根号负数的结果" << endl;
	}
	while (i < end)
	{
		flag = 0;
		if (ssqroot[i] == '.')
		{
			flag = 1;
			i++;
			continue;
		}
		if (flag == 0)
		{
			sum = sum * 10 + (double)(ssqroot[i] - '0');
		}
		else {
			divider = divider * 10;
			sum = sum + ((double(ssqroot[i] - '0')) / divider);
		}
		i++;
	}
	double dsqroot;
	dsqroot = sqrt(sum);
	char* s2 = (char*)malloc(10);
	sprintf(s2, "%lf", dsqroot);
	//sqroot不可能是负值
	return s2;
}

char* Pre_treatment::CalculateSpecialChar(char* str)
{
	int i = 0;
	int j = 0;
	char* s1 = (char*)malloc(MaxSize);
	char sintemp[10], costemp[10], tantemp[10], squaretemp[10], sqroottemp[10];
	while (str[i] != '\0')
	{
		if ((str[i]) == 's')
		{
			strcpy(sintemp, Sin_pre_treatment(str, i, i + 2 + SkipNumber(str, i)));
			for (int i1 = 0; sintemp[i1] != '\0'; i1++) {
				s1[j] = sintemp[i1];
				j++;
			}
			i = i + SkipNumber(str, i) + 2;
		}
		else if (str[i] == 'c') {
			strcpy(costemp, Cos_pre_treatment(str, i, i + 2 + SkipNumber(str, i)));
			for (int i1 = 0; costemp[i1] != '\0'; i1++) {
				s1[j] = costemp[i1];
				j++;
			}
			i = i + SkipNumber(str, i) + 2;
		}
		else if (str[i] == 't') {
			strcpy(tantemp, Tan_pre_treatment(str, i, i + 2 + SkipNumber(str, i)));
			for (int i1 = 0; tantemp[i1] != '\0'; i1++) {
				s1[j] = tantemp[i1];
				j++;
			}
			i = i + SkipNumber(str, i) + 2;
		}
		else if (str[i] == 'q') {
			strcpy(squaretemp, Square_pre_treatment(str, i, i + 2 + SkipNumber(str, i)));
			for (int i1 = 0; squaretemp[i1] != '\0'; i1++) {
				s1[j] = squaretemp[i1];
				j++;
			}
			i = i + SkipNumber(str, i) + 2;
		}
		else if (str[i] == 'r') {
			strcpy(sqroottemp, Sqroot_pre_treatment(str, i, i + 2 + SkipNumber(str, i)));
			for (int i1 = 0; sqroottemp[i1] != '\0'; i1++) {
				s1[j] = sqroottemp[i1];
				j++;
			}
			i = i + SkipNumber(str, i) + 2;
		}
		else {
			s1[j] = str[i];
			j++;
		}
		i++;
	}
	j--;
	if (s1[j] == '=') {
		j++;
		s1[j] = '\0';
	}
	return s1;
}

void Stack::Initc(cStack* s1)
{
	s1->top = -1;
}

//字符栈压栈 
int Stack::Pushc(cStack* c1, char op)
{
	if (c1->top < MaxSize)
	{
		c1->data[++c1->top] = op;
		return 1;
	}
	else return 0;
}

//GET栈顶元素 
char Stack::Gettopc(cStack* c1)
{
	return c1->data[c1->top];
}

//字符栈出栈 
char Stack::Popc(cStack* c1)
{
	return c1->data[c1->top--];
}

//初始化数据栈 
void Stack::Initd(dStack* d1)
{
	d1->top = -1;
}

//数据栈压栈 
int Stack::Pushd(dStack* d1, double data)
{
	if (d1->top < MaxSize)
	{
		d1->data[++d1->top] = data;
		return 1;
	}
	else return 0;
}

//数据栈出栈 
double Stack::Popd(dStack* d1)
{
	return d1->data[d1->top--];
}

int Stack::Isop(char op)		//当前扫描运算符优先级
{
	switch (op)
	{
	case '(': return 6;
	case '+': case '-': return 2;
	case '*': case '/': return 4;
	}
}

int Stack::Inop(char op)		//当前扫描运算符优先级
{
	switch (op)
	{
	case '(': return 1;
	case '+': case '-': return 3;
	case '*': case '/': return 5;
	}
}

void Stack::Trans(char* s1, char* s2)
{
	int i = 0;
	int j = 0;
	int flag1 = -1;				//flag1为0表示上次输出为数字，flag1为1表示上次输出为字符
	int flag2 = -1; 				//flag2为0表示上次扫描为数字，flag为1表示上次扫描为运算符，用于区分数字后加空格
	cStack st1;				//暂放运算符 
	Initc(&st1);

	while (s1[i] != '\0')			//处理负数 
	{
		if (s1[0] == '-')			//第一位数字为负数时 
		{
			j = strlen(s1);
			while (j > 0)
			{
				s1[j + 5] = s1[j];
				j--;
			}
			s1[j++] = '(';
			s1[j++] = '0';
			s1[j++] = '-';
			s1[j++] = '1';
			s1[j++] = ')';
			s1[j] = '*';

		}
		if (s1[i] == '(' && s1[i + 1] == '-')	//非第一位负数时 
		{
			j = strlen(s1);
			while (j > i + 1)
			{
				s1[j + 5] = s1[j];
				j--;
			}
			s1[j++] = '(';
			s1[j++] = '0';
			s1[j++] = '-';
			s1[j++] = '1';
			s1[j++] = ')';
			s1[j] = '*';
			i = i + 5;
		}
		i++;
	}

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		if (flag1 == 0 && flag2 == 1)		//若上次的输出为数字，上次循环扫描为字符，则表示该数字串结束，则在数字后加空格区分 
		{
			s2[j++] = ' ';
			flag1 = 1;
		}
		if (s1[i] >= '0' && s1[i] <= '9' || s1[i] == '.')
		{
			s2[j++] = s1[i];
			flag2 = 0;
			flag1 = 0;
		}
		else if (s1[i] == '+' || s1[i] == '-' || s1[i] == '*' || s1[i] == '/' || s1[i] == '(')
		{
			flag2 = 1;
			if (st1.top<0 || Isop(s1[i])>Inop(Gettopc(&st1)))
			{
				Pushc(&st1, s1[i]);
			}
			else
			{
				while (st1.top >= 0 && Isop(s1[i]) < Inop(Gettopc(&st1)))		//当前扫描字符优先级不断与栈顶字符优先级比较，当前字符小于栈顶字符时退栈并输出 
				{
					s2[j++] = Popc(&st1);
					flag1 = 1;
				}
				if (st1.top<0 || Isop(s1[i])>Inop(Gettopc(&st1)))			//当前字符优先级大于栈顶优先级或栈空时当前字符压入字符栈内 
				{
					Pushc(&st1, s1[i]);
				}

			}
		}
		else if (s1[i] == ')')
		{
			flag2 = 1;
			if (Gettopc(&st1) != '(')		//若括号仅包含数字则没有输出运算符 
			{
				flag1 = 1;
			}
			while (Gettopc(&st1) != '(')
			{
				s2[j++] = Popc(&st1);
			}
			Popc(&st1);		//将'('出栈 
		}
		i++;
	}
	while (st1.top >= 0)		//将栈内剩余的运算符依次退栈输出 
	{
		s2[j++] = Popc(&st1);
	}
	s2[j] = '\0';
}

//表达式求值 
double Stack::Calculate(char* s1)
{
	int i = 0;
	int flag;				//char类型转换为double类型数据标记 
	double data1, data2;
	double sum;
	dStack ds1;
	Initd(&ds1);
	while (s1[i] != '\0')
	{
		if (s1[i] == '+' || s1[i] == '-' || s1[i] == '*' || s1[i] == '/')			//若为运算符获取栈顶两个元素进行计算 
		{
			data1 = Popd(&ds1);
			data2 = Popd(&ds1);
			if (s1[i] == '+') Pushd(&ds1, data2 + data1);
			else if (s1[i] == '-') Pushd(&ds1, data2 - data1);
			else if (s1[i] == '*') Pushd(&ds1, data2 * data1);
			else if (s1[i] == '/') Pushd(&ds1, data2 / data1);
		}
		else							//为数据时转化为double类型压栈 
		{
			flag = 0;					//初始化为0为整数部分标记，1为小数部分标记 
			sum = 0;
			double divider = 1;
			while (s1[i] != ' ' && s1[i] != '+' && s1[i] != '-' && s1[i] != '*' && s1[i] != '/')
			{
				if (s1[i] == '.')		//若有小数点，进入小数转化模式 
				{
					flag = 1;
					i++;
					continue;
				}
				if (flag == 0)
				{
					sum = sum * 10 + (double)(s1[i] - '0');
				}
				else
				{
					divider = divider * 10;
					sum = sum + ((double)(s1[i] - '0')) / divider;
				}
				i++;
			}
			if (s1[i] == '+' || s1[i] == '-' || s1[i] == '*' || s1[i] == '/') i--;	//转化成功一个数据，若下个字符为运算符，则i--，回到当前运算的数据位置 
			Pushd(&ds1, sum);
		}
		i++;		//i++准备下一个字符的转换 
	}
	return Popd(&ds1);
}

void Format::Show()
{
	cout << "请输入需要的功能序号" << endl;
	cout << "1.十进制转二进制" << endl;
	cout << "2.十进制转八进制" << endl;
	cout << "3.十进制转十六进制" << endl;
	cout << "4.二进制转十进制" << endl;
	cout << "5.八进制转十进制" << endl;
	cout << "6.十六进制转十进制" << endl;
	cout << "0.退出" << endl;
	int n;
	cin >> n;
	Choose(n);
}

void Format::Choose(int choose)
{
	if (choose == 1)
	{
		cin >> num;
		DtoOB(2);
	}
	else if (choose == 2) {
		cin >> num;
		DtoOB(8);
	}
	else if (choose == 3)
	{
		cin >> num;
		szsl(16);
	}
	else if (choose == 4)
	{
		cout << "输入需要转换的进制数位数：";
		cin >> ws;
		OBtoD(2);
	}
	else if (choose == 5) {
		cout << "输入需要转换的进制数位数：";
		cin >> ws;
		OBtoD(16);
	}
	else if (choose == 6) {
		int p;
		printf("输入一个十六进制数：");
		scanf("%x", &p);
		printf("进制转换结果：%d", p);
	}
	else if (choose == 0)
		cout << "已退出" << endl;
}

void Format::DtoOB(int n)
{
	int c, i = 0;
	int a[100];
	while (num > 0)
	{
		c = (num % n);
		a[i] = c;
		num = num / n;
		i++;
	}
	cout << "进制转化结果是：";
	for (i--; i >= 0; i--)           //将数组倒序输出
		cout<<a[i];
	cout << endl;
}

void Format::szsl(int n)
{
	int c, i = 0;
	char a[100];
	while (num > 0)
	{
		c = (num % n);
		if (c < 10) {
			a[i] = c + 48;
		}
		else {
			if (c == 10) {
				c = 'A';
			}
			else if (c == 11) {
				c = 'B';
			}
			else if (c == 12) {
				c = 'C';
			}
			else if (c == 13) {
				c = 'D';
			}
			else if (c == 14) {
				c = 'E';
			}
			else if (c == 15) {
				c = 'F';
			}
			a[i] = c;
		}
		num = num / n;
		i++;
	}
	cout << "进制转换结果是：";
	for (i--; i >= 0; i--)           //将数组倒序输出
		cout << a[i];
	cout << endl;
}

void Format::OBtoD(int m)
{
	int i, sum = 0, e = 0, js = 0;
	int b[100];
	cout << "按位输入需要转换的进制数(以空格分开）：" << endl;
	for (i = 1; i <= ws; i++) {
		scanf("%d", &b[i]);
	}
	for (i = ws; i > 0; i--) {
		sum += b[i] * (int)(pow(m, e));
		e++;
	}
	for (i = 1; i <= ws; i++) {
		if (b[i] > m) {
			js++;
		}
	}
	if (js == 0) {
		cout << "进制转化结果是：" << sum << endl;
	}
	else {
		cout << "输入错误！";
	}
}
