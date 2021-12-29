#include "MainViewModel.h"

MainViewModel::MainViewModel()
{
    m_graphViewModel = std::make_unique<GraphViewModel>();
}

GraphViewModel *MainViewModel::graphViewModel()
{
    return m_graphViewModel.get();
}
