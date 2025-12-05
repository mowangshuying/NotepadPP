#pragma once

#include <QObject>

class NewFileId {
protected:
	int m_nIndex;

};

class FileManager : public QObject
{
	Q_OBJECT
public:
    FileManager(QObject *parent = nullptr);

	int getNextNewFileId()
	{

	}
protected:

};

