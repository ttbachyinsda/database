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

    QMLif {
        id: result
        onResultReady: {
//            addEle(result.getDBList())
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
                            result.doSomething("use " + modelData + ";")
                            Logic.addEle(result.getTable())
                            Logic.depth += 1
                        }
                    }
                }
            }
            model: ListModel {
                id:testModel
            }
        }

        Button {
            id:button2
            text: "Refresh"
            elevation: 1
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                Logic.addEle(result.getDBList())
                Logic.depth = 0
            }
        }
    }
}
