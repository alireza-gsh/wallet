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
            sTitle: "BALANCES"
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
        }

        ColumnLayout{
            id: contentColumn
            Layout.fillWidth: false
            Layout.alignment: Qt.AlignCenter
            spacing: 20
            SectionTitle {
                sTitle: "Wallet Address"
            }
            RowLayout {
                spacing: 10
                TextEdit{
                    id: addressText
                    text: backend.wallet_address
                    wrapMode: Text.WordWrap
                    readOnly: true
                    selectByMouse: true
                    color: "#eee"
                }
                Button{
                    onClicked: {
                        addressText.selectAll()
                        addressText.copy()
                    }
                    text: ""
                    font.pointSize: 15
                    Layout.alignment: Qt.AlignRight
                }
            }
            SectionTitle {
                sTitle: "Tokens"
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Component {
                    id: tokenDelegate
                    Item {
                        height: 40
                        Column {
                            spacing: 10
                            Row {
                                spacing: 10
                                Text {
                                    color: "white"
                                    text: modelData.value
                                    font.pointSize: 13
                                    width: balancesListView.width /3
                                }
                                Text {
                                    color: "#888"
                                    text: modelData.name
                                    font.pointSize: 13
                                    width: balancesListView.width /3
                                }
                                Text {
                                    color: "#888"
                                    text: modelData.network
                                    font.pointSize: 13
                                    width: balancesListView.width /3
                                }
                            }
                            Rectangle {
                                color: "#222"
                                width: balancesListView.width
                                height: 1
                            }
                        }
                    }}

                ListView {
                    id: balancesListView
                    visible: true
                    anchors.fill: parent
                    model: backend.tokens_info_list
                    delegate: tokenDelegate

                    Label {
                        anchors.fill: parent
                        horizontalAlignment: Qt.AlignHCenter
                        verticalAlignment: Qt.AlignVCenter
                        visible: parent.count === 0
                        text: qsTr("Empty Balance")
                    }
                }
            }
        }

    }
}
