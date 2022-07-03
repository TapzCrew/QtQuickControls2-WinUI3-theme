import QtQuick 6.3

Canvas {
    id: root

    antialiasing: true

    enum Orientation {
        Left,
        Right,
        Up,
        Down
    }

    property int orientation: Orientation.Left

    property int triangleWidth: 60
    property int triangleHeight: 60
    property color strokeColor: "#ffffff"
    property color fillColor: "#ffffff"
    property int lineWidth: 3
    property bool fill: false
    property bool stroke: true
    property real alpha: 1.0

    onLineWidthChanged: requestPaint()
    onFillChanged: requestPaint()
    onStrokeChanged: requestPaint()

    onPaint: {
        var ctx = getContext("2d")
        ctx.save()
        ctx.clearRect(0, 0, root.width, root.height)

        ctx.strokeStyle = root.strokeColor
        ctx.lineWidth = root.lineWidth
        ctx.fillStyle = root.fillColor
        ctx.globalAlpha = root.alpha

        ctx.lineJoin = "round"

        ctx.beginPath()
        ctx.translate((0.5 * width - 0.5 * triangleWidth),
                      (0.5 * height - 0.5 * triangleHeight))

        if (orientation === Triangle.Orientation.Left) {
            ctx.moveTo(0, triangleHeight / 2)
            ctx.lineTo(triangleWidth, 0)
            ctx.lineTo(triangleWidth, triangleHeight)
        } else if (orientation === Triangle.Orientation.Right) {
            ctx.moveTo(triangleWidth, triangleHeight / 2)
            ctx.lineTo(0, 0)
            ctx.lineTo(0, triangleHeight)
        } else if (orientation === Triangle.Orientation.Up) {
            ctx.moveTo(triangleWidth / 2, 0)
            ctx.lineTo(0, triangleHeight)
            ctx.lineTo(triangleWidth, triangleHeight)
        } else if (orientation === Triangle.Orientation.Down) {
            ctx.moveTo(triangleWidth / 2, triangleHeight)
            ctx.lineTo(0, 0)
            ctx.lineTo(triangleWidth, 0)
        }

        ctx.closePath()
        if (root.fill)
            ctx.fill()
        if (root.stroke)
            ctx.stroke()
        ctx.restore()
    }
}
