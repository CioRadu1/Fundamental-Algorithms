/*
*  Ciobanu Radu-Rares
*  Grupa 30222
	*In acest cod am testat algoritmii de reprezentare a unui arbore prin:
		-Reprezentarea parinte
		-Transformarea in reprezentarea multi-Way
		-Transformarea in reprezentarea binara a acestuia

	 - dupa cum se poare vedea reprezentarea parinte nu necestina o complexitate mai mare de O(n) pentru afisarea "prettyPrint" a reprezentarii parinte
	 - pentru reprezentarea multi-way am facut o fucntie care transforma din reprezentarea parinte in reprezentarea multi-way si am realizat si o functie de prettyPrint si in cazul acesta
	   complexitatea fiind tot O(n)
	 -pentru reprezentarea binara am facut la fe, o functie ce tranforma reprezentarea multi-way in reprezentare binara, iar functia de afisare este similara cu cea de la multi-way,
	  doar ca in aceasta sunt prezenti si pointeri la copii acestuia, complexitatea este de O(n)

*/


#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;


typedef struct node1 {
		
	int key;
	int nrCopii;
	struct node1* kids;

}NodeT;

typedef struct node2 {

	int key;
	struct node2 *copilStang;
	struct node2 *copilDrept;

}NodeD;

NodeT* creaza(int key) {
	NodeT* q = new NodeT;
	q->key = key;
	q->nrCopii = 0;
	q->kids = NULL; 
	return q;
}

void prettyPrintR1(int array[], int size, int index,int count) {

	if (array[index-1] < 0) {
		printf("%d\n", index);
		count++;
	}
	for (int i = 0; i < size; i++) {
		 if (array[i] == index) {
			 printf(" ");
			 for (int j = 0; j < count; j++) { 
				 printf("  "); 
			 }
			 printf("%d\n", i + 1); 
			 count++; 
			 prettyPrintR1(array, size, i + 1, count + 1);
			 count--; 

		  }
	}	
}

NodeT* multiWayTrans(int* array, int size) {

	NodeT* rad = new NodeT;
	NodeT* noduri = new NodeT[size]{NULL}; 
	for (int i = 0; i < size; i++) {
		noduri[i].key = i + 1;
		noduri[i].nrCopii = 0;
		noduri[i].kids = NULL;
	}
	for (int i = 0; i < size; i++) {
		noduri[array[i]].nrCopii++;
	}
	for (int i = 0; i < size; i++) {
		noduri[i].kids = new NodeT[noduri[i].nrCopii];
		noduri[i].nrCopii = 0;
	}
	for (int i = 0; i < size; i++) {
		if (array[i] == -1) {
			rad = &noduri[i];
		}
		else if (array[i] != -1) {
			noduri[array[i] - 1].kids[noduri[array[i] - 1].nrCopii++] = noduri[i];
		}
	}
	return rad;
}

void prettyMulti(NodeT* rad, int count) {
	if (rad != NULL) {
		for (int i = 0; i < count; i++) {
			printf("   ");
		}
		printf("%d\n", rad->key);
		for (int i = 0; i < (rad->nrCopii); i++) {
			prettyMulti(&(rad->kids[i]), count + 1);

		}
	}
}

NodeD* binaryTrans(NodeT *multi, int size) {


}

void prettyBinar(NodeD* rad, int count) {

	if (rad != NULL) {
		for (int i = 0; i < count; i++) {
			printf("   ");
		}
		prettyBinar(rad->copilDrept, count + 1); 
		printf("%d\n", rad->key);
		prettyBinar(rad->copilStang, count + 1);
	}
}

void demo() {
	int pi[] = { 2, 7, 5, 2, 7, 7, -1, 5, 2 };
	int radacina = 0;
	int c = 0;
	int n = sizeof(pi) / sizeof(pi[0]);
	for (int i = 0; i < n; i++) {
		if (pi[i] < 0) {
			radacina = i + 1;
		}
	}
	printf("Reprezentarea Parinte:\n");
	prettyPrintR1(pi, n, radacina, 0);
	printf("\n");
	printf("MultiWay: \n");
	NodeT* multi = multiWayTrans(pi, n);
	prettyMulti(multi,0);
	printf("\n");
	printf("Binara: ");

}

int main() {

	demo();
	return 0;
}