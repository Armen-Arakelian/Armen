#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#include "convertor.h"
#include "list.h"
#include "patient.h"

struct DataHandler{
    sqlite3 * db;
};

static int _getMaxIdPatient(DataHandler_t self){
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT MAX(Id) FROM patient;", -1, &stmt, 0);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't get max id\n");
        sqlite3_finalize(stmt);
        exit(1);
    }

    int maxId = sqlite3_column_int(stmt, 0);

    sqlite3_finalize(stmt);
    return maxId;
}

DataHandler_t DataHandler_new(const char * db){
    DataHandler_t self = (DataHandler_t) malloc(sizeof(DataHandler_s));
    int rc = sqlite3_open(db, &self->db);
    if (SQLITE_ERROR == rc) {
        printf("can't open database\n");
        exit(1);
    }
    return self;
}

void DataHandler_delete(DataHandler_t self){
    sqlite3_close(self->db);
    free(self);
}

char * DataHandler_patientsToXmlStr(DataHandler_t self, char * mem_p){
    xmlDoc * doc = NULL;
	xmlNode * root_element = NULL;
	xmlChar * xmlStr = NULL;

	doc = xmlNewDoc("1.0");
	root_element = xmlNewNode(NULL, "patients");
	xmlDocSetRootElement(doc, root_element);

    void Pt_toXmlNode(patient_t pt){
        patient_convertToXml(pt, doc, root_element);
    }

    DataHandler_foreachPat(self, Pt_toXmlNode);

	xmlDocDumpMemory(doc, &xmlStr, NULL);

	strcpy(mem_p, xmlStr);

    free(xmlStr);
    xmlFreeDoc(doc);
    return mem_p;
}

int DataHandler_getPatientsNum(DataHandler_t self){
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT COUNT(*) FROM patient;", -1, &stmt, 0);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select count\n");
        sqlite3_finalize(stmt);
        exit(1);
    }

    int count = sqlite3_column_int(stmt, 0);

    sqlite3_finalize(stmt);
    return count;
}

patient_t DataHandler_getPatient(DataHandler_t self, unsigned int id){
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT * FROM patient WHERE Id = ?;", -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("error\n");
        sqlite3_finalize(stmt);
        exit(1);
    }else if(SQLITE_ROW != rc){
        return NULL;
    }

    patient_t pt = patient_new();
    pt->id = sqlite3_column_int(stmt, 0);
    strcpy(pt->name, sqlite3_column_text(stmt, 1));
    strcpy(pt->disease, sqlite3_column_text(stmt, 2));
    pt->time = sqlite3_column_int(stmt, 3);
    strcpy(pt->hospitalisedDate, sqlite3_column_text(stmt, 4));
    pt->mass = sqlite3_column_double(stmt, 5);


    sqlite3_finalize(stmt);
    return pt;
}

int DataHandler_addPatient(DataHandler_t self, patient_t pt){
    sqlite3_stmt * stmt = NULL;
    int newPatientId = -1;

    sqlite3_prepare_v2(self->db, "INSERT INTO patient (name, disease, time, hospitalisedDate, mass)"
                       "VALUES(?, ?, ?, ?, ?);", -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, pt->name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pt->disease, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, pt->time);
    sqlite3_bind_text(stmt, 4, pt->hospitalisedDate, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 5, pt->mass);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't insert patient\n");
        sqlite3_finalize(stmt);
        exit(1);
    }

    newPatientId = _getMaxIdPatient(self);

    sqlite3_finalize(stmt);
    return newPatientId;
}

void DataHandler_deletePatient(DataHandler_t self, unsigned int id){
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "DELETE FROM patient WHERE Id = ?;", -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't delete patient\n");
        sqlite3_finalize(stmt);
        exit(1);
    }

    sqlite3_finalize(stmt);
}

void DataHandler_foreachPat(DataHandler_t self, void (fn)(patient_t pt)){
    sqlite3_stmt * stmt = NULL;
    sqlite3_stmt * stmt1 = NULL;
    sqlite3_prepare_v2(self->db, "SELECT * FROM patient;", -1, &stmt, 0);

    int rc = sqlite3_step(stmt);
    while (SQLITE_ROW == rc) {
        patient_t patient = patient_new();
        patient->id = sqlite3_column_int(stmt, 0);
        strcpy(patient->name, sqlite3_column_text(stmt, 1));
        strcpy(patient->disease, sqlite3_column_text(stmt, 2));
        patient->time = sqlite3_column_int(stmt, 3);
        strcpy(patient->hospitalisedDate, sqlite3_column_text(stmt, 4));
        patient->mass = sqlite3_column_double(stmt, 5);

        fn(patient);

        DataHandler_updatePatiet(self, patient);

        patient_delete(patient);

        sqlite3_finalize(stmt1);
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
}

void DataHandler_updatePatiet(DataHandler_t self, patient_t pt) {
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "UPDATE patient SET name = ?, disease = ?, time = ?,hospitalisedDate = ?, mass = ?"
                       "WHERE Id = ?;", -1, &stmt, 0);

    sqlite3_bind_text(stmt, 1, pt->name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pt->disease, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, pt->time);
    sqlite3_bind_text(stmt, 4, pt->hospitalisedDate, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 5, pt->mass);
    sqlite3_bind_int(stmt, 6, pt->id);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc){
        printf("can't update investor\n");
        exit(1);
    }

    sqlite3_finalize(stmt);
}
