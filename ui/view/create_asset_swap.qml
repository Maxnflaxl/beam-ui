import QtQuick 2.11
import QtQuick.Controls 1.2
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.2
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.12
import Beam.Wallet 1.0
import "controls"
import "./utils.js" as Utils

ColumnLayout {
    id: thisView

    // callbacks set by parent
    property var onClosed: undefined

    TopGradient {
        mainRoot: main
        topColor: Style.accent_incoming
    }

    //
    // Title row
    //
    SubtitleRow {
        Layout.fillWidth:    true
        Layout.topMargin:    100
        Layout.bottomMargin: 30

        //% "Create a Asset Swap Offer"
        text: qsTrId("wallet-receive-asset-swap-title")
        onBack: function () {
            onClosed()
        }
    }

    ScrollView {
        id:                  scrollView
        Layout.fillWidth:    true
        Layout.fillHeight:   true
        Layout.bottomMargin: 10
        clip:                true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy:   ScrollBar.AsNeeded

        ColumnLayout {
            width: scrollView.availableWidth

            //
            // Content row
            //
            RowLayout {
                Layout.fillWidth:   true
                spacing:  10

                //
                // Left column
                //
                ColumnLayout {
                    Layout.alignment:       Qt.AlignTop
                    Layout.fillWidth:       true
                    Layout.preferredWidth:  400
                    Layout.rightMargin:     -5
                    spacing:                10
                    //
                    // Send amount
                    //
                    Panel {
                        //% "Send amount"
                        title:                   qsTrId("sent-amount-label")
                        Layout.fillWidth:        true
                        content:
                        AmountInput {
                            id:                         sentAmountInput
                            color:                      Style.accent_outgoing
                            currencies:                 ["BEAM"]
                            currencyIdx:                0
                            amount:                     "3"
                            rate:                       "2"
                            rateUnit:                   "USD"
                            multi:                      true
                            resetAmount:                false
                            currColor:                  Style.content_main
                            error:                      ""

                            onCurrencyIdxChanged: {
                                console.log('LEFT onCurrencyIdxChanged');
                            }
                        }
                    }

                    //
                    // Offer expiration time
                    //
                    FoldablePanel {
                        //% "Offer expiration time"
                        title:                   qsTrId("wallet-receive-offer-expires-label")
                        Layout.fillWidth:        true
                        folded:                  false
                        content: ColumnLayout {
                            CustomComboBox {
                                id:                  expiresCombo
                                Layout.fillWidth:    true
                                currentIndex:        0
                                fontPixelSize:       14
                                model: [
                                    //% "30 minutes"
                                    qsTrId("wallet-receive-expires-30m"),
                                    //% "1 hour"
                                    qsTrId("wallet-receive-expires-1"),
                                    //% "2 hours"
                                    qsTrId("wallet-receive-expires-2"),
                                    //% "6 hours"
                                    qsTrId("wallet-receive-expires-6"),
                                    //% "12 hours"
                                    qsTrId("wallet-receive-expires-12")
                                ]
                            }
        
                            // Binding {
                            //     target:   viewModel
                            //     property: "offerExpires"
                            //     value:    expiresCombo.currentIndex
                            // }
                        }
                    }

                    //
                    // Comment
                    //
                    FoldablePanel {
                        //% "Comment"
                        title:                   qsTrId("general-comment")
                        Layout.fillWidth:        true
                        content: ColumnLayout {
                        SFTextInput {
                            id:               addressComment
                            font.pixelSize:   14
                            Layout.fillWidth: true
                            // font.italic :     !viewModel.commentValid
                            backgroundColor:  Style.content_main
                            color:            Style.content_main
                            focus:            true
                            text:             "Comment"
                            maximumLength:    BeamGlobals.maxCommentLength()
                            // enabled:          !thisView.addressSaved
                            //% "Comments are local and won't be shared"
                            placeholderText:  qsTrId("general-comment-local")
                        }

                            // Binding {
                            //     target:   viewModel
                            //     property: "addressComment"
                            //     value:    addressComment.text
                            // }

                            // Item {
                            //     Layout.fillWidth: true
                            //     SFText {
                            //         //% "Address with the same comment already exists"
                            //         text:           qsTrId("general-addr-comment-error")
                            //         color:          Style.validator_error
                            //         font.pixelSize: 12
                            //         font.italic:    true
                            //         visible:        !viewModel.commentValid
                            //     }
                            // }
                        }
                    }
                }  // ColumnLayout

                //
                // Middle column
                //
                Rectangle {
                    Layout.alignment:       Qt.AlignTop
                    Layout.topMargin:       60
                    Layout.leftMargin:      -12
                    Layout.rightMargin:     -12
                    Layout.preferredHeight: 24
                    Layout.preferredWidth:  24
                    color:                  Style.background_main
                    z:                      1
                    radius:                 12
                    SvgImage {                 
                        Layout.maximumHeight: 24
                        Layout.maximumWidth:  24
                        source: "qrc:/assets/icon-swap-currencies.svg"
                        MouseArea {
                            anchors.fill: parent
                            acceptedButtons: Qt.LeftButton
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                console.log('Swap columns');
                            }
                        }
                    }
                } // Rectangle

                //
                // Right column
                //
                ColumnLayout {
                    Layout.alignment:       Qt.AlignTop
                    Layout.fillWidth:       true
                    Layout.preferredWidth:  400
                    Layout.leftMargin:      -5
                    spacing:                10

                    //
                    // Receive amount
                    //
                    Panel {
                        //% "Receive amount"
                        title: qsTrId("receive-amount-swap-label")
                        Layout.fillWidth:        true
                        content:
                        AmountInput {
                            id:                         receiveAmountInput
                            color:                      Style.accent_outgoing
                            currencies:                 ["ASSET"]
                            currencyIdx:                0
                            amount:                     "9"
                            rate:                       "1"
                            rateUnit:                   "USD"
                            multi:                      true
                            resetAmount:                false
                            currColor:                  Style.content_main
                            error:                      ""
                            onCurrencyIdxChanged: {
                                console.log('RIGHT onCurrencyIdxChanged');
                            }
                        }
                    }

                    //
                    // Summary pane
                    //
                    Pane {
                        Layout.fillWidth:        true
                        padding:                 20

                        background: Rectangle {
                            radius: 10
                            color:  Style.background_button
                        }

                        ColumnLayout {
                            anchors.fill:        parent
                            spacing:             20

                            GridLayout {
                                Layout.fillWidth:    true
                                columnSpacing:       20
                                columns:             2

                                SFText {
                                    Layout.alignment:       Qt.AlignTop
                                    font.pixelSize:         14
                                    color:                  Style.content_secondary
                                    //% "Beam transaction fee (est)"
                                    text:                   qsTrId("general-asset-swap-rate") + ":"
                                }
    
                                SFText {
                                    font.pixelSize:   14
                                    color:            Style.content_main
                                    text:             "11"
                                }

                                SFText {
                                    Layout.topMargin:       20
                                    font.pixelSize:         14
                                    color:                  Style.content_secondary
                                    //% "Exchange rate"
                                    text:                   qsTrId("general-rate") + ":"
                                }

                                SFText {
                                    Layout.topMargin:       20
                                    font.pixelSize:   14
                                    color:            Style.content_main
                                    text:             "33"
                                }

                                SFText {
                                    Layout.alignment:       Qt.AlignTop
                                    Layout.topMargin:       20
                                    font.pixelSize:         14
                                    color:                  Style.content_secondary
                                    //% "Swap token"
                                    text:                   qsTrId("send-swap-token") + ":"
                                }

                                ColumnLayout {
                                    spacing: 11
                                    RowLayout {
                                        Layout.fillWidth:        true
                                        Layout.topMargin:        20

                                        SFLabel {
                                            id:                  tokenLabel
                                            Layout.fillWidth:    true
                                            font.pixelSize:      14
                                            color:               Style.content_main
                                            elide:               Text.ElideMiddle
                                            text:                "token"
                                        }
                                    
                                        LinkButton {
                                            //% "Token details"
                                            text: qsTrId("swap-token-details")
                                            linkColor: Style.accent_incoming
                                            // enabled:  thisView.canSend()
                                            onClicked: {
                                                console.log('tokenInfoDialog.open();');
                                            }
                                        }
                                    }

                                    CustomButton {
                                        //% "copy and close"
                                        text:                qsTrId("general-copy-and-close")
                                        palette.buttonText:  Style.content_main
                                        palette.button:      Style.background_button
                                        icon.source:         enabled ? "qrc:/assets/icon-copy.svg" : "qrc:/assets/icon-copy-gray.svg"
                                        // enabled:             thisView.canSend()
                                        onClicked: {
                                            console.log('copy and close');
                                        }
                                    }
                                }
                            }
                        }
                    }
                } // ColumnLayout
            }

            //
            // Footer
            //
            RowLayout {
                Layout.alignment:    Qt.AlignHCenter
                Layout.topMargin:    30
                Layout.bottomMargin: 30
                spacing:             30

                CustomButton {
                    //% "publish offer"
                    text:                qsTrId("wallet-receive-swap-publish")
                    palette.buttonText:  Style.content_opposite
                    icon.color:          Style.content_opposite
                    palette.button:      Style.active
                    icon.source:         "qrc:/assets/icon-share.svg"
                    // enabled:             thisView.canSend()
                    onClicked: {
                        console.log('publish offer');
                    }
                }
            }
        }  // ColumnLayout
    } // Scroll
}