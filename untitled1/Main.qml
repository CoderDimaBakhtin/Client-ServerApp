import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Client Application"

    Label {
        id:label
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text: labelhandler.labelText
    }

    Image {
        id: displayImage
        anchors.centerIn: parent
        visible: false
    }

    function setImage(imagePath) {
        displayImage.source = imagePath;
        displayImage.visible = true;
    }

    function hideImage() {
        displayImage.visible = false;
    }

    function showImage() {
        displayImage.visible = true;
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 10
        TextField {
            id: inputField
            placeholderText: qsTr("IpAdress PORT")
            Layout.fillWidth: true
            visible: button.visible
        }
        Button {
            id: button
            text: qsTr("Submit")
            Layout.alignment: Qt.AlignCenter
            onClicked: {
                button.visible = false;
                textfield.receiveText(inputField.text)
                textfield.SetFieldState(button.visible);
            }
        }

    }

}
