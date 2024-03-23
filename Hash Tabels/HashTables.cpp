/*
*  Ciobanu Radu-Rares
*  Grupa 30222
	*In acest cod am testat algoritmii de inserare, cautare si stergere intr-un hash cu 
	adresarea deschisa si cu verificare patratica

	 - am ales un hash de dimensiunea 10007 iar efortul necesar pentru gasirea unui element este intre 1 si 5 in ef mediu iar in 
	   cel max intre 450 si 590
	 - pentru elementele negasite efortul mediu este intre 2960 si 2990 iar efortul maxim ramane constant 1500

*/

#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <math.h>
#include <fstream> 
#include "Profiler.h"

#define HASH_SIZE  10007
#define FACTOR1 0.8
#define FACTOR2 0.85
#define FACTOR3 0.9
#define FACTOR4 0.95
#define FACTOR5 0.99
#define NR_TESTE 5
#define M 3000

float eTotG = 0;
float eTotN = 0;
float eMediuG = 0;
float eMediuN = 0;
int eMaxG = 0;
int eMaxN = 0;
int cautare = 0;
int efortCautare = 0;

typedef struct {
	int id;
	char nume[30];
}Entry;

int proba_patratica(int numar, int index, int hashSize) {

	int hPrim = numar % hashSize;
	int rezultat = (hPrim + index + index*index) % hashSize;

	return rezultat;
}

int insertHash(Entry *tabel, int numar, int hashSize) {

	int i = 0;
	while (i != hashSize) {
		int j = proba_patratica(numar, i, hashSize);
		if (tabel[j].id == NULL) {
			tabel[j].id = numar;
			return j;
		}
		else {
			i++;
		}
	}
	return -1;
}

int insertHashDemo(Entry* tabel, int numar, const char nume[], int hashSize) {

	int i = 0;
	while (i != hashSize) {
		int j = proba_patratica(numar, i, hashSize);
		if (tabel[j].id == NULL) {
			tabel[j].id = numar;
			strcpy_s(tabel[j].nume, nume); 
			return j;
		}
		else {
			i++;
		}
	}
	return -1;
}

int cautareHashDemo(Entry *tabel, int numar, int hashSize) {
	int i = 0;
	while (i != hashSize) {
		int j = proba_patratica(numar, i, hashSize);
		if (tabel[j].id != NULL) {
			if ((tabel[j].id == numar)) {
				printf("%s ", tabel[j].nume);
				return j;
			}
		}
		else {
			break;
		}
		i++;
	}
	return -1;
}

int cautareHash(Entry* tabel, int numar, int hashSize) {
	int i = 0;
	while (i != hashSize) {
		int j = proba_patratica(numar, i, hashSize);
		if (tabel[j].id != NULL) {
			if ((tabel[j].id == numar)) {
				return j;
			}
		}
		else {
			break;
		}
		i++;
	}
	return -1;
}

int cautareHashExcel(int* tabel, int numar, int hashSize) {
	int i = 0;
	cautare = 0;
	while (i != hashSize) {
		cautare++;
		int j = proba_patratica(numar, i, hashSize);
		if (tabel[j] != NULL) {
			if ((tabel[j] == numar)) {
				return j;
			}
		}
		else {
			break;
		}
		i++;
	}
	return -1;
}

void stergereHash(Entry* tabel, int nrStergere, int hashSize) {

	int ok = cautareHash(tabel, nrStergere, hashSize);
	if (ok != -1) {

		memset(tabel[ok].nume, 0, 30);
		tabel[ok].id = NULL;
	}

}

void stergereHashExcel(int* tabel, int nrStergere, int hashSize) {

	int ok = cautareHashExcel(tabel, nrStergere, hashSize);
	if (ok != -1) {

		tabel[ok] = NULL;
	}

}

void demo() {

	const int tabelSize = 7;
	Entry a[tabelSize];
	for (int i = 0; i < tabelSize; i++) {
		a[i].id = NULL;
		memset(a[i].nume, NULL , 30);
	}
	insertHashDemo(a, 43, "Radu", tabelSize);
	insertHashDemo(a, 20, "Mihnea", tabelSize);
	insertHashDemo(a, 34, "Dan", tabelSize);
	insertHashDemo(a, 100, "Diana", tabelSize);
	insertHashDemo(a, 40, "Adina", tabelSize);
	insertHashDemo(a, 78, "Razvan", tabelSize);
	insertHashDemo(a, 90, "Ivan", tabelSize);
	stergereHash(a, 78, tabelSize);
	insertHashDemo(a, 75, "Porfirie", tabelSize);
	printf("%d\n", cautareHashDemo(a, 75, tabelSize));
	printf("%d\n", cautareHashDemo(a, 43, tabelSize)); 
	printf("%d\n", cautareHashDemo(a, 20, tabelSize));
	printf("%d\n", cautareHashDemo(a, 34, tabelSize));
	printf("%d\n", cautareHashDemo(a, 100, tabelSize));
	printf("%d\n", cautareHashDemo(a, 78, tabelSize));
	printf("%d\n", cautareHashDemo(a, 90, tabelSize));
	printf("%d\n", cautareHashDemo(a, 40, tabelSize));


}

