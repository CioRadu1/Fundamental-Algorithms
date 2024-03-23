/*
*  Ciobanu Radu-Rares
*  Grupa 30222
	*In acest cod am comparat algoritmii de parcurgere a unui arbore binar in varinata lor recursiva si cea iterativa, plus compararea algoritmilor Quicksort si HybridQuicksort
	
	 -in functia demo am demonstrat corectitudinea acestor algoritmi in complexitate O(n) pentru fiecare tip de parcurgere si de sortare

	 -functia grafice ne genereaza graficele si timpii de executie al algoritmilor quicksort si hybridquicksort cat si operatiile de afisare si de complexitate ale parcurgerilor (am facut daor inorder)
	    * pe aceste grafice putem observa ca operatiile de afisare sunt egale deoarece afiseaza un numar egal de noduri, iar in functiile de parcurgere am comentat linia in care afisez nodurile pentru a fi
		 mai frumos vizibil in consola
		* se poate observa ca algoritmul de parcurgere recursiv este mult mai eficient decat cel iterativ
		
	 -timpul de executie al algoritmului quicksort este considerabil mai mare decat cel al hybridQuicksort-ului

*/

#include <iostream>
#include <stdio.h>
#include <stack>
#include "Profiler.h"

using namespace std;

Profiler p("HibridSort");

#define MAX_INSERT 30
#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTE 100

typedef struct node {

	int key;
	int size;
	struct node* left;
	struct node* right;

}NodeT;

NodeT* create(int key) {

	NodeT* q = new NodeT;
	q->key = key;
	q->size = 1;
	q->left = NULL;
	q->right = NULL;

	return q;
}

NodeT* buildTree(NodeT* x, int left, int right) {

	if (left > right) {
		return NULL;
	}
	int mij = (right + left) / 2;
	NodeT* pr = create(mij);
	pr->left = buildTree(pr, left, mij - 1);
	pr->right = buildTree(pr, mij + 1, right);
	if (pr->right) {
		pr->size += pr->right->size;
	}
	if (pr->left) {
		pr->size += pr->left->size;
	}
	return pr;
}

void parcurgereInorderRecursiv(NodeT* x, int constanta) {
	Operation oppe = p.createOperation("OperatiiRecursiv", constanta);
	Operation afis = p.createOperation("OpAfisareRec", constanta);
	oppe.count();
	if (x != NULL) {
		parcurgereInorderRecursiv(x->left, constanta);
		afis.count();
		printf("%d ", x->key);
		parcurgereInorderRecursiv(x->right, constanta);
	}
}

void parcurgereInorderIterativ(NodeT* x, int constanta) {

	Operation oppe = p.createOperation("OperatiiIterativ", constanta);
	Operation afis = p.createOperation("OpAfisareIter", constanta);
	stack<NodeT*> stiva;
	NodeT* temp = x;
	while ((!stiva.empty()) || (x != NULL))
	{
		oppe.count();
		if (x != NULL)
		{
			stiva.push(x);
			oppe.count();
			x = x->left;
		}
		else
		{
			oppe.count();
			x = stiva.top();
			stiva.pop();
			afis.count();
			printf("%d ", x->key);
			oppe.count();
			x = x->right;
		}
	}
}

void parcurgerePreOrderRecursiv(NodeT* x, int constanta) {

	Operation attr = p.createOperation("AtribuiriR_Pre", constanta);
	Operation comp = p.createOperation("CompR_Pre", constanta);
	comp.count();
	if (x != NULL) {
		printf("%d ", x->key);
		parcurgerePreOrderRecursiv(x->left, constanta);
		parcurgerePreOrderRecursiv(x->right, constanta);
	}
}

void parcurgerePreOrderIterativ(NodeT* x, int constanta) {

	Operation attr = p.createOperation("AtribuiriR_Pre", constanta);
	Operation comp = p.createOperation("CompR_Pre", constanta);
	comp.count();
	if (x == NULL) {
		return;
	}
	stack<NodeT*> stiva;
	stiva.push(x);
	while (stiva.empty() == false) {
		comp.count();
		attr.count();
		NodeT* q = stiva.top();
		printf("%d ", q->key);
		stiva.pop();
		comp.count();
		if (q->right != NULL)
			stiva.push(q->right);
		comp.count();
		if (q->left != NULL)
			stiva.push(q->left);
	}
}

void parcurgerePostOrderRecursiv(NodeT* x) {
	if (x != NULL) {
		parcurgerePostOrderRecursiv(x->left);
		parcurgerePostOrderRecursiv(x->right);
		printf("%d ", x->key);
	}
}

void prettyBinar(NodeT* rad, int count) { 

	if (rad != NULL) {
		for (int i = 0; i < count; i++) {
			printf("   ");
		}
		printf("%d\n", rad->key);
		prettyBinar(rad->left, count + 1);
		prettyBinar(rad->right, count + 1);
	}
}

int partitionare1(int a[], int n, int m, int constanta) {

	Operation oppe = p.createOperation("QuickSort", constanta);
	int i = n - 1;
	for (int j = n; j < m; j++) {
		oppe.count();
		if (a[j] <= a[m]) {
			oppe.count(3);
			i++;
			swap(a[i], a[j]);
		}
	}
	oppe.count(3);
	swap(a[i + 1], a[m]);
	return i + 1;
}

