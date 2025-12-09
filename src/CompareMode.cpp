#include "CompareMode.h"
#include <QFile>
#include <uchardet.h>
#include <QDebug>
#include "EnCode.h"
#include <libucd.h>
#include <QString>

CodeId CompareMode::getTextFileCodeId(uchar *fileFpr, int fileLength, QString filepath)
{
    if (fileLength >= 2 && fileFpr[0] == 0xFF && fileFpr[1] == 0xFE)
    {
        return CodeId::UTF_16LEBOM;
    }
    else if (fileLength >= 2 && fileFpr[0] == 0xFE && fileFpr[1] == 0xFF)
    {
        return CodeId::UTF_16BEBOM;
    }
    else if (fileLength >= 3 && fileFpr[0] == 0xEF && fileFpr[1] == 0xBB && fileFpr[2] == 0xBF)
    {
        return CodeId::UTF_8BOM;
    }

    CodeId cid = CodeId::UNKNOWN;
    // using libucd
    ucd_t t;
    ucd_init(&t);
    int r = ucd_parse(&t, (char*)fileFpr, fileLength);
    ucd_end(&t);
    char name[128];
    memset(name, 0, 128);
    if (r == UCD_RESULT_OK)
    {
        ucd_results(&t,name,127);
        cid = EnCode::getCodeIdByName(QString::fromStdString(name));
    }
    ucd_reset(&t);
    ucd_clear(&t);


    // return EnCode::getQtCodecNameById(name);
    return cid;
}

CodeId CompareMode::scanFileOutput(CodeId& cid, QString filepath, std::vector<FileLineInfo> &lineInfoVct, int &nMaxLineSize, int &charNums)
{
    // return CodeId();
    QFile* file = new QFile(filepath);
    if (!file->open(QIODevice::ReadOnly))
    {
        return CodeId::UNKNOWN;
    }

    uchar* fileptr = (uchar*)file->map(0, file->size());
    cid = getTextFileCodeId(fileptr, file->size(), filepath);


    readLineFromFile(fileptr, file->size(), cid, lineInfoVct, nMaxLineSize, charNums);

    file->unmap(fileptr);
    file->close();
    delete file;

    return cid;
}

CodeId CompareMode::readLineFromFile(uchar *fileptr, const int fileLength, const CodeId cid, std::vector<FileLineInfo> &lineInfoVct, int &nMaxLineSize, int &charNums)
{
    int nStartPos = 0;
    int nLineNums = 0;
    if (cid == CodeId::UTF_8BOM)
    {
        nStartPos = 3;
    }
    else if(cid == CodeId::UTF_16BEBOM || cid == CodeId::UTF_16LEBOM)
    {
        nStartPos = 2;
    }

    QByteArray bytes;
    while(getOneLineFromFile(fileptr, nStartPos, fileLength, cid, bytes))
    {
        FileLineInfo lineInfo;
        lineInfo.nLineNums = nLineNums;
        lineInfo.nCode = cid;
        int nLineLen = bytes.length();
        if (nMaxLineSize < nLineLen)
        {
            nMaxLineSize = nLineLen;
        }

        EnCode::translateStringToUnicode(cid, bytes.data(), nLineLen, lineInfo.unicodeStr);

        if (lineInfo.unicodeStr.endsWith("\r\n"))
        {
            if (nLineLen < 2)
            {
                lineInfo.bLcsExist = false;
                lineInfo.bEmptyLine = true;
            }
            lineInfo.lineEnd = LineEnd::Dos;
        }
        else if(lineInfo.unicodeStr.endsWith("\n"))
        {
            if (nLineLen < 1)
            {
                lineInfo.bLcsExist = false;
                lineInfo.bEmptyLine = true;
            }
            lineInfo.lineEnd = LineEnd::Unix;
        }
        else if(lineInfo.unicodeStr.endsWith("\r"))
        {
            if (nLineLen < 1)
            {
                lineInfo.bLcsExist = false;
                lineInfo.bEmptyLine = true;
            }
            lineInfo.lineEnd = LineEnd::Mac;
        }
        else
        {
            lineInfo.lineEnd = LineEnd::Unknown;
        }

        lineInfoVct.push_back(lineInfo);
        nLineNums++;
        charNums += lineInfo.unicodeStr.length();
    }

    return cid;
}

// 处理三种编码 utf8 utf16be utf16le
// utf8: 0x0d 0x0a
// utf16le: 0x0d 0x00 0x0a 0x00 
// utf16be: 0x00 0x0d 0x00 0x0a 
// 00 31 --- 1   utf16be
// 31 00 --- 1   utf16le
bool CompareMode::getOneLineFromFile(uchar *fileptr, int &nStartPos, const int fileLength, const CodeId cid, QByteArray &bytes)
{
    if (nStartPos >= fileLength)
        return false;

    bytes.clear();
    int nLineLen = 0;
    bool bFindLine = false;

    // 0x0D 和 0x0A 两个常见的ASCII控制字符，分别标识回车符和换行符号
    for (int i = nStartPos; i < fileLength; i++, nLineLen++)
    {
        uchar ch = fileptr[i];
        // 0x0D = CR
        if (ch == 0x0D)
        {
            if (cid == CodeId::UTF_16LE || cid == CodeId::UTF_16LEBOM)
            {
                // \r\0 \n\0
                if ( (i + 3) < fileLength)
                {
                    if (fileptr[i] == 0x0D && fileptr[i + 1] == 0x00 && fileptr[i + 2] == 0x0A && fileptr[i + 3] == 0x00)
                    {
                        nLineLen += 4;
                        bytes.append((char*)(fileptr + nStartPos), nLineLen);
                        nStartPos += nLineLen;
                        bFindLine = true;
                        break;
                    }
                }
            }
            else if (cid == CodeId::UTF_16BE || cid == CodeId::UTF_16BEBOM)
            {
                // \0\r \0\n
                if ( (i > 1) && (i + 2 < fileLength) )
                {
                    if (fileptr[i - 1] == 0x00 && fileptr[i] == 0x0D && fileptr[i + 1] == 0x00 && fileptr[i + 2] == 0x0A)
                    {// /r/n
                        nLineLen += 3;
                        bytes.append((char*)(fileptr + nStartPos), nLineLen);
                        nStartPos += nLineLen;
                        bFindLine = true;
                        break;
                    }
                }

            }
            else if((i+1) < fileLength && fileptr[i+1] == 0x0A)
            {// /r/n
                nLineLen += 2;
                bytes.append((char*)(fileptr + nStartPos), nLineLen);
                nStartPos += nLineLen;
                bFindLine = true;
                break;
            }
            else
            {// 直接以 \r为结尾
                nLineLen += 1;
                bytes.append((char*)(fileptr + nStartPos), nLineLen);
                nStartPos += nLineLen;
                bFindLine = true;
                break;
            }
        }
        else if (ch == 0x0A)
        {
            nLineLen += 1;
            bytes.append((char*)(fileptr + nStartPos), nLineLen);
            nStartPos += nLineLen;
            bFindLine = true;
            break;
        }
    }

    if (!bFindLine)
    {
        // 文件最后一行没有换行符
        bytes.append((char*)(fileptr + nStartPos), fileLength - nStartPos);
        nStartPos = fileLength;
    }

    return true;
}
