#pragma once

#include <QObject>
#include <QList>
#include "__global.h"


class ScintillaEditView;
class NewFileId {
public:
	NewFileId(int nIndex, ScintillaEditView* pEditView)
	{
		m_nIndex = nIndex;
		m_pEditView = pEditView;
	}

	int getIndex()
	{
		return m_nIndex;
	}

	void setIndex(int nIndex)
	{
		m_nIndex = nIndex;
	}

	ScintillaEditView* getEditView()
	{
		return m_pEditView;
	}

	void setEditView(ScintillaEditView* pEditView)
	{
		m_pEditView = pEditView;
	}

protected:
	int m_nIndex;
	ScintillaEditView* m_pEditView;
};

class FileManager : public QObject
{
	Q_OBJECT
public:
    FileManager(QObject *parent = nullptr);

	static FileManager* getMgr();

	ScintillaEditView* newEmptyDocument();

	int getNextNewFileId();

	void insertNewFileId(int nIndex, ScintillaEditView* pEditView);

	void deleteNewFileId(int nIndex);

	int loadFileDataInText(ScintillaEditView* pEditView, QString filepath, CodeId& cid, LineEnd lineEnd);
protected:
	std::vector<NewFileId> m_newFileidList;
};

