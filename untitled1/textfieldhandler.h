#ifndef TEXTFIELDHANDLER_H
#define TEXTFIELDHANDLER_H

#include <QObject>
#include<iostream>
#include<string>

class TextFieldHandler : public QObject{
    Q_OBJECT
public:
    explicit TextFieldHandler(QObject *parent = nullptr){}
public slots:
    void receiveText(const QString &text);
    void SetFieldState(bool state);
    bool GetFieldState();
    uint16_t GetPort();
    std::string GetIpAdress();
signals:
private:
    uint16_t port = 0;
    std::string IpAdress = "";
    bool m_buttonVisible = true;
};

#endif // TEXTFIELDHANDLER_H
