#pragma once

#include "__global.h"
#include <QtGlobal>
#include <QString>

class EnCode
{
public:
	EnCode()
	{
	}

	~EnCode()
	{

	}
public:
	static CodeId getCodeIdByName(QString name);
    static QString getCodeNameById(CodeId id);
	static QString getQtCodecNameById(CodeId id);
	static QByteArray getStartFlagByCodeId(CodeId id);
	static bool translateStringToUnicode(CodeId cid, const char* pText, int nLength, QString& outString);
};

