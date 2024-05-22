#include "labelhandler.h"

LabelHandler::LabelHandler(QObject *parent) : QObject(parent){
    labelText = "";
}

QString LabelHandler::getLabelText() const{
    return labelText;
}

void LabelHandler::setLabelText(const QString &value){
    if (value != labelText) {
        labelText = value;
        emit labelTextChanged();
    }
}
