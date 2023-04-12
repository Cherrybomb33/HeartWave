#include "dbController.h"

//file path for the SQLite database file "heartwave.db"
const QString DBController::DATABASE_PATH = "/database/heartwave.db";

//constructor that creates a DBController managing hearwave database
DBController::DBController() {
    //creates a new database connection object with the SQLite driver type
    //which allows connection and interacttion with an SQLite database
    heartwaveDB = QSqlDatabase::addDatabase("QSQLITE");
    
    //specify the name of the database file to be used
    heartwaveDB.setDatabaseName("heartwave.db");

    if (!heartwaveDB.open()) {
        throw "Error: Database could not be opened";
    }

    if (!dbInit()) {
        throw "Error: Database failed to be initialized";
    }
}

//initialize heartwave database with two records
bool DBController::dbInit() {
    //start a new transaction
    if (!heartwaveDB.transaction()) {
        qDebug() << "Error: Transaction failed to start:" << heartwaveDB.lastError().text();
        return false;
    }

    QSqlQuery query;
    //create table
    query.exec("CREATE TABLE IF NOT EXISTS sessionRecords (datetime TEXT PRIMARY KEY, length INTEGER NOT NULL, lowPercentage DOUBLE, medPercentage DOUBLE, highPercentage DOUBLE, averageCoherence DOUBLE NOT NULL, achievementScore DOUBLE NOT NULL, hrvGraph TEXT NOT NULL);");
    
    //populate table
    query.exec("INSERT OR REPLACE INTO sessionRecords VALUES ('2023-04-06 10:00:00', 180, 30.5, 45.2, 24.3, 5.6, 75.3, '0.97,63;1.93,62;2.92,61;3.88,64;4.87,65;5.84,62;6.81,63;7.78,62;8.76,61;9.72,64;10.73,63;11.69,62;12.68,65;13.67,64;14.63,61;15.62,62;16.58,63;17.55,61;18.53,64;19.51,63;20.48,62;21.47,65;22.44,64;23.41,62;24.37,61;25.33,64;26.32,63;27.29,62;28.28,65;29.25,64;30.22,61;31.20,62;32.17,63;33.14,61;34.12,64;35.08,63;36.07,62;37.05,65;38.02,64;38.98,61;39.94,62;40.93,63;41.90,61;42.89,64;43.86,63;44.83,62;45.81,65;46.78,64;47.74,61;48.73,62;49.70,63;50.68,61;51.65,64;52.63,63;53.61,62;54.58,65;55.56,64;56.53,61;57.52,62;58.49,63;59.45,61;60.44,64;61.41,63;62.39,62;63.37,65;64.33,64;65.30,61;66.29,62;67.26,63;68.24,61;69.20,64;70.19,63;71.17,62;72.15,65;73.11,64;74.08,61;75.07,62;76.04,63;77.01,61;77.99,64;78.95,63;79.94,62;80.92,65;81.89,64;82.86,61;83.83,62;84.81,63;85.78,61;86.76,64;87.73,63;88.70,62;89.67,65;90.64,64;91.62,61;92.59,62;93.57,63;94.54,61;95.52,64;96.49,63;97.47,62;98.44,65;99.42,64;100.39,61;101.37,62;102.34,63;103.31,61;104.29,64;105.26,63;106.24,62;107.21,65;108.19,64;109.16,61;110.14,62;111.11,63;112.08,61;113.05,64;114.03,63;115.00,62;115.98,65;116.95,64;117.93,61;118.91,62;119.88,63;120.85,61;121.83,64;122.80,63;123.78,62;124.75,65;125.73,64;126.70,61;127.68,62;128.65,63;129.62,61;130.60,64;131.57,63;132.55,62;133.52,65;134.50,64;135.47,61;136.45,62;137.42,63;138.39,61;139.37,64;140.34,63;141.32,62;142.29,65;143.27,64;144.24,61;145.22,62;146.19,63;147.16,61;148.14,64;149.11,63;150.09,62;151.06,65;152.04,64;153.01,61;153.99,62;154.96,63;155.93,61;156.91,64;157.88,63;158.86,62;159.83,65;160.81,64;161.78,61;162.76,62;163.73,63;164.70,61;165.68,64;166.65,63;167.63,62;168.60,65;169.58,64;170.55,61;171.53,62;172.50,63;173.47,61;174.45,64;175.42,63;176.40,62;177.37,65;178.35,64;179.32,61;');");
    query.exec("INSERT OR REPLACE INTO sessionRecords VALUES ('2023-04-06 11:03:08', 108, 50.5, 45.2, 4.3, 3.6, 55.3, '0.61,92;1.24,89;1.84,87;2.43,90;3.03,91;3.64,92;4.26,89;4.87,87;5.47,90;6.08,91;6.69,92;7.31,89;7.92,87;8.52,90;9.13,91;9.74,92;10.36,89;10.97,87;11.57,90;12.18,91;12.79,92;13.41,89;14.02,87;14.62,90;15.23,91;15.84,92;16.46,89;17.07,87;17.67,90;18.28,91;18.89,92;19.51,89;20.12,87;20.72,90;21.33,91;21.94,92;22.56,89;23.17,87;23.77,90;24.38,91;24.99,92;25.61,89;26.22,87;26.82,90;27.43,91;28.04,92;28.66,89;29.27,87;29.87,90;30.48,91;31.09,92;31.71,89;32.32,87;32.92,90;33.53,91;34.14,92;34.76,89;35.37,87;35.97,90;36.58,91;37.19,92;37.81,89;38.42,87;39.02,90;39.63,91;40.24,92;40.86,89;41.47,87;42.07,90;42.68,91;43.29,92;43.91,89;44.52,87;45.12,90;45.73,91;46.34,92;46.96,89;47.57,87;48.17,90;48.78,91;49.39,92;50.01,89;50.62,87;51.22,90;51.83,91;52.44,92;53.06,89;53.67,87;54.27,90;54.88,91;55.49,92;56.11,89;56.72,87;57.32,90;57.93,91;58.54,92;59.16,89;59.77,87;60.37,90;60.98,91;61.59,92;62.21,89;62.82,87;63.42,90;64.03,91;64.64,92;65.26,89;65.87,87;66.47,90;67.08,91;67.69,92;68.31,89;68.92,87;69.52,90;70.13,91;70.74,92;71.36,89;71.97,87;72.57,90;73.18,91;73.79,92;74.41,89;75.02,87;75.62,90;76.23,91;76.84,92;77.46,89;78.07,87;78.67,90;79.28,91;79.89,92;80.51,89;81.12,87;81.72,90;82.33,91;82.94,92;83.56,89;84.17,87;84.77,90;85.38,91;85.99,92;86.61,89;87.22,87;87.82,90;88.43,91;89.04,92;89.66,89;90.27,87;90.87,90;91.48,91;92.09,92;92.71,89;93.32,87;93.92,90;94.53,91;95.14,92;95.76,89;96.37,87;96.97,90;97.58,91;98.19,92;98.81,89;99.42,87;100.02,90;100.63,91;101.24,92;101.86,89;102.47,87;103.07,90;103.68,91;104.29,92;104.91,89;105.52,87;106.12,90;106.73,91;107.34,92;107.96,89;');");

    return heartwaveDB.commit();
}

