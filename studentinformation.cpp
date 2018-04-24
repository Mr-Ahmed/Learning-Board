#include "studentinformation.h"
#include <algorithm>

qint32 StudentInformation::id() const
{
    return m_id;
}

void StudentInformation::setId(const qint32 &id)
{
    m_id = id;
}

QString StudentInformation::course_name() const
{
    return m_course_name;
}

void StudentInformation::setCourse_name(const QString &course_name)
{
    m_course_name = course_name;
}

QVector<quint32> StudentInformation::scores() const
{
    return m_scores;
}

void StudentInformation::setScores(const QVector<quint32> &scores)
{
    m_scores = scores;
}

double StudentInformation::gpa() const
{
    return m_gpa;
}



void StudentInformation::calculateGPA()
{
    quint32 sum = std::accumulate(m_scores.begin(), m_scores.end(), 0);
    m_gpa = static_cast<double>(sum)/m_scores.size();
}

void StudentInformation::addNewScore(quint32 scr)
{
    m_scores.push_back(scr);
}

StudentInformation::StudentInformation(const QString &_name, qint32 _id, QString _coursename)
    : m_name(_name), m_id(_id), m_course_name(_coursename)
{

}

QString StudentInformation::name() const
{
    return m_name;
}

void StudentInformation::setName(const QString &name)
{
    m_name = name;
}
