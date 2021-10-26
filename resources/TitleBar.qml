import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Item {
    id: titleBar

    width: parent.width
    height: 80

    property string sTitle: "Title"

    RowLayout {
        anchors.right: parent.right
        anchors.left: parent.left
        height: parent.height
        anchors.margins: 30

        Text{
            color: "white"
            text: sTitle
            font.pointSize: 22
        }
        Button{
            onClicked: backend.update()
            text: ""            
            font.pointSize: 15
            Layout.alignment: Qt.AlignRight
        }
    }

}

