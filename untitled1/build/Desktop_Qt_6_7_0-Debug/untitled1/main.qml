import QtQuick 2.15
import QtQuick.Controls 2.15


ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Image Signal Example"

    Image {
        id: displayImage
        anchors.centerIn: parent
        visible: false
    }

    function showImage(imagePath) {
        displayImage.source = "~/Downloads/Cat2.png"
        displayImage.visible = true
    }
}
