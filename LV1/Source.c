#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_BODOVA 50.0

typedef struct {
    char ime[50];
    char prezime[50];
    double bodovi;
} Student;

int brojRedaka(char imeDatoteke[]) {
    FILE* fp = fopen(imeDatoteke, "r");
    char red[256];
    int br = 0;

    if (fp == NULL)
        return -1;

    while (fgets(red, sizeof(red), fp) != NULL)
        br++;

    fclose(fp);
    return br;
}

int main() {
    char imeDatoteke[] = "studenti.txt";
    Student* studenti;
    FILE* fp;
    int n, i;

    n = brojRedaka(imeDatoteke);
    if (n <= 0) {
        printf("Greska: datoteka se ne moze otvoriti ili je prazna.\n");
        return 1;
    }

    studenti = (Student*)malloc(n * sizeof(Student));
    if (studenti == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return 1;
    }

    fp = fopen(imeDatoteke, "r");
    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        free(studenti);
        return 1;
    }

    for (i = 0; i < n; i++)
        fscanf(fp, "%s %s %lf", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);

    fclose(fp);

    for (i = 0; i < n; i++)
        printf("%s %s  apsolutno: %.2f  relativno: %.2f%%\n",
            studenti[i].ime, studenti[i].prezime,
            studenti[i].bodovi, studenti[i].bodovi / MAX_BODOVA * 100);

    free(studenti);
    return 0;
}