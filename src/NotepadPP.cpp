#include "NotepadPP.h"
#include <QStatusBar>
#include <QDebug>
#include "FileManager.h"
#include "ScintillaEditView.h"
#include "__global.h"
#include <QFileDialog>
#include "EnCode.h"
#include "AboutNotePP.h"
#include <QTextCodec>
// #include <Qsci/qscilexer.h>
// #include <Qsci/qsciglobal.h>
#include <SciLexer.h>
NotepadPP::NotepadPP(QWidget* parent /*= nullptr*/) : QMainWindow(parent),m_nZoomValue(0)
{
	__initUi();
	__connect();
}

void NotepadPP::__initUi()
{
	__initMenu();
	loadRecentFileFromConfig();

	auto contentWidget = new QWidget(this);
	setCentralWidget(contentWidget);
	
	m_horizontalLayout = new QHBoxLayout;
	m_horizontalLayout->setContentsMargins(0, 0, 0, 0);
	contentWidget->setLayout(m_horizontalLayout);

	m_editTabWidget = new QTabWidget(this);
	m_editTabWidget->setIconSize(QSize(22, 22));
	m_editTabWidget->setTabsClosable(true);
	m_editTabWidget->setMovable(true);
	m_editTabWidget->setTabBarAutoHide(false);
	m_horizontalLayout->addWidget(m_editTabWidget);

	// init status bar
    //m_statusBar = new QStatusBar(this);
    //setStatusBar(m_statusBar);
	__initStatusBar();

	resize(1000, 800);
}

