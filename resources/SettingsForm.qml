import QtQuick 2.4
import QtQuick.Layouts 1.3

Item {
    width: swipeView.width
    height: swipeView.height

    RowLayout {
        anchors.fill: parent
        id: row
        TitleBar {
            sTitle: "SETTINGS"
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
        }
    }
}
