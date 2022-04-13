#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "mpi.h"

const double PI = 3.1415926535897932384626433832795;

double factorialOf(int n)
{
  return (n == 1 || n == 0) ? 1 : n * factorialOf(n - 1);
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

  if (argc != 5)
  {
    printf("Erro de argumentos!\nUSO: tangente gg mm ss angulo(em graus, minutos e segundos)\n");
    printf("Informe também o número de interações\n");
    printf("Exemplo prático de uso: tangente 30 15 55 10000\n");
    exit(1);
  }

  int rank, numprocs, index, iterations;
  double startTime = 0.0, endTime = 0.0, time_spent = 0.0;
  double angle = 0.0, sin = 0.0, cos = 0.0, tan = 0.0;
  double sum_sin = 0.0, sum_cos = 0.0;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0)
  {
    iterations = (int)atoi(argv[4]);

    angle = getAngle(argv);
    angle = angleToRad(angle);

    printf("\n----------------------------------------------------------------------\n");
    printf("--- Iterations: %d \n", iterations);
    printf("--- Angle: %0.6f \n", angle);
    printf("----------------------------------------------------------------------\n");

    startTime = MPI_Wtime();
  }

  bool isSum = false;

  MPI_Bcast(&iterations, 1, MPI_INT, 0, MPI_COMM_WORLD);

  isSum = false;

  for (index = rank + 1; index <= iterations; index++)
  {
    if (index % 2 == 1)
    {
      if (index == 1)
      {
        sin += angle;
        isSum = false;
      }
      else
      {
        double step = pow(angle, index) / factorialOf(index);

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
    index++;
  }

  isSum = false;
  for (index = rank; index <= iterations; index++)
  {
    if (index % 2 == 0)
    {
      if (index == 0)
      {
        cos += 1;
      }
      else
      {
        double step = pow(angle, index) / factorialOf(index);
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
    index++;
  }

  MPI_Reduce(&sin, &sum_sin, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&cos, &sum_cos, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  tan = sin / cos;

  if (rank == 0)
  {
    printf("--- Sin %0.50f \n", sin);
    printf("--- Cos %0.50f \n", cos);
    printf("--- Tan %0.50f \n", tan);

    endTime = MPI_Wtime();

    time_spent = fabs(endTime - startTime);

    printf("----------------------------------------------------------------------\n");
    printf("--- The elapsed time is %f seconds\n", time_spent);
    printf("----------------------------------------------------------------------\n");
  }
  MPI_Finalize();
  return 0;
}
