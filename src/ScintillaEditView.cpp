#include "ScintillaEditView.h"
#include <Qsci/qscilexerpython.h>
#include <Qsci/qscilexerasm.h>
#include <Qsci/qscilexerbash.h>
#include <Qsci/qscilexerbatch.h>
#include <Qsci/qscilexercmake.h>
#include <Qsci/qscilexercoffeescript.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscilexercsharp.h>
#include <Qsci/qscilexercss.h>
#include <Qsci/qscilexercustom.h>
#include <Qsci/qscilexerd.h>
#include <Qsci/qscilexerdiff.h>
#include <Qsci/qscilexeredifact.h>
#include <Qsci/qscilexerfortran.h>
#include <Qsci/qscilexerfortran77.h>
#include <Qsci/qscilexerhtml.h>
#include <Qsci/qscilexeridl.h>
#include <Qsci/qscilexerjava.h>
#include <Qsci/qscilexerjavascript.h>
#include <Qsci/qscilexerjson.h>
#include <Qsci/qscilexerlua.h>
#include <Qsci/qscilexermakefile.h>
#include <Qsci/qscilexermarkdown.h>
#include <Qsci/qscilexermatlab.h>
#include <Qsci/qscilexeroctave.h>
#include <Qsci/qscilexerpascal.h>
#include <Qsci/qscilexerperl.h>
#include <Qsci/qscilexerpo.h>
#include <Qsci/qscilexerpostscript.h>
#include <Qsci/qscilexerpov.h>
#include <Qsci/qscilexerproperties.h>
#include <Qsci/qscilexerpython.h>
// #include <Qsci/qscilexerr.h>
#include <Qsci/qscilexerruby.h>
#include <Qsci/qscilexerspice.h>
#include <Qsci/qscilexersql.h>
#include <Qsci/qscilexertcl.h>
#include <Qsci/qscilexertex.h>
#include <Qsci/qscilexerverilog.h>
#include <Qsci/qscilexervhdl.h>
#include <Qsci/qscilexerxml.h>
#include <Qsci/qscilexeryaml.h>
// #include <Qsci/qscilexergo.h>
// #include <Qsci/qscilexertext.h>
// #include <Qsci/qscilexernsis.h>
// #include <Qsci/qscilexerglobal.h>
// #include <Qsci/qscilexerrust.h>
// #include <Qsci/qscilexervb.h>
#include <Qsci/qscilexerasm.h>
#include "StyleSheetUtils.h"
#include <QFileInfo>
#include <unordered_set>

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

	// 行号;
	setMarginLineNumbers(__LineNumberMargin, true);
	updateLineNumberWidth();

	// Fold;
	setFolding(BoxedTreeFoldStyle, __SymbolMargin);
	//updateSymbolWidth(15);
	updateFoldWidth(15);


	// Symbol margin;
	updateSymbolWidth(15);

	// Tab width;
	setTabWidth(4);
	setIndentationsUseTabs(false);


	// 设置换行符号的格式
#ifdef Q_OS_WIN
	execute(SCI_SETEOLMODE, SC_EOL_CRLF);
#else
	execute(SCI_SETEOLMODE, SC_EOL_LF);
#endif

	//开启新行自动缩进
	setAutoIndent(true);

	// 开启后保证长行在滚动条下完整显示
	execute(SCI_SETSCROLLWIDTHTRACKING, true);
	setFrameStyle(QFrame::Box);
	StyleSheetUtils::setQssByFileName(this, "./res/StyleSheet/ScintillaEditView.qss");
}

