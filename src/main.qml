import QtQuick 2.4
import QtQuick.Window 2.2

Window {
    visible: true
    x: 100; y: 100; width: 800; height: 490
    title : "Mercedes-Benz - UI 175873"

    /*MainForm {
        anchors.fill: parent
        mouseArea.onClicked: {
            Qt.quit();
        }
    }*/


    Loader {
        source:"speedo.qml";
        asynchronous: true
        visible: status == Loader.Ready
      }


    ListView {
        id: cpuInfoView
        //anchors.left: parent.left
        //anchors.top: parent.top
        width: 180; height: 80
        //orientation: Qt.Vertical
        spacing: 5


        model: cpuInfoModel
        delegate: Text {
            text: type + "\t: " + val
            color: "gray"
            font.family: "Arial"
            font.pointSize: 14
            smooth: true
            style: Text.Outline
            styleColor: "black"
        }

    }



}

