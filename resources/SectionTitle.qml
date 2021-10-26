import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {
    width: 200
    height: 50

    property string sTitle: "Title"


    Text {
        text: sTitle
        anchors.fill: parent
        color: "#eee"
        font.pointSize: 16
        verticalAlignment: Qt.AlignVCenter

    }

}
