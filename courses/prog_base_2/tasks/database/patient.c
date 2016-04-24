#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "patient.h"

patient_t * patient_new()
{
    patient_t * pt = malloc(sizeof(struct patient_s));
    return pt;
}

void patient_delete(patient_t * self)
{
    free(self);
}
void patient_print(patient_t * pt) {
    printf("Name: %s\nSurname: %s\nage: %d\nenDate: %s\nweight: %f\ntime: %d\ndisease: %s\n\n",
        pt->name, pt->surname, pt->age, pt->enDate, pt->weight, pt->time, pt->disease);
}

void patient_printList(patient_t * arr, int len) {
    for (int i = 0; i < len; i++) {
        patient_print(&arr[i]);
    }
}

