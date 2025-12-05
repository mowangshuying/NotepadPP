#include "EnCode.h"

CodeId EnCode::getCodeIdByName(QString name)
{
	//CodeId id = CodeId::Unknown;
	if (name == "Unknown")
	{
		return CodeId::Unknown;
	}
	else if (name == "Ansi")
	{
		return CodeId::Ansi;
	}
	else if (name == "Utf8")
	{
		return CodeId::Utf8;
	}
	else if (name == "Utf8Bom")
	{
		return CodeId::Utf8Bom;
	}
	else if (name == "Utf16LE")
	{
		return CodeId::Utf16LE;
	}
	else if (name == "Utf16LEBom")
	{
		return CodeId::Utf16LEBom;
	}
	else if (name == "Utf16BE")
	{
		return CodeId::Utf16BE;
	}
	else if (name == "Utf16BEBom")
	{
		return CodeId::Utf16BEBom;
	}
	else if (name == "GBK")
	{
		return CodeId::GBK;
	}

	return CodeId::Unknown;
}

QString EnCode::getCodeNameById(CodeId id)
{
	switch (id)
	{
	case CodeId::Unknown:
		return "Unknown";
	case CodeId::Ansi:
		return "Ansi";
	case CodeId::Utf8:
		return "Utf8";
	case CodeId::Utf8Bom:
		return "Utf8Bom";
	case CodeId::Utf16LE:
		return "Utf16LE";
	case CodeId::Utf16LEBom:
		return "Utf16LEBom";
	case CodeId::Utf16BE:
		return "Utf16BE";
	case CodeId::Utf16BEBom:
		return "Utf16BEBom";
	case CodeId::GBK:
		return "GBK";
	}
	return "Unknown";
}

QByteArray EnCode::getStartFlagByCodeId(CodeId id)
{
	switch (id)
	{
	case CodeId::Utf8Bom:
		return QByteArray("\xEF\xBB\xBF", 3);
	case CodeId::Utf16LEBom:
		return QByteArray("\xFF\xFE", 2);
	case CodeId::Utf16BEBom:
		return QByteArray("\xFE\xFF", 2);
	}
	return QByteArray();
}
