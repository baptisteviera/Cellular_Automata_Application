#include "control_panel.h"
#include <iostream>
#include <string>

void ControlPanel::updateStates(){
    while(statesListWidget->count()>0){
      statesListWidget->takeItem(0);
    }
    for (int i = 0; i < simulatorWidget->getSimulator()->getAutomata()->getNbStates(); i ++) {
        CellState* s = simulatorWidget->getSimulator()->getAutomata()->getAvailableState(i);
        std::string item = std::to_string(s->getId());
        item += ". " + s->getLabel();
        statesListWidget->addItem(item.c_str());
    }
    statesListWidget->adjustSize();
}

void ControlPanel::openNeighborsBrowser() {
    neighborsBrowser->openNeighborsBrowser();
}

void ControlPanel::openTransitionsBrowser() {
    transitionsBrowser->openTransitionBrowser();
}

void ControlPanel::loadStates(){
    try{
        DBManager dbMan = DBManager::getDB();
        std::pair<int,CellState**> statetab=dbMan.loadStatesfromDB();
        statebrowser = new StatesBrowser(this,statetab);
    }


    catch(DBException e){
        QMessageBox window;
        window.setText(QString::fromStdString(e.getInfo()));
        window.open();
    }

    connect(statebrowser,SIGNAL(stateChanged(int,CellState*)),simulatorWidget,SLOT(setState(int,CellState*)));

}



void ControlPanel::loadAutomatas() {
    //Init data
    try{
        DBManager dbMan = DBManager::getDB();
        dbMan.loadAutomatasFromDB();
        setAutomata(0);
        simulatorWidget->setAutomata(0);
    }
    catch(DBException e){
        QMessageBox window;
        window.setText(QString::fromStdString(e.getInfo()));
        window.exec();
    }
    automatasBrowser = new AutomatasBrowser(this);
    connect(automatasBrowser, &AutomatasBrowser::automataChanged, this, &ControlPanel::setAutomata);
    connect(automatasBrowser, &AutomatasBrowser::automataChanged, simulatorWidget, &SimulatorWidget::setAutomata);
}

void ControlPanel::initEventHandler() {
    connect(nbRowsSpb, SIGNAL(valueChanged(int)), simulatorWidget, SLOT(setNbRows(int)));
    connect(nbColsSpb, SIGNAL(valueChanged(int)), simulatorWidget, SLOT(setNbCols(int)));
    connect(cellSizeSpb, SIGNAL(valueChanged(int)), simulatorWidget, SLOT(setCellSize(int)));
    connect(bufferSizeSpb, SIGNAL(valueChanged(int)), simulatorWidget, SLOT(setBufferSize(int)));
    connect(sliderSpeed, SIGNAL(valueChanged(int)), simulatorWidget, SLOT(changeFrequency(int)));
    connect(statesListWidget,SIGNAL(currentRowChanged(int)),statebrowser,SLOT(receiveStateID(int)));
    connect(btnEditState, &QPushButton::clicked, this, &ControlPanel::openStateBrowser);
    connect(simulatorWidget,SIGNAL(stateHasChanged()),this,SLOT(updateStates()));
    connect(btnBrowseAutomatas, &QPushButton::clicked, this, &ControlPanel::openAutomatasBrowser);
    connect(btnBrowseNeighborhoods, &QPushButton::clicked, this, &ControlPanel::openNeighborsBrowser);
    connect(btnBrowseTransitions, &QPushButton::clicked, this, &ControlPanel::openTransitionsBrowser);
    connect(btnSaveConfig, &QPushButton::clicked, this, &ControlPanel::btnSaveConfigClicked);
    connect(btnLoadConfig, &QPushButton::clicked, this, &ControlPanel::openConfigsBrowser);

    connect(automatasBrowser, &AutomatasBrowser::automataChanged, this, &ControlPanel::setAutomata);
    connect(automatasBrowser, &AutomatasBrowser::automataChanged, simulatorWidget, &SimulatorWidget::setAutomata);
    connect(transitionsBrowser, &TransitionsBrowser::transitionChanged, this, &ControlPanel::setTransition);
    connect(transitionsBrowser, &TransitionsBrowser::transitionChanged, simulatorWidget, &SimulatorWidget::setTransition);
    connect(neighborsBrowser, &NeighborsBrowser::neighborChanged, this, &ControlPanel::setNeighbor);
    connect(neighborsBrowser, &NeighborsBrowser::neighborChanged, simulatorWidget, &SimulatorWidget::setNeighbor);
    connect(configsBrowser, &ConfigsBrowser::configChanged, this, &ControlPanel::setConfig);
    connect(configsBrowser, &ConfigsBrowser::configChanged, simulatorWidget, &SimulatorWidget::setConfig);
}

