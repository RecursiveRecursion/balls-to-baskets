import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    id: mainWnd
    // the most optimal settings for different screen resolutions
    width: screen.desktopAvailableWidth / 1.4
    height: screen.desktopAvailableHeight / 1.2
    minimumWidth: screen.desktopAvailableWidth / 1.4
    minimumHeight: screen.desktopAvailableHeight / 1.2
    visible: true
    title: qsTr("Balls To Baskets")

    GroupBox {
        id: basketBox1
        title: qsTr("Корзина 1")
        property double blueChance:
            basket1.totalBalls > 0
            ? (basket1.blueBalls / basket1.totalBalls * 100).toFixed(2) : 0
        property double redChance:
            basket1.totalBalls > 0
            ? (basket1.redBalls / basket1.totalBalls * 100).toFixed(2) : 0

        anchors.left: parent.left
        anchors.right: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: 10
        anchors.rightMargin: 5

        ColumnLayout {
            anchors.fill: parent
            Text { text: qsTr("Всего шаров в корзине: ") + basket1.totalBalls }
            Text { text: qsTr("Синих шаров в корзине: ") + basket1.blueBalls }
            Text { text: qsTr("Красных шаров в корзине: ") + basket1.redBalls }
            Text { text: qsTr("Вероятность достать синий шар: ")
                         + basketBox1.blueChance + "%" }
            Text { text: qsTr("Вероятность достать красный шар: ")
                         + basketBox1.redChance + "%" }
            Text { text: qsTr("Последнее действие: ") + basket1.lastAction }
            Button {
                text: "Переложить шар в корзину 2"
                Layout.topMargin: 10
                Layout.preferredHeight: 25
                Layout.alignment: Qt.AlignCenter
                onClicked: {
                    performer.shiftBall(basket1, basket2);

                    basket1.blueBallsChanged();
                    basket1.redBallsChanged();
                    basket1.totalBallsChanged();
                    basket1.lastActionChanged();

                    basket2.blueBallsChanged();
                    basket2.redBallsChanged();
                    basket2.totalBallsChanged();
                    basket2.lastActionChanged();
                }
            }
        }
    }

    GroupBox {
        id: basketBox2
        title: qsTr("Корзина 2")
        property double blueChance:
            basket2.totalBalls > 0
            ? (basket2.blueBalls / basket2.totalBalls * 100).toFixed(2) : 0
        property double redChance:
            basket2.totalBalls > 0
            ? (basket2.redBalls / basket2.totalBalls * 100).toFixed(2) : 0

        anchors.left: parent.horizontalCenter
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
        anchors.leftMargin: 5

        ColumnLayout {
            anchors.fill: parent
            Text { text: qsTr("Всего шаров в корзине: ") + basket2.totalBalls }
            Text { text: qsTr("Синих шаров в корзине: ") + basket2.blueBalls }
            Text { text: qsTr("Красных шаров в корзине: ") + basket2.redBalls }
            Text { text: qsTr("Вероятность достать синий шар: ")
                         + basketBox2.blueChance + "%" }
            Text { text: qsTr("Вероятность достать красный шар: ")
                         + basketBox2.redChance + "%" }
            Text { text: qsTr("Последнее действие: ") + basket2.lastAction }
            Button {
                text: "Переложить шар в корзину 1"
                Layout.topMargin: 10
                Layout.preferredHeight: 25
                Layout.alignment: Qt.AlignCenter
                onClicked: {
                    performer.shiftBall(basket2, basket1);

                    basket2.blueBallsChanged();
                    basket2.redBallsChanged();
                    basket2.totalBallsChanged();
                    basket2.lastActionChanged();

                    basket1.blueBallsChanged();
                    basket1.redBallsChanged();
                    basket1.totalBallsChanged();
                    basket1.lastActionChanged();
                }
            }
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
            Button {
                text: "Извлечь 2 шара из случайной корзины"
                Layout.topMargin: 10
                Layout.preferredHeight: 25
                Layout.alignment: Qt.AlignCenter
                onClicked: {

                }
            }
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
