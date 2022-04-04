#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const double PI = 3.1415926535897932384626433832795;

double factorialOf(int n)
{
  return (n == 1 || n == 0) ? 1 : n * factorialOf(n - 1);
}

double sinX(int iteration, double angle)
{
  if (iteration <= 0)
    return 1;

  if (iteration % 2 == 1)
  {
    double step = pow(angle, iteration) / factorialOf(iteration);
    double result = sinX(iteration - 1, angle) + step;
    // printf("SinX Iteration:%d: = %0.2f\n", iteration, step);
    // printf("Result: %0.2f\n\n", result);
    return result;
  }
  else
  {
    return sinX(iteration - 1, angle);
  }
}

double cosX(int iteration, double angle)
{
  if (iteration <= -1)
    return 0;

  if (iteration % 2 == 0)
  {
    double step = pow(angle, iteration) / factorialOf(iteration);
    double result = cosX(iteration - 1, angle) + step;
    // printf("CosX Iteration:%d: = %0.2f\n", iteration, step);
    // printf("Result: %0.2f\n\n", result);
    return result;
  }
  else
  {
    return cosX(iteration - 1, angle);
  }
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
  printf("Angle: %0.2f\n", angle);
  printf("---------------\n");

  double sin = sinX(iterations, angle);
  double cos = cosX(iterations, angle);
  double tan = tanX(sin, cos);

  printf("Sin %0.2f\n", sin);
  printf("Cos %0.2f\n", cos);
  printf("Tan %0.2f\n", tan);

  clock_t end = clock();

  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

  printf("The elapsed time is %f seconds\n", time_spent);

  return 0;
}