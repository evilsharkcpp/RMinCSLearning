#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>

long long factorial(long long x)
{
    if (x>20) exit(1);
    if(x==0) return 1;
    return x * factorial(x-1);
}

double expTeilor(double x, double eps)
{
    double result = 0;
    int n = 0;
    for(int i = 0; i <= n++; i++)
    {
        double iter = pow(x,(double)i) / factorial(i);
        result += iter;
        if (fabs(iter) < fabs(eps)) break;
    }
    return result;
}

double function(double lambda, double k, double x, double eps)
{
    double exponent = 0;
    pid_t pid = fork();
    if (pid == 0)
    {
       exponent = expTeilor(-pow(x/lambda,k),eps);
       FILE *file = fopen("tmp","w");
       if(file == NULL)
       {
           fprintf(stderr,"Can't create file\n");
           exit(-1);
       }
       fprintf(file,"%.*lf",18,exponent);
       fclose(file);
       exit(0);
    }
    if (pid > 0)
    {
        double tmp = (k/lambda)*pow(x/lambda,k-1);
        int status;
        wait(&status);
        FILE *file = fopen("tmp","r");
        if(file != NULL && WEXITSTATUS(status)==0)
        {
            fscanf(file,"%lf",&exponent);
            fclose(file);
            remove("tmp");
            return tmp*exponent;
        }
        else
        {
            if (WEXITSTATUS(status)==1)
            {
                fprintf(stderr,"Impossible calculate factorial\n");
                exit(1);
            }
            fprintf(stderr,"Can't read file\n");
            exit(-1);
        }
    }
    
}

int main(int argc, char*argv[])
{
    if (argc != 5)
    {
        fprintf(stderr,"Invalid count of arguments\n");
        return -1;
    }
    double lambda, k, x, eps;
    lambda = strtod(argv[1],0);
    k = strtod(argv[2],0);
    x = strtod(argv[3],0);
    if (lambda <= 0 || k <= 0 || x < 0)
    {
        fprintf(stderr,"Some parameters negative or null\n");
        return -1;
    }
    eps = strtod(argv[4],0);
    printf("Result: %.*lf\n",18, function(lambda,k,x,eps));
    return 0;
}