void ScintillaEditView::setNoteWidget(QWidget* pNoteWidget)
{
	m_pNoteWidget = pNoteWidget;
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

QsciLexer* ScintillaEditView::makeLexerByName(QString lexerName)
{
	QsciLexer *lexer = nullptr;
	if (lexerName == "php" || lexerName == "html" || lexerName == "asp" || lexerName == "jsp")
	{
		lexer = new QsciLexerHTML();
		return lexer;
	}
	else if (lexerName == "cpp" || lexerName == "c" || lexerName == "rc" || lexerName == "objc" || lexerName == "flash")
	{
		lexer = new QsciLexerCPP();
		return lexer;
	}
	else if (lexerName == "csharp")
	{
		lexer = new QsciLexerCSharp();
		return lexer;
	}
	else if (lexerName == "java")
	{
		lexer = new QsciLexerJava();
		return lexer;
	}
	else if (lexerName == "xml")
	{
		lexer = new QsciLexerXML();
		return lexer;
	}
	else if (lexerName == "makefile")
	{
		lexer = new QsciLexerMakefile();
		return lexer;
	}
	else if (lexerName == "pascal")
	{
		lexer = new QsciLexerPascal();
		return lexer;
	}
	else if (lexerName == "batch")
	{
		lexer = new QsciLexerBatch();
		return lexer;
	}
	else if (lexerName == "ini")
	{
		lexer = new QsciLexerProperties();
		return lexer;
	}
	else if(lexerName == "sql")
	{
		lexer = new QsciLexerSQL();
		return lexer;
	}
	else if (lexerName == "css")
	{
		lexer = new QsciLexerCSS();
		return lexer;
	}//perl
	else if (lexerName == "perl")
	{
		lexer = new QsciLexerPerl();
		return lexer;
	}//python
	else if (lexerName == "python")
	{
		lexer = new QsciLexerPython();
		return lexer;
	}//lua
	else if(lexerName == "lua")
	{
		lexer = new QsciLexerLua();
		return lexer;
	}//fortran
	else if (lexerName == "fortran")
	{
		lexer = new QsciLexerFortran();
		return lexer;
	}//bash
	else if (lexerName == "bash")
	{
		lexer = new QsciLexerBash();
		return lexer;
	}
	else if (lexerName == "nsis")
	{
		// lexer = new QsciLexerNsis();
		return lexer;
	}
	else if (lexerName == "tcl")
	{
		lexer = new QsciLexerTCL();
		return lexer;
	}
	else if (lexerName == "asm")
	{
		// lexer = new QsciLexerAsm();
		return lexer;
	}
	else if (lexerName == "diff")
	{
		lexer = new QsciLexerDiff();
		return lexer;
	}
	else if (lexerName == "r")
	{
		// lexer = new QsciLexerR();
		return lexer;
	}
	else if (lexerName == "Ruby")
	{
		lexer = new QsciLexerRuby();
		return lexer;
	}
	else if (lexerName == "vhdl")
	{
		lexer = new QsciLexerVHDL();
		return lexer;
	}
	else if (lexerName == "verilog")
	{
		lexer = new QsciLexerVerilog();
		return lexer;
	}
	else if(lexerName == "matlab")
	{
		lexer = new QsciLexerMatlab();
		return lexer;
	}
	else if (lexerName == "cmake")
	{
		lexer = new QsciLexerCMake();
		return lexer;
	}
	else if(lexerName == "yaml")
	{
		lexer = new QsciLexerYAML();
		return lexer;
	}
	else if (lexerName == "coffeescript")
	{
		lexer = new QsciLexerCoffeeScript();
		return lexer;
	}
	else if (lexerName == "json")
	{
		lexer = new QsciLexerJSON();
		return lexer;
	}
	else if (lexerName == "javascript")
	{
		lexer = new QsciLexerJavaScript();
		return lexer;
	}
	else if (lexerName == "rust")
	{
		// lexer = new QsciLexerRust();
		return lexer;
	}
	else if (lexerName == "txt")
	{
		// lexer = new QsciLexerText();
		return lexer;
	}
	return lexer;
}

void ScintillaEditView::setLexerByFilePath(QString filepath)
{
	QFileInfo fileinfo(filepath);
	QString suffixName = fileinfo.suffix();
	auto lexer = makeLexerByName(suffixName);
	setLexer(lexer);
}

QString ScintillaEditView::getEOLString()
{
    intptr_t eolMode = execute(SCI_GETEOLMODE);
	if (eolMode == SC_EOL_CRLF)
	{
		return QString("\r\n");
	}
	else if (eolMode == SC_EOL_LF)
	{
		return QString("\n");
	}
	else if(eolMode == SC_EOL_CR)
	{
		return QString("\r");
	}
	return QString("\n");
}

void ScintillaEditView::getText(char *dest, size_t start, size_t end)
{
	Sci_TextRange tr;
	tr.chrg.cpMin = static_cast<Sci_PositionCR>(start);
	tr.chrg.cpMax = static_cast<Sci_PositionCR>(end);
	tr.lpstrText = dest;
	execute(SCI_GETTEXTRANGE, 0, reinterpret_cast<sptr_t>(&tr));
}

QString ScintillaEditView::getGenericTextAsQString(size_t start, size_t end)
{
	size_t bufSize = end - start;
	QByteArray bytes;
	bytes.resize(bufSize);
	getText(bytes.data(), start, end);
	return QString(bytes);
}

void ScintillaEditView::removeAnyDuplicateLines()
{
	size_t fromLine = 0;
	size_t toLine = 0;

	sptr_t selStart = execute(SCI_GETSELECTIONSTART);
	sptr_t selEnd = execute(SCI_GETSELECTIONEND);

	bool hasLineSelection = selStart != selEnd;
	if (hasLineSelection)
	{
		std::pair<size_t, size_t> linesRange = getSelectionLinesRange();
		fromLine = linesRange.first;
		toLine = linesRange.second;
	}
	else
	{
		fromLine = 0;
		toLine = execute(SCI_GETLINECOUNT) - 1;
	}

	if (fromLine >= toLine)
		return;

	size_t startPos = execute(SCI_POSITIONFROMLINE, fromLine);
	size_t endPos = execute(SCI_POSITIONFROMLINE, toLine) + execute(SCI_LINELENGTH, toLine);
	QString text = getGenericTextAsQString(startPos, endPos);

	QStringList lines = text.split(getEOLString());
	size_t lineCount = execute(SCI_GETLINECOUNT);

	bool doingEntireDocument = (toLine == lineCount - 1);
	if (!doingEntireDocument)
	{
		if (lines.rbegin()->isEmpty())
		{
			lines.pop_back();
		}
	}

	size_t oriLinesSize = lines.size();
	size_t newLinesSize = removeDuplicateLines(lines);
	if (oriLinesSize != newLinesSize)
	{
		QString joined = lines.join(getEOLString());
		if (!doingEntireDocument)
		{
			joined += getEOLString();
		}
		
		if (text != joined)
		{
			QByteArray bytes = joined.toUtf8();
			replaceTarget(bytes, startPos, endPos);
		}
	}
}

std::pair<size_t, size_t> ScintillaEditView::getSelectionLinesRange(intptr_t selectionNumer)
{
    // return std::pair<size_t, size_t>();
	size_t numSelections = execute(SCI_GETSELECTIONS);
	size_t startPos;
	size_t endPos;

	if ((selectionNumer < 0) || static_cast<size_t>(selectionNumer) >= numSelections)
	{
		startPos = execute(SCI_GETSELECTIONSTART);
		endPos = execute(SCI_GETSELECTIONEND);
	}
	else
	{
		startPos = execute(SCI_GETSELECTIONNSTART, selectionNumer);
		endPos = execute(SCI_GETSELECTIONNEND, selectionNumer);
	}

	size_t startLine = execute(SCI_LINEFROMPOSITION, startPos);
	size_t endLine = execute(SCI_LINEFROMPOSITION, endPos);

	if ((startLine != endLine) && (static_cast<size_t>(execute(SCI_POSITIONFROMLINE, endLine)) == endPos))
	{
		endLine--;
	}

	return std::pair<size_t, size_t>(startLine, endLine);
}

size_t ScintillaEditView::removeDuplicateLines(QStringList &lines)
{
	QStringList newLines;

	for (int i = 0; i < lines.size(); i++)
	{
		if (!newLines.contains(lines[i]))
		{
			newLines.append(lines[i]);
		}
	}

	lines = newLines;
	return lines.size();
}

intptr_t ScintillaEditView::replaceTarget(QByteArray &bytes, intptr_t fromTargetPos, intptr_t toTargetPos)
{
	if (fromTargetPos < 0 || toTargetPos < 0)
		return 0;

	execute(SCI_SETTARGETRANGE, fromTargetPos, toTargetPos);
	return execute(SCI_REPLACETARGET, bytes.size(), reinterpret_cast<sptr_t>(bytes.data()));
}
