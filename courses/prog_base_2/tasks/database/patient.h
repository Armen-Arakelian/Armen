#ifndef PATIENT_H_INCLUDED
#define PATIENT_H_INCLUDED

typedef struct patient_s
{
    int id;
    char name[100];
    char surname[100];
    int age;
    char enDate[20];
    double weight;
    int time;
    char disease[100];
}patient_t;

void patient_print(patient_t * pt);
void patient_printList(patient_t * arr, int len);

#endif // PATIENT_H_INCLUDED
