#ifndef STUDENTINFORMATION_H
#define STUDENTINFORMATION_H

#include <QVector>
#include <QString>
#include <QTextStream>
#include <QFile>


///
/// \brief The StudentInformation class
/// This is the simple class that contains the
/// data for student's data

class StudentInformation
{
private:
    QString m_name;
    qint32 m_id;
    QString m_course_name;
    QVector<quint32> m_scores;
    double m_gpa;


public:
    StudentInformation() = default;
    StudentInformation(const QString& _name, qint32 _id, QString _coursename);

    // getters/setters
    QString name() const;
    void setName(const QString &name);

    qint32 id() const;
    void setId(const qint32 &id);

    QString course_name() const;
    void setCourse_name(const QString &course_name);

    QVector<quint32> scores() const;
    void setScores(const QVector<quint32> &scores);

    double gpa() const;

    void calculateGPA();
    void addNewScore(quint32 scr);

    // file input
    friend QTextStream& operator>>(QTextStream& strm, StudentInformation& info)
    {

        info.m_name = strm.readLine();
        info.m_id = strm.readLine().toInt();
        info.m_course_name = strm.readLine();

        QString listScores = strm.readLine();
        auto lst = listScores.split(' ');

        for(const auto& it : lst)
            info.m_scores.push_back(it.toInt());

        info.calculateGPA();

        return strm;

    }

    // file output
    friend QTextStream& operator<<(QTextStream& strm, const StudentInformation& info)
    {
        QFile* file = dynamic_cast<QFile*>(strm.device());
        if(file)
        {
            QByteArray array = info.m_name.toLatin1();
            array.append("\n");
            array.append(QString::number(info.m_id).toLatin1());
            array.append("\n");
            array.append(info.m_course_name);
            array.append("\n");

            for(int i = 0; i < info.m_scores.size(); i++)
            {              
                if(i != info.m_scores.size()-1)
                   array.append(QString::number(info.m_scores[i]) + " ");
                else
                   array.append(QString::number(info.m_scores[i]));
            }
            array.append("\n");

            file->write(array);
        }
        return strm;
    }
};





#endif
