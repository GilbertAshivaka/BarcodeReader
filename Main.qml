import QtQuick
import QtQuick.Window
import QtMultimedia

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")


    CaptureSession{
        id: captureSession
        camera: Camera{
            id: camera
        }

        videoOutput: viewFinder
    }

    VideoOutput{
        id: viewFinder
        visible: true
        anchors.fill: parent
    }

    Component.onCompleted: {
        camera.start()
    }
}
