#pragma once

#include <memory>

#include <QObject>
#include <QVariant>

#include "GraphViewModel.h"

class MainViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(GraphViewModel *graphViewModel READ graphViewModel CONSTANT)
public:
    MainViewModel();

    GraphViewModel *graphViewModel();

private:
    std::unique_ptr<GraphViewModel> m_graphViewModel;
};