int comparaFloat(float a, float b) {

	float p = 0.0001;
	if (((a - p) < b) && ((a + p) > b)) {
		return 1;
	}
	else {
		return 0;
	}

}

void calcEfortului(FILE *g, int *a, int m ,int n) {
	
	 int tabelCautare[M] = { NULL };
	 FillRandomArray(tabelCautare, m/2, 10, 10050, true, UNSORTED);
	 eTotG = 0;
	 eTotN = 0;
	 eMediuG = 0;
	 eMediuN = 0;
	 eMaxG = 0;
	 eMaxN = 0;
	for (int i = 0; i < NR_TESTE; i++) {
		for (int j = 0; j < m; j++) {
			if (cautareHashExcel(a, tabelCautare[j], m/2) != -1) {
				eTotG += cautare;
				if (cautare > eMaxG) {
					eMaxG = cautare;
				}
				else {
					eMaxG = eMaxG;
				}

			}
			else {
				eTotN += cautare;
				if (cautare > eMaxN) {
					eMaxN = cautare;
				}
				else {
					eMaxN = eMaxN;
				}
			}
		}
	}
	eMediuG = float (eTotG / (5 * (m / 2)));
	eMediuN = float (eTotN / (5 * (m / 2)));
	fprintf(g, "%.2f,%d,%.2f,%d\n", eMediuG, eMaxG, eMediuN, eMaxN);

}

void efortNecesarStergere(int* a, int m, int n) {
	int tabelCautare[M] = { NULL }; 
	FillRandomArray(tabelCautare, m/2, 10, 50000, true, UNSORTED); 
	for (int i = 0; i < m; i++) {

		cautareHashExcel(a, tabelCautare[i], HASH_SIZE);
		efortCautare += cautare;

	}
	efortCautare /= (m / 2);
}

int excel() {
	
	int n1 = 0;
	int n2 = 0;
	int n3 = 0;
	int n4 = 0;
	int n5 = 0;
	int a1[HASH_SIZE] = { NULL };
	int a2[HASH_SIZE] = { NULL };
	int a3[HASH_SIZE] = { NULL };
	int a4[HASH_SIZE] = { NULL };
	int a5[HASH_SIZE] = { NULL };

	FILE* f;
	fopen_s(&f, "Tabel.csv", "w");
	if (f == NULL)
		return -1;
	float factorUmplere1 = 0.0;
	float factorUmplere2 = 0.0;
	float factorUmplere3 = 0.0;
	float factorUmplere4 = 0.0;
	float factorUmplere5 = 0.0;

	while (!comparaFloat(factorUmplere1, FACTOR1)) {
		n1++;		
		factorUmplere1 = float(n1) / HASH_SIZE;
	}
	

	while (!comparaFloat(factorUmplere2, FACTOR2)) {
		n2++;
		factorUmplere2 = float(n2) / HASH_SIZE;
	}

	while (!comparaFloat(factorUmplere3, FACTOR3)) {
		n3++;
		factorUmplere3 = float(n3) / HASH_SIZE;
	}

	while (!comparaFloat(factorUmplere4, FACTOR4)) {
		n4++;
		factorUmplere4 = float(n4) / HASH_SIZE;
	}

	while (!comparaFloat(factorUmplere5, FACTOR5)) {
		n5++;
		factorUmplere5 = float(n5) / HASH_SIZE;
	}
	FillRandomArray(a1, n1, 10, 10050, true);
	FillRandomArray(a2, n2, 10, 10050, true);
	FillRandomArray(a3, n3, 10, 10050, true);
	FillRandomArray(a4, n4, 10, 10050, true);
	FillRandomArray(a5, n5, 10, 10050, true);

	fprintf(f, "Factor de umplere, Efort mediu gasite, Efort maxim gasite, Efort mediu ne-gasite ,Efort maxim ne-gasite\n");
	fprintf(f, "%.2f,", factorUmplere1);
	calcEfortului(f, a1, M, n1);
	fprintf(f, "%.2f,", factorUmplere2);
	calcEfortului(f, a2, M, n2);
	fprintf(f, "%.2f,", factorUmplere3);
	calcEfortului(f, a3, M, n3);
	fprintf(f, "%.2f,", factorUmplere4);
	calcEfortului(f, a4, M, n4);
	fprintf(f, "%.2f,", factorUmplere5);
	calcEfortului(f, a5, M, n5);

	while (!comparaFloat(factorUmplere5, FACTOR1)) {
		stergereHashExcel(a5, a5[rand() % n5], HASH_SIZE); 
		n5--;
		factorUmplere5 = float(n5) / HASH_SIZE;
	}
	efortNecesarStergere(a5, M, n5); 
	fprintf(f, "\n");
	fprintf(f, "%d ", efortCautare);
}

int main() {

	//demo();
	excel();
	return 0;
}