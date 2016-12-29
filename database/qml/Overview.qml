import QtQuick 2.4
import QtQuick.Layouts 1.1
import Material 0.2
import Material.ListItems 0.1 as ListItem

Item {
    id: overview

    ColumnLayout {
        id: column
        spacing: dp(16)

         nLabel {
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
            textFormat: Text.RichText
            text: "<p>Version 3.0 Release</p>
        <p>Author: Guo Fangze, Jiang Zhongyu, Huang Jiahui</p>
        <p>This is a powerful RDBMS provided for <br>you proudly with support for many SQL Commands</p>
        <p>The default working directory is the one your program starts.</p>
        <p>Currently, our supporting functions include:</p>
        <ul>
            <li>SELECT, UPDATE, DELETE</li>
            <li>INDEXING, BULB FILES, DATABASE MANAGEMENT</li>
            <li>NETWORKING, ENCRYPTION</li>
        </ul>
        <p>Select one of the buttons on the left to begin.</p>"
            font.pixelSize: dp(15)

            anchors {
                left: parent.left
                margins: dp(16)
            }
        }
    }
}
