#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 50

typedef struct Osoba* Pozicija;

struct Osoba {
    char ime[MAX];
    char prezime[MAX];
    int godinaRodjenja;
    Pozicija Next;
};

void dodajNaPocetak(Pozicija head, char ime[], char prezime[], int godina) {
    Pozicija q = (Pozicija)malloc(sizeof(struct Osoba));
    if (q == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return NULL;
    }
    strcpy(q->ime, ime);
    strcpy(q->prezime, prezime);
    q->godinaRodjenja = godina;
    q->Next = head->Next;
    head->Next = q;
}

void ispisi(Pozicija head) {
    head = head->Next;
    while (head != NULL) {
        printf("%s %s %d\n", head->ime, head->prezime, head->godinaRodjenja);
        head = head->Next;
    }
}

void dodajNaKraj(Pozicija head, char ime[], char prezime[], int godina) {
    //Pozicija t = head;
    Pozicija q = (Pozicija)malloc(sizeof(struct Osoba));
    strcpy(q->ime, ime);
    strcpy(q->prezime, prezime);
    q->godinaRodjenja = godina;
    q->Next = NULL;

    while (head->Next != NULL) {
        head = head->Next;
    }

    head->Next = q;
}

Pozicija NadiPoImenu(Pozicija head, char prezime[]) {
    while (head != NULL && strcmp(head->prezime, prezime) != 0) {
        head = head->Next;
    }
    return head;
}

void Obrisi(Pozicija head, char prezime[]) {
    Pozicija prev = head;
    Pozicija temp;
    while (prev->Next != NULL && strcmp(prev->Next->prezime, prezime) != 0) {
        prev = prev->Next;

        if (prev->Next != NULL) {
            temp = prev->Next;
            prev->Next = temp->Next;
            free(temp);
        }
    }


}

int main() {
    struct Osoba* head = malloc(sizeof(struct Osoba));
    Pozicija p;
    head->Next = NULL;
    dodajNaPocetak(head, "Mihael", "Zelic", 2006);
    dodajNaPocetak(head, "Luka", "Lukic", 2001);

    dodajNaKraj(head, "Ivo", "Ivic", 1989);

    ispisi(head);

    p = NadiPoImenu(head->Next, "Ivic");
    if (p != NULL)
        printf("Pronadeno %s %s %d\n", p->ime, p->prezime, p->godinaRodjenja);
    else
        printf("Ne postoji ta osoba.");

    Obrisi(head->Next, "Ivic");

    ispisi(head);
    return 0;
}