#pragma once

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include "__global.h"

class ScintillaEditView;
class NotepadPP : public QMainWindow
{
	Q_OBJECT
public:
	NotepadPP(QWidget* parent = nullptr);

	void __initUi();

    void __initMenu();

    void __initEncodingMenu();

    void __initStatusBar();

    void __connect();

    bool isNewFileNameExist(const QString& filename);

    void newTxtFile(QString filename, int nIndex, QString contentPath = "");

    void openFile(QString filename);

    void openTextFile(QString filepath);
    void reopenTextFileByCodeId(QString filepath, CodeId cid);

    void saveTabEdit(int nIndex);
    void saveTabEditByCodeId(int nIndex, CodeId cid);

    void saveFile(QString filename, ScintillaEditView* pEditView);
    void saveFileByCodeId(QString filename, ScintillaEditView *pEditView, CodeId cid);

	//打开监控文件修改的信号
	void enableEditTextChangeSign(ScintillaEditView* pEdit);

	//关闭监控文件修改的信号。这样是为了高效，一旦文字修改后，后续不需要在监控该信号。直到保存后，再放开
	void disEnableEditTextChangeSign(ScintillaEditView* pEdit);

    void setZoomLabelValue(int nZoomValue);

    void closeTab(int index);

    QString getRegularFilePath(QString path);

    int findFileIsOpenAtPad(QString filepath);

    void setCodeBarLabelByCodeId(CodeId cid);
    void setLineEndBarLabelByLineEnd(LineEnd lineEnd);

    bool convertDocLineEnd(LineEnd lineEnd);

    /// 处理最近打开的文件
    void loadRecentFileFromConfig();
    void addRecentFile(QString filepath);
    void deleteRecentFile(QString filepath);
    bool findRecentFile(QString filepath);
    void saveRecentFileToConfig();
    void updateRecentFileMenu();

    // 获取文件名, 根据文件路径
    QString getFileNameByPath(QString filepath);
    
public slots:
    void __onTriggerNewFile();
    void __onTriggerOpenFile();
    void __onTriggerSaveFile();
    void __onTriggerSaveAs();
    void __onTriggerClose();
    void __onTriggerCloseAll();

    void __onTriggerClearHistory();
    void __onTriggerOpenRecentFile();

    void __onTriggerExit();


    void __onTriggerUndo();
    void __onTriggerRedo();

    void __onTriggerCut();
    void __onTriggerCopy();
    void __onTriggerPaste();

    void __onTriggerSelectAll();

    void __onTriggerConvertWinLineEnd();
    void __onTriggerConvertUnixLineEnd();
    void __onTriggerConvertMacLineEnd();

    void __onTriggerRemoveHeadBlank();
    void __onTriggerRemoveEndBlank();
    void __onTriggerRemoveHeadEndBlank();

    void __onTriggerShowSpaces(bool bChecked);
    void __onTriggerShowLineEnd(bool bChecked);
    void __onTriggerShowAll(bool bChecked);

    void __onTriggerReopenWithEncoding(QAction* action);
    void __onTriggerSaveWithEncoding(QAction* action);

    void __onTextChanged();
    void __onZoomValueChange();
    void __onTabCloseRequested(int index);
    void __onTriggerAboutNotepadPP();
protected:
    // 
    QAction* m_actionNewFile;
    QAction* m_actionOpenFile;
    QAction* m_actionSave;
    QAction* m_actionSaveAs;
    QAction* m_actionClose;
    QAction* m_actionExit;
    QAction* m_actionCloseAll;
    
    //
    QAction* m_actionUndo;
    QAction* m_actionRedo;
    QAction* m_actionCut;
    QAction* m_actionCopy;
    QAction* m_actionPaste;
    QAction* m_actionSelectAll;
    QAction* m_actionConverWindowsCRLF;
    QAction* m_actionConvertUnixLF;
    QAction* m_actionConvertMacCR;
    QAction* m_actionFind;
    QAction* m_actionReplace;
    QAction* m_actionGoline;
    QAction* m_actionShowSpaces;
    QAction* m_actionShowEndOfLine;
    QAction* m_actionShowAll;


    QAction* m_actionBatchConvert;
    QAction* m_actionOptions;
    QAction* m_actionBugFix;
    QAction* m_actionFileCompare;
    QAction* m_actionDirCompare;

