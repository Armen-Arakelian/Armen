#ifndef CONVERTOR_H_INCLUDED
#define CONVERTOR_H_INCLUDED

#include "patient.h"


typedef struct DataHandler DataHandler_s;
typedef DataHandler_s * DataHandler_t;

int db_checkPatient(DataHandler_t self, int K, char * P, patient_t * arr, int arrMax);

DataHandler_t DataHandler_new(const char * db);
void DataHandler_delete(DataHandler_t self);

char * DataHandler_patientsToXmlStr(DataHandler_t self, char * mem_p);
int DataHandler_getPatientsNum(DataHandler_t self);
patient_t DataHandler_getPatient(DataHandler_t self, unsigned int id);
int DataHandler_addPatient(DataHandler_t self, patient_t pt);
void DataHandler_deletePatient(DataHandler_t self, unsigned int id);
void DataHandler_setPatient(DataHandler_t self, unsigned int index, const char * key, const char * value);
void DataHandler_foreachPat(DataHandler_t self, void (fn)(patient_t pt));
void DataHandler_updatePatiet(DataHandler_t self, patient_t pt);

#endif // CONVERTOR_H_INCLUDED
