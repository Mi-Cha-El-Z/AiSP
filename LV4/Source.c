#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAX_RED 1024

typedef struct Polinom* Pozicija;

struct Polinom {
    int koef;
    int eksp;
    Pozicija Next;
};

Pozicija napraviListu() {
    Pozicija head = (Pozicija)malloc(sizeof(struct Polinom));
    if (head == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        exit(1);
    }
    head->koef = 0;
    head->eksp = 0;
    head->Next = NULL;
    return head;
}


void dodajClan(Pozicija head, int koef, int eksp) {
    Pozicija prev = head;
    Pozicija q;
    Pozicija temp;

    while (prev->Next != NULL && prev->Next->eksp > eksp) {
        prev = prev->Next;
    }

    if (prev->Next != NULL && prev->Next->eksp == eksp) {
        prev->Next->koef += koef;

        if (prev->Next->koef == 0) {
            temp = prev->Next;
            prev->Next = temp->Next;
            free(temp);
        }
    }
    else {
        q = (Pozicija)malloc(sizeof(struct Polinom));
        if (q == NULL) {
            printf("Greska pri alokaciji memorije!\n");
            return;
        }
        q->koef = koef;
        q->eksp = eksp;
        q->Next = prev->Next;
        prev->Next = q;
    }
}

void ispisi(Pozicija head) {
    int prvi = 1;
    int k;

    head = head->Next;

    if (head == NULL) {
        printf("0\n");
        return;
    }

    while (head != NULL) {
        k = head->koef;

        if (k < 0)
            printf(prvi ? "-" : " - ");
        else if (!prvi)
            printf(" + ");

        if (k < 0)
            k = -k;

        if (k != 1 || head->eksp == 0)
            printf("%d", k);

        if (head->eksp == 1)
            printf("x");
        else if (head->eksp != 0)
            printf("x^%d", head->eksp);

        prvi = 0;
        head = head->Next;
    }
    printf("\n");
}

int citajPolinom(Pozicija head, FILE* fp) {
    char red[MAX_RED];
    char* pos;
    int k, e, n;

    if (fgets(red, MAX_RED, fp) == NULL)
        return 0;

    pos = red;
    while (sscanf(pos, "%d %d%n", &k, &e, &n) == 2) {
        dodajClan(head, k, e);
        pos += n;
    }
    return 1;
}

void zbroji(Pozicija p1, Pozicija p2, Pozicija rezultat) {
    Pozicija a = p1->Next;
    Pozicija b = p2->Next;

    while (a != NULL) {
        dodajClan(rezultat, a->koef, a->eksp);
        a = a->Next;
    }
    while (b != NULL) {
        dodajClan(rezultat, b->koef, b->eksp);
        b = b->Next;
    }
}

void pomnozi(Pozicija p1, Pozicija p2, Pozicija rezultat) {
    Pozicija a, b;

    for (a = p1->Next; a != NULL; a = a->Next) {
        for (b = p2->Next; b != NULL; b = b->Next) {
            dodajClan(rezultat, a->koef * b->koef, a->eksp + b->eksp);
        }
    }
}

void obrisiListu(Pozicija head) {
    Pozicija temp;
    while (head->Next != NULL) {
        temp = head->Next;
        head->Next = temp->Next;
        free(temp);
    }
}

int main() {
    Pozicija p1 = napraviListu();
    Pozicija p2 = napraviListu();
    Pozicija zbroj = napraviListu();
    Pozicija umnozak = napraviListu();
    FILE* fp;

    fp = fopen("Polinomi.txt", "r");
    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }

    if (!citajPolinom(p1, fp) || !citajPolinom(p2, fp)) {
        printf("Datoteka mora imati dva retka (po jedan polinom).\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);

    printf("Prvi polinom:  ");
    ispisi(p1);

    printf("Drugi polinom: ");
    ispisi(p2);

    zbroji(p1, p2, zbroj);
    printf("\nZbroj:   ");
    ispisi(zbroj);

    pomnozi(p1, p2, umnozak);
    printf("Umnozak: ");
    ispisi(umnozak);

    obrisiListu(p1);
    obrisiListu(p2);
    obrisiListu(zbroj);
    obrisiListu(umnozak);
    free(p1);
    free(p2);
    free(zbroj);
    free(umnozak);

    return 0;
}