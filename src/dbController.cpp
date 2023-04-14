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
    //populate table sessionRecords with 2 records if it is not created
    if (!heartwaveDB.tables().contains("sessionRecords")){
        //create table
        query.exec("CREATE TABLE IF NOT EXISTS sessionRecords (datetime TEXT PRIMARY KEY, challengeLevel INTEGER, length INTEGER NOT NULL, lowPercentage DOUBLE, medPercentage DOUBLE, highPercentage DOUBLE, averageCoherence DOUBLE NOT NULL, achievementScore DOUBLE NOT NULL, hrvGraph TEXT NOT NULL);");
    
        //populate table
        query.exec("INSERT OR REPLACE INTO sessionRecords VALUES ('2023-04-06 10:00:00', 4, 120, 30.5, 45.2, 24.3, 1.78, 42.72, '0.87416,68.6373;0.665166,90.2031;0.720152,83.3157;0.880128,68.1719;0.81526,73.5962;0.979716,61.2422;0.652678,91.9289;0.656342,91.4157;0.680488,88.1721;0.641697,93.5021;0.707528,84.8023;0.822084,72.9852;0.835624,71.8027;0.838596,71.5482;0.870849,68.8983;0.868428,69.0904;0.865385,69.3333;0.635047,94.4812;0.805882,74.4526;0.908324,66.0557;0.826531,72.5925;0.873441,68.6938;0.820378,73.137;0.620313,96.7254;0.918481,65.3253;0.956796,62.7093;0.825452,72.6875;0.656826,91.3484;0.801649,74.8458;0.904798,66.3131;0.631983,94.9393;0.675809,88.7825;0.969964,61.858;0.752135,79.7729;0.955937,62.7657;0.785224,76.4113;0.731851,81.9839;0.608615,98.5845;0.841566,71.2956;0.812339,73.8608;0.650312,92.2634;0.949094,63.2182;0.634423,94.5742;0.885935,67.725;0.78769,76.1721;0.905272,66.2784;0.754363,79.5373;0.653076,91.873;0.940319,63.8081;0.960245,62.484;0.9614,62.409;0.783425,76.5868;0.816843,73.4535;0.790889,75.864;0.793582,75.6066;0.776084,77.3113;0.769287,77.9943;0.706308,84.9488;0.804497,74.5808;0.870111,68.9567;0.858707,69.8725;0.820488,73.1272;0.708016,84.7439;0.843689,71.1163;0.896555,66.9228;0.885984,67.7213;0.736301,81.4884;0.762481,78.6905;0.890291,67.3937;0.857084,70.0048;0.86865,69.0727;0.715447,83.8637;0.831631,72.1474;0.885861,67.7307;0.858415,69.8963;0.725476,82.7043;0.838497,71.5566;0.735596,81.5665;0.752014,79.7858;0.808657,74.1971;0.715719,83.8318;0.732714,81.8874;0.892082,67.2584;0.832562,72.0667;0.823603,72.8507;0.785664,76.3686;0.708646,84.6685;0.89289,67.1976;0.791971,75.7603;0.813142,73.7878;0.863001,69.5249;0.750678,79.9278;0.73363,81.7851;0.871016,68.885;0.894367,67.0866;0.730185,82.1709;0.857,70.0117;0.730667,82.1167;0.792666,75.6939;0.847291,70.8139;0.843876,71.1005;0.780658,76.8582;0.831369,72.1701;0.809691,74.1023;0.773589,77.5606;0.810576,74.0214;0.822429,72.9546;0.842837,71.1881;0.828375,72.431;0.848436,70.7184;0.797166,75.2667;0.836234,71.7503;0.764793,78.4526;0.793207,75.6423;0.802515,74.765;0.826594,72.587;0.836038,71.767;0.806838,74.3644;0.823039,72.9006;0.782024,76.724;0.763409,78.5948;0.804539,74.5768;0.807363,74.316;0.780224,76.901;0.790047,75.9448;0.804546,74.5762;0.795317,75.4417;0.768548,78.0693;0.81988,73.1815;0.84165,71.2886;0.842193,71.2426;0.813755,73.7322;0.772308,77.6892;0.823562,72.8542;0.773446,77.5749;0.795896,75.3867;0.784139,76.5171;0.845875,70.9324;0.788734,76.0713;0.762513,78.6871;0.844311,71.0638;0.835899,71.779;0.848747,70.6924;0.759104,79.0405;0.779106,77.0114;0.801262,74.8819;0.835698,71.7962;0.765144,78.4166;0.7581,79.1452;0.808737,74.1897;');");
        query.exec("INSERT OR REPLACE INTO sessionRecords VALUES ('2023-04-06 11:03:08', 3, 108, 50.5, 45.2, 4.3, 1.45, 31.32, '0.690773,86.8592;0.795607,75.4141;0.720351,83.2927;0.872932,68.7338;0.736464,81.4703;0.846836,70.852;0.911583,65.8196;0.844136,71.0786;0.663802,90.3884;0.756629,79.2991;0.992578,60.4487;0.786472,76.29;0.937268,64.0158;0.988715,60.6848;0.673144,89.134;0.639698,93.7943;0.775678,77.3517;0.635675,94.3879;0.971062,61.788;0.681768,88.0065;0.86379,69.4614;0.786952,76.2435;0.835251,71.8347;0.771624,77.7581;0.624388,96.0941;0.866069,69.2785;0.651785,92.0549;0.730375,82.1496;0.831666,72.1444;0.682091,87.9648;0.690939,86.8384;0.922439,65.0449;0.877698,68.3607;0.81129,73.9563;0.795371,75.4365;0.614162,97.6941;0.658126,91.168;0.706954,84.8711;0.858299,69.9057;0.721928,83.1108;0.863583,69.4779;0.850876,70.5156;0.9084,66.0502;0.800851,74.9203;0.839591,71.4634;0.981544,61.1282;0.820275,73.1462;0.707634,84.7895;0.708609,84.6729;0.805806,74.4596;0.748518,80.1583;0.840504,71.3857;0.899282,66.7199;0.866144,69.2726;0.726316,82.6087;0.711476,84.3317;0.799179,75.0771;0.752208,79.7651;0.776663,77.2536;0.715012,83.9147;0.793254,75.6378;0.822133,72.9809;0.876231,68.4751;0.732103,81.9557;0.727777,82.4428;0.773917,77.5277;0.739184,81.1706;0.75684,79.277;0.827394,72.5169;0.868333,69.0979;0.817804,73.3672;0.759185,79.0321;0.793771,75.5886;0.772004,77.7198;0.859611,69.799;0.713566,84.0847;0.762776,78.6601;0.779886,76.9343;0.721201,83.1946;0.771385,77.7822;0.885692,67.7437;0.769719,77.9505;0.711889,84.2828;0.884974,67.7986;0.735863,81.5369;0.738205,81.2783;0.896449,66.9307;0.835042,71.8527;0.790413,75.9097;0.773113,77.6084;0.850053,70.5838;0.883667,67.8989;0.847623,70.7862;0.813142,73.7878;0.757885,79.1677;0.761511,78.7907;0.7501,79.9893;0.777477,77.1727;0.789931,75.956;0.813797,73.7284;0.761643,78.7771;0.848833,70.6852;0.84339,71.1415;0.808528,74.2089;0.784835,76.4492;0.823196,72.8867;0.815312,73.5915;0.816223,73.5093;0.763138,78.6227;0.825912,72.647;0.751916,79.7962;0.755984,79.3667;0.760772,78.8673;0.75786,79.1703;0.848471,70.7154;0.778703,77.0512;0.776963,77.2238;0.846696,70.8637;0.846224,70.9032;0.822169,72.9777;0.783252,76.6037;0.821251,73.0593;0.814003,73.7098;0.780875,76.8369;0.784393,76.4923;0.821887,73.0027;0.792386,75.7207;0.784493,76.4825;0.849364,70.6411;0.832317,72.0879;0.848291,70.7305;0.761007,78.8429;0.831151,72.1891;0.841681,71.2859;0.819535,73.2122;0.765986,78.3304;');");
    }
    return heartwaveDB.commit();
}

