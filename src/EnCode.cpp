#include "EnCode.h"
#include <QTextCodec>

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
	else if (name == "EucJp")
	{
		return CodeId::EucJp;
	}
	else if(name == "ShiftJis")
	{
		return CodeId::ShiftJis;
	}
	else if (name == "EucKr")
	{
		return CodeId::EucKr;
	}
	else if (name == "Koi8R")
	{
		return CodeId::Koi8R;
	}
	else if (name == "Tis620")
	{
		return CodeId::Tis620;
	}
	else if (name == "Big5")
	{
		return CodeId::Big5;
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
	case CodeId::EucJp:
		return "EucJp";
	case CodeId::ShiftJis:
		return "ShiftJis";
	case CodeId::EucKr:
	    return "EucKr";
	case CodeId::Koi8R:
	    return "Koi8R";
	case CodeId::Tis620:
	    return "Tis620";
	case CodeId::Big5:
	    return "Big5";	
	}
	return "Unknown";
}

QString EnCode::getQtCodecNameById(CodeId id)
{
    switch (id)
	{
	case CodeId::Unknown:
		return "Unknown";
	case CodeId::Ansi:
		return "Ansi";
	case CodeId::Utf8:
		return "UTF-8";
	case CodeId::Utf8Bom:
		return "UTF-8";
	case CodeId::Utf16LE:
		return "UTF-16";
	case CodeId::Utf16LEBom:
		return "UTF-16";
	case CodeId::Utf16BE:
		return "UTF-16";
	case CodeId::Utf16BEBom:
		return "UTF-16";
	case CodeId::GBK:
		return "GB18030";
	case CodeId::EucJp:
		return "EUC-JP";
	case CodeId::ShiftJis:
		return "Shift-JIS";
	case CodeId::EucKr:
	    return "EUC-KR";
	case CodeId::Koi8R:
	    return "KOI8-R";
	case CodeId::Tis620:
	    return "TIS620";
	case CodeId::Big5:
	    return "Big5";	
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

bool EnCode::translateStringToUnicode(CodeId cid, const char *pText, int nLength, QString &outString)
{
	QString codecName = getQtCodecNameById(cid);
	QTextCodec* pCodec = QTextCodec::codecForName(codecName.toUtf8());
    return false;
}