    QAction* m_actionSearchResult;
    QAction* m_actionDonate;
    QAction* m_actionDefaultStyle;
    QAction* m_actionLightBlueStyle;
    QAction* m_actionThinBlue;
    QAction* m_actionRiceYellow;
    QAction* m_actionYellow;
    QAction* m_actionSilver;
    QAction* m_actionLavenderBlush;
    QAction* m_actionMistyRose;
    QAction* m_actionEnglish;
    QAction* m_actionChinese;
    QAction* m_actionLanguageFormat;
    QAction* m_actionOpenInText;
    QAction* m_actionOpenInBin;
    QAction* m_actionRemoveHeadBlank;
    QAction* m_actionRemoveEndBlank;
    QAction* m_actionRemoveHeadEndBlank;
    QAction* m_actionColumnBlockEditing;
    // QAction* m_actionWrap;
    QAction* m_actionDefineLanguage;
    QAction* m_actionUpperCase;
    QAction* m_actionLowerCase;
    QAction* m_actionProperCase;
    QAction* m_actionProperCaseBlend;
    QAction* m_actionSentenceCase;
    QAction* m_actionSentenceCaseBlend;
    QAction* m_actionInvertCase;
    QAction* m_actionRandomCase;
    QAction* m_actionRemoveEmptyLines;
    QAction* m_actionRemoveEmptyLinesCbc;
    QAction* m_actionUserDefine;
    QAction* m_actionColumnEditMode;
    QAction* m_actionTABToSpace;
    QAction* m_actionSpaceToTABAll;
    QAction* m_actionSpaceToTABLeading;
    QAction* m_actionDuplicateCurrentLine;
    QAction* m_actionRemoveDuplicateLines;
    QAction* m_actionRemoveConsecutiveDuplicateLines;
    QAction* m_actionSplitLines;
    QAction* m_actionJoinLines;
    QAction* m_actionMoveUpCurrentLine;
    QAction* m_actionMoveDownCurrentLine;
    QAction* m_actionInsertBlankLineAboveCurrent;
    QAction* m_actionInsertBlankLineBelowCurrent;
    QAction* m_actionReverseLineOrder;
    QAction* m_actionRandomizeLineOrder;
    QAction* m_actionSortLinesLexicographicallyAscending;
    QAction* m_actionSortLinesLexAscendingIgnoringCase;
    QAction* m_actionSortLinesAsIntegersAscending;
    QAction* m_actionSortLinesAsDecimalsCommaAscending;
    QAction* m_actionSortLinesAsDecimalsDotAscending;
    QAction* m_actionSortLinesLexicographicallyDescending;
    QAction* m_actionSortLinesLexDescendingIgnoring_Case;
    QAction* m_actionSortLinesAsIntegersDescending;
    QAction* m_actionSortLinesAsDecimalsCommaDescending;
    QAction* m_actionSortLinesAsDecimalsDotDescending;
    QAction* m_actionFindInDir;
    QAction* m_actionFindNext;
    QAction* m_actionFindPrev;
    QAction* m_actionRed;
    QAction* m_actionYellow2;
    QAction* m_actionBlue;
    QAction* m_actionBig5;
    QAction* m_actionToBig5;
    // QAction* m_action24;
    // QAction* m_action36;
    // QAction* m_action48;
    QAction* m_actionInfo;
    QAction* m_action1;
    QAction* m_actionFormatXml;
    QAction* m_actionFormatJson;
    QAction* m_actionDark;
    QAction* m_actionVb;
    QAction* color1;
    QAction* color2;
    QAction* color3;
    QAction* color4;
    QAction* color5;
    QAction* loopColor;
    QAction* m_actionClearHistory;
    QAction* m_actionFileListView;
    // QAction* m_actionShowToolBar;
    QAction* m_actionBatchFind;
    // QAction* m_actionShowWebAddr;
    QAction* m_actionLanguageFileSuffix;
    QAction* m_actionShortcutKeyManager;
    QAction* m_actionR2;
    QAction* m_actiontest3;
    QAction* m_actionPluginManager;
    QAction* m_actionMd5Sha;
    QWidget* centralWidget;


    QMenuBar* m_menuBar;
    QMenu* m_menuFile;
    QMenu* m_menuReceneFile;
    QMenu* m_menuEdit;
    QMenu* m_menuFormatConversion;
    QMenu* m_menuBlankCharOperate;
    QMenu* m_menuConvertCaseTo;
    QMenu* m_menuLineOperations;
    QMenu* m_menuSearch;
    QMenu* m_menuBookMark;
    QMenu* m_menuMarkColor;
    QMenu* m_menuView;
    QMenu* m_menuDisplaySymbols;
    // QMenu* m_menuIconSize;
    
    QMenu* m_menuEncoding;

    // reopen with encoding
    QMenu* m_menuReopenWithEncoding;
    // save with encoding
    QMenu* m_menuSaveWithEncoding;

    QMenu* m_menuASNI;
    QMenu* m_menuConvertToOther;

    QMenu* m_menuSet;
    QMenu* m_menuLanguage;
    QMenu* m_menuHelp;
    QMenu* m_menuAbout;
    QMenu* m_menuTools;
    QMenu* m_menuPlugin;

    // ToolBar;
    //QToolBar* m_mainToolBar;
    
	QHBoxLayout* m_horizontalLayout;
	QTabWidget* m_editTabWidget;

    // StatusBar;
    QStatusBar* m_statusBar;
    QLabel* m_codeNameLabel;
    QComboBox* m_lineEndComboBox;
    QLabel* m_lineNumLabel;
    QLabel* m_langDescLabel;
    QLabel* m_zoomLabel;

protected:
    int m_nZoomValue;
    // bool m_bShowSpaces;
    // bool m_bShowLineEnd;

    std::vector<QString> m_recentOpenFileList;
};

