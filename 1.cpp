#include <fstream>
#include<iostream>
#include<cmath>
using namespace std;
class SLAU
{
      double **a, *x, *p, eps, *b;
      int n;
public:
       void Solve()
       {
            SetData();
           	Method_by_Seidel();
            Display();
       }
       void SetData()
       {
            ifstream in("data.txt");
            cout<<"enter quantity of arguments and accuracy";
            cin>>n>>eps;
            a=new double*[n];
            b=new double[n];
            for(int i=0;i<n;i++)a[i]=new double[n];
            for(int i=0;i<n;i++)
            	{
            		for(int j=0;j<n;j++)in>>a[i][j];
            		in>>b[i];
				}
			in.close();
		}
       bool converge(double *currage, double *previous)
       {
            double norm = 0;
            for (int i = 0; i < n; i++)
                norm += (currage[i] - previous[i])*(currage[i] - previous[i]);
                return (sqrt(norm)<eps);
       }
       void Method_by_Seidel()
       {
       		x=new double[n];
       		for(int i=0;i<n;i++)x[i]=0;
            do
            {
               for (int i = 0; i < n; i++)
                    p[i] = x[i];
               for (int i = 0; i < n; i++)
                {
                    double var = 0;
                    for (int j = 0; j < i; j++)
                          var += (a[i][j] * x[j]);
                    for (int j = i + 1; j < n; j++)
                          var += (a[i][j] * p[j]);
                    x[i] = (b[i] - var) / a[i][i];
                }
            }
            while (!converge(x, p));
       }
       void Display()
       {
       		ofstream out("result.txt");
       		for(int i=0;i<n;i++)out<<x[i]<<'\t';
       		for(int i=0;i<n;i++)cout<<x[i]<<'\t';
       		out.close();
	   }
};
int main()
{
    SLAU a;
    a.Solve();
    return 0;
}
