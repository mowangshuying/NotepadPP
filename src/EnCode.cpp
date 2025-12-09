#include "EnCode.h"
#include <QTextCodec>

CodeId EnCode::getCodeIdByName(QString name)
{
	if (name == "UNKNOWN")
	{
		return CodeId::UNKNOWN;
	}
	else if (name == "Big5")
	{
		return CodeId::Big5;
	}
	else if (name == "Big5-HKSCS")
	{
		return CodeId::Big5_HKSCS;
	}
	else if (name == "CP949")
	{
		return CodeId::CP949;
	}
	else if (name == "EUC-JP")
	{
		return CodeId::EUC_JP;
	}
	else if (name == "EUC-KR")
	{
		return CodeId::EUC_KR;
	}
	else if (name == "GB18030")
	{
		return CodeId::GB18030;
	}
	else if (name == "HP-ROMAN8")
	{
		return CodeId::HP_ROMAN8;
	}
	else if (name == "IBM 850")
	{
		return CodeId::IBM_850;
	}
	else if (name == "IBM 866")
	{
		return CodeId::IBM_866;
	}
	else if (name == "IBM 874")
	{
		return CodeId::IBM_874;
	}
	else if (name == "ISO 2022-JP")
	{
		return CodeId::ISO_2022_JP;
	}
	else if (name == "ISO-8859-1")
	{
		return CodeId::ISO_8859_1;
	}
	else if (name == "ISO-8859-2")
	{
		return CodeId::ISO_8859_2;
	}
	else if (name == "ISO-8859-3")
	{
		return CodeId::ISO_8859_3;
	}
	else if (name == "ISO-8859-4")
	{
		return CodeId::ISO_8859_4;
	}
	else if (name == "ISO-8859-5")
	{
		return CodeId::ISO_8859_5;
	}
	else if (name == "ISO-8859-6")
	{
		return CodeId::ISO_8859_6;
	}
	else if (name == "ISO-8859-7")
	{
		return CodeId::ISO_8859_7;
	}
	else if (name == "ISO-8859-8")
	{
		return CodeId::ISO_8859_8;
	}
	else if (name == "ISO-8859-9")
	{
		return CodeId::ISO_8859_9;
	}
	else if (name == "ISO-8859-10")
	{
		return CodeId::ISO_8859_10;
	}
	else if (name == "ISO-8859-13")
	{
		return CodeId::ISO_8859_13;
	}
	else if (name == "ISO-8859-14")
	{
		return CodeId::ISO_8859_14;
	}
	else if (name == "ISO-8859-15")
	{
		return CodeId::ISO_8859_15;
	}
	else if (name == "ISO-8859-16")
	{
		return CodeId::ISO_8859_16;
	}
	else if (name == "KOI8-R")
	{
		return CodeId::KOI8_R;
	}
	else if (name == "KOI8-U")
	{
		return CodeId::KOI8_U;
	}
	else if (name == "Macintosh")
	{
		return CodeId::Macintosh;
	}
	else if (name == "Shift_JIS")
	{
		return CodeId::Shift_JIS;
	}
	else if (name == "TIS-620")
	{
		return CodeId::TIS_620;
	}
	else if (name == "TSCII")
	{
		return CodeId::TSCII;
	}
	else if (name == "UTF-8")
	{
		return CodeId::UTF_8;
	}
	else if (name == "UTF-8 BOM")
	{
		return CodeId::UTF_8BOM;
	}
	else if (name == "UTF-16")
	{
		return CodeId::UTF_16;
	}
	else if (name == "UTF-16BE")
	{
		return CodeId::UTF_16BE;
	}
	else if (name == "UTF-16BE BOM")
	{
		return CodeId::UTF_16BEBOM;
	}
	else if (name == "UTF-16LE")
	{
		return CodeId::UTF_16LE;
	}
	else if (name == "UTF-16LE BOM")
	{
		return CodeId::UTF_16LEBOM;
	}
	else if (name == "UTF-32")
	{
		return CodeId::UTF_32;
	}
	else if (name == "UTF-32BE")
	{
		return CodeId::UTF_32BE;
	}
	else if (name == "UTF-32LE")
	{
		return CodeId::UTF_32LE;
	}

	return CodeId::UNKNOWN;
}

