import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15


Item {
    width: swipeView.width
    height: swipeView.height

    ColumnLayout {
        anchors.right: parent.right
        anchors.left: parent.left
        height: parent.height
        spacing: 20
        id: row

        TitleBar {
            sTitle: "SETTINGS"
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
        }

        ColumnLayout{
            id: contentColumn
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter
            spacing: 20
            SectionTitle {
                sTitle: "Cashier Address"
            }
            RowLayout {
                spacing: 10
                TextEdit{
                    id: cashierAddressText
                    text: backend.cashier_address
                    wrapMode: Text.WordWrap
                    readOnly: true
                    selectByMouse: true
                    color: "#eee"
                }
                Button{
                    onClicked: {
                        cashierAddressText.selectAll()
                        cashierAddressText.copy()
                    }
                    text: ""
                    font.pointSize: 15
                    Layout.alignment: Qt.AlignRight
                }
            }
        }
    }
}
