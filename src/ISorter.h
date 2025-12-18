#pragma once

#include <QStringList>

class LexAscendingSorter;
class LexDescendingSorter;
class LexIgnoreCaseAscendingSorter;
class LexIgnoreCaseDescendingSorter;

enum class SortType
{
    LexAscending,
    LexDescending,
    LexAscendingIgnoreCase,
    LexDescendingIgnoreCase,
};

class ISorter
{

public:
    ISorter();

    virtual void sort(QStringList& lines) = 0;

    static ISorter* makeSorter(SortType sortType);

    static void sort(QStringList& lines, SortType sortType);
protected:
    // size_t m_nFromLine;
    // size_t m_nToLine;
};

// 升序排列
class LexAscendingSorter : public ISorter
{
public:
    LexAscendingSorter();

    void sort(QStringList& lines) override;
};

// 升序排列忽略大小写
class LexAscendingIgnoreCaseSorter : public ISorter
{
public:
    LexAscendingIgnoreCaseSorter();

    void sort(QStringList& lines) override;
};

// 降序
class LexDescendingSorter : public ISorter
{
public:
    LexDescendingSorter();

    void sort(QStringList& lines) override;
};

// 降序排列忽略大小写
class LexDescendingIgnoreCaseSorter : public ISorter
{
public:
    LexDescendingIgnoreCaseSorter();

    void sort(QStringList& lines) override;
};