void quickSort(int a[], int n, int m, int constanta) {
	if (n < m) {
		int q = partitionare1(a, n, m, constanta);
		quickSort(a, n, q - 1, constanta);
		quickSort(a, q + 1, m, constanta);
	}
}

void insertionSort(int v[],int n, int m, int constanta) {

	Operation opp = p.createOperation("HybridSort", constanta);
	int val = 0;
	int j = 0;
	for (int i = n + 1; i <= m; i++) {
		opp.count();
		val = v[i];
		j = i;
		while (j >= n + 1) {
			opp.count();
			if (v[j - 1] > val) {
				opp.count();
				v[j] = v[j - 1];
				j--;
			}
			else
				break;
		}
		opp.count();
		v[j] = val;
	}
}

int partitionare(int a[], int n, int m, int constanta) {

	Operation opp = p.createOperation("HybridSort", constanta);
	int i = n;
	for (int j = n; j < m; j++) {
		opp.count();
		if (a[j] <= a[m]) {
			opp.count(3);
			swap(a[i], a[j]);
			i++;
		}
	}
	opp.count(3);
	swap(a[i], a[m]);
	return i;
}

void hybridQuicksort(int a[], int n, int m, int constanta) {
	if (n < m) {
		if (m - n + 1 < MAX_INSERT) {
			insertionSort(a, n, m , constanta);
		}
		else {
			int q = partitionare(a, n, m, constanta); 
			hybridQuicksort(a, n, q - 1, constanta);
			hybridQuicksort(a, q + 1, m, constanta);
		} 
	}
}

void grafice() {
	NodeT* r = new NodeT;
	r = NULL;
	for (int n = 100; n <= MAX_SIZE; n += STEP_SIZE) {
		int m = n;
		r = NULL;
		r = buildTree(r, 1, n);
		parcurgereInorderRecursiv(r, m);
		parcurgereInorderIterativ(r, m);
	}

	for (int n = 100; n <= MAX_SIZE; n += STEP_SIZE) {

		p.startTimer("hybridQuicksort", n);
		for (int teste = 0; teste < NR_TESTE; teste++) {
			int a1[MAX_SIZE];
			FillRandomArray(a1, n, 10, 50000, true, UNSORTED);
			hybridQuicksort(a1, 0, n - 1, n);
		}
		p.stopTimer("hybridQuicksort", n);

		p.startTimer("quickSort", n);
		for (int teste = 0; teste < NR_TESTE; teste++) { 
			int a2[MAX_SIZE];
			FillRandomArray(a2, n, 10, 50000, true, UNSORTED);  
			quickSort(a2, 0, n - 1, n); 
		}
		p.stopTimer("quickSort", n); 

		for (int teste = 0; teste < NR_TESTE; teste++) {
			int a2[MAX_SIZE];
			FillRandomArray(a2, n, 10, 50000, true, UNSORTED);
			quickSort(a2, 0, n - 1, n);
		}

		for (int teste = 0; teste < NR_TESTE; teste++) {
			int a1[MAX_SIZE];
			FillRandomArray(a1, n, 10, 50000, true, UNSORTED);
			hybridQuicksort(a1, 0, n - 1, n);
		}
	}

	p.createGroup("Total", "HybridSort", "QuickSort");
	p.createGroup("TimpiDeExecutie", "quickSort", "hybridQuicksort");
	p.createGroup("OperatiiAfisare", "OpAfisareRec", "OpAfisareIter");
	p.createGroup("Parcurgeri", "OperatiiRecursiv", "OperatiiIterativ");

	p.showReport();
}

void demo() {

	int v[] = { 3, 5, 9, 2, 10, 15, 8, 99, 34, 64, 15, 63, 1 , 81, 76, 32, 100, 231, 19, 73, 1002,34, 812, 981, 432, 9810, 239, 431, 9182, 4231, 741, 918 };
	int l[] = { 7, 9, 1, 10, 24, 76, 12 };
	int h = sizeof(l) / sizeof(l[0]);
	int m = sizeof(v) / sizeof(v[0]);
	NodeT* rada = new NodeT;
	rada = NULL;
	int n = 11;
	rada = buildTree(rada, 1, n);
	prettyBinar(rada, 0);
	printf("\nParcurgere Inorder-Recursiv: ");
	parcurgereInorderRecursiv(rada, 0);
	printf("\nParcurgere Inorder-Iterativ: ");
	parcurgereInorderIterativ(rada, 0);
	puts("");
	printf("\nParcurgere PreOrder-Recursiv: ");
	parcurgerePreOrderRecursiv(rada, 0);
	printf("\nParcurgere PreOrder-Iterativ: ");
	parcurgerePreOrderIterativ(rada, 0);
	puts(""); 
	printf("\nParcurgere PostOrder-Recursiv: "); 
	parcurgerePostOrderRecursiv(rada); 
	puts("");
	printf("\nHybridOuicksortCuQuicksort: ");
	hybridQuicksort(v, 0, m - 1, 0);
	for (int i = 0; i < m; i++) {
		printf("%d ", v[i]);
	}
	puts("");
	printf("\nHybridOuicksortCuInsertionSort: ");
	hybridQuicksort(l, 0, h - 1, 0);
	for (int i = 0; i < h; i++) {
		printf("%d ", l[i]);
	}
	puts("");
}

int main() {

	demo();
	//grafice();
	return 0;
}