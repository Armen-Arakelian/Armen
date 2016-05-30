#ifndef DATA_HANDLER_H_INCLUDED
#define DATA_HANDLER_H_INCLUDED

#include "patient.h"

typedef struct DataHandler DataHandler_s;
typedef DataHandler_s * DataHandler_t;

DataHandler_t DataHandler_new();
void DataHandler_delete(DataHandler_t self);

char * DataHandler_convertToXml(DataHandler_t self, char * buff);
int DataHandler_getNumberOfPatients(DataHandler_t self);
patient_t DataHandler_getPatient(DataHandler_t self, unsigned int index);
void DataHandler_addPatient(DataHandler_t self, patient_t pat);
void DataHandler_deletePatient(DataHandler_t self, int i);
void DataHandler_setPatient(DataHandler_t self, unsigned int index, const char * key, const char * value);

#endif // DATA_HANDLER_H_INCLUDED
