/*
*  Ciobanu Radu-Rares
*  Grupa 30222
	*In acest cod am testat algoritmul DFS, algoritmul lui Tarjan, si sortarea topografica a unui graf, cat si analiza operatiilor pentru algoritmul DFS:

	 - Pentru algoritmul DFS putem incepe din orice nod si ni se returneaza arborele rezultat si are complexitate O(V+N)
	 - Algoritmul lui Tarjan este folosit pentru aflearea componentelor puternic conectate
	 - Sortarea topografica returneaza o lista in care este inserat la inceput nodul care si-a atins timpul de sfarsit
*/

#include <stdio.h>
#include <iostream>
#include "Profiler.h"
#include <stack>

using namespace std;

Profiler p("Lab11");

#define MAX_SIZE 4500
#define START_SIZE 1000
#define STEP_SIZE 100

typedef struct lnode {

	int key;
	struct lnode* next;

}LNode;

typedef struct list {

	struct lnode* first;
	struct lnode* last;

}List;

typedef struct node {

	int key;
	int dist;
	int time;
	int color;
	int adjSize;
	struct node *parent;
	struct node **lista;
	int index;
	int link;
	bool stiva;

}Node;

typedef struct graf {

	int nrNoduri;
	int nrMuchii;
	struct node** noduri;

}Graf;

stack<Node*> tarjanStack;
int indexGl = 0;

List* creareListaGoala() {

	List* list = new List;
	list->first = NULL;
	list->last = NULL;
	return list;
}

void DFS_Visit(Graf* f, Node* u, int *timp,Operation opp) {

	*timp += 1;
	opp.count();
	u->dist = *timp;
	u->color = 2;
	for (int i = 0; i < u->adjSize; i++) {
		opp.count();
		if (u->lista[i]->color == 0) {
			opp.count();
			u->lista[i]->parent = u;
			DFS_Visit(f, u->lista[i], timp,opp);
		}
	}
	opp.count();
	u->color = 1;
	timp += 1;
	opp.count();
	u->time = *timp;
}

void DFS(Graf* f, Operation opp) {

	for (int i = 0; i < f->nrNoduri; i++) {
		f->noduri[i]->color = 0;
		f->noduri[i]->dist = 0;
		f->noduri[i]->parent = NULL;
		f->noduri[i]->time = 0;
	}
	int timp = 0;
	for (int i = 0; i < f->nrNoduri; i++) {
		opp.count();
		if (f->noduri[i]->color == 0) {
			DFS_Visit(f, f->noduri[i], &timp, opp);
		}
	}

}

Node* initializareNod(int nod) {
	
	Node* q = new Node;
	q->key = nod;
	q->dist = 0;
	q->time = 0;
	q->color = 0;
	q->adjSize = 0;
	q->parent = NULL;
	q->lista = NULL; 
	return q;

}

Graf* creeareGraf(Graf* f, int nrNoduri,int nrMuc) {

	int nrMuchii = 0;
	f->nrMuchii = nrMuc;
	f->nrNoduri = nrNoduri;
	f->noduri = new Node * [f->nrNoduri];
	for (int i = 0; i < f->nrNoduri; i++) {

		f->noduri[i] = initializareNod(i);
	}
	int** matrice = new int* [f->nrNoduri];
	for (int i = 0; i < f->nrNoduri; i++) {
		matrice[i] = new int[f->nrNoduri];
		for (int j = 0; j < f->nrNoduri; j++) {
			matrice[i][j] = 0;
		}
	}
	while (nrMuchii != f->nrMuchii) {
		
		int emit = (rand() + 1) % f->nrNoduri;
		int prim = rand() % f->nrNoduri;
		if (emit != prim) {

			if (matrice[emit][prim] == 0) {
				f->noduri[emit]->adjSize++;
				f->noduri[emit]->lista = (Node**)realloc(f->noduri[emit]->lista, f->noduri[emit]->adjSize * sizeof(Node*));
				f->noduri[emit]->lista[f->noduri[emit]->adjSize - 1] = f->noduri[prim];
				matrice[emit][prim] = 1;
				nrMuchii++;
			}
			else if (matrice[prim][emit] == 0) {
				f->noduri[prim]->adjSize++;
				f->noduri[prim]->lista = (Node**)realloc(f->noduri[prim]->lista, f->noduri[prim]->adjSize * sizeof(Node*));
				f->noduri[prim]->lista[f->noduri[prim]->adjSize - 1] = f->noduri[emit];
				matrice[prim][emit] = 1;
				nrMuchii++;
			}
		}
	}

	return f;
}