void NotepadPP::__initMenu()
{
	m_menuBar = new QMenuBar(this);
	setMenuBar(m_menuBar);

	//  ---init File Menu;
	m_menuFile = new QMenu("File", m_menuBar);
	m_menuFile->setLayoutDirection(Qt::LeftToRight);


	m_actionNewFile = new QAction("New");
	m_actionNewFile->setShortcut(QKeySequence::New);
	m_actionOpenFile = new QAction("Open ...");
	m_actionOpenFile->setShortcut(QKeySequence::Open);
	m_actionSave = new QAction("Save");
	m_actionSave->setShortcut(QKeySequence::Save);

	m_actionSaveAs = new QAction("Save As ...");
	m_actionSaveAs->setShortcut(QKeySequence::SaveAs);

	m_actionClose = new QAction("Close");
	// m_actionClose->setShortcut(QKeySequence::Close);

	m_actionCloseAll = new QAction("Close All");
	// m_actionCloseAll->setShortcut(QKeySequence::CloseAll);


	m_actionClearHistory = new QAction("Clear History");

	m_menuReceneFile = new QMenu("Recene File");

	m_actionExit = new QAction("Exit");
	m_actionExit->setShortcut(QKeySequence::Quit);


	m_menuFile->addAction(m_actionNewFile);
	m_menuFile->addAction(m_actionOpenFile);
	m_menuFile->addAction(m_actionSave);
	m_menuFile->addAction(m_actionSaveAs);
	m_menuFile->addAction(m_actionClose);
	m_menuFile->addAction(m_actionCloseAll);

	m_menuFile->addSeparator();

	m_menuFile->addAction(m_actionClearHistory);
	m_menuFile->addAction(m_menuReceneFile->menuAction());

	m_menuFile->addSeparator();
	m_menuFile->addAction(m_actionExit);

	m_menuBar->addAction(m_menuFile->menuAction());

	// --- init Edit Menu
	m_menuEdit = new QMenu("Edit", m_menuBar);
	m_actionUndo = new QAction("Undo");
	m_actionUndo->setShortcut(QKeySequence::Undo);
	m_actionRedo = new QAction("Redo");
	m_actionRedo->setShortcut(QKeySequence::Redo);

	// split

	m_actionCut = new QAction("Cut");
	m_actionCut->setShortcut(QKeySequence::Cut);
	m_actionCopy = new QAction("Copy");
	m_actionCopy->setShortcut(QKeySequence::Copy);
	m_actionPaste = new QAction("Paste");
	m_actionPaste->setShortcut(QKeySequence::Paste);

	// split

	m_actionSelectAll = new QAction("Select All");
	m_actionSelectAll->setShortcut(QKeySequence::SelectAll);

	m_menuFormatConversion = new QMenu("Format Conversion");
	m_actionConverWindowsCRLF = new QAction("Windows(CRLF)");
	m_actionConvertUnixLF = new QAction("Unix(LF)");
	m_actionConvertMacCR = new QAction("Mac(CR)");

	m_menuFormatConversion->addAction(m_actionConverWindowsCRLF);
	m_menuFormatConversion->addAction(m_actionConvertUnixLF);
	m_menuFormatConversion->addAction(m_actionConvertMacCR);

	// m_actionOpenInText = new QAction("Open In Text");
	// m_actionOpenInBin = new QAction("Open In Bin");

	/// --- black char operator
	m_menuBlankCharOperate = new QMenu("Blank Char Operate");
	m_actionRemoveHeadBlank = new QAction("Remove Head Blank");
	m_actionRemoveEndBlank = new QAction("Remove End Blank");
	m_actionRemoveHeadEndBlank = new QAction("Remove Head End Blank");
	m_menuBlankCharOperate->addAction(m_actionRemoveHeadBlank);
	m_menuBlankCharOperate->addAction(m_actionRemoveEndBlank);
	m_menuBlankCharOperate->addAction(m_actionRemoveHeadEndBlank);

	/// --- convert case to
	m_menuConvertCaseTo = new QMenu("Convert Case To");
	m_actionUpperCase = new QAction("Upper Case");
	m_actionLowerCase = new QAction("Lower Case");
	m_actionProperCase = new QAction("Proper Case");
	m_actionProperCaseBlend = new QAction("Proper Case(Blend)");
	m_actionSentenceCase = new QAction("Scentence Case");
	m_actionSentenceCaseBlend = new QAction("Scentence Case(Blend)");
	m_actionInvertCase = new QAction("Invert Case");
	m_actionRandomCase = new QAction("Random Case");

	m_menuConvertCaseTo->addAction(m_actionUpperCase);
	m_menuConvertCaseTo->addAction(m_actionLowerCase);
	m_menuConvertCaseTo->addAction(m_actionProperCase);
	m_menuConvertCaseTo->addAction(m_actionProperCaseBlend);
	m_menuConvertCaseTo->addAction(m_actionSentenceCase);
	m_menuConvertCaseTo->addAction(m_actionSentenceCaseBlend);
	m_menuConvertCaseTo->addAction(m_actionRandomCase);

	// line operator
	m_menuLineOperations = new QMenu("Line Operator");
	m_actionDuplicateCurrentLine = new QAction("Duplicate Current Line");
	m_actionRemoveDuplicateLines = new QAction("Remove Duplicate Lines");
	m_actionSplitLines = new QAction("Split Lines");
	m_actionJoinLines = new QAction("Join Lines");
	m_actionMoveUpCurrentLine = new QAction("Move Up Current Line");
	m_actionMoveDownCurrentLine = new QAction("Move Down Current Line");
	m_actionRemoveEmptyLines = new QAction("Remove Empty Lines");
	m_actionRemoveEmptyLinesCbc = new QAction("Remove Empty Lines(Containing blank charactors)");
	m_actionInsertBlankLineAboveCurrent = new QAction("Insert Blank Line Above Current");
	m_actionInsertBlankLineBelowCurrent = new QAction("Insert Blank Line Below Current");
	m_actionReverseLineOrder = new QAction("Reverse Line Order");

	m_menuLineOperations->addAction(m_actionDuplicateCurrentLine);
	m_menuLineOperations->addAction(m_actionRemoveDuplicateLines);
	m_menuLineOperations->addAction(m_actionSplitLines);
	m_menuLineOperations->addAction(m_actionJoinLines);
	m_menuLineOperations->addAction(m_actionMoveUpCurrentLine);
	m_menuLineOperations->addAction(m_actionMoveDownCurrentLine);
	m_menuLineOperations->addAction(m_actionRemoveEmptyLines);
	m_menuLineOperations->addAction(m_actionRemoveEmptyLinesCbc);
	m_menuLineOperations->addAction(m_actionInsertBlankLineAboveCurrent);
	m_menuLineOperations->addAction(m_actionInsertBlankLineBelowCurrent);
	m_menuLineOperations->addAction(m_actionReverseLineOrder);
	//m_menuLineOperations->addAction(m_actionColumnBlockEditing);
	//m_menuLineOperations->addAction(m_actionColumnEditMode);

	// m_actionColumnBlockEditing = new QAction("Column Block Editing");
	// m_actionColumnEditMode = new QAction("Column Edit Mode");

	m_menuEdit->addAction(m_actionUndo);
	m_menuEdit->addAction(m_actionRedo);
	m_menuEdit->addSeparator();
	m_menuEdit->addAction(m_actionCut);
	m_menuEdit->addAction(m_actionCopy);
	m_menuEdit->addAction(m_actionPaste);
	m_menuEdit->addSeparator();
	m_menuEdit->addAction(m_actionSelectAll);
	m_menuEdit->addAction(m_menuFormatConversion->menuAction());

	m_menuEdit->addSeparator();

	// m_menuEdit->addAction(m_actionOpenFile);
	// m_menuEdit->addAction(m_actionOpenInBin);
	m_menuEdit->addAction(m_menuBlankCharOperate->menuAction());
	m_menuEdit->addAction(m_menuConvertCaseTo->menuAction());
	m_menuEdit->addAction(m_menuLineOperations->menuAction());

	// m_menuEdit->addSeparator();
	// m_menuEdit->addAction(m_actionColumnBlockEditing);
	// m_menuEdit->addAction(m_actionColumnEditMode);

	m_menuBar->addAction(m_menuEdit->menuAction());

	// searchMenu
	m_menuSearch = new QMenu("Search");
	m_actionFind = new QAction("Find");
	m_actionFindNext = new QAction("Find Next");
	m_actionFindPrev = new QAction("Find Prev");
	m_actionFindInDir = new QAction("Find In Directory");
	m_actionReplace = new QAction("Replace");
	m_actionGoline = new QAction("Go To Line");

	//m_menuBookMark = new QMenu("BookMark");
	//m_ac = new QAction("Add BookMark");

	// View MenuFileListView
	m_menuView = new QMenu("View");

	m_menuDisplaySymbols = new QMenu("Display Symbols");
	m_actionShowSpaces = new QAction("Show Spaces");
	m_actionShowSpaces->setCheckable(true);

	m_actionShowEndOfLine = new QAction("Show End Of Line");
	m_actionShowEndOfLine->setCheckable(true);

	m_actionShowAll = new QAction("Show All");
	m_actionShowAll->setCheckable(true);

	m_menuDisplaySymbols->addAction(m_actionShowSpaces);
	m_menuDisplaySymbols->addAction(m_actionShowEndOfLine);
	m_menuDisplaySymbols->addAction(m_actionShowAll);


	m_actionSearchResult = new QAction("Search Result");

	m_menuIconSize = new QMenu("Icon Size");
	m_action24 = new QAction("24x24");
	m_action36 = new QAction("36x36");
	m_action48 = new QAction("48x48");
	m_menuIconSize->addAction(m_action24);
	m_menuIconSize->addAction(m_action36);
	m_menuIconSize->addAction(m_action48);

	m_actionWrap = new QAction("Wrap");
	m_actionFileListView = new QAction("FileListView");
	m_actionShowToolBar = new QAction("Show ToolBar");
	m_actionShowWebAddr = new QAction("Show WebAddr");

	m_menuView->addAction(m_menuDisplaySymbols->menuAction());
	m_menuView->addAction(m_actionSearchResult);
	m_menuView->addAction(m_menuIconSize->menuAction());
	m_menuView->addAction(m_actionWrap);
	m_menuView->addAction(m_actionFileListView);
	m_menuView->addAction(m_actionShowToolBar);
	m_menuView->addAction(m_actionShowWebAddr);

	m_menuBar->addAction(m_menuView->menuAction());

	// language
	m_menuLanguage = new QMenu("Language");

	m_menuA = new QMenu("A");
	m_actionASP = new QAction("ASP");
	m_actionASP->setProperty("Suffix", "asp");
	m_actionASP->setProperty("LexerId", SCLEX_HTML);
	m_actionASP->setProperty("description", "Active Server Pages script file");


	m_actionActionScript = new QAction("ActionScript");
	m_actionAssembly = new QAction("Assembly");
	m_actionAutoIt = new QAction("AutoIt");
	m_actionAviSynth = new QAction("AviSynth");
	m_actionASN1 = new QAction("ASN.1");

	m_menuA->addAction(m_actionASP);
	m_menuA->addAction(m_actionActionScript);
	m_menuA->addAction(m_actionAssembly);
	m_menuA->addAction(m_actionAutoIt);
	m_menuA->addAction(m_actionAviSynth);
	m_menuA->addAction(m_actionASN1);


	m_menuB = new QMenu("B");
	m_actionBaanC = new QAction("Baan C");
	m_actionbash = new QAction("bash");
	m_actionBatch = new QAction("Batch");
	m_actionBlitzBasic = new QAction("BlitzBasic");
	m_menuB->addAction(m_actionBaanC);
	m_menuB->addAction(m_actionbash);
	m_menuB->addAction(m_actionBatch);
	m_menuB->addAction(m_actionBlitzBasic);


	m_menuC = new QMenu("C");
	m_actionC = new QAction("C");
	
	m_actionCPP = new QAction("C++");
	m_actionCPP->setProperty("Suffix", "cpp");
	m_actionCPP->setProperty("LexerId", SCLEX_CPP);

	m_actionCShape = new QAction("C#");
	m_actionObjectiveC = new QAction("Objective-C");
	m_actionCss = new QAction("CSS");
	m_actionCMake = new QAction("CMake");
	m_actionCoffeeScript = new QAction("CoffeeScript");
	m_actionCsound = new QAction("Csound");
	m_menuC->addAction(m_actionC);
	m_menuC->addAction(m_actionCPP);
	m_menuC->addAction(m_actionCShape);
	m_menuC->addAction(m_actionObjectiveC);
	m_menuC->addAction(m_actionCss);
	m_menuC->addAction(m_actionCMake);
	m_menuC->addAction(m_actionCoffeeScript);
	m_menuC->addAction(m_actionCsound);


	m_menuD = new QMenu("D");
	m_actionD = new QAction("D");
	m_actionDiff = new QAction("Diff");
	m_menuD->addAction(m_actionD);
	m_menuD->addAction(m_actionDiff);

	//m_menuLanguage->addMenu(m_menuC);

	m_menuE = new QMenu("E");
	m_actionESCRIPT = new QAction("ESCRIPT");
	m_actionErlang = new QAction("Erlang");
	m_actionEdifact = new QAction("Edifact");
	m_menuE->addAction(m_actionESCRIPT);
	m_menuE->addAction(m_actionErlang);
	m_menuE->addAction(m_actionEdifact);


	m_menuF = new QMenu("F");
	m_actionFortran = new QAction("Fortran");
	m_actionFortran77 = new QAction("Fortran77");
	m_actionForth = new QAction("Forth");
	m_actionFreeBasic = new QAction("FreeBasic");
	m_menuF->addAction(m_actionFortran);
	m_menuF->addAction(m_actionFortran77);
	m_menuF->addAction(m_actionForth);
	m_menuF->addAction(m_actionFreeBasic);


	m_menuG = new QMenu("G");
	m_actionGo = new QAction("Go");
	m_menuG->addAction(m_actionGo);

	m_menuH = new QMenu("H");
	m_actionHTML = new QAction("HTML");
	m_menuH->addAction(m_actionHTML);


	m_menuI = new QMenu("I");
	m_actionIDL = new QAction("IDL");
	m_actionIni = new QAction("ini");
	m_actionIntelHEX = new QAction("Intel HEX");
	m_menuI->addAction(m_actionIDL);
	m_menuI->addAction(m_actionIni);
	m_menuI->addAction(m_actionIntelHEX);



	m_menuJ = new QMenu("J");
	m_actionJava = new QAction("Java");
	m_actionJavaScript = new QAction("JavaScript");
	m_actionJsp = new QAction("Jsp");
	m_actionJson = new QAction("json");
	m_menuJ->addAction(m_actionJava);
	m_menuJ->addAction(m_actionJavaScript);
	m_menuJ->addAction(m_actionJsp);
	m_menuJ->addAction(m_actionJson);

	//m_menuK = new QMenu("K");
	m_menuL = new QMenu("L");
	m_actionLua = new QAction("Lua");
	m_actionLisp = new QAction("Lisp");
	m_actionLaTex = new QAction("LaTex");
	m_menuL->addAction(m_actionLua);
	m_menuL->addAction(m_actionLisp);
	m_menuL->addAction(m_actionLaTex);


	m_menuM = new QMenu("M");
	m_actionMakefile = new QAction("Makefile");
	m_actionMMIXAL = new QAction("MMIXAL");
	m_actionMarkDown = new QAction("MarkDown");
	m_actionMatlab = new QAction("Matlab");
	m_menuM->addAction(m_actionMakefile);
	m_menuM->addAction(m_actionMMIXAL);
	m_menuM->addAction(m_actionMarkDown);
	m_menuM->addAction(m_actionMatlab);



	m_menuN = new QMenu("N");
	m_actionNfo = new QAction("Nfo");
	m_actionNSIS = new QAction("Nsis");
	m_actionNncrontab = new QAction("Nncrontab");
	m_actionNim = new QAction("Nim");
	m_menuN->addAction(m_actionNfo);
	m_menuN->addAction(m_actionNSIS);
	m_menuN->addAction(m_actionNncrontab);
	m_menuN->addAction(m_actionNim);

	m_menuO = new QMenu("O");
	m_actionOScript = new QAction("OScript");
	m_actionOctave = new QAction("Octave");
	m_menuO->addAction(m_actionOScript);
	m_menuO->addAction(m_actionOctave);

	m_menuP = new QMenu("P");
	m_actionPascal = new QAction("Pascal");
	m_actionPerl = new QAction("Perl");
	m_actionPhp = new QAction("PHP");
	m_actionPo = new QAction("PO");
	m_actionPostScript = new QAction("PostScript");
	m_actionPov = new QAction("Pov");
	m_actionPowerShell = new QAction("PowerShell");
	m_actionPropertiesFile = new QAction("Properties File");
	m_actionPureBasic = new QAction("PureBasic");
	m_actionPython = new QAction("Python");
	m_menuP->addAction(m_actionPascal);
	m_menuP->addAction(m_actionPerl);
	m_menuP->addAction(m_actionPhp);
	m_menuP->addAction(m_actionPo);
	m_menuP->addAction(m_actionPostScript);
	m_menuP->addAction(m_actionPov);
	m_menuP->addAction(m_actionPowerShell);
	m_menuP->addAction(m_actionPropertiesFile);
	m_menuP->addAction(m_actionPureBasic);
	m_menuP->addAction(m_actionPython);


	//m_menuQ = new QMenu("Q");
	m_menuR = new QMenu("R");
	m_actionR = new QAction("R");
	m_actionRC = new QAction("RC");
	m_actionRuby = new QAction("Ruby");
	m_actionRust = new QAction("Rust");
	m_actionRegistry = new QAction("Registry");
	m_actionREBOL = new QAction("Rebol");
	m_menuR->addAction(m_actionR);
	m_menuR->addAction(m_actionRC);
	m_menuR->addAction(m_actionRuby);
	m_menuR->addAction(m_actionRust);
	m_menuR->addAction(m_actionRegistry);
	m_menuR->addAction(m_actionREBOL);

	m_menuS = new QMenu("S");
	m_actionSql = new QAction("SQL");
	m_actionShell = new QAction("Shell");
	m_actionScheme = new QAction("Scheme");
	m_actionSmalltalk = new QAction("Smalltalk");
	m_actionSRecord = new QAction("S Record");
	m_actionSwift = new QAction("Swift");
	m_actionSpice = new QAction("Spice");
	m_menuS->addAction(m_actionSql);
	m_menuS->addAction(m_actionShell);
	m_menuS->addAction(m_actionScheme);
	m_menuS->addAction(m_actionSmalltalk);
	m_menuS->addAction(m_actionSRecord);
	m_menuS->addAction(m_actionSwift);
	m_menuS->addAction(m_actionSpice);


	m_menuT = new QMenu("T");
	m_actionTex = new QAction("Tex");
	m_actionTcl = new QAction("Tcl");
	m_actionTypeScript = new QAction("TypeScript");
	m_actionTxt2tags = new QAction("Txt2Tag");
	m_actionTxt = new QAction("Txt");

	m_menuT->addAction(m_actionTex);
	m_menuT->addAction(m_actionTcl);
	m_menuT->addAction(m_actionTypeScript);
	m_menuT->addAction(m_actionTxt2tags);
	m_menuT->addAction(m_actionTxt);


	//m_menuU = new QMenu("U");
	m_menuV = new QMenu("V");
	m_actionVb = new QAction("Vb");
	m_actionVerilog = new QAction("Verilog");
	m_actionVirsualBasic = new QAction("Virsual Basic");
	m_actionVHDL = new QAction("VHDL");
	m_actionVisualProlog = new QAction("Visual Prolog");
	m_menuV->addAction(m_actionVb);
	m_menuV->addAction(m_actionVerilog);
	m_menuV->addAction(m_actionVirsualBasic);
	m_menuV->addAction(m_actionVHDL);
	m_menuV->addAction(m_actionVisualProlog);


	//m_menuW = new QMenu("W");
	m_menuX = new QMenu("X");
	m_actionXML = new QAction("XML");
	m_menuX->addAction(m_actionXML);


	m_menuY = new QMenu("Y");
	m_actionYAML = new QAction("YAML");
	m_menuY->addAction(m_actionYAML);

	//m_menuZ = new QMenu("Z");

	m_menuLanguage->addMenu(m_menuA);
	m_menuLanguage->addMenu(m_menuB);
	m_menuLanguage->addMenu(m_menuC);
	m_menuLanguage->addMenu(m_menuD);
	m_menuLanguage->addMenu(m_menuE);
	m_menuLanguage->addMenu(m_menuF);
	m_menuLanguage->addMenu(m_menuG);
	m_menuLanguage->addMenu(m_menuH);
	m_menuLanguage->addMenu(m_menuI);
	m_menuLanguage->addMenu(m_menuJ);
	//m_menuLanguage->addMenu(m_menuK);
	m_menuLanguage->addMenu(m_menuL);
	m_menuLanguage->addMenu(m_menuM);
	m_menuLanguage->addMenu(m_menuN);
	m_menuLanguage->addMenu(m_menuO);
	m_menuLanguage->addMenu(m_menuP);
	//m_menuLanguage->addMenu(m_menuQ);
	m_menuLanguage->addMenu(m_menuR);
	m_menuLanguage->addMenu(m_menuS);
	m_menuLanguage->addMenu(m_menuT);
	//m_menuLanguage->addMenu(m_menuU);
	m_menuLanguage->addMenu(m_menuV);
	//m_menuLanguage->addMenu(m_menuW);
	m_menuLanguage->addMenu(m_menuX);
	m_menuLanguage->addMenu(m_menuY);
	//m_menuLanguage->addMenu(m_menuZ);
	m_menuBar->addAction(m_menuLanguage->menuAction());




	// EnCoding
	m_menuEncoding = new QMenu("Encoding");
	// gbk utf8 utf8bom 
	m_actionEncodeInGBK = new QAction("GBK");
	m_actionEncodeInUft8 = new QAction("UTF-8");
	m_actionEncodeInUTF8BOM = new QAction("UTF-8 BOM");
	m_actionEncodeInUCSBEBOM = new QAction("UCS-BE BOM");
	m_actionEncodeInUCS2LEBOM = new QAction("UCS-2 LE BOM");

	m_actionConvertToGBK = new QAction("Convert To GBK");
	m_actionConvertToUTF8 = new QAction("Convert To UTF-8");
	m_actionConvertToUTF8BOM = new QAction("Convert To UTF-8 BOM");
	m_actionConvertToUCS2BEBOM = new QAction("Convert To UCS-BE BOM");
	m_actionConvertToUCS2LEBOM = new QAction("Convert To UCS-2 LE BOM");

	m_menuEncoding->addAction(m_actionEncodeInGBK);
	m_menuEncoding->addAction(m_actionEncodeInUft8);
	m_menuEncoding->addAction(m_actionEncodeInUTF8BOM);
	m_menuEncoding->addAction(m_actionEncodeInUCSBEBOM);
	m_menuEncoding->addAction(m_actionEncodeInUCS2LEBOM);
	m_menuEncoding->addSeparator();
	m_menuEncoding->addAction(m_actionConvertToGBK);
	m_menuEncoding->addAction(m_actionConvertToUTF8);
	m_menuEncoding->addAction(m_actionConvertToUTF8BOM);
	m_menuEncoding->addAction(m_actionConvertToUCS2BEBOM);
	m_menuEncoding->addAction(m_actionConvertToUCS2LEBOM);
	m_menuBar->addAction(m_menuEncoding->menuAction());

	// set menu
	m_menuSet = new QMenu("Set");
	m_actionOptions = new QAction("Options");

	m_menuLanguage = new QMenu("Language");
	m_actionChinese = new QAction("Chinese");
	m_actionEnglish = new QAction("English");
	m_menuLanguage->addAction(m_actionChinese);
	m_menuLanguage->addAction(m_actionEnglish);

	m_actionDefineLanguage = new QAction("Define Language");
	m_actionLanguageFileSuffix = new QAction("Language File Suffix");
	m_actionShortcutKeyManager = new QAction("Shortcut Key Manager");

	m_menuSet->addAction(m_actionOptions);
	m_menuSet->addAction(m_menuLanguage->menuAction());
	m_menuSet->addAction(m_actionDefineLanguage);
	m_menuSet->addAction(m_actionLanguageFileSuffix);
	m_menuSet->addAction(m_actionShortcutKeyManager);
	m_menuBar->addAction(m_menuSet->menuAction());

	// toolsMenu
	m_menuTools = new QMenu("Tools");
	m_actionMd5Sha = new QAction("Md5/Sha");
	//m_actionBatchFind = new QAction("Batch Find");
	m_menuTools->addAction(m_actionMd5Sha);
	//m_menuTools->addAction(m_actionBatchFind);

	m_menuBar->addAction(m_menuTools->menuAction());

	// pluginMenu
	m_menuPlugin = new QMenu("Plugin");
	m_actionPluginManager = new QAction("Plugin Manager");
	m_menuPlugin->addAction(m_actionPluginManager);
	m_menuBar->addAction(m_menuPlugin->menuAction());

	// feedbackMenu
	//m_menuFeed

	// helpMenu
	m_menuHelp = new QMenu("Help");
	// m_actionDonate = new QAction("Donate");
	// m_actionBugFix = new QAction("Fix Bug");
	m_actionInfo = new QAction("About NotepadPP");

	// m_menuHelp->addAction(m_actionDonate);
	// m_menuHelp->addAction(m_actionBugFix);
	m_menuHelp->addAction(m_actionInfo);
	m_menuBar->addAction(m_menuHelp->menuAction());
}

