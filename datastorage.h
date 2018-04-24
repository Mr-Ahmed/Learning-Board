#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QVector>
#include <QString>
#include "studentinformation.h"


const QString FILENAME = "db.txt";

class DataStorage
{
private:
    QVector<StudentInformation> students;

public:
    //load data from file
    bool loadFromFile(const QString& filename);
    const StudentInformation& operator[] (size_t idx) const;
    StudentInformation& operator[] (size_t idx);
    void remove(size_t idx);
    void change(const StudentInformation& newinfo, size_t idx);
    void add(const StudentInformation& newinfo);
    // number of entries
    size_t size() const;
    // save data to file
    bool saveToFile(const QString& filename) const;
};

#endif // DATASTORAGE_H
