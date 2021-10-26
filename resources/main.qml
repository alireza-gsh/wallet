import QtQuick 2.15
import QtQuick.Controls 2.15


ApplicationWindow {
    id: mainWindow
    minimumWidth: 600
    minimumHeight: 800
    visible: true
    title: qsTr("DarkWallet")

    FontLoader { id: fontAwesomeSolid; source: "qrc:fonts/fa-solid-900.ttf" }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        BalancesForm {}
        TransferForm {}
        DepositAndWithdrawForm {}
        SettingsForm {}
    }

    footer: Column {
        TextEdit {
            id: texEdit
            visible: backend.notification === "" ? false : true
            text: " %1".arg(backend.notification)
            wrapMode: Text.WordWrap
            readOnly: true
            selectByMouse: true
            color: "#eee"
            font.pointSize: 14
            focus: true
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 30
        }
        TabBar {
            id: tabBar
            currentIndex: swipeView.currentIndex
            width: parent.width
            Repeater {
                model: ["", "", "", ""]
                TabButton {
                    text: modelData
                }
            }
        }
    }
}
