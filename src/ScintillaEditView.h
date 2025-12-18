#pragma  once

//#include <Qsci/qsciscintilla.h>
// #include <Scintilla.h>
// #include <Scintilla.h>
#include <Qsci/qsciscintilla.h>
#include <Scintilla.h>
#include <Qsci/qscilexer.h>

#include <QDebug>
#include "ISorter.h"

using ScintillaFunc = sptr_t(*)(sptr_t, unsigned int, uptr_t, sptr_t);
using ScintillaPtr = sptr_t;

// enum class MarginType {
// 	LineNumbers = 0,
// 	Symbol = 1,
// 	Folder = 2,
// };

const int __LineNumberMargin = 0;
const int __SymbolMargin = 1;
const int __FolderMargin = 2;

class ScintillaEditView : public QsciScintilla
{ 
	Q_OBJECT
public:
	ScintillaEditView(QWidget* parent = nullptr)
	{
		__init();
	}

	~ScintillaEditView()
	{

	}

	void __init();

	void setNoteWidget(QWidget* pNoteWidget);

	sptr_t execute(quint32 Msg, uptr_t wParam = 0, sptr_t lParam = 0);

	int nbDigitsFromNbLines(size_t nbLines);

	void updateLineNumberWidth();

	void updateSymbolWidth(int nWidth);

	void updateFoldWidth(int nWidth);

	void setTabWidth(int nWidth);

	QsciLexer* makeLexerByName(QString lexerName);

	void setLexerByFilePath(QString filepath);

	QString getEOLString();

	void getText(char* dest, size_t start, size_t end);

	QString getGenericTextAsQString(size_t start, size_t end);

	void removeAnyDuplicateLines();

	std::pair<size_t, size_t> getSelectionLinesRange(intptr_t selectionNumer = -1);

	size_t removeDuplicateLines(QStringList& lines);

	intptr_t replaceTarget(QByteArray& bytes, intptr_t fromTargetPos, intptr_t toTargetPos);

	void sortLines(size_t nFromLine, size_t nToLine, SortType sortType);
protected:
	ScintillaFunc m_pScintillaFunc;
	ScintillaPtr m_pScintillaPtr;
    QWidget* m_pNoteWidget;
};