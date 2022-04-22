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
	char infix[100];//infix expression ��׺���ʽ
};

class Stack {
private:
	typedef struct CharStack				//�ַ�ջ 
	{
		char data[MaxSize];
		int top;
	}cStack;

	typedef struct DoubleStack				//����ջ 
	{
		double data[MaxSize];
		int top;
	}dStack;

	char s2[MaxSize];
public:
	Stack(char *s1) {
		Trans(s1, s2);
		cout << "������Ϊ: " << Calculate(s2) << endl;
	}
	char* GetS2() {
		return s2;
	}
private:
	int Isop(char);				//��ǰɨ��Ԫ�����ȼ� 
	int Inop(char);				//ջ��Ԫ�����ȼ� 

	void Initc(cStack*);				//��ʼ���ַ�ջ 
	int Pushc(cStack*, char);			//�ַ�ջѹջ 
	char Gettopc(cStack*);				//����ջ��Ԫ�� 
	char Popc(cStack*);				//��ջ 

	void Initd(dStack*);				//��ʼ������ջ 
	int Pushd(dStack*, double);			//����ѹջ 
	double Popd(dStack*);				//��ջ 

	void Trans(char* s1, char* s2);		        //ת��Ϊ��׺���ʽ 

	double Calculate(char* s2);			//��׺���ʽ��ֵ 
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
	void szsl(int n);//ʮ����ת����ʮ������
	void OBtoD(int m);
};
int main() {
	char s1[MaxSize], stemp[MaxSize];
	cout << "��ѡ���ܣ�" << endl;
	cout << "1.������ 2.����ת��" << endl;
	int a;
	cin >> a;
	if (a == 1) {
		cout << "ע������Ӣ�ķ�������(����������),�ԡ�=����������" << endl;
		cout << "s(90),c(-180),t(45),q(-2),r(4),�ֱ��ʾ" << endl;
		cout << "sin��90�㣩��cos(-180��)��tan(45��)��(-2)��ƽ����4��ƽ��" << endl;
		cout << "��ȷ�����ӣ�-5+(7-t(-135)*2)+20/r(4)=" << endl;
		cout << "��������ӣ�2*(1+3��"<<endl;
		cout << "�����������ʽ��" << endl;
		cin >> s1;
		cout << "�ü���ʽת������������ʽΪ��" << endl;
		Pre_treatment A(s1);
		strcpy(stemp, A.CalculateSpecialChar(s1));
		cout << stemp << endl;
		Stack B(stemp);
	}
	else if (a == 2) {
		Format C;
		C.Show();
		cout << "���˳�" << endl;
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
		cout << "������ƥ��ʧ��" << endl;
		return 0;
	}
}

