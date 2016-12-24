import QtQuick 2.4
import QtQuick.Layouts 1.1
import Material 0.2
import Material.ListItems 0.1 as ListItem

Item {
    id: overview

    ColumnLayout {
        id: column
        spacing: dp(16)

        Label {
            font.family: "Roboto"
            font.weight: Font.DemiBold
            text: "Database Overview"
            font.pixelSize: dp(34)

            anchors {
                left: parent.left
                top: parent.top
                margins: dp(16)
            }
        }

        Label {
            font.family: "Roboto"
            text: "Here is the introduction"
            font.pixelSize: dp(15)

            anchors {
                left: parent.left
                margins: dp(16)
            }
        }
    }
}