void NotepadPP::__initStatusBar()
{
	m_statusBar = new QStatusBar(this);
	//setStatusBar(m_statusBar);

	m_codeNameLabel = new QLabel("");
	m_lineEndComboBox = new QComboBox;

	QStringList lineEnds;
    lineEnds << "Windows(CRLF)" << "Unix(LF)" << "Mac(CR)";
	m_lineEndComboBox->addItems(lineEnds);
	m_lineNumLabel = new QLabel("Line: 1, Col: 1");
	m_langDescLabel = new QLabel("Txt");
	m_zoomLabel = new QLabel("Zoom: 100%");

	m_codeNameLabel->setMinimumWidth(120);
	m_lineEndComboBox->setMinimumWidth(100);
	m_lineNumLabel->setMinimumWidth(120);
	m_langDescLabel->setMinimumWidth(100);
	m_zoomLabel->setMinimumWidth(100);

	m_statusBar->insertPermanentWidget(0, m_zoomLabel);
	m_statusBar->insertPermanentWidget(1, m_langDescLabel);
	m_statusBar->insertPermanentWidget(2, m_lineNumLabel);
	m_statusBar->insertPermanentWidget(3, m_lineEndComboBox);
	m_statusBar->insertPermanentWidget(4, m_codeNameLabel);

	setStatusBar(m_statusBar);

}