void tarjanConect(Node* u) {
	u->index = indexGl;
	u->link = indexGl;
	indexGl++;
	tarjanStack.push(u);
	u->stiva = true;

	for (int i = 0; i < u->adjSize; i++) {
		Node* v = u->lista[i];
		if (v->index == -1) {
			tarjanConect(v);
			u->link = min(u->link, v->link);
		}
		else if (v->stiva) {
			u->link = min(u->link, v->index);
		}
	}

	if (u->link == u->index) {
		Node* v;
		do {
			v = tarjanStack.top();
			tarjanStack.pop();
			v->stiva = false;
			printf("%d ", v->key);
		} while (v != u);
		printf("\n");
	}
}

void tarjanAlgorithm(Graf* f) {
	for (int i = 0; i < f->nrNoduri; i++) {
		f->noduri[i]->index = -1;
		f->noduri[i]->link = -1;
		f->noduri[i]->stiva = false;
	}
	indexGl = 0;

	for (int i = 0; i < f->nrNoduri; i++) {
		if (f->noduri[i]->index == -1) {
			tarjanConect(f->noduri[i]);
		}
	}
}

void DFS_Top(Graf* f, Node* u, List* q) {

	u->color = 1;
	for (int i = 0; i < u->adjSize; i++) {
		Node* v = new Node;
		v = u->lista[i];
		if (v->color == 0) {
			v->parent = u;
			DFS_Top(f, v, q);
		}
	}

	LNode* p = new LNode;
	p->key = u->key;
	p->next = NULL;

	if (q->first == NULL) {
		q->first = p;
		q->last = p;
	}
	else {
		p->next = q->first;
		q->first = p;
	
	}
}

List* sortareTopologica(Graf* f, List* q) {

	for (int i = 0; i < f->nrNoduri; i++) {
		if (f->noduri[i]->color == 0) {
			DFS_Top(f, f->noduri[i], q);
		}
	}

	return q;
}


void prettyPrint(Node* rad, int *lista) {

	if (rad->key == lista[rad->key]) {
		return;
	}
	else {
		lista[rad->key] = rad->key;
	}
	printf("%d\n", rad->key);
	for (int i = 0; i < rad->adjSize ; i++) {
		printf("  ");
	}

	for (int i = 0; i < rad->adjSize; i++) {
		if (rad->lista[i]->key != lista[rad->lista[i]->key]) {
			prettyPrint(rad->lista[i], lista);
		}
	}

}

void afisareGraf(Graf *f) {
   
	for (int i = 0; i < f->nrNoduri; i++) {
		printf("%d: ", f->noduri[i]->key);
		for (int j = 0; j < f->noduri[i]->adjSize; j++) {
			printf("%d ", f->noduri[i]->lista[j]->key);
		}
		puts("");
	}
}

void afisareListaSortata(List* list)
{
	LNode* q = list->first;

	while (q != NULL)
	{
		printf("%d ", q->key);
		q = q->next;
	}
	printf("\n");
}

void demo() {
	int lista[7] = { NULL };
	Graf* f = new Graf;
	f = creeareGraf(f, 7, 12);
	Operation a = p.createOperation("Nimic", 0);
	Graf* g= new Graf;
	g = creeareGraf(g, 7, 12);
	for (int i = 0; i < 7; i++) {
		lista[i] = -1;
	}
	afisareGraf(f);
	DFS(f, a);
	puts("");
	printf("Rezultatul dupa DFS:\n");
	prettyPrint(f->noduri[5], lista);
	puts("");
	printf("Componentele puternic conectate:\n");
	tarjanAlgorithm(f);
	puts("");
	printf("Lista rezultata din sortarea topologica: ");
	List* listaSortata = creareListaGoala();
	listaSortata = sortareTopologica(g, listaSortata);
	afisareListaSortata(listaSortata);

}

void graficeNrMuchii() {

	Graf* f = new Graf;
	int nrNoduri = 100;
	for (int nrMuchii = START_SIZE; nrMuchii <= MAX_SIZE; nrMuchii += STEP_SIZE) {
		Operation opp1 = p.createOperation("OperatiiDFSMuchii", nrMuchii);
		f = creeareGraf(f, nrNoduri, nrMuchii);
		DFS(f, opp1);
	}
}

void graficeNrNoduri() {

	Graf* g = new Graf;
	int nrMuchii = 4500;
	for (int nrNoduri = 100; nrNoduri <= 200; nrNoduri += 10) {
		Operation opp2 = p.createOperation("OperatiiDFSNoduri", nrNoduri);
		g = creeareGraf(g, nrNoduri, nrMuchii);
		DFS(g, opp2);
	}
}

void grafice() {
	graficeNrNoduri();
	graficeNrMuchii();
	p.showReport();
	
}

int main() {

	demo();
	//grafice();
	return 0;
}