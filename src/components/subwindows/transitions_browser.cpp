#include "transitions_browser.h"

TransitionsBrowser::TransitionsBrowser(QWidget* parent) : QDialog(parent) {
    mainLayout = new QVBoxLayout(this);
    transitionLayout = new QFormLayout(this);
    transitionsCbb = new QComboBox(this);

    btnConfirm = new QPushButton("Confirm", this);

    transitionLayout->addRow("Transition rule", transitionsCbb);

    connect(btnConfirm, &QPushButton::clicked, this, &TransitionsBrowser::chooseTransition);
    connect(transitionsCbb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TransitionsBrowser::transitionsCbbChanged);

    mainLayout->addLayout(transitionLayout);
    mainLayout->addWidget(btnConfirm);

    adjustSize();
}

TransitionsBrowser::~TransitionsBrowser() {

}

void TransitionsBrowser::openTransitionBrowser(){
    std::pair<int, TransitionStrategy**> loadedTransitionInfos;
    try{
        loadedTransitionInfos = DBManager::getDB().loadTransitionsFromDB();
        setTransitions(loadedTransitionInfos.first, loadedTransitionInfos.second);
    }
    catch(DBException e){
        QMessageBox window;
        window.setText(QString::fromStdString(e.getInfo()));
        window.show();
    }

    this->exec();
}


void TransitionsBrowser::setTransitions(int nbTransitions, TransitionStrategy** transitions) {
    this->nbTransitions = nbTransitions;
    this->transitions = transitions;
    updateCombobox();
}

void TransitionsBrowser::updateCombobox() {
    transitionsCbb->clear();
    for (int i = 0; i < nbTransitions; i ++) {
        transitionsCbb->addItem(transitions[i]->getName().c_str());
    }
}

void TransitionsBrowser::transitionsCbbChanged(int id) {
    selectedTransition = transitions[id];
}

void TransitionsBrowser::chooseTransition() {
    emit transitionChanged(selectedTransition);
    close();
}
