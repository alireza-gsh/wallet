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
            sTitle: "TRANSFER"
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
        }
        Item{
            Layout.fillHeight: true
            Layout.fillWidth: true
            Column{
                anchors.fill: parent
                anchors.margins: 30
                spacing: 15
                ComboBox {
                    id: tokenComboBox
                    anchors.right: parent.right
                    anchors.left: parent.left
                    model: backend.own_tokens
                }
                TextField {
                    id: addressField
                    placeholderText: qsTr("Address")
                    anchors.right: parent.right
                    anchors.left: parent.left
                }
                TextField {
                    id: amountField
                    placeholderText: qsTr("Amount")
                    anchors.right: parent.right
                    anchors.left: parent.left
                }
                Button {
                    text: qsTr("send")
                    leftPadding: 40
                    rightPadding: 40
                    onClicked: backend.on_transfer(tokenComboBox.displayText, addressField.text, amountField.text)
                }
            }
        }
    }
}
