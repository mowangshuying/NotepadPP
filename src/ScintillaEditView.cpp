#include "ScintillaEditView.h"

void ScintillaEditView::__init()
{
	m_pScintillaFunc = (ScintillaFunc)SendScintillaPtrResult(SCI_GETDIRECTFUNCTION);
	m_pScintillaPtr = (ScintillaPtr)SendScintillaPtrResult(SCI_GETDIRECTPOINTER);

	if (!m_pScintillaFunc)
	{
		qDebug() << "Can't Get Direct function.";
	}

	if (!m_pScintillaPtr)
	{
		qDebug() << "Can't Get Direct pointer.";
	}

	// // 行号;
	// setMarginLineNumbers(__LineNumberMargin, true);
	// updateLineNumberWidth();

	// // Fold;
	// setFolding(BoxedTreeFoldStyle, __SymbolMargin);
	// //updateSymbolWidth(15);
	// updateFoldWidth(15);


	// // Symbol margin;
	// updateSymbolWidth(15);

	// // Tab width;
	// setTabWidth(4);
	// setIndentationsUseTabs(false);


	//设置换行符号的格式
// #ifdef Q_OS_WIN
// 	execute(SCI_SETEOLMODE, SC_EOL_CRLF);
// #else
// 	execute(SCI_SETEOLMODE, SC_EOL_LF);
// #endif

// 	//开启新行自动缩进
// 	setAutoIndent(true);

// 	// 开启后保证长行在滚动条下完整显示
// 	execute(SCI_SETSCROLLWIDTHTRACKING, true);
}

sptr_t ScintillaEditView::execute(quint32 Msg, uptr_t wParam /*= 0*/, sptr_t lParam /*= 0*/)
{
	try {
		return (m_pScintillaFunc) ? m_pScintillaFunc(m_pScintillaPtr, Msg, wParam, lParam) : -1;
	}
	catch (...)
	{
		return -1;
	}
}

int ScintillaEditView::nbDigitsFromNbLines(size_t nbLines)
{
	int nbDigits = 0; // minimum number of digit should be 4
	if (nbLines < 10) nbDigits = 1;
	else if (nbLines < 100) nbDigits = 2;
	else if (nbLines < 1000) nbDigits = 3;
	else if (nbLines < 10000) nbDigits = 4;
	else if (nbLines < 100000) nbDigits = 5;
	else if (nbLines < 1000000) nbDigits = 6;
	else // rare case
	{
		nbDigits = 7;
		nbLines /= 1000000;

		while (nbLines)
		{
			nbLines /= 10;
			++nbDigits;
		}
	}
	return nbDigits;
}

void ScintillaEditView::updateLineNumberWidth()
{
	sptr_t lineVisible = execute(SCI_LINESONSCREEN);
	if (lineVisible <= 0)
		return;

	int nbLineCount = execute(SCI_GETLINECOUNT);
	int nbDigits = nbDigitsFromNbLines(nbLineCount);
	if (nbDigits < 4)
		nbDigits = 4;

	int nDigitWidth = execute(SCI_TEXTWIDTH, STYLE_LINENUMBER, reinterpret_cast<sptr_t>("8"));
	int nPixelWidth = 6 + nDigitWidth * nbDigits;
	execute(SCI_SETMARGINWIDTHN, __LineNumberMargin, nPixelWidth);
}

void ScintillaEditView::updateSymbolWidth(int nWidth)
{
	execute(SCI_SETMARGINWIDTHN, __SymbolMargin, nWidth);
}

void ScintillaEditView::updateFoldWidth(int nWidth)
{
	execute(SCI_SETMARGINWIDTHN, __FolderMargin, nWidth);
}

void ScintillaEditView::setTabWidth(int nWidth)
{
	execute(SCI_SETTABWIDTH, nWidth);
}
