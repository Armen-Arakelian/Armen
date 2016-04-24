#ifndef DB_MANAGER_H_INCLUDED
#define DB_MANAGER_H_INCLUDED

#include "patient.h"

typedef struct db_s db_t;

db_t * db_new(const char * dbFile);
void db_free(db_t * self);

int db_insertPatient(db_t * self, patient_t * pt) ;
patient_t * db_getPatientById(db_t * self, int id);
void db_updatePatient(db_t * self, patient_t * pt);
void db_deletePatient(db_t * self, int id);
int db_countPatients(db_t * self);
int db_checkPatient(db_t * self, int K, char * P, patient_t * arr, int arrMax);

#endif // DB_MANAGER_H_INCLUDED
