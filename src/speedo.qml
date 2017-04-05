
// diese Datei stammt von  http://community.qnx.com/sf/discussion/do/listPosts/projects.qt/discussion.general.topc21389?_pagenum=1
//import Qt 4.7
import QtQuick 2.4

Rectangle {
    id: mainBox
    width:  800
    height: 480


    Connections {
        target: speedData
        onValuesChanged: {
            speedMtr = Mtr0*2
            tachMtr = Mtr1*1
            totalFrames = totFrames
            frameText.text = persecFrames
            ndl_1x.visible = true;
        }
        //console.log("stuff"); prints as Application output in windows i.e.
        //onValuesChanged: { console.log("onValuesChanged()") }
    }

    Image {
        id: backgrnd
        source: "images/base2d.png"
        anchors.centerIn: parent
    }

    Rectangle {
         id: ndl_0x
         width: 32; height: 113
         x: 388; y: 271
         color:"transparent"
         smooth:true
         Image {
             id: ndl_0
             source: "images/needle5.png"
             anchors.centerIn: parent
             transform: Rotation { origin.x:22; origin.y:26; angle: speedMtr
                 Behavior on angle { SpringAnimation { spring: 2; damping: 0.3; modulus: 360 }}
             }
         }
    }

    Rectangle {
         id: ndl_1x
         width: 8; height: 220
         x: 342; y: 46
         color:"transparent"
         //smooth:true
         visible: false
         Image {
             id: ndl_1
             source: "images/redDot.png"
             transform: Rotation { origin.x:60; origin.y:220; angle: tachMtr
                 Behavior on angle { SpringAnimation { spring: 2; damping: 0.4; modulus: 360 }}
             }
         }
     }


    // text field for framerate

    Text {
            id: frameText
            anchors.centerIn: parent
            anchors.horizontalCenterOffset : 0
            anchors.verticalCenterOffset : 205
            font.family: "Arial"
            font.pointSize: 24
            smooth: true
            color: "gray"
            style: Text.Outline
            styleColor: "black"
            text: " "
    }


    property int totalFrames: 0
    property int lastFrames: 0
    property int persecFrames: 0
    property int speedMtr : 0
    property int tachMtr : 0

    function timeChanged() {
        persecFrames = totalFrames - lastFrames;
        lastFrames = totalFrames;
    }

    Timer {
        id: runTimer
        interval: 1000; running: true; repeat: true
        onTriggered: timeChanged()
    }
}

