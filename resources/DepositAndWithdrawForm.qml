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
        spacing: 10
        id: row
        TitleBar {
            sTitle: "DEPOSIT & WITHDRAW"
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
        }
        Item{
            Layout.fillHeight: true
            Layout.fillWidth: true
            Column{
                anchors.fill: parent
                anchors.leftMargin: 30
                anchors.rightMargin: 30
                spacing: 20
                SectionTitle {
                    sTitle: "Network"
                }
                ComboBox {
                    id: comboBoxNetwork
                    anchors.right: parent.right
                    anchors.left: parent.left
                    model: backend.networks
                    onCurrentTextChanged:  {
                        backend.on_select_network(currentText)
                    }
                }
                SectionTitle {
                    sTitle: "Withdraw"
                }
                ComboBox {
                    id: comboBoxWithdrawToken
                    anchors.right: parent.right
                    anchors.left: parent.left
                    model: backend.supported_withdraw_tokens
                }
                TextField {
                    id: addressWithdrawField
                    placeholderText: qsTr("Token Address")
                    anchors.right: parent.right
                    anchors.left: parent.left
                }
                TextField {
                    id: amountWithdrawField
                    placeholderText: qsTr("Amount")
                    anchors.right: parent.right
                    anchors.left: parent.left
                }
                Button {
                    text: qsTr("Withdraw")
                    leftPadding: 40
                    rightPadding: 40
                    onClicked: backend.on_withdraw(comboBoxWithdrawToken.displayText,
                                                   addressWithdrawField.text,
                                                   amountWithdrawField.text)
                }
                SectionTitle {
                    sTitle: "Deposit"
                }
                ComboBox {
                    id: comboBoxDepositToken
                    anchors.right: parent.right
                    anchors.left: parent.left
                    model: backend.supported_deposit_tokens
                }
                Button {
                    text: qsTr("Deposit")
                    leftPadding: 40
                    rightPadding: 40
                    onClicked: backend.on_deposit(comboBoxDepositToken.displayText)
                }
            }
        }
    }
}