//get a QStringlist of records from the sessionRecords table in the database
//which includes datetime, challengelevel, and length fields information for each record
QStringList DBController::getHistory() {
    QSqlQuery query;
    QStringList history;

    //prepare the SELECT statement to get datetime, challengelevel, and length from sessionRecords
    query.prepare("SELECT datetime, length FROM sessionRecords;");

    //execute the SELECT statement
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return history;    //return an empty QStringList in case of a query execution error
    }

    //iterate the results of the SELECT statement
    while (query.next()) {
        //get the datetime, challengelevel, and length values from the query result
        QDateTime datetime = QDateTime::fromString(query.value(0).toString(), DATE_FORMAT);
        //int challengeLevel = query.value(1).toInt();
        int length = query.value(1).toInt();

        //format the QString
        QString newString = datetime.toString(DATE_FORMAT) + "\n"
            //+ "   Challenge Level: Level " + QString::number(challengeLevel) + "\n"
            + "   Length: " + QString::number(length / 60)
            + ((length % 60 < 10) ? ":0" + QString::number(length % 60) : ":" + QString::number(length % 60));

        //add the QString to the history QStringList
        history.push_back(newString);
    }

    return history;
}

//get the record with the specified datetime from the database. 
//If a record is found, initialize a new Record object with the query result,
//and store it to record output parameter and return true. 
//If the record is not found, returns false.
bool DBController::getRecord(const QDateTime& time, Record** record){  
    QSqlQuery query;
    //prepare the SELECT statement
    query.prepare("SELECT datetime, length, lowPercentage, medPercentage, highPercentage, averageCoherence, achievementScore, hrvGraph FROM sessionRecords WHERE datetime = :datetime");
    query.bindValue(":datetime", time.toString(DATE_FORMAT));

    //execute the SELECT statement
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    //check if a record with the specified datetime exists
    if (query.next()) {
        // if the record exists, extract the values from the query result
        QDateTime datetime = QDateTime::fromString(query.value(0).toString(), DATE_FORMAT);
        //int challengeLevel = query.value(1).toInt();
        int length = query.value(1).toInt();
        double lowPercentage = query.value(2).toDouble();
        double medPercentage = query.value(3).toDouble();
        double highPercentage = query.value(4).toDouble();
        double averageCoherence = query.value(5).toDouble();
        double achievementScore = query.value(6).toDouble();
        QString hrvGraphString = query.value(7).toString();

        // Convert the hrvGraphString to QVector<QPointF>
        QVector<QPointF> hrvGraph;
        QStringList hrvGraphStringList = hrvGraphString.split(";");
        for (const QString& pointString : hrvGraphStringList) {
            QStringList pointCoordinates = pointString.split(",");
            if (pointCoordinates.size() == 2) {
                QPointF point(pointCoordinates[0].toDouble(), pointCoordinates[1].toDouble());
                hrvGraph.push_back(point);
            }
        }

        // Create a new Record object with the extracted values
        *record = new Record(datetime, length, lowPercentage, medPercentage, highPercentage, averageCoherence, achievementScore, hrvGraph);

        return true;
    } else {
        //if the record doesn't exist, return false
        return false;
    }

}

