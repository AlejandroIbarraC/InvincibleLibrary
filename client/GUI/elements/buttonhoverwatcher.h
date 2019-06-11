#ifndef BUTTONHOVERWATCHER_H
#define BUTTONHOVERWATCHER_H

#include <QObject>
#include <QPushButton>
#include <QEvent>

class ButtonHoverWatcher : public QObject
{
    Q_OBJECT
public:
    explicit ButtonHoverWatcher(QObject * parent = Q_NULLPTR, QString not_hovered = "", QString hovered = "");
    virtual bool eventFilter(QObject * watched, QEvent * event) Q_DECL_OVERRIDE;
    QString on_hover;
    QString on_not_hovered;
};

#endif // BUTTONHOVERWATCHER_H
