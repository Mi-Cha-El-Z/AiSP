#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

typedef struct Element* Pozicija;
struct Element {
	int broj;
	Pozicija Next;
};

Pozicija noviElement(int broj) {
    Pozicija q = (Pozicija)malloc(sizeof(struct Element));
    if (q == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        exit(1);
    }
    q->broj = broj;
    q->Next = NULL;
    return q;
}

Pozicija napraviListu() {
    return noviElement(0);
}

Pozicija dodajIza(Pozicija p, int broj) {
    Pozicija q = noviElement(broj);
    q->Next = p->Next;
    p->Next = q;
    return q;
}

void dodajSortirano(Pozicija head, int broj) {
    Pozicija prev = head;
    while (prev->Next != NULL && prev->Next->broj < broj) {
        prev = prev->Next;
    }
    if (prev->Next != NULL && prev->Next->broj == broj) {
        return;
    }

    dodajIza(prev, broj);
}

int citajIzDat(Pozicija head, char naziv[]) {
    FILE* fp = fopen(naziv, "r");
    int broj;

    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke %s!\n", naziv);
        return 0;
    }

    while (fscanf(fp, "%d", &broj) == 1) {
        dodajSortirano(head, broj);
    }

    fclose(fp);
    return 1;
}

void ispisi(Pozicija head) {
    head = head->Next;

    if (head == NULL) {
        printf("(prazna lista)\n");
        return;
    }

    while (head != NULL) {
        printf("%d ", head->broj);
        head = head->Next;
    }
    printf("\n");
}

void unija(Pozicija L1, Pozicija L2, Pozicija rezultat) {
    Pozicija a = L1->Next;
    Pozicija b = L2->Next;
    Pozicija tail = rezultat;

    while (a != NULL && b != NULL) {
        if (a->broj < b->broj) {
            tail = dodajIza(tail, a->broj);
            a = a->Next;
        }
        else if (a->broj > b->broj) {
            tail = dodajIza(tail, b->broj);
            b = b->Next;
        }
        else {
            tail = dodajIza(tail, a->broj);
            a = a->Next;
            b = b->Next;
        }
    }
    while (a!=NULL) {
        tail = dodajIza(tail, a->broj);
        a = a->Next;
    }
    while (b != NULL) {
        tail = dodajIza(tail, b->broj);
        b = b->Next;
    }

}

void presjek(Pozicija L1, Pozicija L2, Pozicija rezultat) {
    Pozicija a = L1->Next;
    Pozicija b = L2->Next;
    Pozicija tail = rezultat;

    while (a != NULL && b != NULL) {
        if (a->broj < b->broj) {
            a = a->Next;
        }
        else if (a->broj > b->broj) {
            b = b->Next;
        }
        else {
            tail = dodajIza(tail, a->broj);
            a = a->Next;
            b = b->Next;
        }
    }
}

void obrisiListu(Pozicija head) {
    Pozicija temp;
    while (head->Next) {
        temp = head->Next;
        head->Next = temp->Next;
        free(temp);
    }
}


int main() {

    Pozicija L1 = napraviListu();
    Pozicija L2 = napraviListu();
    Pozicija U = napraviListu();
    Pozicija P = napraviListu();

    if (!citajIzDat(L1, "L1.txt") || !citajIzDat(L2, "L2.txt")){
        return 1;
    }
    printf("L1: ");
    ispisi(L1);
    printf("L2: ");
    ispisi(L2);

    unija(L1, L2, U);
    printf("\nUnija: ");
    ispisi(U);

    presjek(L1, L2, P);
    printf("\nPresjek: ");
    ispisi(P);

    obrisiListu(L1);
    obrisiListu(L2);
    obrisiListu(U);
    obrisiListu(P);
    free(L1);
    free(L2);
    free(U);
    free(P);

	return 0;
}