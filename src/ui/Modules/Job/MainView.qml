import QtQuick 2.15
import QtQuick.Controls 2.15

import "../../Custom" as Custom

Item {
    id: module

    SwipeView {
        id: swipeView
        anchors.fill: parent

        currentIndex: 0

        SummaryView {
            id: summaryView
        }

        HistoryView {
            id: historyView
        }

    }

    PageIndicator {
        id: indicator

        count: swipeView.count
        currentIndex: swipeView.currentIndex

        anchors.bottom: swipeView.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 24
    }
}
