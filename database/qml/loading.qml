import QtQuick 2.4
import Material 0.2
import Material.ListItems 0.1 as ListItem

ApplicationWindow {
    id: demo
    Loader {id:pageLoader}
    title: "Loading"
    visible: true
    width: 640
    height: 480
    theme {
        primaryColor: "red"
        accentColor: "purple"
        tabHighlightColor: "white"
    }
    Image {
        id: image1
        fillMode: Image.verticalCenter
        smooth: true
        source: "images/loadingimage.jpeg"
    }
    Button{
        text:"click to load"
        onClicked:
        {
            pageLoader.source="qrc:/qml/main.qml"
            demo.close()
        }
    }
}