//get a QStringlist of records from the sessionRecords table in the database
//which includes datetime, challengelevel, and length fields information for each record
QStringList DBController::getHistory() {
    QSqlQuery query;
    QStringList history;

    //prepare the SELECT statement to get datetime, challengelevel, and length from sessionRecords
    query.prepare("SELECT datetime, challengeLevel, length FROM sessionRecords;");

    //execute the SELECT statement
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return history;    //return an empty QStringList in case of a query execution error
    }

    //iterate the results of the SELECT statement
    while (query.next()) {
        //get the datetime, challengelevel, and length values from the query result
        QDateTime datetime = QDateTime::fromString(query.value(0).toString(), DATE_FORMAT);
        int challengeLevel = query.value(1).toInt();
        int length = query.value(2).toInt();

        //format the QString
        QString newString = datetime.toString(DATE_FORMAT) + "\n"
            + "   Challenge Level: Level " + QString::number(challengeLevel) + "\n"
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
    query.prepare("SELECT datetime, challengeLevel, length, lowPercentage, medPercentage, highPercentage, averageCoherence, achievementScore, hrvGraph FROM sessionRecords WHERE datetime = :datetime");
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
        int challengeLevel = query.value(1).toInt();
        int length = query.value(2).toInt();
        double lowPercentage = query.value(3).toDouble();
        double medPercentage = query.value(4).toDouble();
        double highPercentage = query.value(5).toDouble();
        double averageCoherence = query.value(6).toDouble();
        double achievementScore = query.value(7).toDouble();
        QString hrvGraphString = query.value(8).toString();

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
        *record = new Record(datetime, challengeLevel, length, lowPercentage, medPercentage, highPercentage, averageCoherence, achievementScore, hrvGraph);

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
bool DBController::isValidRecord(const QDateTime& time,  const int challengeLevel, const int length, const double lowPercentage, const double medPercentage, const double highPercentage, const double averageCoherence, const double achievementScore) {
    bool isValid = true;

    if (!time.isValid()) {
        qDebug() << "Error: Database cannot add record, datetime is not valid";
        isValid = false;
    }else if (challengeLevel < 1 || challengeLevel > 4) {
        qDebug() << "Error: Database cannot add record, challenge Level is not valid";
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
bool DBController::addRecord(const QDateTime &time,  const int challengeLevel, const int length, const double lowPercentage, const double medPercentage, const double highPercentage, const double averageCoherence, const double achievementScore, const QVector<QPointF> &hrvGraph){
    //validate data
    if (!isValidRecord(time, challengeLevel, length, lowPercentage, medPercentage, highPercentage, averageCoherence, achievementScore)) {
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
    query.prepare("INSERT INTO sessionRecords (datetime, challengeLevel, length, lowPercentage, medPercentage, highPercentage, averageCoherence, achievementScore, hrvGraph) VALUES (:datetime, :challengeLevel, :length, :lowPercentage, :medPercentage, :highPercentage, :averageCoherence, :achievementScore, :hrvGraph)");

    //bind the values of involved parameters to the prepared INSERT statement
    query.bindValue(":datetime", time.toString(DATE_FORMAT));
    query.bindValue(":challengeLevel", challengeLevel);
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
