#include "datastorage.h"
#include <QFile>
#include <QTextStream>



bool DataStorage::loadFromFile(const QString &filename)
{
    // if the file is not exist create the file and write the data
    QFile file(filename);


    if(!file.open(QFile::ReadOnly)) return false;

    QTextStream stream(&file);

    while(!stream.atEnd())
    {
         StudentInformation temp;
         stream >> temp;

         students.push_back(temp);
    }

    return true;
}

const StudentInformation &DataStorage::operator[](size_t idx) const
{
    return students.at(idx);
}

StudentInformation &DataStorage::operator[](size_t idx)
{
      return students[idx];
}
// if index is valid emove the entry
void DataStorage::remove(size_t idx)
{
    if(idx < students.size() && idx >= 0)
        students.remove(idx);
}
// if index is valid change the data
void DataStorage::change(const StudentInformation &newinfo, size_t idx)
{
    if(idx < students.size() && idx >= 0)
        students[idx] = newinfo;
}

// add new entry to vector
void DataStorage::add(const StudentInformation &newinfo)
{
    students.push_back(newinfo);
}

size_t DataStorage::size() const
{
    return students.size();
}

bool DataStorage::saveToFile(const QString &filename) const
{
    // check is file exist and open file
    QFile file(filename);
    if(!file.open(QFile::WriteOnly))
        return false;

    QTextStream stream(&file);
    // save all information to file
    for(const auto& student : students)
        stream << student;

    return true;
}
