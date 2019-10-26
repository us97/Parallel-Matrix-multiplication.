#include<iostream>
#include<omp.h>
#include<stdlib.h>
#include<stdio.h>
#include<stddef.h>
using namespace std;
//OS Project Parallelism Matrix Multiplication Open_MP

void  main()
{
	int Mat1[10][10];
	int Mat2[10][10];
	int Mat3[10][10];
	for (int b=0;b<10;b++)
	{
		for (int b1 = 0; b1<10; b1++)
		{
			Mat1[b][b1] = b1 + 1;
			Mat2[b][b1] = b1 + 1;
			Mat3[b][b1] = b1 + 1;
		}
	}
	int TempMat[10][10];
	int MatFinal[10][10];
	int  threadnum = 0;
	
	omp_set_num_threads(10); 
	double starttime = omp_get_wtime();
	#pragma omp parallel shared(Mat1,Mat2,TempMat) private(threadnum)
	for (int i = 0; i < 10; i++)
	{
		int t = 0;
		threadnum = omp_get_thread_num();
		#pragma omp critical
		if (i == threadnum)
		{
			t++;
			cout << "Thread number: " << threadnum << "   i value: " << i <<"\t\t Parallel Test Var: " << t <<endl;			
			for (int j = 0; j < 10; j++)
			{
				int Sum = 0;
				for (int k = 0; k < 10; k++)
				{
					{						
						int Prody = Mat1[i][k] * Mat2[k][j];
						Sum = Sum + Prody;
						TempMat[i][j] = Sum;
					}
				}
				if (j == 9)
				{
					cout << "Row " << i << " Thread Number " << threadnum << "                 " << TempMat[i][j] << endl;
					for (int A = 0; A < 10; A++)
					{
						int Sum1 = 0;
						for (int n = 0; n < 10; n++)
						{
							int Prody2 = TempMat[i][n] * Mat3[n][A];
							Sum1 = Sum1 + Prody2;
							MatFinal[i][A] = Sum1;
						}
					}
				}
			}
		}

	}
	double endtime = omp_get_wtime();
	double time = endtime - starttime;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << MatFinal[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\n\n\n\n\nTotal time taken for parallel execution was :  " << time << endl;
	system("pause");
}