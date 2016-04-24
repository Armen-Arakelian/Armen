#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sqlite3.h>

#include "db_manager.h"
#include "patient.h"

static int getLastId(db_t * self);
static void _fillPatient(sqlite3_stmt * stmt, patient_t * pt);

struct db_s
{
    sqlite3 * db;
};

db_t * db_new(const char * dbFile)
{
    db_t * self = malloc(sizeof(struct db_s));
    int rc = sqlite3_open(dbFile, &self->db);
    if (SQLITE_ERROR == rc) {
        printf("can't open database\n");
        exit(1);
    }
    return self;
}

void db_free(db_t * self)
{
    sqlite3_close(self->db);
    free(self);
}

int db_insertPatient(db_t * self, patient_t * pt) //done
{
    int newPatientId = -1;

    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "INSERT INTO patient (name, surname, age, enDate, weight, time, disease)"
                       "VALUES(?, ?, ?, ?, ? ,?, ?);", -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, pt->name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pt->surname, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, pt->age);
    sqlite3_bind_text(stmt, 4, pt->enDate, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 5, pt->weight);
    sqlite3_bind_int(stmt, 6, pt->time);
    sqlite3_bind_text(stmt, 7, pt->disease, -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't insert patient\n");
        sqlite3_finalize(stmt);
        exit(1);
    }
    newPatientId = getLastId(self);
    return newPatientId;
}

patient_t * db_getPatientById(db_t * self, int id) //done
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT * FROM patient WHERE id = ?;", -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select count\n");
        sqlite3_finalize(stmt);
        exit(1);
    }

    patient_t * pt = patient_new();
    strcpy(pt->name, sqlite3_column_text(stmt, 1));
    strcpy(pt->surname, sqlite3_column_text(stmt, 2));
    pt->age = sqlite3_column_int(stmt, 3);
    strcpy(pt->enDate, sqlite3_column_text(stmt, 4));
    pt->weight = sqlite3_column_double(stmt, 5);
    pt->time = sqlite3_column_int(stmt, 6);
    strcpy(pt->disease, sqlite3_column_text(stmt, 7));

    sqlite3_finalize(stmt);
    return pt;
}

void db_updatePatient(db_t * self, patient_t * pt) //done
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "UPDATE patient SET name = ?, surname = ?, age = ?, enDate = ?, weight = ?, time = ? disease = ?" "WHERE id = ?;", -1, &stmt, 0);

    sqlite3_bind_int(stmt, 0, pt->id);
    sqlite3_bind_text(stmt, 1, pt->name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pt->surname, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, pt->age);
    sqlite3_bind_text(stmt, 4, pt->enDate, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 5, pt->weight);
    sqlite3_bind_int(stmt, 6, pt->time);
    sqlite3_bind_text(stmt, 7, pt->disease, -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc){
        printf("can't update patient\n");
        exit(1);
    }

    sqlite3_finalize(stmt);
}

void db_deletePatient(db_t * self, int id) //done
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "DELETE FROM patient WHERE id = ?;", -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't delete patient\n");
        sqlite3_finalize(stmt);
        exit(1);
    }

    sqlite3_finalize(stmt);
}

int db_countPatients(db_t * self)
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT COUNT(*) FROM patient;", -1, &stmt, 0);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select count\n");
        exit(1);
    }
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

static void _fillPatient(sqlite3_stmt * stmt, patient_t * pt) //done
{
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char * name = sqlite3_column_text(stmt, 1);
    const unsigned char * surname = sqlite3_column_text(stmt, 2);
    int age = sqlite3_column_int(stmt, 3);
    const unsigned char * enDate = sqlite3_column_text(stmt, 4);
    double weight = sqlite3_column_double(stmt, 5);
    int time = sqlite3_column_int(stmt, 6);
    const unsigned char * disease = sqlite3_column_text(stmt, 7);
    pt->id = id;
    strcpy(pt->name, (const char *)name);
    strcpy(pt->surname, (const char *)surname);
    pt->age = age;
    strcpy(pt->enDate, (const char *)enDate);
    pt->weight = weight;
    pt->time = time;
    strcpy(pt->disease, (const char *)disease);
}

int db_checkPatient(db_t * self, int K, char * P, patient_t * arr, int arrMax)
{
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM patient WHERE time > ? AND disease == ?;";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, K);
    sqlite3_bind_text(stmt, 2, P, -1, SQLITE_STATIC);
    int count = 0;
    while (1) {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc) {
            printf("can't select students\n");
            exit(1);
        } else if (SQLITE_DONE == rc) {
            break;
        } else {
            _fillPatient(stmt, &arr[count]);
            count++;
        }
    }
    sqlite3_finalize(stmt);
    return count;
}

static int getLastId(db_t * self){
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT MAX(id) FROM patient;", -1, &stmt, 0);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't get last id\n");
        sqlite3_finalize(stmt);
        exit(1);
    }

    int lastId = sqlite3_column_int(stmt, 0);

    sqlite3_finalize(stmt);
    return lastId;
}