void NotepadPP::__connect()
{
	QTabBar* pTabBar = m_editTabWidget->tabBar();
    connect(pTabBar, &QTabBar::tabCloseRequested, this, &NotepadPP::__onTabCloseRequested);
	connect(m_actionNewFile, &QAction::triggered, this, &NotepadPP::__onTriggerNewFile);
	connect(m_actionOpenFile,&QAction::triggered, this, &NotepadPP::__onTriggerOpenFile);
	connect(m_actionSave, &QAction::triggered, this, &NotepadPP::__onTriggerSaveFile);
	connect(m_actionSaveAs, &QAction::triggered, this, &NotepadPP::__onTriggerSaveAs);
	connect(m_actionClose, &QAction::triggered, this, &NotepadPP::__onTriggerClose);
	connect(m_actionCloseAll, &QAction::triggered, this, &NotepadPP::__onTriggerCloseAll);
	connect(m_actionClearHistory, &QAction::triggered, this, &NotepadPP::__onTriggerClearHistory);
	connect(m_actionExit, &QAction::triggered, this, &NotepadPP::__onTriggerExit);

	connect(m_actionUndo, &QAction::triggered, this, &NotepadPP::__onTriggerUndo);
	connect(m_actionRedo, &QAction::triggered, this, &NotepadPP::__onTriggerRedo);
	connect(m_actionCut, &QAction::triggered, this, &NotepadPP::__onTriggerCut);
	connect(m_actionCopy, &QAction::triggered, this, &NotepadPP::__onTriggerCopy);
	connect(m_actionPaste, &QAction::triggered, this, &NotepadPP::__onTriggerPaste);

	connect(m_actionSelectAll, &QAction::triggered, this, &NotepadPP::__onTriggerSelectAll);
	connect(m_actionConverWindowsCRLF, &QAction::triggered, this, &NotepadPP::__onTriggerConvertWinLineEnd);
	connect(m_actionConvertUnixLF, &QAction::triggered, this, &NotepadPP::__onTriggerConvertUnixLineEnd);
	connect(m_actionConvertMacCR, &QAction::triggered, this, &NotepadPP::__onTriggerConvertMacLineEnd);

	connect(m_actionShowSpaces, &QAction::toggled, this, &NotepadPP::__onTriggerShowSpaces);
	connect(m_actionShowEndOfLine, &QAction::toggled, this, &NotepadPP::__onTriggerShowLineEnd);
	connect(m_actionShowAll, &QAction::toggled, this, &NotepadPP::__onTriggerShowAll);

	connect(m_menuLanguage, &QMenu::triggered, this, &NotepadPP::__onTriggerLexerLanguage);

	connect(m_actionInfo, &QAction::triggered, this, &NotepadPP::__onTriggerAboutNotepadPP);
}

