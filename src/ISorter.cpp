#include "ISorter.h"

ISorter::ISorter()
{
}

ISorter* ISorter::makeSorter(SortType sortType)
{
    switch (sortType)
    {
        case SortType::LexAscending:
            return new LexAscendingSorter();
        case SortType::LexDescending:
            return new LexDescendingSorter();
        case SortType::LexAscendingIgnoreCase:
            return new LexAscendingIgnoreCaseSorter();
        case SortType::LexDescendingIgnoreCase:
            return new LexDescendingIgnoreCaseSorter();
    }
    return nullptr;
}

void ISorter::sort(QStringList& lines, SortType sortType)
{
    ISorter* pSorter = makeSorter(sortType);
    pSorter->sort(lines);
    delete pSorter;
}

LexAscendingSorter::LexAscendingSorter()
{
}

void LexAscendingSorter::sort(QStringList& lines)
{
    // 升序排列
    std::sort(lines.begin(), lines.end(), [=](const QString& s1, const QString& s2) {
        return s1.compare(s2) < 0;
        // return s1 < s2;
    });
}

LexAscendingIgnoreCaseSorter::LexAscendingIgnoreCaseSorter() : ISorter()
{
}

void LexAscendingIgnoreCaseSorter::sort(QStringList& lines)
{
    // 升序排列
    std::sort(lines.begin(), lines.end(), [=](const QString& s1, const QString& s2) { return s1.compare(s2, Qt::CaseInsensitive) < 0; });
}

LexDescendingSorter::LexDescendingSorter() : ISorter()
{
}

void LexDescendingSorter::sort(QStringList& lines)
{
    // 降序排列
    std::sort(lines.begin(), lines.end(), [=](const QString& s1, const QString& s2) { return s1.compare(s2, Qt::CaseInsensitive) > 0; });
}

LexDescendingIgnoreCaseSorter::LexDescendingIgnoreCaseSorter() : ISorter()
{
}

void LexDescendingIgnoreCaseSorter::sort(QStringList& lines)
{
    // 降序排列
    std::sort(lines.begin(), lines.end(), [=](const QString& s1, const QString& s2) { return s1.compare(s2, Qt::CaseInsensitive) > 0; });
}