char* Pre_treatment::Sin_pre_treatment(char* ssin, int n, int end)
{
	int i = n;
	int flag;
	int flag2 = 1;//sin��x���е�x�Ƿ�Ϊ������Ĭ��Ϊ����
	double sum = 0, divider = 1;
	i = i + 2;
	//�ж�sin(x)�е�x�Ƿ�Ϊ����
	if (ssin[i] == '-'){
		i++;
		flag2 = 0;
	}
	//��s()�ַ���sin�����еĲ���ת��ΪС��

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
	//sumΪ���������������sum�����ڱ任
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
	//sin��ֵ��������ֻ��һλ�����Բ��ðѵ��򻻳�����
	if (j == 0) {
		s2[k++] = '0';
	}
	while (j > 0)
	{
		s2[k++] = j % 10 + '0';
		j /= 10;
	}
	if (dsin - i > 0)//���dsin��������
	{
		s2[k++] = '.';//����С����
	}
	//d2��dsin��С������
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
	//���sin�Ǹ�ֵ
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
	//��s()�ַ���cos�����еĲ���ת��ΪС��
	//cos��ż���������԰Ѹ���������������
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
	//cos��ֵ��������ֻ��һλ�����Բ��ðѵ��򻻳�����
	if (j == 0) {
		s2[k++] = '0';
	}
	while (j > 0)
	{
		s2[k++] = j % 10 + '0';
		j /= 10;
	}
	if (dcos - i > 0)//���dcos��������
	{
		s2[k++] = '.';//����С����
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
	//���cos�Ǹ�ֵ
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
	int flag2 = 1;//Ĭ������
	double sum = 0, divider = 1;
	i = i + 2;
	//��s()�ַ���tan�����еĲ���ת��ΪС��
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
		cout << "tan��k��/2��k��N*��" << endl;
		cout << "��Ч����";
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
	//�ַ�����ΪС��
	sprintf(s2, "%lf", dtan);
	//���tan�Ǹ�ֵ
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
	//��s()�ַ���square�����еĲ���ת��ΪС��
	//��Ϊ������ƽ�����������ֵ��ƽ�������Կ�����������
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
	//dsquare�������Ǹ�ֵ
	return s2;
}

char* Pre_treatment::Sqroot_pre_treatment(char* ssqroot, int n, int end)
{
	int i = n;
	int flag;
	double sum = 0, divider = 1;
	i = i + 2;
	//��s()�ַ���sqroot�����еĲ���ת��ΪС��
	if (ssqroot[i] == '-') {
		cout << "��Ч���룡���ܶԸ�����ƽ��" << endl;
		i++;
		cout << "����Ϊ���Ը��Ÿ����Ľ��" << endl;
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
	//sqroot�������Ǹ�ֵ
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

//�ַ�ջѹջ 
int Stack::Pushc(cStack* c1, char op)
{
	if (c1->top < MaxSize)
	{
		c1->data[++c1->top] = op;
		return 1;
	}
	else return 0;
}

//GETջ��Ԫ�� 
char Stack::Gettopc(cStack* c1)
{
	return c1->data[c1->top];
}

//�ַ�ջ��ջ 
char Stack::Popc(cStack* c1)
{
	return c1->data[c1->top--];
}

//��ʼ������ջ 
void Stack::Initd(dStack* d1)
{
	d1->top = -1;
}

//����ջѹջ 
int Stack::Pushd(dStack* d1, double data)
{
	if (d1->top < MaxSize)
	{
		d1->data[++d1->top] = data;
		return 1;
	}
	else return 0;
}

//����ջ��ջ 
double Stack::Popd(dStack* d1)
{
	return d1->data[d1->top--];
}

int Stack::Isop(char op)		//��ǰɨ����������ȼ�
{
	switch (op)
	{
	case '(': return 6;
	case '+': case '-': return 2;
	case '*': case '/': return 4;
	}
}

int Stack::Inop(char op)		//��ǰɨ����������ȼ�
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
	int flag1 = -1;				//flag1Ϊ0��ʾ�ϴ����Ϊ���֣�flag1Ϊ1��ʾ�ϴ����Ϊ�ַ�
	int flag2 = -1; 				//flag2Ϊ0��ʾ�ϴ�ɨ��Ϊ���֣�flagΪ1��ʾ�ϴ�ɨ��Ϊ������������������ֺ�ӿո�
	cStack st1;				//�ݷ������ 
	Initc(&st1);

	while (s1[i] != '\0')			//������ 
	{
		if (s1[0] == '-')			//��һλ����Ϊ����ʱ 
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
		if (s1[i] == '(' && s1[i + 1] == '-')	//�ǵ�һλ����ʱ 
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
		if (flag1 == 0 && flag2 == 1)		//���ϴε����Ϊ���֣��ϴ�ѭ��ɨ��Ϊ�ַ������ʾ�����ִ��������������ֺ�ӿո����� 
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
				while (st1.top >= 0 && Isop(s1[i]) < Inop(Gettopc(&st1)))		//��ǰɨ���ַ����ȼ�������ջ���ַ����ȼ��Ƚϣ���ǰ�ַ�С��ջ���ַ�ʱ��ջ����� 
				{
					s2[j++] = Popc(&st1);
					flag1 = 1;
				}
				if (st1.top<0 || Isop(s1[i])>Inop(Gettopc(&st1)))			//��ǰ�ַ����ȼ�����ջ�����ȼ���ջ��ʱ��ǰ�ַ�ѹ���ַ�ջ�� 
				{
					Pushc(&st1, s1[i]);
				}

			}
		}
		else if (s1[i] == ')')
		{
			flag2 = 1;
			if (Gettopc(&st1) != '(')		//�����Ž�����������û���������� 
			{
				flag1 = 1;
			}
			while (Gettopc(&st1) != '(')
			{
				s2[j++] = Popc(&st1);
			}
			Popc(&st1);		//��'('��ջ 
		}
		i++;
	}
	while (st1.top >= 0)		//��ջ��ʣ��������������ջ��� 
	{
		s2[j++] = Popc(&st1);
	}
	s2[j] = '\0';
}

