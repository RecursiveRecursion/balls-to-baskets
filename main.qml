import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    id: mainWnd
    // the most optimal settings for different screen resolutions
    width: screen.desktopAvailableWidth/1.4
    height: screen.desktopAvailableHeight/1.2
    minimumWidth: screen.desktopAvailableWidth/1.4
    minimumHeight: screen.desktopAvailableHeight/1.2
    visible: true
    title: qsTr("Balls To Baskets")

    GroupBox {
        id: basketBox1
        title: qsTr("Корзина 1")

        anchors.left: parent.left
        anchors.right: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: 10
        anchors.rightMargin: 5

        ColumnLayout {
            anchors.fill: parent
            Text { text: qsTr("Всего шаров в корзине: ") }
            Text { text: qsTr("Синих шаров в корзине: ") }
            Text { text: qsTr("Красных шаров в корзине:") }
            Text { text: qsTr("Вероятность достать синий шар: ") + "%" }
            Text { text: qsTr("Вероятность достать красный шар: ") + "%" }
            Text { text: qsTr("Последнее действие: ") }
            Button { text: "Переложить шар в корзину 2";
                     Layout.topMargin: 10;
                     Layout.preferredHeight: 25;
                     Layout.alignment: Qt.AlignCenter }
        }
    }

    GroupBox {
        id: basketBox2
        title: qsTr("Корзина 2")

        anchors.left: parent.horizontalCenter
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
        anchors.leftMargin: 5

        ColumnLayout {
            anchors.fill: parent
            Text { text: qsTr("Всего шаров в корзине: ") }
            Text { text: qsTr("Синих шаров в корзине: ") }
            Text { text: qsTr("Красных шаров в корзине:") }
            Text { text: qsTr("Вероятность достать синий шар: ") + "%" }
            Text { text: qsTr("Вероятность достать красный шар: ") + "%" }
            Text { text: qsTr("Последнее действие: ") }
            Button { text: "Переложить шар в корзину 1";
                     Layout.topMargin: 10;
                     Layout.preferredHeight: 25;
                     Layout.alignment: Qt.AlignCenter }
        }
    }

    GroupBox {
        id: bottomBox

        anchors.left: basketBox1.horizontalCenter
        anchors.right: basketBox2.horizontalCenter
        anchors.top: basketBox1.bottom
        anchors.margins: 10

        ColumnLayout {
            anchors.fill: parent
            Text { text: qsTr("Вероятность достать 2 синих шара: ") + "%" }
            Text { text: qsTr("Вероятность достать 2 красных шара: ") + "%" }
            Text { text: qsTr("Вероятность достать 1 красный и 1 синий шары: ") + "%" }
            Text { text: qsTr("Последнее действие: ") }
            Button { text: "Извлечь 2 шара из случайной корзины";
                     Layout.topMargin: 10;
                     Layout.preferredHeight: 25;
                     Layout.alignment: Qt.AlignCenter }
        }
    }

    Button {
        id: exitButton
        text: qsTr("Выход")

        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10

        onClicked: {
            Qt.quit();
        }
    }
}
