import QtQuick 2.4
import Material 0.2
import thjdb.QMLif 1.0
import QtQuick.Controls 1.3 as Controls

Item {

    QMLif {
        id:qmlif1
        onResultReady: button1.text = qmlif1.gettext()
    }
    QMLif {
        id:qmlif2
        onResultReady:
        {
            snackbar.open(qmlif2.gettext())
            button2.text = qmlif2.gettext()
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: dp(20)

        Button {
            id:button1
            text: "Simple Button"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: qmlif1.doSomething()
        }

        Button {
            id:button2
            text: "Raised Button"
            elevation: 1
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked:
            {
                qmlif2.doSomething()
                qmlif2.receivedastring(button2.text)
                snackbar.open("This is a snackbar")
            }
        }

        Button {
            text: "Disabled Raised Button"
            elevation: 1
            enabled: false
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            text: "Wide Button"

            width: dp(200)
            elevation: 1
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: snackbar.open("That button is wide, and so is this snackbar!")
        }

        Button {
            id: focusableButton
            text: "Focusable with really long text"
            elevation: 1
            activeFocusOnPress: true
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: snackbar.open("The text is really very very very very very long and now it needs to wrap, so this should show as two lines!")
        }

        Button {
            text: "Colored button"
            textColor: Theme.accentColor
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: snackbar.open("That button is colored!")
        }

        Button {
            text: "Focusable button #2"
            elevation: 1
            activeFocusOnPress: true
            backgroundColor: Theme.primaryColor
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: snackbar.open("That button is colored!")
        }
    }

    ActionButton {
        anchors {
            right: parent.right
            bottom: snackbar.top
            margins: dp(32)
        }

        action: Action {
            id: addContent
            text: "&Copy"
            shortcut: "Ctrl+C"
            onTriggered: snackbar.open("We do actions too!")
        }
        iconName: "content/add"
    }

    Snackbar {
        id: snackbar
    }
}
