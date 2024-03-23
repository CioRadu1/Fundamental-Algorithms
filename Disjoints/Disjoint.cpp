/*
*  Ciobanu Radu-Rares
*  Grupa 30222
	*In acest cod am testat algoritmul Kruskal cu multimi disjuncte prin functiile:
		-MakeSet
		-Union
		-FindSet

	 - MakeSet are o complexitate de O(1) pentru fiecare nod apelat
	 - FindSet are o complexitate tot de O(1) iar la fel si Union
	 - pentru sortarea muchiilor am folosit algoritmul insertionSortRecursiv
	 - algoritmul kruskal are complexitatea O(n*logk) unde n este numarul de noduri si k este numarul de muchii 
	 - din grafice se poate observa ca avem o complexitate cat de cat liniara
*/

#include <stdio.h>
#include <iostream>
#include "Profiler.h"
using namespace std;

Profiler p("Djoints");

#define MAX_SIZE 10000
#define STEP_SIZE 100


typedef struct node {

	struct node *p;
	int key;
	int rank;
}NodeT;

typedef struct muchie {

	NodeT* emit;
	NodeT* primi;
	int flux;

}Muchie;

typedef struct graf{

	int nrMuchii;
	int nrNoduri;
	Muchie** muchii;


}Graf;

void insertionSortRecursiv(Muchie* v[], int n){

	if (n <= 1) {
		return;
	}
	insertionSortRecursiv(v, n - 1);
	Muchie* val = v[n - 1];
	int j = n - 2;
	while (j >= 0) {
		if (v[j]->flux > val->flux) {
			v[j + 1] = v[j];
		}
		else {
			break;
		}
		j--;
	}

	v[j + 1]= val;
}

NodeT* makeSet(int x, int consta) {
	Operation att = p.createOperation("makeSet", consta);
	NodeT* q = new NodeT;
	att.count(2);
	q->key = x;
	q->p = q;
	q->rank = 0;

	return q;
}

NodeT* gasesteSet(NodeT* x, int consta) {
	Operation set = p.createOperation("GasesteSet", consta);
	set.count();
	if (x->p != x) {
		set.count();
		x->p = gasesteSet(x->p, consta);
	}
	return x->p;
}

void leagaUnion(NodeT* t, NodeT* q, int consta) {
	Operation att = p.createOperation("Union", consta);

	att.count(2);
	NodeT* temp1 = gasesteSet(t,consta);
	NodeT* temp2 = gasesteSet(q, consta);

	att.count();
	if (temp1->key == temp2->key) {
		return;
	}
	att.count();
	if (temp1->rank >= temp2->rank) {
		att.count(2);
		temp2->p = temp1;
		temp1->rank = (temp1->rank == temp2->rank) ? temp1->rank + 1 : temp1->rank;
	}
	else {
		att.count();
		temp1->p = temp2;
	}
}

void make(NodeT* v[], int n) {
	for (int i = 0; i < n; i++) {
		v[i] = makeSet(i + 1, n);
	}
}

int numarSeturi(NodeT* a[], int nrElem) {
	int k = 0;
	int i = 0;
	while (i != nrElem) {
		if (gasesteSet(a[i], nrElem) != a[i]) {
			k = k;
		}
		else {
			k++;
		}

		i++;
	}

	return k;
}

NodeT** vectorTati(NodeT* a[], int nrElem) {
	NodeT** v = new NodeT * [nrElem];;
	int k = 0;
	int i = 0;
	while (i != nrElem) {
    	if (gasesteSet(a[i], nrElem) != a[i]) {
			k = k;
		}
		else {
			v[k] = a[i];
			k++;
		}
		i++;
	}

	return v;
}

void afisareSeturi(NodeT* a[], int nrSeturi, int nrElem) {

	NodeT** tati = vectorTati(a, nrElem); 
	for (int i = 0; i < nrSeturi; i++) {
		printf("Set %d: ", i + 1);
		for (int j = 0; j < nrElem; j++) {
			if ((gasesteSet(a[j], nrElem) == tati[i])&&(gasesteSet(a[j], nrElem) != a[j]))
			{
				printf("%d ", a[j]->key);
			}
		}
		printf("%d ", tati[i]->key);
		printf("\n");
	}
}

