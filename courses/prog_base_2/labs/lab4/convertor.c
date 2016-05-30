#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdlib.h>

#include "convertor.h"

#include "list.h"

struct DataHandler
{
    List_t patients;
};

static const char * const patientsXmlPass = "data/patients.xml";

DataHandler_t DataHandler_new()
{
    DataHandler_t self = (DataHandler_t) malloc(sizeof(DataHandler_s));
    self->patients = List_new();
    return self;
}

void DataHandler_delete(DataHandler_t self)
{
    List_deepDelete(self->patients, patient_delete);
    free(self);
}

char * DataHandler_convertToXml(DataHandler_t self, char * buff)
{
    xmlDoc * doc = NULL;
	xmlNode * root = NULL;
	xmlChar * str = NULL;

	doc = xmlNewDoc("1.0");
	root = xmlNewNode(NULL, "patients");
	xmlDocSetRootElement(doc, root);

	int numberOfPatients = List_getSize(self->patients);

	for(int i = 0; i < numberOfPatients; i++)
        {
        patient_convertToXml(List_get(self->patients, i, NULL), doc, root);
	}

	xmlDocDumpMemory(doc, &str, NULL);

	strcpy(buff, str);

    free(str);
    xmlFreeDoc(doc);
    return buff;
}

int DataHandler_getNumberOfPatients(DataHandler_t self)
{
    return List_getSize(self->patients);
}

patient_t DataHandler_getPatient(DataHandler_t self, unsigned int index)
{
    return List_get(self->patients, index, NULL);
}

void DataHandler_addPatient(DataHandler_t self, patient_t pat)
{
    List_append(self->patients, pat);
}

void DataHandler_deletePatient(DataHandler_t self, int i)
{
    patient_delete(List_remove(self->patients, i, NULL));
}

void DataHandler_setPatient(DataHandler_t self, unsigned int index, const char * key, const char * value)
{
    patient_setParametr(List_get(self->patients, index, NULL), key, value);
}