bool NotepadPP::isNewFileNameExist(const QString& filename)
{
	for (int i = 0; i < m_editTabWidget->count(); i++)
	{
		auto pw = m_editTabWidget->widget(i);
		if (pw != nullptr)
		{
			int nNewFileIndex = pw->property("NewFileIndex").toInt();
			if (nNewFileIndex != -1)
			{
				QString filepath = pw->property("FilePath").toString();
				if (filepath == filename)
				{
					return true;
				}
			}
		}
	}

	return false;
}

void NotepadPP::newTxtFile(QString filename, int nIndex, QString contentPath /*= ""*/)
{
	auto pEdit = FileManager::getMgr()->newEmptyDocument();
	pEdit->setNoteWidget(this);

	CodeId cid = CodeId::UTF_8;
	// 目前只是处理windows
	LineEnd lineEnd = LineEnd::Dos;

	// contentpath非空暂时不处理
	if (!contentPath.isEmpty())
    {
		return;
    }

	connect(pEdit, SIGNAL(SCN_ZOOM()), this, SLOT(__onZoomValueChange()));

	// enable text change sign
	enableEditTextChangeSign(pEdit);

	// add tab;
    int nCurTabIndex = m_editTabWidget->addTab(pEdit, QIcon("./res/imgs/noneedsave.png"), filename);
	pEdit->setProperty("NewFileIndex", nIndex);
	pEdit->setProperty("FilePath", filename);
	pEdit->setProperty("TextChanged", false);
	pEdit->setProperty("CodeId", (int)cid);
	pEdit->setProperty("LineEnd", (int)lineEnd);

	//NewFileId nfid(nIndex, pEdit);
	FileManager::getMgr()->insertNewFileId(nIndex, pEdit);
	
	// set zoom value
	if (m_nZoomValue != 0)
	{
		pEdit->zoomTo(m_nZoomValue);
	}

	int nZoomValue = 100 + m_nZoomValue * m_nZoomValue;

    QString statusText = QString::asprintf("New File Finished [Text Mode] Zoom %d%", nZoomValue);
	m_statusBar->showMessage(statusText, 8000);
    setZoomLabelValue(nZoomValue);
	pEdit->viewport()->setFocus();
}

void NotepadPP::openFile(QString filename)
{
	QString filepath = getRegularFilePath(filename);
	QFileInfo fileInfo(filepath);
	if (!fileInfo.exists())
	{
		qDebug() << "File not exists:" << filepath;
		return;
	}

	int nIndex = findFileIsOpenAtPad(filepath);
	if (nIndex != -1)
	{
		m_editTabWidget->setCurrentIndex(nIndex);
		QString statusText = QString::asprintf("file %s already opened at tab %d", filepath, nIndex);
		m_statusBar->showMessage(statusText, 8000);
		return;
	}

	openTextFile(filepath);
}

