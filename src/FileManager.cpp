#include "FileManager.h"
#include "ScintillaEditView.h"
#include <QFile>
#include "CompareMode.h"
#include <vector>

FileManager::FileManager(QObject* parent)
{
}

FileManager* FileManager::getMgr()
{
    static FileManager instance;
    return &instance;
}

ScintillaEditView* FileManager::newEmptyDocument()
{
    ScintillaEditView* pEditView = new ScintillaEditView();
    return pEditView;
}

int FileManager::getNextNewFileId()
{
    if (m_newFileidList.empty())
    {
        return 0;
    }

    bool bFind = false;
    int nIndex = 0;
    for (int i = 0; i < m_newFileidList.size(); i++)
    {
        if (m_newFileidList[i].getIndex() > i)
        {
            nIndex = i;
            bFind = true;
            break;
        }
    }

    if (!bFind)
    {
        nIndex = m_newFileidList.size();
    }

    return nIndex;
}

void FileManager::insertNewFileId(int nIndex, ScintillaEditView* pEditView)
{
    NewFileId newFileId(nIndex, pEditView);
    m_newFileidList.push_back(newFileId);
    std::sort(m_newFileidList.begin(), m_newFileidList.end(), [](NewFileId& a, NewFileId& b) { return a.getIndex() < b.getIndex(); });
}

void FileManager::deleteNewFileId(int nIndex)
{
    for (int i = 0; i < m_newFileidList.size(); i++)
    {
        if (m_newFileidList[i].getIndex() == nIndex)
        {
            m_newFileidList.erase(m_newFileidList.begin() + i);
            break;
        }
    }
}

int FileManager::loadFileDataInText(ScintillaEditView* pEditView, QString filepath, CodeId& cid, LineEnd& lineEnd)
{
    QFile file(filepath);
    if (!file.exists())
    {
        return -1;
    }

    QIODevice::OpenMode mode = QIODevice::ReadOnly | QIODevice::ExistingOnly;
    if (!file.open(mode))
    {
        return -1;
    }

    std::vector<FileLineInfo> lineInfoVct;
    int nMaxLineSize = 0;
    int nCharNums = 0;
    CompareMode::scanFileOutput(cid, filepath, lineInfoVct, nMaxLineSize, nCharNums);

    QString text;
    for (auto it = lineInfoVct.begin(); it != lineInfoVct.end(); it++)
    {
        text.append(it->unicodeStr);
        if (it == lineInfoVct.begin())
            lineEnd = it->lineEnd;
    }

    file.close();

    pEditView->setText(text);

    return 0;
}

int FileManager::loadFileDataByCodeId(ScintillaEditView* pEditView, QString filepath, CodeId cid, LineEnd& lineEnd)
{
    QFile file(filepath);
    if (!file.exists())
    {
        return -1;
    }

    QIODevice::OpenMode mode = QIODevice::ReadOnly | QIODevice::ExistingOnly;
    if (!file.open(mode))
    {
        return -1;
    }

    std::vector<FileLineInfo> lineInfoVct;
    int nMaxLineSize = 0;
    int nCharNums = 0;
    CompareMode::scanFileOutputByCodeId(cid, filepath, lineInfoVct, nMaxLineSize, nCharNums);

    QString text;
    for (auto it = lineInfoVct.begin(); it != lineInfoVct.end(); it++)
    {
        text.append(it->unicodeStr);
        if (it == lineInfoVct.begin())
            lineEnd = it->lineEnd;
    }

    file.close();

    pEditView->setText(text);

    return 0;
}
