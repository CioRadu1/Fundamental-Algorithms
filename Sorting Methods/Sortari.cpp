/*
*  Ciobanu Radu-Rares 
*  Grupa 30222 
	*In acest cod am testat 3 algoritmi de sortare pentru a 
	 verifica si compara eficienta acestora si anume:

	* Bubble sort
	* Insertion sort
	* Selection sort 
	
	* Pentru cazul in care ne este dat un sir nesortat (average case)
	   - algoritmul selection sort efectueaza cele mai putine operatii si drept urmare este mai eficient
	   - complexitatea acestor algoritmi in acest caz este O(n^2)

	* Pentru cazul in care ne este dat un sir sortat crescator (best case)
       - algoritmul bubble sort efectueaza cele mai putine operatii iar acesta si selection sort nu efectuaeaza 
	     operatii de atribuire
	   - complexitatea bubble sort si insertion sort este de O(n) in timp ce selection sort are o 
	     complexitatea de O(n^2)

	* Pentru cazul in care ne este dat un sir sortat descrescator (worst case)    
		- algoritmul selection sort efectueaza cele mai putine operatii si este cel mai eficient 
		- toti algoritmii au o complexitate de O(n^2)
   
*/

#include <stdio.h>
#include "Profiler.h"
using namespace std;

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_OPERATII 10

Profiler p ("Sortari");

void bubble_sort (int v[], int n) {
	 
	Operation comp = p.createOperation("bubble_sort_comp", n);
	Operation atribuire = p.createOperation("bubble_sort_atribuiri", n);
	int k = 0;
	while (!k) {

		k = 1;
		
		for (int i = 0; i < n - 1; i++) {
			comp.count();
			if (v[i] > v[i + 1]) {
				atribuire.count(3);
				swap(v[i], v[i + 1]);
				k = 0;

			}

		}
		n--;

	}
}


void insertion_sort (int v[], int n) {

	Operation comp = p.createOperation("insertion_sort_comp", n);
	Operation atribuire = p.createOperation("insertion_sort_atribuiri", n);
	int val = 0;
	int j = 0;
	for (int i = 1; i < n; i++) {
		atribuire.count();
		val = v[i];
		j = i - 1;
		while (j >= 0) {
			comp.count();
			if (v[j] > val) {
				atribuire.count();
				v[j + 1] = v[j];
				j--;
			}
			else
				break;
	   }
		atribuire.count(); 
		v[j + 1] = val; 
	}
}

void selection_sort (int v[], int n) {

	Operation comp = p.createOperation("selection_sort_comp", n);
	Operation atribuire = p.createOperation("selection_sort_atribuiri", n);
	int minimul = 0;
	for (int i = 0; i < n-1; i++) {
		minimul = i;
		for (int j = i+1; j < n; j++){
			comp.count();
			if (v[j] > v[minimul]) {
				minimul = j;
			}
		}
		if (minimul != i) {
			atribuire.count(3);
			swap(v[i], v[minimul]);
		}
	}
}

void demo () {
	
	int v1[] = { 7, 2, 1, 5, 9, 2, 4 };
	int v2[] = { 7, 2, 1, 5, 9, 2, 4 };
	int v3[] = { 7, 2, 1, 5, 9, 2, 4 };
	int n = sizeof(v1) / sizeof(v1[0]) ;
	int m = sizeof(v1) / sizeof(v2[0]) ;
	int q = sizeof(v1) / sizeof(v3[0]) ;

	bubble_sort(v1,n);
	printf("bubble_sort:-> ");
	for (int i = 0; i < n; i++) {
		printf("%d ", v1[i]);
	}
	printf("\n");
	insertion_sort(v2, m);
	printf("insertion_sort:-> ");
	for (int i = 0; i < n; i++) {
		printf("%d ", v2[i]);
	}
	printf("\n");
	selection_sort(v3, q);
	printf("selection_sort:-> ");
	for (int i = 0; i < n; i++) {
		printf("%d ", v3[i]);
	}

}



void grafic (int order) {

	int v1 [MAX_SIZE];
	int v2[MAX_SIZE];
	int v3[MAX_SIZE];
	int n;
	for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
		for (int test = 0; test < NR_OPERATII; test++) {
			FillRandomArray(v1, n, 10, 10000, false, order);
			copy(v1, v1 + n, v2);
			copy(v1, v1 + n, v3); 
			bubble_sort(v1, n); 
			insertion_sort(v2, n);
			selection_sort(v3, n); 
		}
	}
	p.divideValues("bubble_sort_comp", NR_OPERATII);
	p.divideValues("bubble_sort_atribuiri", NR_OPERATII);
	p.addSeries("Bubble", "bubble_sort_comp", "bubble_sort_atribuiri");


	p.divideValues("insertion_sort_comp", NR_OPERATII);
	p.divideValues("insertion_sort_atribuiri", NR_OPERATII);
	p.addSeries("Insertion", "insertion_sort_comp", "insertion_sort_atribuiri");

	p.divideValues("selection_sort_comp", NR_OPERATII);
	p.divideValues("selection_sort_atribuiri", NR_OPERATII);
	p.addSeries("Selection", "selection_sort_comp", "selection_sort_atribuiri");

	p.createGroup("Algoritmi", "Bubble", "Insertion","Selection");

	if (order == UNSORTED) {
		p.createGroup("Atribuiri_selec", "selection_sort_atribuiri");
		p.createGroup("Comparari Ins", "insertion_sort_comp"); 
		p.createGroup("Comparari Bubb", "bubble_sort_comp"); 
		p.createGroup("Comparari Sel", "selection_sort_comp");
		
	}

	if (order == ASCENDING) { 
		
		p.createGroup("Comparari Bubble Insertion", "bubble_sort_comp", "insertion_sort_comp");
		p.createGroup("Bubble", "Bubble");
		p.createGroup("Insertion", "Insertion");
	}

	if (order == DESCENDING) { 
		p.createGroup("Comparari Ins", "insertion_sort_comp"); 
		p.createGroup("Comparari Bubb Sel", "bubble_sort_comp", "selection_sort_comp");
	}

	p.createGroup("Atribuiri", "bubble_sort_atribuiri", "insertion_sort_atribuiri","selection_sort_atribuiri");
	p.createGroup("Comparari", "bubble_sort_comp", "insertion_sort_comp","selection_sort_comp");

}

void grafic_all() {

	grafic(UNSORTED);
	p.reset("best");
	grafic(ASCENDING);
	p.reset("worst");
	grafic(DESCENDING);

	p.showReport();

}


int main() {

	demo();
	//grafic_all();
	return 0;
}