void NotepadPP::openTextFile(QString filepath)
{
	filepath = getRegularFilePath(filepath);
	auto pEdit = FileManager::getMgr()->newEmptyDocument();
	pEdit->setNoteWidget(this);

	CodeId cid = CodeId::UNKNOWN;
	LineEnd lineEnd = LineEnd::Unknown;
	FileManager::getMgr()->loadFileDataInText(pEdit, filepath, cid, lineEnd);
	int nCurIndex = m_editTabWidget->addTab(pEdit, QIcon("./res/imgs/noneedsave.png"), filepath);
	m_editTabWidget->setCurrentIndex(nCurIndex);

	// enable text change sign
	enableEditTextChangeSign(pEdit);

	// show code id;
	setCodeBarLabelByCodeId(cid);
	// show line end;
	setLineEndBarLabelByLineEnd(LineEnd::Dos);

	// set line end;
	pEdit->setProperty("LineEnd", (int)LineEnd::Unknown);
	// set filepath;
	pEdit->setProperty("FilePath", filepath);
	// set Tab Tool tip;
	m_editTabWidget->setTabToolTip(nCurIndex, filepath);
	// set new file index;
	pEdit->setProperty("NewFileIndex", -1);
	// set motify flag
	pEdit->setProperty("TextChanged", false);
	// set code id;
	pEdit->setProperty("CodeId", (int)cid);

	// zoom value changed;
	// connect(pEdit, SIGNAL(SCN_ZOOM()), this, SLOT(__onZoomValueChange()));
}

void NotepadPP::saveTabEdit(int nIndex)
{
	auto pEdit = dynamic_cast<ScintillaEditView*>(m_editTabWidget->widget(nIndex));
	if (pEdit == nullptr)
	{
		return;
	}

	bool bModify = pEdit->property("TextChanged").toBool();
	if (!bModify)
	{
		return;
	}

	int nNewFileIndex = pEdit->property("NewFileIndex").toInt();
	if (nNewFileIndex >= 0)
	{
		QString filter("Text files (*.txt);;XML files (*.xml);;h files (*.h);;cpp file(*.cpp);;All types(*.*)");
		QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), filter);

		if (fileName.isEmpty())
		{
			return;
		}

		int retIndex = findFileIsOpenAtPad(fileName);
		if (retIndex >= 0)
		{
			return;
		}
		
		saveFile(fileName, pEdit);
	}
	else
	{
		QString filepath = pEdit->property("FilePath").toString();
		if (filepath.isEmpty())
		{
			return;
		}
		saveFile(filepath, pEdit);
	}

	pEdit->setProperty("TextChanged", false);
	m_editTabWidget->setTabIcon(nIndex, QIcon("./res/imgs/noneedsave.png"));
	enableEditTextChangeSign(pEdit);
}

void NotepadPP::saveFile(QString filename, ScintillaEditView *pEditView)
{
	QFile srcFile(filename);

	bool bNewFile = true;
	if (srcFile.exists())
	{
		QFlags<QFileDevice::Permission> power = QFile::permissions(filename);
		if (!power.testFlag(QFile::WriteUser))
		{
			m_statusBar->showMessage(tr("No write permission for file %1").arg(filename), 8000);
			return;
		}
		bNewFile = false;
	}

	/// save work;
	if (!srcFile.open(QIODevice::ReadWrite | QIODevice::Truncate))
	{
		m_statusBar->showMessage(tr("Open file %1 failed for write.").arg(filename), 8000);
		return;
	}

	QString textout = pEditView->text();
	if (textout.isEmpty())
	{
		return;
	}

	CodeId cid = (CodeId)pEditView->property("CodeId").toInt();
	QString codeName = EnCode::getQtCodecNameById(cid);

	// 是否带BOM
	// bool bWithBOM = false;
	if (cid == CodeId::UTF_8BOM || cid == CodeId::UTF_16BEBOM || cid == CodeId::UTF_16LEBOM)
	{
		// bWithBOM = true;
		QByteArray bom = EnCode::getStartFlagByCodeId(cid);
		if (!bom.isEmpty())
		{
			srcFile.write(bom);
		}
	}

	QTextCodec::setCodecForLocale(QTextCodec::codecForName(codeName.toStdString().c_str()));
	
	QByteArray text = textout.toUtf8();
	srcFile.write(text);
	srcFile.close();
	return;
}

void NotepadPP::enableEditTextChangeSign(ScintillaEditView* pEdit)
{
	connect(pEdit, &ScintillaEditView::textChanged, this, &NotepadPP::__onTextChanged);
}

void NotepadPP::disEnableEditTextChangeSign(ScintillaEditView* pEdit)
{
	pEdit->disconnect(SIGNAL(textChanged()));
}

void NotepadPP::setZoomLabelValue(int nZoomValue)
{
	QString zoomText = QString::asprintf("Zoom:%d%", nZoomValue);
	m_zoomLabel->setText(zoomText);
}

void NotepadPP::closeTab(int index)
{
	auto pEdit = dynamic_cast<ScintillaEditView*>(m_editTabWidget->widget(index));
	if (pEdit == nullptr)
	{
		return;
	}

	QString filepath = pEdit->property("FilePath").toString();

	m_editTabWidget->removeTab(index);
	int nNewFileIndex = pEdit->property("NewFileIndex").toInt();
	if (nNewFileIndex != -1)
	{
		FileManager::getMgr()->deleteNewFileId(nNewFileIndex);
	}

	if (nNewFileIndex == -1)
	{
		addRecentFile(filepath);
		// updateRecentFileMenu();
	}

	pEdit->deleteLater();
}

QString NotepadPP::getRegularFilePath(QString path)
{
#ifdef _WIN32
	path = path.replace("/", "\\");
#else
	path = path.replace("\\", "/");
#endif
	return path;
}

int NotepadPP::findFileIsOpenAtPad(QString filepath)
{
	int nRet = -1;
	filepath = getRegularFilePath(filepath);
	for (int i = 0; i < m_editTabWidget->count(); i++)
	{
		auto pw = m_editTabWidget->widget(i);
		if (pw != nullptr)
		{
			QString curFilePath = pw->property("FilePath").toString();
			if (filepath == curFilePath)
			{
				nRet = i;
				break;
			}
		}
	}
	return nRet;
}

void NotepadPP::setCodeBarLabelByCodeId(CodeId cid)
{
	QString codeName = EnCode::getCodeNameById(cid);
	m_codeNameLabel->setText(codeName);
}

void NotepadPP::setLineEndBarLabelByLineEnd(LineEnd lineEnd)
{
	QString lineEndName = EnCode::getLineEndNameByLineEndId(lineEnd);
	if (m_lineEndComboBox->currentText() != lineEndName)
	{
		int nIndex = m_lineEndComboBox->findText(lineEndName);
		if (nIndex != -1)
		{
			m_lineEndComboBox->setCurrentIndex(nIndex);
		}
	}
}

