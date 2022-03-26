#include  <iostream>
#include  <string>
#include  <string.h>
#include  <stdio.h>

using  namespace  std;

int Function1(int A[], int N)
{
	int ThisSum=0, MaxSum = 0;
	int i, j, k;
	for (i = 0; i < N; i++) {
		for (j = i; j < N; j++) {
			for (k = i; k <= j; k++)
				ThisSum += A[k];
			if (ThisSum > MaxSum)
				MaxSum = ThisSum;
		}
	}
	return MaxSum;
}

int Function2(int A[], int N)
{
	int ThisSum=0, MaxSum = 0;
	int i, j, k;
	for (i = 0; i < N; i++) {
		for (j = i; j < N; j++) {
			ThisSum += A[j];
			if (ThisSum > MaxSum)
				MaxSum = ThisSum;
		}
	}
	return MaxSum;
}

int Max3(int A, int B, int C) {
	return(A > B) ? ((A > C) ? A : C) : ((B > C) ? B : C);
}
int DivideAndConquer(int a[], int left, int right) {
	/*递归结束条件，子列只有一个数字*/
	if (left == right) {
		if (0 < a[left])
			return a[left];
		return 0;
	}
	/*分别找到左右最大子列和*/
	int center = (left + right)/2;
	int MaxLeftSum = DivideAndConquer(a, left, center);
	int MaxRightSum = DivideAndConquer(a, center + 1, right);

	/*再分别找最有跨界最大子列和*/
	int MaxLeftBorderSum = 0;
	int LeftBorderSum = 0;
	for (int i = center; i >= left; i--) {
		LeftBorderSum += a[i];
		if (MaxLeftBorderSum < LeftBorderSum)
			MaxLeftBorderSum = LeftBorderSum;
	}
	int MaxRightBorderSum = 0;
	int RightBorderSum = 0;
	for (int i = center + 1; i <= right; i++) {
		RightBorderSum += a[i];
		if (MaxRightBorderSum < RightBorderSum)
			MaxRightBorderSum = RightBorderSum;
	}
	/*最后返回分解的左边最大子列和，右边最大子列和，和跨界最大子列和三者中最大的数*/
	return Max3(MaxLeftSum, MaxRightSum, MaxRightBorderSum + MaxLeftBorderSum);
}
/*分而治之解法*/
int Function3(int A[],int N) {
	return DivideAndConquer(A, 0, N - 1);
}

/*最快的解法：在线处理*/
int Fuction4(int A[], int N) {
	int Max = 0;
	int TempMax = 0;
	for (int i = 0; i < N; i++) {
		TempMax += A[i];
		if (TempMax < 0) {
			TempMax = 0;
		}
		else if (Max < TempMax) {
			Max = TempMax;
		}
	}
	return Max;
}
int main() {
	int a[8] = { 4,-3,5,-2,-1,2,6,2 };
	int n = 8;
	cout << Function3(a, n);
}

