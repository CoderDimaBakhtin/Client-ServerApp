#ifndef LABELHANDLER_H
#define LABELHANDLER_H

#include <QObject>

class LabelHandler : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString labelText READ getLabelText WRITE setLabelText NOTIFY labelTextChanged)
public:
    explicit LabelHandler(QObject *parent = nullptr);
    QString getLabelText() const;
    void setLabelText(const QString &value);
signals:
    void labelTextChanged();
private:
    QString labelText;
};

#endif
