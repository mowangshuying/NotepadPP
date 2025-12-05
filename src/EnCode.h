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

	QByteArray getStartFlagByCodeId(CodeId id);


};

