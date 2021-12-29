import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"

ApplicationWindow {
    id: view
    property var viewModel: dataContext

    initialPage: Component { MainPage { viewModel: view.viewModel } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations
}
