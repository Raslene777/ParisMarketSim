import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 1300
    height: 750
    title: "Serveur Boursier - Trading Terminal"
    color: "#121212"

    Rectangle {
        anchors.fill: parent
        anchors.margins: 15
        color: "transparent"

        ColumnLayout {
            anchors.fill: parent
            spacing: 15

            Rectangle {
                Layout.fillWidth: true
                height: 70
                radius: 8
                color: "#1E1E1E"

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 40

                    Label {
                        text: "SERVEUR BOURSIER"
                        color: "white"
                        font.pixelSize: 24
                        font.bold: true
                    }

                    Label {
                        text: "ACTION1 : 152.30 €"
                        color: "#00FF88"
                        font.pixelSize: 20
                    }

                    Label {
                        text: "Marché Ouvert"
                        color: "#00AAFF"
                        font.pixelSize: 18
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 15

                Rectangle {
                    Layout.preferredWidth: 350
                    Layout.fillHeight: true
                    radius: 8
                    color: "#1E1E1E"

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 20
                        spacing: 15

                        Label {
                            text: "Nouvel Ordre"
                            color: "white"
                            font.pixelSize: 20
                        }

                        TextField {
                            id: clientField
                            placeholderText: "Client ID"
                        }

                        TextField {
                            id: actionField
                            placeholderText: "Action (ex: ACTION1)"
                        }

                        TextField {
                            id: quantityField
                            placeholderText: "Quantité"
                            inputMethodHints: Qt.ImhDigitsOnly
                        }

                        TextField {
                            id: priceField
                            placeholderText: "Prix"
                            inputMethodHints: Qt.ImhFormattedNumbersOnly
                        }

                        ComboBox {
                            id: typeBox
                            model: ["Achat", "Vente"]
                        }

                        Button {
                            text: "Envoyer Ordre"
                            onClicked: {
                                console.log("Ordre envoyé:",
                                            clientField.text,
                                            actionField.text,
                                            quantityField.text,
                                            priceField.text,
                                            typeBox.currentText)
                            }
                        }
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    radius: 8
                    color: "#1E1E1E"

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 20
                        spacing: 10

                        Label {
                            text: "Portefeuille"
                            color: "white"
                            font.pixelSize: 20
                        }

                        Rectangle {
                            height: 40
                            width: parent.width
                            color: "#2C2C2C"

                            Row {
                                anchors.fill: parent
                                anchors.leftMargin: 10
                                anchors.verticalCenter: parent.verticalCenter
                                spacing: 50

                                Text { text: "Action"; color: "white"; width: 250 }
                                Text { text: "Quantité"; color: "white"; width: 150 }
                            }
                        }

                        ListView {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            clip: true

                            model: ListModel {
                                ListElement { action: "ACTION1"; qty: 120 }
                                ListElement { action: "ACTION2"; qty: 75 }
                                ListElement { action: "ACTION3"; qty: 310 }
                            }

                            delegate: Rectangle {
                                height: 40
                                width: parent.width
                                color: index % 2 === 0 ? "#222222" : "#262626"

                                Row {
                                    anchors.fill: parent
                                    anchors.leftMargin: 10
                                    anchors.verticalCenter: parent.verticalCenter
                                    spacing: 50

                                    Text {
                                        text: action
                                        color: "white"
                                        width: 250
                                    }

                                    Text {
                                        text: qty
                                        color: "white"
                                        width: 150
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 180
                radius: 8
                color: "#1E1E1E"

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 10

                    Label {
                        text: "Transactions Récentes"
                        color: "white"
                        font.pixelSize: 20
                    }

                    ListView {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        model: ListModel {
                            ListElement { txt: "C1 a acheté 100 ACTION1 à 150€" }
                            ListElement { txt: "C2 a vendu 50 ACTION2 à 175€" }
                            ListElement { txt: "C3 a acheté 200 ACTION3 à 98€" }
                        }

                        delegate: Text {
                            text: txt
                            color: "white"
                            padding: 4
                        }
                    }
                }
            }
        }
    }
}