bool NotepadPP::convertDocLineEnd(LineEnd lineEnd)
{
    // return false;
	auto pEdit = dynamic_cast<ScintillaEditView*>(m_editTabWidget->currentWidget());
	if (pEdit == nullptr)
	{
		return false;
	}

	int eolMode = 0;
	switch (lineEnd)
	{
	case LineEnd::Dos:
		eolMode = SC_EOL_CRLF;
		break;
	case LineEnd::Unix:
		eolMode = SC_EOL_LF;
		break;
	case LineEnd::Mac:
		eolMode = SC_EOL_CR;
		break;
	default:
		return false;
	}

	int nCurMode = pEdit->execute(SCI_GETEOLMODE);
	if (nCurMode != eolMode)
	{
		// return false;
		m_statusBar->showMessage("Convert end of line in progress..., please wait...");
		pEdit->execute(SCI_SETEOLMODE, eolMode);
		pEdit->execute(SCI_CONVERTEOLS, eolMode);

		m_statusBar->showMessage("Convert end of line completed.", 8000);

		pEdit->setProperty("LineEnd", (int)lineEnd);
		pEdit->setProperty("TextChanged", true);
		setLineEndBarLabelByLineEnd(lineEnd);
	}
	return true;
}

void NotepadPP::loadRecentFileFromConfig()
{
	QString configFile("./config/recentfile");
	// 按行读取直接放入到m_recentFileList中
	QFile file(configFile);
	if (!file.open(QIODevice::ReadOnly))
	{
		return; 
	}

	// utf-8格式读取一行一行
	QTextStream in(&file);
	while (!in.atEnd())
	{
		QString line = in.readLine();
		m_recentOpenFileList.push_back(line);
	}

	updateRecentFileMenu();
}

