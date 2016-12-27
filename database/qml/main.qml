import QtQuick 2.4
import Material 0.2
import Material.ListItems 0.1 as ListItem

ApplicationWindow {
    id: demo

    title: "THJDB 2.0.9.5"

    // Necessary when loading the window from C++
    visible: true

    theme {
        primaryColor: "purple"
        accentColor: "purple"
        tabHighlightColor: "white"
    }

    property var databaseSettings: [

    ]
    property var databaseCommand: [
            "Overview", "Execute", "Dbmanage"
    ]
//    property var aboutDatabase: [

//    ]
//    property var aboutDatabaseString: [

//    ]
    property var sections: [ databaseCommand ]

    property var sectionTitles: [ "Database Command" ]

    property string selectedComponent: sections[0][0]

    property var gettext:
    {
        "Custom Icons":"basic settings",
        "Color Palette":"search optimize",
        "Typography":"database optimize",
        "Overview":"Database Overview",
        "Execute":"Execute",
        "Dbmanage":"Manage Database",
        "Radio Button":"test1",
        "Slider":"test2",
        "Switch":"test3",
        "TextField":"test4",
        "Bottom Sheet":"About Author",
        "Dialog":"Thanks",
        "Forms":"Libs Included",
        "List Items":"License",
        "Page Stack":"test1",
        "Time Picker":"test2",
        "Date Picker":"test3"
    }

    initialPage: TabbedPage {
        id: page

        title: "THJDB 一个有情怀的数据库"

        actionBar.maxActionCount: navDrawer.enabled ? 3 : 4

        actions: [

            Action {
                iconName: "image/color_lens"
                name: "Colors"
                onTriggered: colorPicker.show()
            }
        ]

        backAction: navDrawer.action

        NavigationDrawer {
            id: navDrawer

            enabled: page.width < dp(500)

            onEnabledChanged: smallLoader.active = enabled

            Flickable {
                anchors.fill: parent

                contentHeight: Math.max(content.implicitHeight, height)

                Column {
                    id: content
                    anchors.fill: parent

                    Repeater {
                        model: sections

                        delegate: Column {
                            width: parent.width

                            ListItem.Subheader {
                                text: sectionTitles[index]
                            }

                            Repeater {
                                model: modelData
                                delegate: ListItem.Standard {
                                    text: modelData
                                    selected:
                                    {
                                        modelData == demo.selectedComponent
                                    }
                                    onClicked: {
                                        demo.selectedComponent = modelData
                                        navDrawer.close()
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        Repeater {
            model: !navDrawer.enabled ? sections : 0

            delegate: Tab {
                title: sectionTitles[index]

                property string selectedComponent: modelData[0]
                property var section: modelData


                sourceComponent: tabDelegate
            }
        }

        Loader {
            id: smallLoader
            anchors.fill: parent
            sourceComponent: tabDelegate

            property var section: []
            visible: active
            active: false
        }
    }

    Dialog {
        id: colorPicker
        title: "Choose your favorite color"

        positiveButtonText: "Done"

        MenuField {
            id: selection
            model: ["Primary color", "Accent color", "Background color"]
            width: dp(160)
        }

        Grid {
            columns: 7
            spacing: dp(8)

            Repeater {
                model: [
                    "red", "pink", "purple", "deepPurple", "indigo",
                    "blue", "lightBlue", "cyan", "teal", "green",
                    "lightGreen", "lime", "yellow", "amber", "orange",
                    "deepOrange", "grey", "blueGrey", "brown", "black",
                    "white"
                ]

                Rectangle {
                    width: dp(30)
                    height: dp(30)
                    radius: dp(2)
                    color: Palette.colors[modelData]["500"]
                    border.width: modelData === "white" ? dp(2) : 0
                    border.color: Theme.alpha("#000", 0.26)

                    Ink {
                        anchors.fill: parent

                        onPressed: {
                            switch(selection.selectedIndex) {
                                case 0:
                                    theme.primaryColor = parent.color
                                    break;
                                case 1:
                                    theme.accentColor = parent.color
                                    break;
                                case 2:
                                    theme.backgroundColor = parent.color
                                    break;
                            }
                        }
                    }
                }
            }
        }

        onRejected: {
            // TODO set default colors again but we currently don't know what that is
        }
    }

    Component {
        id: tabDelegate

        Item {

            Sidebar {
                id: sidebar

                expanded: !navDrawer.enabled

                Column {
                    width: parent.width

                    Repeater {
                        model: section
                        delegate: ListItem.Standard {
                            text: gettext[modelData]
                            selected:
                            {
                                modelData == selectedComponent
                            }
                            onClicked:
                            {
                                selectedComponent = modelData
                            }
                        }
                    }
                }
            }
            Flickable {
                id: flickable
                anchors {
                    left: sidebar.right
                    right: parent.right
                    top: parent.top
                    bottom: parent.bottom
                }
                clip: true
                contentHeight: Math.max(example.implicitHeight + 40, height)
                Loader {
                    id: example
                    anchors.fill: parent
                    asynchronous: true
                    visible: status == Loader.Ready
                    // selectedComponent will always be valid, as it defaults to the first component
                    source: {
                        if (navDrawer.enabled) {
                            return Qt.resolvedUrl("%.qml").arg(demo.selectedComponent.replace(" ", ""))
                        } else {
                            return Qt.resolvedUrl("%.qml").arg(selectedComponent.replace(" ", ""))
                        }
                    }
                }

                ProgressCircle {
                    anchors.centerIn: parent
                    visible: example.status == Loader.Loading
                }
            }
            Scrollbar {
                flickableItem: flickable
            }
        }
    }
}
