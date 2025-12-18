#pragma once

#include <QStringList>

class ISorter
{
public:
    ISorter(size_t nFromLine, size_t nToLine) : m_nFromLine(nFromLine), m_nToLine(nToLine) 
    {

    }

    virtual void sort(QStringList& lines) = 0;
protected:
    size_t m_nFromLine;
    size_t m_nToLine;
};

// 升序排列
class LexAscendingSorter : public ISorter
{
public:
    LexAscendingSorter(size_t nFromLine, size_t nToLine) : ISorter(nFromLine, nToLine) 
    {

    }

    void sort(QStringList& lines) override
    {
        // 升序排列
        std::sort(lines.begin(), lines.end(), [=](const QString& s1, const QString& s2) {
            return s1.compare(s2) < 0;
            // return s1 < s2;
        });
    }
};

// 升序排列忽略大小写
class LexAscendingIgnoreCaseSorter : public ISorter
{
public:
    LexAscendingIgnoreCaseSorter(size_t nFromLine, size_t nToLine) : ISorter(nFromLine, nToLine) 
    {

    }

    void sort(QStringList& lines) override
    {
        // 升序排列
        std::sort(lines.begin(), lines.end(), [=](const QString& s1, const QString& s2){
            return s1.compare(s2, Qt::CaseInsensitive) < 0;
        });
    }
};

// 降序
class LexDescendingSorter : public ISorter
{
public:
    LexDescendingSorter(size_t nFromLine, size_t nToLine) : ISorter(nFromLine, nToLine) 
    {

    }

    void sort(QStringList& lines) override
    {
        // 降序排列
        std::sort(lines.begin(), lines.end(), [=](const QString& s1, const QString& s2){
            return s1.compare(s2, Qt::CaseInsensitive) > 0;
        });
    }
};

// 降序排列忽略大小写
class LexDescendingIgnoreCaseSorter : public ISorter
{
public:
    LexDescendingIgnoreCaseSorter(size_t nFromLine, size_t nToLine) : ISorter(nFromLine, nToLine) 
    {

    }

    void sort(QStringList& lines) override
    {
        // 降序排列
        std::sort(lines.begin(), lines.end(), [=](const QString& s1, const QString& s2){
            return s1.compare(s2, Qt::CaseInsensitive) > 0;
        });
    }
};