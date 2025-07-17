#pragma once

#include <QObject>


const int MaxFileSize = 1024 * 1000;

enum class ErrorType {
    NoError,
    OpenEmptyFile,
};

class NewFileIdMgr {
    public:
        int nIndex;
};

class FlieManager : public QObject 
{
        Q_OBJECT
    private:
        FlieManager()
        {

        }

        ~FlieManager()
        {

        }

    public:
        static FlieManager& getInstance()
        {
            static FlieManager instance;
            return instance;
        }

        int getNextNewFileId()
        {
            
        }
};