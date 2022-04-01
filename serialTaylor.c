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
    return pow(angle, iteration) / factorialOf(iteration);
  }
  else
  {
    return pow(angle, iteration - 1) / factorialOf(iteration - 1);
  }
}

double cosX(int iteration, double angle)
{
  if (iteration <= 0)
    return 1;

  if (iteration % 2 == 0)
  {
    return pow(angle, iteration) / factorialOf(iteration);
  }
  else
  {
    return pow(angle, iteration - 1) / factorialOf(iteration - 1);
  }
}

double tanX(double sin, double cos)
{
  return sin / cos;
}

double angleToRad(double deg, double min, double sec)
{
  return deg + (min / 60.0) + (sec / 3600.0);
}

double getAngle(char *argv[])
{
  return angleToRad(atof(argv[1]), atof(argv[2]), atof(argv[3]));
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

  angle = angle * PI / 180.0;

  printf("Iterations: %d\n", iterations);
  printf("Angle: %0.2f\n", angle);
  printf("---------------\n");

  double sin = sinX(iterations, angle);
  double cos = cosX(iterations, angle);
  double tan = tanX(sin, cos);

  printf("Sin %0.50f\n", sin);
  printf("Cos %0.50f\n", cos);
  printf("Tan %0.2f\n", tan);

  clock_t end = clock();

  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

  printf("The elapsed time is %f seconds\n", time_spent);

  return 0;
}