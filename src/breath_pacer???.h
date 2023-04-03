#include <QtWidgets>

void createBreathPacer(QGraphicsScene* scene, int x, int y, int diameter, int duration)
{
    // Create an ellipse item with the specified diameter and position
    QGraphicsEllipseItem* ellipseItem = scene->addEllipse(x, y, diameter, diameter);

    // Set the color and opacity of the ellipse item
    ellipseItem->setBrush(QBrush(Qt::blue));
    ellipseItem->setOpacity(0.5);

    // Create a horizontal animation for the ellipse item
    QPropertyAnimation* animation = new QPropertyAnimation(ellipseItem, "pos");
    animation->setDuration(duration * 1000);
    animation->setLoopCount(-1);
    animation->setStartValue(QPointF(x, y));
    animation->setEndValue(QPointF(x + diameter, y));
    animation->setEasingCurve(QEasingCurve::InOutSine);

    // Start the animation
    animation->start();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create a graphics view and a graphics scene
    QGraphicsView view;
    QGraphicsScene scene(0, 0, 400, 300);

    // Add the graphics scene to the graphics view
    view.setScene(&scene);
    view.show();

    // Create a breath pacer in the form of a ball going back and forth on the session screen
    createBreathPacer(&scene, 50, 100, 30, 10);

    return app.exec();
}