//delete a record from the database and return true it the removal is successful or false otherwise.
bool DBController::deleteRecord(const QDateTime& time) {
    QSqlQuery query;
    //prepare the DELETE statement
    query.prepare("DELETE FROM sessionRecords WHERE datetime = :datetime");

    //bind the value of datetime
    QString datetimeDelete = time.toString(DATE_FORMAT);
    query.bindValue(":datetime", datetimeDelete);

    //execute the DELETE statement
    if (query.exec()) {
        qDebug() << "Record with datetime " << datetimeDelete << " deleted successfully.";
        return true;
    } else {
        qDebug() << "Error deleting record: " << query.lastError().text();
        return false;
    }
}

/*check the record parameters are valid or not. 
  Parameters include:
  time - the time the session started in QDateTime format
  challengeLevel - the challenge level set by user, the range is 1-4
  length - the duration of a measurement session in seconds
  lowPercentage/medPercentage/highPercentage - percentage of time in different coherence levels low/medium/high
  averageCoherence - average of coherence scores
  achievementScore - total sum of coherence scores sampled every 5 seconds
  Returen true if the parameters are all valid and false otherwise
*/
bool DBController::isValidRecord(const QDateTime& time, const int length, const double lowPercentage, const double medPercentage, const double highPercentage, const double averageCoherence, const double achievementScore) {
    bool isValid = true;

    if (!time.isValid()) {
        qDebug() << "Error: Database cannot add record, datetime is not valid";
        isValid = false;
    }else if (length <= 0) {
        qDebug() << "Error: Database cannot add record, length is not valid";
        isValid = false;
    }else if (lowPercentage < 0 || medPercentage < 0 || highPercentage < 0 || averageCoherence < 0 || achievementScore < 0){
        qDebug() << "Error: Database cannot add record, lowPercentage/medPercentage/highPercentage/averageCoherence/achievementScore is not valid";
        isValid = false;
    }
    return isValid;
}

//add a session record to the database and return true if successful and false otherwise.
bool DBController::addRecord(const QDateTime &time, const int length, const double lowPercentage, const double medPercentage, const double highPercentage, const double averageCoherence, const double achievementScore, const QVector<QPointF> &hrvGraph){
    //validate data
    if (!isValidRecord(time, length, lowPercentage, medPercentage, highPercentage, averageCoherence, achievementScore)) {
        return false;
    }

    //start a new transaction
    if (!heartwaveDB.transaction()) {
        qDebug() << "Error: Transaction failed to start:" << heartwaveDB.lastError().text();
        return false;
    }

    QSqlQuery query;

    //convert QVector<QPointF> to a QString
    QStringList hrvGraphStringList;
    for (const QPointF &point : hrvGraph) {
        hrvGraphStringList << QString("%1,%2").arg(point.x()).arg(point.y());
    }
    QString hrvGraphString = hrvGraphStringList.join(";");

    //prepare the INSERT statement
    query.prepare("INSERT INTO sessionRecords (datetime, length, lowPercentage, medPercentage, highPercentage, averageCoherence, achievementScore, hrvGraph) VALUES (:datetime, :length, :lowPercentage, :medPercentage, :highPercentage, :averageCoherence, :achievementScore, :hrvGraph)");

    //bind the values of involved parameters to the prepared INSERT statement
    query.bindValue(":datetime", time.toString(DATE_FORMAT));
    query.bindValue(":length", length);
    query.bindValue(":lowPercentage", lowPercentage);
    query.bindValue(":medPercentage", medPercentage);
    query.bindValue(":highPercentage", highPercentage);
    query.bindValue(":averageCoherence", averageCoherence);
    query.bindValue(":achievementScore", achievementScore);
    query.bindValue(":hrvGraph", hrvGraphString);

    //execute the INSERT statement.Log the error and rollback the transaction if there's an error when doing the query
    if (!query.exec()) {
        qDebug() << "Error: Failed to insert record:" << query.lastError().text();
        heartwaveDB.rollback();
        return false;
    }

    //commit the transaction
    return heartwaveDB.commit();
}

