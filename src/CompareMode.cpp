#include "CompareMode.h"
#include <QFile>
#include <uchardet.h>
#include <QDebug>

CodeId CompareMode::getTextFileCodeId(uchar *fileFpr, int fileLength, QString filepath)
{
    if (fileLength >= 2 && fileFpr[0] == 0xFF && fileFpr[1] == 0xFE)
    {
        return CodeId::Utf16BEBom;
    }
    else if (fileLength >= 2 && fileFpr[0] == 0xFE && fileFpr[1] == 0xFF)
    {
        return CodeId::Utf16LEBom;
    }
    else if (fileLength >= 3 && fileFpr[0] == 0xEF && fileFpr[1] == 0xBB && fileFpr[2] == 0xBF)
    {
        return CodeId::Utf8Bom;
    }

    // // no bom
    uchardet_t detector = uchardet_new();
    uchardet_handle_data(detector, (char*)fileFpr, fileLength);
    uchardet_data_end(detector);
    const char* charset = uchardet_get_charset(detector);
    QString strCharset = QString::fromUtf8(charset);
    uchardet_delete(detector);
    qDebug() << "detected charset:" << strCharset;
    return CodeId::Unknown;
}

CodeId CompareMode::scanFileOutput(CodeId cid, QString filepath, std::vector<FileLineInfo> &lineInfoVct, int &nMaxLineSize, int &charNums)
{
    // return CodeId();
    QFile* file = new QFile(filepath);
    if (!file->open(QIODevice::ReadOnly))
    {
        return CodeId::Unknown;
    }

    uchar* fileptr = (uchar*)file->map(0, file->size());
    cid = getTextFileCodeId(fileptr, file->size(), filepath);
    file->unmap(fileptr);
    file->close();
    delete file;

    return cid;
}

CodeId CompareMode::readLineFromFile(uchar *fileptr, const int fileLength, const CodeId cid, std::vector<FileLineInfo> &lineInfoVct, 
    std::vector<FileLineInfo> &blankLineInfoVct, int mode, int &nMaxLineSize)
{
    int nStartPos = 0;
    int nLineNums = 0;
    if (cid == CodeId::Utf8Bom)
    {
        nStartPos = 3;
    }
    else if(cid == CodeId::Utf16BEBom || cid == CodeId::Utf16LEBom)
    {
        nStartPos = 2;
    }

    QByteArray bytes;
    while(getOneLineFromFile(fileptr, nStartPos, fileLength, cid, bytes))
    {
        FileLineInfo lineInfo;
        lineInfo.nLineNums = nLineNums;

        int nLineLen = bytes.length();
        if (nMaxLineSize < nLineLen)
        {
            nMaxLineSize = nLineLen;
        }


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
            if (cid == CodeId::Utf16LE || cid == CodeId::Utf16LEBom)
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
            else if (cid == CodeId::Utf16BE || cid == CodeId::Utf16BEBom)
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
