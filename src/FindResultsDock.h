#pragma once

#include <QDockWidget>

class FindResultsView;
class FindResultsDock : public QDockWidget
{ 
    Q_OBJECT
public:
    FindResultsDock(QWidget *parent = nullptr);
protected:
    FindResultsView* m_findResultsView;
};