#ifndef IMAGESIGNALSENDER_H
#define IMAGESIGNALSENDER_H

#include <QObject>

class ImageSignalSender : public QObject{
    Q_OBJECT
public:
    explicit ImageSignalSender(QObject *parent = nullptr);
signals:
    void setImageSignal(const QString &imagePath);
    void hideImageSignal();
    void showImageSignal();
};

#endif
