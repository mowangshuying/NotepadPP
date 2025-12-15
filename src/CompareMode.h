
#pragma once

#include <QObject>
#include "__global.h"
#include <QString>

class FileLineInfo {
public:
    FileLineInfo() {
        nLineNums = 0;
        bLcsExist = false;
        bEmptyLine = false;
        nCode = CodeId::UNKNOWN;
        lineEnd = LineEnd::Unknown;
    }
public:
    int nLineNums;
    bool bLcsExist;
    bool bEmptyLine;
    CodeId nCode; // 该行字符编码
    LineEnd lineEnd;
    QByteArray md4;
    QString unicodeStr;
};

class CompareMode : public QObject {
    Q_OBJECT
public:
    CompareMode(QObject *parent = nullptr) : QObject(parent) {}
    ~CompareMode() {}
public:
    static CodeId getTextFileCodeId(uchar* fileFpr, int fileLength, QString filepath);
    
    // 自适应匹配codeid
    static CodeId scanFileOutput(CodeId& cid, QString filepath,
        std::vector<FileLineInfo>& lineInfoVct, int& nMaxLineSize, int& charNums);
    
        // 指定codeid去打开文件;
    static CodeId scanFileOutputByCodeId(CodeId cid, QString filepath,
        std::vector<FileLineInfo>& lineInfoVct, int& nMaxLineSize, int& charNums);

    static CodeId readLineFromFile(uchar* fileptr, const int fileLength, 
        const CodeId cid, std::vector<FileLineInfo>& lineInfoVct, int &nMaxLineSize, int& charNums);

    static bool getOneLineFromFile(uchar* fileptr, int& nStartPos, const int fileLength, const CodeId cid, QByteArray& bytes);
};