ControlPanel::ControlPanel(QWidget* parent, SimulatorWidget* simulatorWidget) : QWidget(parent), simulatorWidget(simulatorWidget) {
    mainLayout = new QVBoxLayout(this);

    // 1 : grid settings
    gridSettingsBox = new QGroupBox(tr("Grid settings"));
    initGridSettings();
    mainLayout->addWidget(gridSettingsBox);

    // 2 : automata settings
    automataSettingsBox = new QGroupBox(tr("Automata settings"));
    initAutomataSettings();
    mainLayout->addWidget(automataSettingsBox);


    // 3 : run settings
    runSettingsBox = new QGroupBox(tr("Run settings"));
    initRunSettings();
    mainLayout->addWidget(runSettingsBox);

    mainLayout->addStretch();

    loadStates();

    setLayout(mainLayout);

    setMaximumWidth(500);

    configsBrowser = new ConfigsBrowser(this);
    automatasBrowser = new AutomatasBrowser(this);
    transitionsBrowser = new TransitionsBrowser(this);
    neighborsBrowser = new NeighborsBrowser(this);
    initEventHandler();
}

void ControlPanel::initGridSettings() {
    //Creation of the boxes widget
    nbRowsSpb = new QSpinBox(gridSettingsBox);
    nbColsSpb = new QSpinBox(gridSettingsBox);
    cellSizeSpb = new QSpinBox(gridSettingsBox);
    txtConfigName = new QLineEdit(gridSettingsBox);
    btnLoadConfig = new QPushButton("Load", gridSettingsBox);
    btnSaveConfig = new QPushButton("Save", gridSettingsBox);

    nbRowsSpb->setKeyboardTracking(false);
    nbRowsSpb->setValue(simulatorWidget->getNbRows());
    nbRowsSpb->setMaximum(100);
    nbRowsSpb->setMinimum(2);

    nbColsSpb->setKeyboardTracking(false);
    nbColsSpb->setValue(simulatorWidget->getNbCols());
    nbColsSpb->setMaximum(100);
    nbColsSpb->setMinimum(2);

    cellSizeSpb->setKeyboardTracking(false);
    cellSizeSpb->setValue(simulatorWidget->getCellSize());
    cellSizeSpb->setMaximum(50);
    cellSizeSpb->setMinimum(5);



    //Creation of the boxes layout
    gridSettingsLayout = new QFormLayout(gridSettingsBox);
    configButtonsLayout = new QHBoxLayout(gridSettingsBox);

    configButtonsLayout->addWidget(btnLoadConfig);
    configButtonsLayout->addWidget(btnSaveConfig);

    gridSettingsLayout->addRow("Config name", txtConfigName);
    gridSettingsLayout->addRow("Rows number", nbRowsSpb);
    gridSettingsLayout->addRow("Cols number", nbColsSpb);
    gridSettingsLayout->addRow("Cell size", cellSizeSpb);
    gridSettingsLayout->addRow("", configButtonsLayout);
}

void ControlPanel::initAutomataSettings() {
    automataSettingsLayout = new QVBoxLayout(automataSettingsBox);

    //Choose automata
    automatasLabel = new QLabel("Automata", automataSettingsBox);
    btnBrowseAutomatas = new QPushButton(tr("Browse"), automataSettingsBox);
    textAutomataName = new QLineEdit(automataSettingsBox);
    automataFieldLayout = new QHBoxLayout(automataSettingsBox);
    automataFieldLayout->addWidget(automatasLabel);
    automataFieldLayout->addWidget(textAutomataName);
    automataFieldLayout->addWidget(btnBrowseAutomatas);
    automataSettingsLayout->addLayout(automataFieldLayout);

    // List states
    statesLabel = new QLabel("States", this);
    statesListWidget = new QListWidget(this);
    statesListWidget->setMaximumHeight(200);
    btnEditState = new QPushButton("Edit", this);
    statesFieldLayout = new QHBoxLayout(this);
    statesListWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    statesListWidget->setMaximumHeight(100);
    statesFieldLayout->addWidget(statesLabel, 0, Qt::AlignTop);
    statesFieldLayout->addWidget(statesListWidget, 0, Qt::AlignTop);
    statesFieldLayout->addWidget(btnEditState, 0, Qt::AlignTop);
    automataSettingsLayout->addLayout(statesFieldLayout);


    //Choose neighborhood
    neighborhoodLabel = new QLabel("Neighborhood", automataSettingsBox);
    textNeighborhoodName = new QLineEdit(automataSettingsBox);
    btnBrowseNeighborhoods = new QPushButton("Browse", automataSettingsBox);
    neighborhoodFieldLayout = new QHBoxLayout(automataSettingsBox);


    neighborhoodFieldLayout->addWidget(neighborhoodLabel);
    neighborhoodFieldLayout->addWidget(textNeighborhoodName);
    neighborhoodFieldLayout->addWidget(btnBrowseNeighborhoods);
    automataSettingsLayout->addLayout(neighborhoodFieldLayout);

    //Choose transition rule
    transitionsLabel = new QLabel("Transition rule", automataSettingsBox);
    textTransitionName = new QLineEdit(automataSettingsBox);
    btnBrowseTransitions = new QPushButton("Browse", automataSettingsBox);
    transitionsFieldLayout = new QHBoxLayout(automataSettingsBox);

    transitionsFieldLayout->addWidget(transitionsLabel);
    transitionsFieldLayout->addWidget(textTransitionName);
    transitionsFieldLayout->addWidget(btnBrowseTransitions);
    automataSettingsLayout->addLayout(transitionsFieldLayout);


}

