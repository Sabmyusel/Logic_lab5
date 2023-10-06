#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

int size = 0;
int num = 0;

void gen(int **arr) {
	int temp = 0;
	srand(time(NULL));
	
	for(int i =0; i<size;i++)
		for (int k = i + 1; k < size; k++) {
			temp = rand() % 2;
			arr[i][k] = temp;
			arr[k][i] = temp;
		}
}

void print(int **graph, int **matr, int var) {

	if (var == 1) {// для матрицы смежности 
		printf("   ");
		for (int i = 0; i < size; i++)
			printf(" %d ", i + 1);
		printf("\n    ");
		for (int i = 0; i < size; i++)
			printf("-- ");

		for (int i = 0; i < size; i++) {
			printf("\n %d | ", i + 1);
			for (int k = 0; k < size; k++) {
				printf("%d  ", graph[i][k]);
			}
		}
	}
	if (var == 2) {// для матрицы инцидентности
		num = 0;
		for (int i = 0; i < size; i++)
			for (int k = i + 1; k < size; k++)
				if (graph[i][k] == 1)
					num++;

		for (int i = 0; i < size; i++)
			matr[i] = new int[num] {0};

		num = 0;
		for (int i = 0; i < size; i++)
			for (int k = i + 1; k < size; k++)
				if (graph[i][k] == 1) {
					matr[i][num] = 1;
					matr[k][num] = 1;
					num++;
				}

		printf("\n\n");
		for (int i = 0; i < size; i++) {
			printf("%d | ", i + 1);
			for (int k = 0; k < num; k++) {
				printf("%d  ", matr[i][k]);
			}
			printf("\n");
		}

	}
}

int count_size(int **graph, int var) {
	if (var == 1) {// для матрицы смежности 
		int count = 0;

		for (int i = 0; i < size; i++)
			for (int k = i + 1; k < size; k++)
				count += graph[i][k];
		return count;
	}
	if (var == 2)// для матрицы инцидентности
		return num;
}


void find(int **graph, int **matrix, int var) {
	int* arr = new int[size] {0};

	if (var == 1) {// для матрицы смежности 
		for (int i = 0; i < size; i++)
			for (int k = 0; k < size; k++)
				arr[i] += graph[i][k];
	}
	if (var == 2) {// для матрицы инцидентности
		for (int i = 0; i < size; i++)
			for (int k = 0; k < num; k++)
				arr[i] += matrix[i][k];
	}

	printf("\nИзолированные вершины : ");
	for (int i = 0; i < size; i++)
		if (arr[i] == 0)
			printf("%d, ", i + 1);

	printf("\nКонцевые вершины : ");
	for (int i = 0; i < size; i++)
		if (arr[i] == 1)
			printf("%d, ", i + 1);

	printf("\nДоминирующие вершины : ");
	for (int i = 0; i < size; i++)
		if (arr[i] == size - 1)
			printf("%d, ", i + 1);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int** graph;
	int** matrix2;
	int s = 0;


	while (1) {
		printf("Введите кол-во вершин графа: ");
		scanf("%d", &size);
		graph = new int* [size];
		for (int i = 0; i < size; i++)
			graph[i] = new int[size] {0};

		matrix2 = new int* [size];
		gen(graph);

		for (int var = 1; var <= 2; var++) {// var = 1 - работа с матрицей смежности
			print(graph, matrix2, var);// i = var - работа с матрицей инцидентности

			s = count_size(graph, var);
			printf("\n\nРазмер графа : %d\n", s);

			find(graph, matrix2, var);
			printf("\n");
		}

		system("pause");
		system("cls");
	}

	return 0;
}