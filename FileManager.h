#pragma once

#include <QObject>

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
};