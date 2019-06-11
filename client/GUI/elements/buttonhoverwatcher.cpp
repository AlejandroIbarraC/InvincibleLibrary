#include "buttonhoverwatcher.h"

ButtonHoverWatcher::ButtonHoverWatcher(QObject * parent, QString not_hovered, QString hovered) :
    QObject(parent)
{
    on_hover = hovered;
    on_not_hovered = not_hovered;
}

bool ButtonHoverWatcher::eventFilter(QObject * watched, QEvent * event) {
    QPushButton * button = qobject_cast<QPushButton*>(watched);
    if (!button) {
        return false;
    }
    if (event->type() == QEvent::Enter) {
        // The push button is hovered by mouse
        button->setIcon(QIcon(on_hover));
        return true;
    }
    if (event->type() == QEvent::Leave){
        // The push button is not hovered by mouse
        button->setIcon(QIcon(on_not_hovered));
        return true;
    }
    return false;
}
