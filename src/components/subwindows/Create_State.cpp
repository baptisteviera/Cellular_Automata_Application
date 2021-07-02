#include "Create_State.h"

Create_State::Create_State(QWidget* parent) : QDialog(parent) {
    mainLayout = new QVBoxLayout(this);
    colorLayout = new QFormLayout(this);
    labelLayout = new QFormLayout(this);

    colorCbb = new QComboBox(this);
    idLayout = new QFormLayout(this);
    id = new QLineEdit(this);
    label = new QLineEdit(this);
    colorCbb->addItem("white");
    colorCbb->addItem("yellow");
    colorCbb->addItem("blue");
    colorCbb->addItem("cyan");
    colorCbb->addItem("darkcyan");
    colorCbb->addItem("red");
    colorCbb->addItem("green");
    colorCbb->addItem("magenta");
    colorLayout->addRow("Colors", colorCbb);
    labelLayout->addRow("Label", label);
    idLayout->addRow("id", id);

    btnConfirm =  new QPushButton("Confirm",this);
    mainLayout->addWidget(btnConfirm);


    connect(btnConfirm, &QPushButton::clicked, this, &Create_State::newState) ;

    mainLayout->addLayout(colorLayout);
    mainLayout->addLayout(labelLayout);
    mainLayout->addLayout(idLayout);

    mainLayout->addWidget(btnConfirm);

    adjustSize();
}


void Create_State::newState() {
    try{
        DBManager dbMan = DBManager::getDB();
        QString label=this->label->displayText();
        int id=this->id->displayText().toInt();
        QString color=this->colorCbb->currentText();
        dbMan.DbaddState(label, id , color);


    }
    catch(DBException e){
        QMessageBox window;
        window.setText(QString::fromStdString(e.getInfo()));
        window.exec();
    }

        emit stateadded();
        close();
}
