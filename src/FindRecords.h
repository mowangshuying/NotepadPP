#pragma once

#include <QString>
#include <QVector>

class FindRecord
{
  public:
    FindRecord() : m_nLineNum(0), m_nLineStartPos(0), m_nTargetStartPos(0), m_nTargetEndPos(0), m_sLineContents("")
    {
    }

    void setLineNums(int lineNums)
    {
        m_nLineNum = lineNums;
    }

    int getLineNums() const
    {
        return m_nLineNum;
    }

    void setLineStartPos(int lineStartPos)
    {
        m_nLineStartPos = lineStartPos;
    }

    int getLineStartPos() const
    {
        return m_nLineStartPos;
    }

    void setTargetStartPos(int targetStartPos)
    {
        m_nTargetStartPos = targetStartPos;
    }

    int getTargetStartPos() const
    {
        return m_nTargetStartPos;
    }

    void setTargetEndPos(int targetEndPos)
    {
        m_nTargetEndPos = targetEndPos;
    }

    int getTargetEndPos() const
    {
        return m_nTargetEndPos;
    }

    void setLineContents(const QString& lineContents)
    {
        m_sLineContents = lineContents;
    }

    QString getLineContents() const
    {
        return m_sLineContents;
    }

  protected:
    int m_nLineNum;
    int m_nLineStartPos;
    int m_nTargetStartPos;
    int m_nTargetEndPos;
    QString m_sLineContents;
};

class ScintillaEditView;
class FindRecords
{
  public:
    FindRecords()
    {
    }

    void setFindFilePath(const QString& filepath)
    {
        m_findFilePath = filepath;
    }

    QString getFindFilePath() const
    {
        return m_findFilePath;
    }

    void setFindText(const QString& text)
    {
        findText = text;
    }

    QString getFindText() const
    {
        return findText;
    }

    void setHeightLightColor(int nColor)
    {
        m_nHeightLightColor = nColor;
    }

    int getHeightLightColor() const
    {
        return m_nHeightLightColor;
    }

    void setEditView(ScintillaEditView* pEdit)
    {
        m_editView = pEdit;
    }

    ScintillaEditView* getEditView() const
    {
        return m_editView;
    }

    void addFindRecord(const FindRecord& findRecord)
    {
        m_findRecordList.push_back(findRecord);
    }

    QVector<FindRecord>& getFindRecordList()
    {
        return m_findRecordList;
    }

  protected:
    QString m_findFilePath;
    QString findText;
    int m_nHeightLightColor;
    ScintillaEditView* m_editView;
    QVector<FindRecord> m_findRecordList;
};