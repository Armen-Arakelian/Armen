#ifndef PATIENT_H_INCLUDED
#define PATIENT_H_INCLUDED

typedef struct patient_s patient_t;
patient_t * patient_new();
void patient_delete(patient_t * patient);

char * patient_getText(const char * filename);
void patient_parse(char * text, patient_t * patients[]);

#endif // PATIENT_H_INCLUDED
