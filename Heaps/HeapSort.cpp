/*
*  Ciobanu Radu-Rares
*  Grupa 30222
	*In acest cod am testat cei 2 algoritmi de creeare a unui heap
	 dar si sortarea acestuia si am verificat complexitatea pentru fiecare, acestia fiind:

	* Bottom-up
	* Top-down
	* Heapsort

	* Pentru cazul in care ne este dat un vector nesortat (average case)
	   - algoritmul Bottom-up efectueaza cele mai putine operatii si drept urmare este mai eficient
	   - complexitatea metodei Bottom-up este de O(n) in timp ce metoda Top-down are complexitatea O(n*log n)

	* Pentru cazul in care ne este dat un vector sortat crescator (worst case)
		- algoritmul Bottom-up ramane cel mai eficient tot cu complexitatea O(n)
		- numarul operatiilor pentru metoda Top-down nu se modifica

*/

#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
using namespace std;

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTE 5

Profiler p("HeapSort");

void heapify(int a[], int index, int n) {

	Operation comparatii = p.createOperation("Comparatii_bottom_up", n);
	Operation atribuiri = p.createOperation("Atribuiri_bottom_up", n);

	int left = (2 * index) + 1;
	int right = (2 * index) + 2; 
	int max = index;
	 
	if (left < n) {
		comparatii.count();
		if (a[left] > a[index]) {
			max = left;
		}
	}
	 if (right < n) {
		 comparatii.count(); 
		if (a[right] > a[max]) { 
			max = right; 
		}
	}
	if (max != index)
	{
		atribuiri.count(3);
		swap(a[index], a[max]); 
		heapify(a, max, n); 
	}
   
}

void bottom_up(int a[], int n) {

	for (int i = ((n / 2) - 1); i >= 0; i--) {
		heapify(a, i, n); 
	}
}


//int extragere_heap_max(int a[], int &n) {
//
//	Operation atribuiri = p.createOperation("Atribuiri_extragere_max", n);
//
//	if (n < 0) {
//		printf("Underflow.\n");
//	}
//	int maxim = a[0];
//	atribuiri.count();
//	a[0] = a[n];
//	n = n - 1;
//	heapify(a, 0, n);
//	return maxim;
//}

void heap_sort(int a[], int n) {
 
	bottom_up(a, n);
	for (int i = n - 1; i > 0; i--) {

		swap(a[0], a[i]);
		heapify(a, 0, i);
	}
}

void top_down(int a[], int *n, int cheie, int lenght) {

	Operation comparatii = p.createOperation("Comparatii_top_down", lenght);
	Operation atribuiri = p.createOperation("Atribuiri_top_down", lenght);
	int index = *n;
	*n = *n + 1;
	atribuiri.count();
	a[index] = cheie; 
	while (index > 0) { 
		comparatii.count();
		if (a[index] > a[((index - 1) / 2)]) { 
			atribuiri.count(3);
			swap(a[index], a[((index - 1) / 2)]);  
		} 
		index = (index - 1) / 2; 
	}
}

void demo() {

	int v[] = {90, 1, 24, 100, 1, 23, 123};
	int n = sizeof(v)/sizeof(v[0]);
	int* v1 = (int*)malloc(n * sizeof(int));
	int m = 0;
	//heap_sort(v, n);
	/*for (int i = 0; i < n; i++) {
		top_down(v1, &m, v[i], 0);
	}
	top_down(v1, &m, 13, 0);*/
	heap_sort(v, n); 
	for (int i = 0; i < n; i++) {
		printf("%d ", v[i]);
	}
	//printf("\n");
	//for (int i = 0; i < m; i++) {
	//	printf("%d ", v1[i]); 
	//}
	/*printf("\n");
	for (int i = m-1; i >=0; i--) {
		printf("%d\n", extragere_heap_max(v1, i));
	}*/
}

void grafice(int order) { 

	int v1[MAX_SIZE];
	int v2[MAX_SIZE];
	int n;
	for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
		for (int test = 0; test < NR_TESTE; test++) {
			FillRandomArray(v1, n, 10, 10000, false, order);
			bottom_up(v1, n);
			int m = 0;
			for (int i = 0; i < n; i++) {
				top_down(v2, &m, v1[i], n);
			}
			

		}
	}
	
	p.divideValues("Comparatii_bottom_up", NR_TESTE);
	p.divideValues("Atribuiri_bottom_up", NR_TESTE);
	p.divideValues("Comparatii_top_down", NR_TESTE);
	p.divideValues("Atribuiri_top_down", NR_TESTE);

	p.addSeries("Bottom-up", "Atribuiri_bottom_up", "Comparatii_bottom_up");
	p.addSeries("Top-down", "Atribuiri_top_down", "Comparatii_top_down");

	p.createGroup("Comparatii", "Comparatii_top_down", "Comparatii_bottom_up");
	p.createGroup("Atribuiri", "Atribuiri_top_down", "Atribuiri_bottom_up");
	p.createGroup("Algoritmi", "Bottom-up", "Top-down");

}

void grafice_all() {

	grafice(UNSORTED);
	p.reset("Worst");
	grafice(ASCENDING);
	p.showReport();
}

int main()
{
	demo();
	//grafice_all();
	return 0;
}