QString EnCode::getCodeNameById(CodeId id)
{
	switch (id)
	{
	case CodeId::UNKNOWN:
		return "UNKNOWN";
	case CodeId::Big5:
		return "Big5";
	case CodeId::Big5_HKSCS:
		return "Big5-HKSCS";
	case CodeId::CP949:
		return "CP949";
	case CodeId::EUC_JP:
		return "EUC-JP";
	case CodeId::EUC_KR:
		return "EUC-KR";
	case CodeId::GB18030:
		return "GB18030";
	case CodeId::HP_ROMAN8:
		return "HP-ROMAN8";
	case CodeId::IBM_850:
		return "IBM 850";
	case CodeId::IBM_866:
		return "IBM 866";
	case CodeId::IBM_874:
		return "IBM 874";
	case CodeId::ISO_2022_JP:
		return "ISO 2022-JP";
	case CodeId::ISO_8859_1:
		return "ISO-8859-1";
	case CodeId::ISO_8859_2:
		return "ISO-8859-2";
	case CodeId::ISO_8859_3:
		return "ISO-8859-3";
	case CodeId::ISO_8859_4:
		return "ISO-8859-4";
	case CodeId::ISO_8859_5:
		return "ISO-8859-5";
	case CodeId::ISO_8859_6:
		return "ISO-8859-6";
	case CodeId::ISO_8859_7:
		return "ISO-8859-7";
	case CodeId::ISO_8859_8:
		return "ISO-8859-8";
	case CodeId::ISO_8859_9:
		return "ISO-8859-9";
	case CodeId::ISO_8859_10:
		return "ISO-8859-10";
	case CodeId::ISO_8859_13:
		return "ISO-8859-13";
	case CodeId::ISO_8859_14:
		return "ISO-8859-14";
	case CodeId::ISO_8859_15:
		return "ISO-8859-15";
	case CodeId::ISO_8859_16:
		return "ISO-8859-16";
	case CodeId::KOI8_R:
		return "KOI8-R";
	case CodeId::KOI8_U:
		return "KOI8-U";
	case CodeId::Macintosh:
		return "Macintosh";
	case CodeId::Shift_JIS:
		return "Shift_JIS";
	case CodeId::TIS_620:
		return "TIS-620";
	case CodeId::TSCII:
		return "TSCII";
	case CodeId::UTF_8:
		return "UTF-8";
	case CodeId::UTF_8BOM:
		return "UTF-8 BOM";
	case CodeId::UTF_16:
		return "UTF-16";
	case CodeId::UTF_16BE:
		return "UTF-16BE";
	case CodeId::UTF_16BEBOM:
		return "UTF-16BE BOM";
	case CodeId::UTF_16LE:
		return "UTF-16LE";
	case CodeId::UTF_16LEBOM:
		return "UTF-16LE BOM";
	case CodeId::UTF_32:
		return "UTF-32";
	case CodeId::UTF_32BE:
		return "UTF-32BE";
	case CodeId::UTF_32LE:
		return "UTF-32LE";
	}
	return "UNKNOWN";
}

QString EnCode::getQtCodecNameById(CodeId id)
{
    switch (id)
	{
	case CodeId::UNKNOWN:
		return "UNKNOWN";
	case CodeId::Big5:
		return "Big5";
	case CodeId::Big5_HKSCS:
		return "Big5-HKSCS";
	case CodeId::CP949:
		return "CP949";
	case CodeId::EUC_JP:
		return "EUC-JP";
	case CodeId::EUC_KR:
		return "EUC-KR";
	case CodeId::GB18030:
		return "GB18030";
	case CodeId::HP_ROMAN8:
		return "HP-ROMAN8";
	case CodeId::IBM_850:
		return "IBM 850";
	case CodeId::IBM_866:
		return "IBM 866";
	case CodeId::IBM_874:
		return "IBM 874";
	case CodeId::ISO_2022_JP:
		return "ISO 2022-JP";
	case CodeId::ISO_8859_1:
		return "ISO 8859-1";
	case CodeId::ISO_8859_2:
		return "ISO 8859-2";
	case CodeId::ISO_8859_3:
		return "ISO 8859-3";
	case CodeId::ISO_8859_4:
		return "ISO 8859-4";
	case CodeId::ISO_8859_5:
		return "ISO 8859-5";
	case CodeId::ISO_8859_6:
		return "ISO 8859-6";
	case CodeId::ISO_8859_7:
		return "ISO 8859-7";
	case CodeId::ISO_8859_8:
		return "ISO 8859-8";
	case CodeId::ISO_8859_9:
		return "ISO 8859-9";
	case CodeId::ISO_8859_10:
		return "ISO 8859-10";
	case CodeId::ISO_8859_13:
		return "ISO 8859-13";
	case CodeId::ISO_8859_14:
		return "ISO 8859-14";
	case CodeId::ISO_8859_15:
		return "ISO 8859-15";
	case CodeId::ISO_8859_16:
		return "ISO 8859-16";
	case CodeId::KOI8_R:
		return "KOI8-R";
	case CodeId::KOI8_U:
		return "KOI8-U";
	case CodeId::Macintosh:
		return "Macintosh";
	case CodeId::Shift_JIS:
		return "Shift_JIS";
	case CodeId::TIS_620:
		return "TIS-620";
	case CodeId::TSCII:
		return "TSCII";
	case CodeId::UTF_8:
		return "UTF-8";
	case CodeId::UTF_8BOM:
		return "UTF-8";
	case CodeId::UTF_16:
		return "UTF-16";
	case CodeId::UTF_16BE:
		return "UTF-16BE";
	case CodeId::UTF_16BEBOM:
		return "UTF-16BE";
	case CodeId::UTF_16LE:
		return "UTF-16LE";
	case CodeId::UTF_16LEBOM:
		return "UTF-16LE";
	case CodeId::UTF_32:
		return "UTF-32";
	case CodeId::UTF_32BE:
		return "UTF-32BE";
	case CodeId::UTF_32LE:
		return "UTF-32LE";
	}
	return "UNKNOWN";
}

QByteArray EnCode::getStartFlagByCodeId(CodeId id)
{
	switch (id)
	{
	case CodeId::UTF_8BOM:
		return QByteArray("\xEF\xBB\xBF", 3);
	case CodeId::UTF_16LEBOM:
		return QByteArray("\xFF\xFE", 2);
	case CodeId::UTF_16BEBOM:
		return QByteArray("\xFE\xFF", 2);
	}
	return QByteArray();
}

bool EnCode::translateStringToUnicode(CodeId cid, const char *pText, int nLength, QString &outString)
{
	QString codecName = getQtCodecNameById(cid);
	QTextCodec* pCodec = QTextCodec::codecForName(codecName.toStdString().c_str());
	QTextCodec::ConverterState state;
	outString = pCodec->toUnicode((const char*)pText, nLength, &state);
	if (state.invalidChars > 0)
		return false;
    return true;
}
