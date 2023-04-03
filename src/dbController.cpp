#include "dbController.h"

const Qstring DBController::DATABASE_PATH = "/database/heartwave.db";

DBController::DBController(){
    heartwaveDB = = QSqlDatabase::addDatabase("QSQLITE");
    heartwaveDB.setDatabaseName("hearwave.db");
    
    if (!heartwaveDB.open()) {
        throw "Error: Database could not be opened";
    }

    if (!DBInit()) {
        throw "Error: Database could not be initialized";
    }


}
