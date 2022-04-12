#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

const double PI = 3.1415926535897932384626433832795;

double factorialOf(int n)
{
  return (n == 1 || n == 0) ? 1 : n * factorialOf(n - 1);
}

double sinX(int iteration, double angle)
{
  int n = 1;
  double result = 0.0;
  bool isSum = false;
  for (; n <= iteration; n++)
  {
    if (n % 2 == 1)
    {
      if (n == 1)
      {
        result += angle;
        isSum = false;
      }
      else
      {
        double step = pow(angle, n) / factorialOf(n);

        if (isSum)
        {
          result += step;
        }
        else
        {
          result -= step;
        }
        isSum = !isSum;
      }
    }
    n++;
  }
  return result;
}

double cosX(int iteration, double angle)
{
  int n = 0;
  double result = 0.0;
  bool isSum = false;
  for (; n <= iteration; n++)
  {
    if (n % 2 == 0)
    {
      if (n == 0)
      {
        result += 1;
      }
      else
      {
        double step = pow(angle, n) / factorialOf(n);
        if (isSum)
        {
          result += step;
        }
        else
        {
          result -= step;
        }
        isSum = !isSum;
      }
    }
    n++;
  }
  return result;
}

double tanX(double sin, double cos)
{
  return sin / cos;
}

double angleToRad(double angle)
{
  return angle * PI / 180.0;
}

double getAngle(char *argv[])
{

  double angle = atof(argv[1]) + (atof(argv[2]) / 60) + (atof(argv[3]) / 3600);

  return angle;
}

double ErrorSin(double sin, int interations)
{
  double error;

  if (interations == 10)
    error = fabs(874406.74 - sin);

  if (interations == 15)
    error = fabs(153697.26 - sin);

  return error;
}

double ErrorCos(double cos, int interations)
{
  double error;

  if (interations == 10)
    error = fabs(2573140.52 - cos);

  if (interations == 15)
    error = fabs(78965.25 - cos);

  return error;
}

double ErrorTg(double tan, int interations)
{
  double error;

  if (interations == 10)
    error = fabs(0.00593412 - tan);

  if (interations == 15)
    error = fabs(0.033964 - tan);

  return error;
}

int main(int argc, char *argv[])
{

  double time_spent = 0.0;

  clock_t begin = clock();

  if (argc != 5)
  {
    printf("Erro de argumentos!\nUSO: tangente gg mm ss angulo(em graus, minutos e segundos)\n");
    printf("Informe também o número de interações\n");
    printf("Exemplo prático de uso: tangente 30 15 55 10000\n");
    exit(1);
  }

  int iterations = (int)atoi(argv[4]);

  double angle = getAngle(argv);

  angle = angleToRad(angle);

  printf("Iterations: %d\n", iterations);
  printf("Angle: %0.6f\n", angle);
  printf("---------------\n");

  double sin = 0.0;
  double cos = 0.0;
  double tan = 0.0;

  int n = 0;
  bool isSum = false;

  for (n = 1; n <= iterations; n++)
  {
    if (n % 2 == 1)
    {
      if (n == 1)
      {
        sin += angle;
        isSum = false;
      }
      else
      {
        double step = pow(angle, n) / factorialOf(n);

        if (isSum)
        {
          sin += step;
        }
        else
        {
          sin -= step;
        }
        isSum = !isSum;
      }
    }
    n++;
  }

  isSum = false;
  for (n = 0; n <= iterations; n++)
  {
    if (n % 2 == 0)
    {
      if (n == 0)
      {
        cos += 1;
      }
      else
      {
        double step = pow(angle, n) / factorialOf(n);
        if (isSum)
        {
          cos += step;
        }
        else
        {
          cos -= step;
        }
        isSum = !isSum;
      }
    }
    n++;
  }

  tan = sin / cos;

  printf("Sin %0.6f\n", sin);
  printf("Cos %0.6f\n", cos);
  printf("Tan %0.6f\n", tan);

  clock_t end = clock();

  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

  printf("The elapsed time is %f seconds\n", time_spent);

  return 0;
}
