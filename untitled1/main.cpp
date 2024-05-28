#include<QGuiApplication>
#include<QQmlApplicationEngine>
#include<QQmlContext>
#include<QString>
#include<iostream>
#include<thread>
#include"Client.h"
#include"labelhandler.h"
#include "imagesignalsender.h"
#include"textfieldhandler.h"

void MainLogic(ImageSignalSender& SignalHandler,LabelHandler& labelhandler,TextFieldHandler& textfield){
    std::cout<<"Client"<<std::endl;
    while(textfield.GetFieldState()){}

    Client client(textfield.GetPort(),textfield.GetIpAdress());
    client.Run(SignalHandler,labelhandler);
}

int main(int argc, char *argv[]){
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    LabelHandler labelhandler;
    TextFieldHandler textfield;

    engine.rootContext()->setContextProperty("textfield", &textfield);
    engine.rootContext()->setContextProperty("labelhandler", &labelhandler);

    const QUrl url(QStringLiteral("qrc:/untitled1/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);
    if (engine.rootObjects().isEmpty()){
        return -1;
    }
    ImageSignalSender imageSignalSender;

    QObject::connect(&imageSignalSender, &ImageSignalSender::setImageSignal, [&engine](const QString &imagePath) {
        QMetaObject::invokeMethod(engine.rootObjects().first(), "setImage", Qt::AutoConnection, Q_ARG(QVariant, imagePath));
    });
    QObject::connect(&imageSignalSender, &ImageSignalSender::hideImageSignal, [&engine]() {
        QMetaObject::invokeMethod(engine.rootObjects().first(), "hideImage", Qt::AutoConnection);
    });
    QObject::connect(&imageSignalSender, &ImageSignalSender::showImageSignal, [&engine]() {
        QMetaObject::invokeMethod(engine.rootObjects().first(), "showImage", Qt::AutoConnection);
    });

    // MainLogic.start();

    // not sychronized labelHandler, textfield ...
    std::thread LogicThread(MainLogic,std::ref(imageSignalSender),std::ref(labelhandler),std::ref(textfield));
    LogicThread.detach(); // Should be logic of client

    return app.exec();
}
