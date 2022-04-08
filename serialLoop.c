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

  // angle = angleToRad(angle);

  printf("Iterations: %d\n", iterations);
  printf("Angle: %0.2f\n", angle);
  printf("---------------\n");

  double sin = sinX(iterations, angle);
  double cos = cosX(iterations, angle);
  double tan = tanX(sin, cos);

  printf("Sin %0.3f\n", sin);
  printf("Cos %0.3f\n", cos);
  printf("Tan %0.3f\n", tan);

  printf("\n************ Diferenca/Erro ************\n");
  printf("\nError Sin %0.2f\n", ErrorSin(sin, iterations));
  printf("Error Cos %0.2f\n", ErrorSin(cos, iterations));
  printf("Error Tg %0.2f\n\n", ErrorTg(tan, iterations));

  clock_t end = clock();

  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

  printf("The elapsed time is %f seconds\n", time_spent);

  return 0;
}