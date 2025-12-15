#pragma once

#include "__global.h"
#include <QtGlobal>
#include <QString>
#include <vector>

class EnCode
{
public:
	EnCode() = default;
	~EnCode() = default;
public:
	static CodeId getCodeIdByName(QString name);
    static QString getCodeNameById(CodeId id);
    static QString getQtCodecNameById(CodeId id);
	static QByteArray getStartFlagByCodeId(CodeId id);
	static bool translateStringToUnicode(CodeId cid, const char* pText, int nLength, QString& outString);
	static std::vector<QString> getAllCodecNames();

	static QString getLineEndNameByLineEndId(LineEnd lineEnd)
	{
		QString ret;

		switch (lineEnd)
		{
		case LineEnd::Unknown:
	#ifdef WIN32
			ret = "Windows(CR LF)";
	#else
			ret = "Unix(LF)";
	#endif
			ret = "NULL";
			break;
		case LineEnd::Unix:
			ret = "Unix(LF)";
			break;
		case LineEnd::Dos:
			ret = "Windows(CR LF)";
			break;
		case LineEnd::Mac:
			ret = "Mac(CR)";
			break;
		default:
			break;
		}
		return  ret;
	}
};

