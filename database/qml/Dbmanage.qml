import QtQuick 2.4
import QtQuick.Layouts 1.1
import Material 0.2
import Material.ListItems 0.1 as ListItem
import thjdb.QMLif 1.0
import QtQuick.Controls 1.3 as Controls
import "clickEvent.js" as Logic

Item {
    id: manage
    objectName: "DbManage"
    implicitHeight: column.height

    QMLif {
        id: result
        onResultReady: {
            resultLable.text = result.gettext()
        }
    }

    ColumnLayout {
        id: column
        anchors.centerIn: parent
        spacing: dp(32)

        ListView {
            id: list
            highlight: Rectangle{
                color: "lightsteelblue"
                radius: 3
            }
            highlightFollowsCurrentItem: true
            focus: true

            width: 300; height: 400
            delegate: Item {
                id: wrapper
                height: 35
                width: 300
                Rectangle {
                    color: "transparent"
                    Text {
                        text: modelData
                        font.family: "Roboto"
                        font.weight: Font.Light
                        font.pixelSize: dp(25)
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: list.currentIndex = index
                    onDoubleClicked: {
                        if (Logic.depth == 0) {
                            Logic.addEle(result.getTable(modelData))
                            Logic.depth += 1
                        } else if (Logic.depth == 1) {
                            result.doSomething("select * from " + modelData + ";")
                            Logic.depth += 1
                            resultLable.visible = true
                            list.visible = false
                        }
                    }
                }
            }
            model: ListModel {
                id:testModel
            }
        }

        Text {
            id: resultLable
            visible: false
            textFormat: Text.RichText
            anchors.horizontalCenter: parent.horizontalCenter

            font.family: "Roboto"
            font.weight: Font.Light
            font.pixelSize: dp(20)
        }

        Button {
            id:button2
            text: "Refresh"
            elevation: 1
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                list.visible = true
                resultLable.visible = false
                Logic.addEle(result.getDBList())
                Logic.depth = 0
            }
        }
    }
}
