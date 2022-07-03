import QtQuick 6.3
import QtQuick.Templates 6.3 as T

import WinUI3Style 1.0

T.Label {
    id: control

    opacity: enabled ? 1.0 : 0.2
    color: control.WinUI3Style.textFillColorPrimary
    linkColor: control.WinUI3Style.accent

    wrapMode: Text.WordWrap
}
