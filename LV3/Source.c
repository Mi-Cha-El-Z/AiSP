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
        return;
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

Pozicija NadiPoPrezimu(Pozicija head, char prezime[]) {
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

void dodajIza(Pozicija p, char ime[], char prezime[], int god) {
    Pozicija q;
    if (p == NULL) {
        printf("Elemetn nije pronaden\n");
        return;
    }
    q = (Pozicija)malloc(sizeof(struct Osoba));
    if (q == NULL) {
        printf("Greska pri alokaciji memorije\n");
        return;
    }
    strcpy(q->ime, ime);
    strcpy(q->prezime, prezime);
    q->godinaRodjenja = god;

    q->Next = p->Next;
    p->Next = q;
}

void dodajIspred(Pozicija head, Pozicija p, char ime[], char prezime[], int godina) {
    Pozicija prev = head;
    Pozicija q;

    if (p == NULL) {
        printf("Element nije pronaden!\n");
        return;
    }
    while (prev->Next != NULL && prev->Next != p)
        prev = prev->Next;

    if (prev->Next == NULL) {
        printf("Element nije u listi!\n");
        return;
    }

    q = (Pozicija)malloc(sizeof(struct Osoba));

    if (q == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return;
    }

    strcpy(q->ime, ime);
    strcpy(q->prezime, prezime);
    q->godinaRodjenja = godina;

    q->Next = p;
    prev->Next = q;
}

void sortiraj(Pozicija p) {
    Pozicija j, prev_j, temp, end;

    end = NULL;
    while (p->Next != end) {
        prev_j = p;
        j = p->Next;

        while (j->Next != end) {
            if (strcmp(j->prezime, j->Next->prezime) > 0) {
                temp = j->Next;
                prev_j->Next = temp;
                j->Next = temp->Next;
                temp->Next = j;
                j = temp;
            }

            prev_j = j;
            j = j->Next;
        }
        end = j;
    }

}

void upisiUDatoteku(Pozicija head, char nazivDat[]) {
    FILE* fp = fopen(nazivDat, "w");
    Pozicija p = head->Next;

    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke.\n");
        return;
    }

    while (p != NULL) {
        fprintf(fp, "%s %s %d\n", p->ime, p->prezime, p->godinaRodjenja);
        p = p->Next;
    }

    fclose(fp);
    printf("Lista je zapisana u datoteku.\n");

}


int postojiUListi(Pozicija head, char ime[], char prezime[], int godina) {
    Pozicija p = head->Next;
    while (p != NULL) {
        if (strcmp(p->ime, ime) == 0 &&
            strcmp(p->prezime, prezime) == 0 &&
            p->godinaRodjenja == godina)
            return 1;
        p = p->Next;
    }
    return 0;
}


void citajDatoteku(Pozicija head, char imeDat[]) {
    FILE* fp = fopen(imeDat, "r");
    char ime[MAX], prezime[MAX];
    int godina;

    if (fp == NULL) {
        printf("Datoteka %s ne postoji, nema sto citati.\n", imeDat);
        return;
    }

    while (fscanf(fp, "%s %s %d", ime, prezime, &godina) == 3) {
        if (!postojiUListi(head, ime, prezime, godina)) {
            dodajNaKraj(head, ime, prezime, godina);
            printf("Procitano iz datoteke i dodano: %s %s %d\n", ime, prezime, godina);
        }
    }

    fclose(fp);
}

int main() {
    struct Osoba* head = malloc(sizeof(struct Osoba));
    Pozicija p;
    head->Next = NULL;
    dodajNaPocetak(head, "Mihael", "Zelic", 2006);
    dodajNaPocetak(head, "Luka", "Lukic", 2001);

    dodajNaKraj(head, "Ivo", "Ivic", 1989);

    ispisi(head);

    p = NadiPoPrezimu(head->Next, "Ivic");
    if (p != NULL)
        printf("Pronadeno %s %s %d\n", p->ime, p->prezime, p->godinaRodjenja);
    else
        printf("Ne postoji ta osoba.");

    ispisi(head);

    p = NadiPoPrezimu(head->Next, "Ivic");
    dodajIza(p, "Ana", "Anic", 2004);

    p = NadiPoPrezimu(head->Next, "Zelic");
    dodajIspred(head, p, "Marko", "Maric", 2003);

    printf("\nLista nakon dodavanja:\n");
    ispisi(head);

    printf("\nCitanje datoteke prije upisa:\n");
    citajDatoteku(head, "osobe.txt");

    sortiraj(head);
    printf("\nLista nakon sortiranja:\n");
    ispisi(head);

    printf("\nUpis u datoteku:\n");
    upisiUDatoteku(head, "osobe.txt");

    ispisi(head);

    while (head->Next != NULL) {
        Pozicija temp = head->Next;
        head->Next = temp->Next;
        free(temp);
    }

    free(head);
    return 0;
}