void NotepadPP::addRecentFile(QString filepath)
{
	// 直接插入到最前边
	m_recentOpenFileList.insert(m_recentOpenFileList.begin(), filepath);

	// 移除重复的元素
	for (auto iter = m_recentOpenFileList.begin(); iter != m_recentOpenFileList.end();)
	{
		if ( (*iter) == filepath && iter != m_recentOpenFileList.begin())
		{
			iter = m_recentOpenFileList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	// 最多保留10条记录
	if (m_recentOpenFileList.size() > 10)
	{
		m_recentOpenFileList.pop_back();
	}

	updateRecentFileMenu();
	saveRecentFileToConfig();
}

void NotepadPP::deleteRecentFile(QString filepath)
{
	for (auto iter = m_recentOpenFileList.begin(); iter != m_recentOpenFileList.end();)
	{
		if ( (*iter) == filepath)
		{
			iter = m_recentOpenFileList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	saveRecentFileToConfig();
}

bool NotepadPP::findRecentFile(QString filepath)
{
	for (auto iter = m_recentOpenFileList.begin(); iter != m_recentOpenFileList.end();)
	{
		if ( (*iter) == filepath)
		{
			iter = m_recentOpenFileList.erase(iter);
			return true;
		}
	}

	return false;
}

void NotepadPP::saveRecentFileToConfig()
{
	QString configFile("./config/recentfile");
	QFile file(configFile);

	// 删除该文件后再创建该文件
	if (file.exists())
	{
		file.remove();
	}

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return;
	}

	QTextStream out(&file);
	for (auto iter = m_recentOpenFileList.begin(); iter != m_recentOpenFileList.end(); iter++)
	{
		out << *iter << "\n";
	}
}

void NotepadPP::updateRecentFileMenu()
{
	// 根据m_recentOpenFileList更新菜单
	m_menuReceneFile->clear();
	for (auto iter = m_recentOpenFileList.begin(); iter != m_recentOpenFileList.end(); iter++)
	{
		QAction* recentOpenFileAction = m_menuReceneFile->addAction(*iter);
		recentOpenFileAction->setProperty("recentFilePath", *iter);
		recentOpenFileAction->setText(*iter);
		connect(recentOpenFileAction, &QAction::triggered, this, &NotepadPP::__onTriggerOpenRecentFile);
	}
}

void NotepadPP::__onTriggerNewFile()
{
	qDebug() << "Trigger New File action.";
	int nIndex = FileManager::getMgr()->getNextNewFileId();

	QString filename;
	while(true)
	{
		filename = QString("NewFile%1").arg(nIndex);
		if (!isNewFileNameExist(filename))
		{
			break;
		}
		nIndex++;
	}
	newTxtFile(filename, nIndex);
}

void NotepadPP::__onTriggerOpenFile()
{
	QFileDialog qfd(this);
	qfd.setFileMode(QFileDialog::ExistingFile);
	int nExec = qfd.exec();
	if (nExec != QDialog::Accepted)
	{
		qfd.close();
		return;
	}

	QStringList sFiles = qfd.selectedFiles();
	QFileInfo fileinfo(sFiles[0]);
	openFile(fileinfo.filePath());
	// qfd.close();
}

void NotepadPP::__onTriggerSaveFile()
{
	int nIndex = m_editTabWidget->currentIndex();
	saveTabEdit(nIndex);
}

void NotepadPP::__onTriggerSaveAs()
{
	int nIndex = m_editTabWidget->currentIndex();
	auto pEdit = dynamic_cast<ScintillaEditView*>(m_editTabWidget->widget(nIndex));
	if (pEdit == nullptr)
	{
		return;
	}

	int nNewFileIndex = pEdit->property("NewFileIndex").toInt();
	if (nNewFileIndex >= 0)
	{
		QString filter("Text files (*.txt);;XML files (*.xml);;h files (*.h);;cpp file(*.cpp);;All types(*.*)");
		QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), filter);

		if (fileName.isEmpty())
		{
			return;
		}

		int retIndex = findFileIsOpenAtPad(fileName);
		if (retIndex >= 0)
		{
			return;
		}
		
		saveFile(fileName, pEdit);
		// return;
	}
	else
	{
		// QString filepath = pEdit->property("FilePath").toString();
		QString filter("Text files (*.txt);;XML files (*.xml);;h files (*.h);;cpp file(*.cpp);;All types(*.*)");
		QString curFilePath = pEdit->property("FilePath").toString();
		QString newFilePath = QFileDialog::getSaveFileName(this, tr("Save File as"), curFilePath, filter);
		if (newFilePath.isEmpty())
		{
			return;
		}

		saveFile(newFilePath, pEdit);
	}

	pEdit->setProperty("TextChanged", false);
	enableEditTextChangeSign(pEdit);
	m_editTabWidget->setTabIcon(nIndex, QIcon("./res/imags/noneedsave.png"));
}

void NotepadPP::__onTriggerClose()
{
	int nIndex = m_editTabWidget->currentIndex();
	if (nIndex >= 0)
	{
		closeTab(nIndex);
	}
}

void NotepadPP::__onTriggerCloseAll()
{
	while (m_editTabWidget->count() > 0)
	{
		closeTab(0);
	} 
}

void NotepadPP::__onTriggerClearHistory()
{
	m_recentOpenFileList.clear();
	updateRecentFileMenu();
	saveRecentFileToConfig();
}

void NotepadPP::__onTriggerOpenRecentFile()
{
	QAction* action = dynamic_cast<QAction*>(sender());
	if (action == nullptr)
	{
		return;
	}

	QString filepath = action->property("recentFilePath").toString();
	openFile(filepath);
}

void NotepadPP::__onTriggerExit()
{
	close();
}

void NotepadPP::__onTriggerUndo()
{
	auto pEdit = dynamic_cast<ScintillaEditView*>(m_editTabWidget->currentWidget());
	if (pEdit == nullptr)
	{
		return;
	}

	pEdit->undo();
}

void NotepadPP::__onTriggerRedo()
{
	auto pEdit = dynamic_cast<ScintillaEditView*>(m_editTabWidget->currentWidget());
	if (pEdit == nullptr)
	{
		return;
	}
	pEdit->redo();
}

void NotepadPP::__onTriggerCut()
{
	auto pEdit = dynamic_cast<ScintillaEditView*>(m_editTabWidget->currentWidget());
	if (pEdit == nullptr)
	{
		return;
	}
	pEdit->cut();
}

void NotepadPP::__onTriggerCopy()
{
	auto pEdit = dynamic_cast<ScintillaEditView*>(m_editTabWidget->currentWidget());
	if (pEdit == nullptr)
	{
		return;
	}
	pEdit->copy();
}

void NotepadPP::__onTriggerPaste()
{
	auto pEdit = dynamic_cast<ScintillaEditView*>(m_editTabWidget->currentWidget());
	if (pEdit == nullptr)
	{
		return;
	}
	pEdit->paste();
}

void NotepadPP::__onTriggerSelectAll()
{
	auto pEdit = dynamic_cast<ScintillaEditView*>(m_editTabWidget->currentWidget());
	if (pEdit == nullptr)
	{
		return;
	}
	pEdit->selectAll();
}

void NotepadPP::__onTriggerConvertWinLineEnd()
{
	convertDocLineEnd(LineEnd::Dos);
}

void NotepadPP::__onTriggerConvertUnixLineEnd()
{
	convertDocLineEnd(LineEnd::Unix);
}

void NotepadPP::__onTriggerConvertMacLineEnd()
{
	convertDocLineEnd(LineEnd::Mac);
}

void NotepadPP::__onTriggerRemoveHeadBlank()
{
}

void NotepadPP::__onTriggerRemoveEndBlank()
{
}

void NotepadPP::__onTriggerRemoveHeadEndBlank()
{
}

void NotepadPP::__onTriggerShowSpaces(bool bChecked)
{
	QsciScintilla::WhitespaceVisibility mode;
	if (bChecked)
	{
		// m_bShowSpaces = true;
		mode = QsciScintilla::WsVisible;
		
	}
	else
	{
		// m_bShowSpaces = false;
		mode = QsciScintilla::WsInvisible;
	}

	for (int i = 0; i < m_editTabWidget->count(); i++)
	{
		auto pEditView = dynamic_cast<ScintillaEditView*>(m_editTabWidget->widget(i));
		pEditView->setWhitespaceVisibility(mode);
		pEditView->setEolVisibility(false);
	}
}

void NotepadPP::__onTriggerShowLineEnd(bool bChecked)
{
	for (int i = 0; i < m_editTabWidget->count(); i++)
	{
		auto pEditView = dynamic_cast<ScintillaEditView*>(m_editTabWidget->widget(i));
		pEditView->setWhitespaceVisibility(QsciScintilla::WsInvisible);
		pEditView->setEolVisibility(bChecked);
	}
}

void NotepadPP::__onTriggerShowAll(bool bChecked)
{
	QsciScintilla::WhitespaceVisibility mode;
	bool bShowLineEnd;
	if (bChecked)
	{
		// m_bShowSpaces = true;
		mode = QsciScintilla::WsVisible;
		bShowLineEnd = true;
		
	}
	else
	{
		// m_bShowSpaces = false;
		mode = QsciScintilla::WsInvisible;
		bShowLineEnd = false;
	}

	for (int i = 0; i < m_editTabWidget->count(); i++)
	{
		auto pEditView = dynamic_cast<ScintillaEditView*>(m_editTabWidget->widget(i));
		pEditView->setWhitespaceVisibility(mode);
		pEditView->setEolVisibility(bShowLineEnd);
	}
}

void NotepadPP::__onTriggerLexerLanguage(QAction *action)
{
	
}

void NotepadPP::__onTextChanged()
{
	auto pEditView = dynamic_cast<ScintillaEditView*>(sender());
	if (pEditView != nullptr)
	{
		bool bTextChanged = pEditView->property("TextChanged").toBool();
		if (!bTextChanged)
		{
            pEditView->setProperty("TextChanged", true);
		}

		// 一旦变化后设置tab图标为红色
		int nTabIndex = m_editTabWidget->indexOf(pEditView);
		if (nTabIndex != -1)
		{
			m_editTabWidget->setTabIcon(nTabIndex, QIcon("./res/imgs/needsave.png"));
		}
		disEnableEditTextChangeSign(pEditView);
	}
}

void NotepadPP::__onZoomValueChange()
{
	auto pSrcEdit = dynamic_cast<ScintillaEditView*>(sender());
	if (pSrcEdit != nullptr)
	{
		pSrcEdit->updateLineNumberWidth();
		int nCurZoomValue = pSrcEdit->execute(SCI_GETZOOM);
		if (m_nZoomValue != nCurZoomValue)
		{
			m_nZoomValue = nCurZoomValue;

			int nZoomValue = 100 + nCurZoomValue * 10;
			setZoomLabelValue(nZoomValue);
			m_statusBar->showMessage(tr("Current Zoom Value is %1%").arg(nZoomValue));
		}

		// 修改其他编辑器的缩放值
		///for (int i = 0; i < m_editTabWidget->count(); i++)
  //      {
  //          auto pEdit = dynamic_cast<ScintillaEditView*>(m_editTabWidget->widget(i));
  //          if (pEdit != nullptr && pEdit != pSrcEdit)
  //          {
		//		disconnect(pEdit, SIGNAL(SCN_ZOOM()), this, SLOT(__onZoomValueChange()));
		//		pEdit->zoomTo(m_nZoomValue);
		//		pEdit->updateLineNumberWidth();
		//		connect(pEdit, SIGNAL(SCN_ZOOM()), this, SLOT(__onZoomValueChange()));
  //          }
  //      }
	}
}

void NotepadPP::__onTabCloseRequested(int index)
{
	closeTab(index);
}

void NotepadPP::__onTriggerAboutNotepadPP()
{
	AboutNotePP aboutDialog(this);
	aboutDialog.exec();
}