//reset database to the initial contidion
bool DBController::reset() {
    QSqlQuery query;

    if (heartwaveDB.isOpen()) {
            // Close the connection
            heartwaveDB.close();
     }

    if (!heartwaveDB.open()) {
        throw "Error: Database could not be opened";
    }

    //start a new transaction
    if (!heartwaveDB.transaction()) {
        qDebug() << "Error: Transaction failed to start:" << heartwaveDB.lastError().text();
        return false;
    }

    //delete all records from the sessionRecords table
    //query.prepare("DELETE FROM sessionRecords;");
    if (!query.exec("DELETE FROM sessionRecords;")) {
        qDebug() << "Error: Failed to delete all records from sessionRecords:" << query.lastError().text();
        heartwaveDB.rollback();
        return false;
    }

    if (!query.exec("DROP TABLE IF EXISTS sessionRecords;")) {
        qDebug() << "Error deleting table sessionRecords:" << query.lastError().text();
    }

    //if (!query.exec("INSERT OR REPLACE INTO sessionRecords VALUES ('2023-04-06 11:03:08', 108, 50.5, 45.2, 4.3, 3.6, 55.3, '0.61,92;1.24,89;1.84,87;2.43,90;3.03,91;3.64,92;4.26,89;4.87,87;5.47,90;6.08,91;6.69,92;7.31,89;7.92,87;8.52,90;9.13,91;9.74,92;10.36,89;10.97,87;11.57,90;12.18,91;12.79,92;13.41,89;14.02,87;14.62,90;15.23,91;15.84,92;16.46,89;17.07,87;17.67,90;18.28,91;18.89,92;19.51,89;20.12,87;20.72,90;21.33,91;21.94,92;22.56,89;23.17,87;23.77,90;24.38,91;24.99,92;25.61,89;26.22,87;26.82,90;27.43,91;28.04,92;28.66,89;29.27,87;29.87,90;30.48,91;31.09,92;31.71,89;32.32,87;32.92,90;33.53,91;34.14,92;34.76,89;35.37,87;35.97,90;36.58,91;37.19,92;37.81,89;38.42,87;39.02,90;39.63,91;40.24,92;40.86,89;41.47,87;42.07,90;42.68,91;43.29,92;43.91,89;44.52,87;45.12,90;45.73,91;46.34,92;46.96,89;47.57,87;48.17,90;48.78,91;49.39,92;50.01,89;50.62,87;51.22,90;51.83,91;52.44,92;53.06,89;53.67,87;54.27,90;54.88,91;55.49,92;56.11,89;56.72,87;57.32,90;57.93,91;58.54,92;59.16,89;59.77,87;60.37,90;60.98,91;61.59,92;62.21,89;62.82,87;63.42,90;64.03,91;64.64,92;65.26,89;65.87,87;66.47,90;67.08,91;67.69,92;68.31,89;68.92,87;69.52,90;70.13,91;70.74,92;71.36,89;71.97,87;72.57,90;73.18,91;73.79,92;74.41,89;75.02,87;75.62,90;76.23,91;76.84,92;77.46,89;78.07,87;78.67,90;79.28,91;79.89,92;80.51,89;81.12,87;81.72,90;82.33,91;82.94,92;83.56,89;84.17,87;84.77,90;85.38,91;85.99,92;86.61,89;87.22,87;87.82,90;88.43,91;89.04,92;89.66,89;90.27,87;90.87,90;91.48,91;92.09,92;92.71,89;93.32,87;93.92,90;94.53,91;95.14,92;95.76,89;96.37,87;96.97,90;97.58,91;98.19,92;98.81,89;99.42,87;100.02,90;100.63,91;101.24,92;101.86,89;102.47,87;103.07,90;103.68,91;104.29,92;104.91,89;105.52,87;106.12,90;106.73,91;107.34,92;107.96,89;');")){
        //qDebug() << "Error inserting second record:" << query.lastError().text();
        //return false;
    //}

    //commit the transaction
    if (!heartwaveDB.commit()) {
        qDebug() << "Error: Transaction failed to commit:" << heartwaveDB.lastError().text();
        heartwaveDB.rollback();
        return false;
    }

    //re-initialize the database
    if (!dbInit()) {
        qDebug() << "Error: Re-initializing the database failed";
        return false;
   }

    qDebug() << "Reset database successfully";
    return true;
}
