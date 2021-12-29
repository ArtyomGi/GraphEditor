#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>

#include "ViewModel/GraphViewModel.h"
#include "ViewModel/MainViewModel.h"

int main(int argc, char *argv[])
{
    MainViewModel mainVM;
    QGuiApplication *app = SailfishApp::application(argc, argv);
    QQuickView *view = SailfishApp::createView();
    view->setSource(SailfishApp::pathToMainQml());

    qmlRegisterUncreatableType<MainViewModel>("ViewModels.MainViewModel", 1, 0, "MainViewModel", "Cant'create MainViewModel!");
    qmlRegisterUncreatableType<GraphViewModel>("ViewModels.GraphViewModel", 1, 0, "GraphViewModel", "Cant'create GraphViewModel!");
    view->rootContext()->setContextProperty("dataContext", qobject_cast<QObject *>(&mainVM));
    view->showFullScreen();

    return app->exec();
}