//���ʽ��ֵ 
double Stack::Calculate(char* s1)
{
	int i = 0;
	int flag;				//char����ת��Ϊdouble�������ݱ�� 
	double data1, data2;
	double sum;
	dStack ds1;
	Initd(&ds1);
	while (s1[i] != '\0')
	{
		if (s1[i] == '+' || s1[i] == '-' || s1[i] == '*' || s1[i] == '/')			//��Ϊ�������ȡջ������Ԫ�ؽ��м��� 
		{
			data1 = Popd(&ds1);
			data2 = Popd(&ds1);
			if (s1[i] == '+') Pushd(&ds1, data2 + data1);
			else if (s1[i] == '-') Pushd(&ds1, data2 - data1);
			else if (s1[i] == '*') Pushd(&ds1, data2 * data1);
			else if (s1[i] == '/') Pushd(&ds1, data2 / data1);
		}
		else							//Ϊ����ʱת��Ϊdouble����ѹջ 
		{
			flag = 0;					//��ʼ��Ϊ0Ϊ�������ֱ�ǣ�1ΪС�����ֱ�� 
			sum = 0;
			double divider = 1;
			while (s1[i] != ' ' && s1[i] != '+' && s1[i] != '-' && s1[i] != '*' && s1[i] != '/')
			{
				if (s1[i] == '.')		//����С���㣬����С��ת��ģʽ 
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
			if (s1[i] == '+' || s1[i] == '-' || s1[i] == '*' || s1[i] == '/') i--;	//ת���ɹ�һ�����ݣ����¸��ַ�Ϊ���������i--���ص���ǰ���������λ�� 
			Pushd(&ds1, sum);
		}
		i++;		//i++׼����һ���ַ���ת�� 
	}
	return Popd(&ds1);
}

void Format::Show()
{
	cout << "��������Ҫ�Ĺ������" << endl;
	cout << "1.ʮ����ת������" << endl;
	cout << "2.ʮ����ת�˽���" << endl;
	cout << "3.ʮ����תʮ������" << endl;
	cout << "4.������תʮ����" << endl;
	cout << "5.�˽���תʮ����" << endl;
	cout << "6.ʮ������תʮ����" << endl;
	cout << "0.�˳�" << endl;
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
		cout << "������Ҫת���Ľ�����λ����";
		cin >> ws;
		OBtoD(2);
	}
	else if (choose == 5) {
		cout << "������Ҫת���Ľ�����λ����";
		cin >> ws;
		OBtoD(16);
	}
	else if (choose == 6) {
		int p;
		printf("����һ��ʮ����������");
		scanf("%x", &p);
		printf("����ת�������%d", p);
	}
	else if (choose == 0)
		cout << "���˳�" << endl;
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
	cout << "����ת������ǣ�";
	for (i--; i >= 0; i--)           //�����鵹�����
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
	cout << "����ת������ǣ�";
	for (i--; i >= 0; i--)           //�����鵹�����
		cout << a[i];
	cout << endl;
}

void Format::OBtoD(int m)
{
	int i, sum = 0, e = 0, js = 0;
	int b[100];
	cout << "��λ������Ҫת���Ľ�����(�Կո�ֿ�����" << endl;
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
		cout << "����ת������ǣ�" << sum << endl;
	}
	else {
		cout << "�������";
	}
}