void ControlPanel::initRunSettings() {
    runSettingsLayout = new QFormLayout(runSettingsBox);

    sliderSpeed = new BSlider(Qt::Horizontal, runSettingsBox);
    sliderSpeed->setValue(simulatorWidget->getFrequency());
    sliderSpeed->setMinimum(simulatorWidget->getFrequency());
    sliderSpeed->setMaximum(50);
    runSettingsLayout->addRow("execution speed", sliderSpeed);
    bufferSizeSpb = new QSpinBox(runSettingsBox);
    bufferSizeSpb->setKeyboardTracking(false);
    bufferSizeSpb->setValue(simulatorWidget->getSimulator()->getBufferSize());
    bufferSizeSpb->setMaximum(500);
    bufferSizeSpb->setMinimum(2);
    runSettingsLayout->addRow("Buffer size", bufferSizeSpb);
}

ControlPanel::~ControlPanel() {
    delete gridSettingsLayout;
    delete automatasBrowser;
    delete neighborsBrowser;
    delete statebrowser;
}

void ControlPanel::setAutomata(int id) {
    textAutomataName->setText(QString::fromStdString(AutomataManager::getAutomataManager()->getAutomata(id)->getName()));
    textNeighborhoodName->setText(QString::fromStdString(AutomataManager::getAutomataManager()->getAutomata(id)->getNeighborhoodStrategy()->getName()));
    textTransitionName->setText(QString::fromStdString(AutomataManager::getAutomataManager()->getAutomata(id)->getTransitionStrategy()->getName()));


    statesListWidget->clear();
    for (int i = 0; i < AutomataManager::getAutomataManager()->getAutomata(id)->getNbStates(); i ++) {
        CellState* s = AutomataManager::getAutomataManager()->getAutomata(id)->getAvailableState(i);
        std::string item = std::to_string(s->getId());
        item += ". " + s->getLabel();
        statesListWidget->addItem(item.c_str());
    }
    statesListWidget->adjustSize();
}

void ControlPanel::setNeighbor(NeighborhoodStrategy* neighbor) {
    textNeighborhoodName->setText(QString::fromStdString(neighbor->getName()));
}

void ControlPanel::setTransition(TransitionStrategy* transition) {
    textTransitionName->setText(QString::fromStdString(transition->getName()));
}

void ControlPanel::setConfig(Grid* config) {
    nbColsSpb->setValue(config->getWidth());
    nbRowsSpb->setValue(config->getHeight());
    txtConfigName->setText(config->getName().c_str());
}

void ControlPanel::openAutomatasBrowser() {
    automatasBrowser->openAutomatasBrowser();
}

void ControlPanel::openStateBrowser(){


    statebrowser->open();
}

void ControlPanel::btnSaveConfigClicked() {
    try {
        DBManager dbMan = DBManager::getDB();
        dbMan.insertConfigIntoDB(txtConfigName->text(), simulatorWidget->getSimulator()->getIterator().current(), simulatorWidget->getSimulator()->getAutomata());
        QMessageBox window;
        window.setText("Configuration saved successfully");
        window.exec();
    } catch (DBException e) {
        QMessageBox window;
        window.setText(e.getInfo().c_str());
        window.exec();
    }
}

void ControlPanel::openConfigsBrowser() {
    configsBrowser->openConfigsBrowser(simulatorWidget->getSimulator()->getAutomata());

}