Graf* randomGraf(Graf* f, int nrMuchii, int nrNoduri) {

	f->nrMuchii = nrMuchii;
	f->nrNoduri = nrNoduri;
	f->muchii = new Muchie * [nrMuchii];
	int** matrice = new int*[nrNoduri];
	for (int i = 0; i < nrNoduri; i++) {
		matrice[i] = new int[nrNoduri];
		for (int j = 0; j < nrNoduri; j++) {
			matrice[i][j] = 0;
		}
	}
	NodeT** noduri = new NodeT * [nrNoduri]; 
	for (int i = 0; i < nrNoduri; i++) { 
		noduri[i] = makeSet(i + 1, nrNoduri); 
	}

	for (int i = 0; i < nrMuchii; i++) {
		f->muchii[i] = new Muchie;
	}

	for (int i = 0; i < nrMuchii; i++) {
		int r1, r2;
		do {
			r1 = rand() % nrNoduri;
			r2 = rand() % nrNoduri;
		} while (r1 == r2 || matrice[r1][r2] == 1);
			
		f->muchii[i]->emit = noduri[r1]; 
		f->muchii[i]->primi = noduri[r2]; 
		f->muchii[i]->flux = rand() % nrMuchii + 1;
		matrice[r1][r2] = 1;
		matrice[r2][r1] = 1;
	}

	return f;
}

Muchie** kruskal(Graf* f) {
	NodeT* t1 = NULL;
	NodeT* t2 = NULL;
	int k = 0;
	NodeT** noduri = new NodeT*[f->nrNoduri];
	Muchie** muchi = new Muchie*[f->nrMuchii];
	make(noduri, f->nrNoduri);
	insertionSortRecursiv(f->muchii, f->nrMuchii); 
	for (int i = 0; i < f->nrMuchii; i++) {
		 t1 = gasesteSet(f->muchii[i]->emit, f->nrNoduri);
		 t2 = gasesteSet(f->muchii[i]->primi, f->nrNoduri);
		if (t1 != t2) {
			muchi[k] = f->muchii[i];
			leagaUnion(t1, t2, f->nrNoduri);
			k++;
		}
		if (k == f->nrNoduri) {
			break;
		}
	}
	return muchi;
}

void demo() {

	int nrMuchii = 9;
	int nrNoduri = 5;
	Graf* g = new Graf;
	g = randomGraf(g, nrMuchii, nrNoduri);
	Muchie** muchii = kruskal(g);
	NodeT* v[10] = { NULL };
	make(v,10);
	leagaUnion(v[0], v[1], 10);
	leagaUnion(v[1], v[2], 10);
	leagaUnion(v[3], v[4], 10);
	leagaUnion(v[5], v[6], 10);
	leagaUnion(v[4], v[5], 10);
	leagaUnion(v[2], v[6], 10);
	leagaUnion(v[8], v[7], 10);
	leagaUnion(v[7], v[9], 10);
	int nrSeturi = numarSeturi(v, 10);
	NodeT* q = gasesteSet(v[2], 10);
	printf("Radacina este %d.\n\n", q->key);
	NodeT* p = gasesteSet(v[8], 10);
	printf("Radacina este %d.\n\n", p->key);
	afisareSeturi(v, nrSeturi, 10);
	puts("");
	for (int i = 0; i < g->nrMuchii; i++) {
		printf("%d-%d flux %d \n", g->muchii[i]->emit->key, g->muchii[i]->primi->key, g->muchii[i]->flux);
	}
	puts("\nMST:");
	for (int i = 0; i < g->nrNoduri - 1; i++) {
		printf("%d-%d flux %d \n", muchii[i]->emit->key, muchii[i]->primi->key, muchii[i]->flux);
	}


}

void perf() {
	
	for (int n = 100; n < MAX_SIZE; n += STEP_SIZE) {

		Graf* g = new Graf;
		g = randomGraf(g, n * 4, n);
		Muchie** muchii = kruskal(g);
			
	}

	p.addSeries("TotalUnionMake", "Union", "makeSet");
	p.addSeries("TotalOperatii", "TotalUnionMake", "GasesteSet");
	p.createGroup("Grupate", "Union", "makeSet","GasesteSet");

	p.showReport();
}

int main() {

	demo();
	//perf();
	return 0;
}
