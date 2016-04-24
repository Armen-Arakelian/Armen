#include <stdio.h>
#include <stdlib.h>

#include "db_manager.h"
#include "patient.h"

int main(void) {
    const char * dbFile = "db.db";
    patient_t patientList[100];
    db_t * db = db_new(dbFile);

    int countAllPatients = db_countPatients(db);
    printf("Students total: %i\n\n", countAllPatients);
    patient_t * pt1 = patient_new();
    pt1 = db_getPatientById(db, 1);
    patient_print(pt1);
    printf("\nnext test\n");
    int time = 5;
    char disease[100] = "s";
    int count = db_checkPatient(db, time, disease, patientList, 100);
    printf("Count of patients with time > 5 and disease 's'% d\n", count);
    patient_printList(patientList, count);
    printf("\nnext test\n");
    patient_t * pt2 = patient_new();
    strcpy(pt2->name, "a");
    strcpy(pt2->surname, "aa");
    pt2->age = 43;
    strcpy(pt2->disease, "2015-02-07");
    pt2->time = 11;
    pt2->weight = 73.4;
    strcpy(pt2->disease, "dfgd");

    patient_t * pt3 = patient_new();
    strcpy(pt3->name, "b");
    strcpy(pt3->surname, "bb");
    pt3->age = 31;
    strcpy(pt3->disease, "2015-05-07");
    pt3->time = 111;
    pt3->weight = 61.4;
    strcpy(pt3->disease, "jhgkjhgvkjgkg");

    pt2->id = db_insertPatient(db, pt2);
    printf("%d", pt2->id);
    patient_print(pt2);
    printf("\nnext test\n");

    pt2->age = 19;
    db_updatePatient(db, pt2);
    patient_print(pt2);
    db_deletePatient(db, 3);
    printf("%d", db_countPatients(db));

    db_free(db);
    return 0;
}
