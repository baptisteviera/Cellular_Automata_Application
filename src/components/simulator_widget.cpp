#include "simulator_widget.h"
#include <iostream>
void SimulatorWidget::initLayout() {
    simulatorLayout = new QVBoxLayout(this);
    gridLayout = new QGridLayout(this);
    controllerLayout = new QHBoxLayout(this);
    configBtnLayout = new QHBoxLayout(this);

    gridLayout->setAlignment(Qt::AlignCenter);
    gridLayout->setSpacing(2);
}

void SimulatorWidget::setButtonIcon(QPushButton* btn, const QString& path) {
    btn->setIcon(QIcon(path));
    btn->setIconSize(QSize(48, 48));
    btn->setFixedSize(48, 48);
    btn->setStyleSheet("border-radius : 50;");
}

void SimulatorWidget::btnPlayPauseClicked() {
    if (!playing) {
        playing = true;
        timer->start(1000 / frequency);
        setButtonIcon(btnPlay, PAUSE_BTN_ICON_PATH);
    } else {
        playing = false;
        timer->stop();
        setButtonIcon(btnPlay, PLAY_BTN_ICON_PATH);
    }
}

void SimulatorWidget::btnNextClicked() {
    try {
        simulator->next();
        updateGridDisplay();
    }  catch (TransitionException e) {
        QMessageBox msgBox;
        msgBox.setText(QString(e.getInfo().c_str()));
        msgBox.exec();
    }
}

void SimulatorWidget::btnResetClicked() {
    try {
        simulator->reset();
        updateGridDisplay();
    }  catch (TransitionException e) {
        QMessageBox msgBox;
        msgBox.setText(QString(e.getInfo().c_str()));
        msgBox.exec();
    }
}

void SimulatorWidget::btnRandomClicked() {
    if(playing) {
        playing = false;
        timer->stop();
        setButtonIcon(btnPlay, PLAY_BTN_ICON_PATH);
    }
    regenerateRandomGrid();
    updateGridDisplay();
}

void SimulatorWidget::btnPrevClicked(){
    if(simulator->getIterator().isDone()){
       QMessageBox window;
       window.setText("End of buffer reached !");
       window.exec();
    }
    else if(simulator->getCurrentGridID() != 0){
        simulator->getIterator().previousGrid();
        updateGridDisplay();
    }
}

void SimulatorWidget::initButtons() {
    btnPlay = new QPushButton(this);
    btnPrev = new QPushButton(this);
    btnNext = new QPushButton(this);
    btnReset = new QPushButton(this);
    btnRandom = new QPushButton(this);

    setButtonIcon(btnPrev, PREV_BTN_ICON_PATH);
    setButtonIcon(btnPlay, PLAY_BTN_ICON_PATH);
    setButtonIcon(btnReset, RESET_BTN_ICON_PATH);
    setButtonIcon(btnNext, NEXT_BTN_ICON_PATH);
    setButtonIcon(btnRandom, RANDOM_BTN_ICON_PATH);

    controllerLayout->setSizeConstraint(QLayout::SetMinimumSize);

    controllerLayout->addWidget(btnPrev);
    controllerLayout->addWidget(btnPlay);
    controllerLayout->addWidget(btnReset);
    controllerLayout->addWidget(btnRandom);
    controllerLayout->addWidget(btnNext);

    connect(btnPlay, &QPushButton::clicked, this, &SimulatorWidget::btnPlayPauseClicked);
    connect(btnNext, &QPushButton::clicked, this, &SimulatorWidget::btnNextClicked);
    connect(btnReset, &QPushButton::clicked, this, &SimulatorWidget::btnResetClicked);
    connect(btnRandom, &QPushButton::clicked, this, &SimulatorWidget::btnRandomClicked);
    connect(btnPrev, &QPushButton::clicked, this, &SimulatorWidget::btnPrevClicked);
}

void SimulatorWidget::regenerateRandomGrid() {
    if (this->simulator->getAutomata() == nullptr) {
        return;
    }
    this->simulator->setStartGrid(Simulator::getGridFactory().generateGrid(RANDOM, this->nbCols, this->nbRows, this->simulator->getAutomata()));
}

void SimulatorWidget::regenerateEmptyGrid() {
    if (this->simulator->getAutomata() == nullptr) {
        return;
    }
    this->simulator->setStartGrid(Simulator::getGridFactory().generateGrid(EMPTY, this->nbCols, this->nbRows, this->simulator->getAutomata()));
}

void SimulatorWidget::updateGridDisplay() {
    Grid* currentGrid = simulator->getIterator().current();
    if (currentGrid == nullptr) {
        return;
    }
    lblCurrentGeneration->setText(tr("Generation #").append(QString::number(simulator->getCurrentGridID())));
    for (int r = 0; r < nbRows; r ++) {
        for (int c = 0; c < nbCols; c ++) {
            cellWidgets[r * nbCols + c]->setCell(currentGrid->getCell(r, c));
            cellWidgets[r * nbCols + c]->setSize(this->cellSize);
            cellWidgets[r * nbCols + c]->updateDisplay();
        }
    }
}

void SimulatorWidget::resetGridDisplay() {
    Grid* currentGrid = simulator->getIterator().current();
    if (currentGrid == nullptr) {
        return;
    }
    lblCurrentGeneration->setText(tr("Generation #").append(QString::number(simulator->getCurrentGridID())));
    cellWidgets = new CellWidget*[nbRows * nbCols];
    for (int r = 0; r < nbRows; r ++) {
        for (int c = 0; c < nbCols; c ++) {
            cellWidgets[r * nbCols + c] = new CellWidget(this, cellSize, currentGrid->getCell(r, c));
            gridLayout->addWidget(cellWidgets[r * nbCols + c], r, c);
            connect(cellWidgets[r * nbCols + c], &CellWidget::leftClicked, this, &SimulatorWidget::changeCellState);
            connect(cellWidgets[r * nbCols + c], &CellWidget::rightClicked, this, &SimulatorWidget::changeAnt);
        }
    }
    adjustSize();
}

int SimulatorWidget::getNbRows() const {
    return this->nbRows;
}

Simulator* SimulatorWidget::getSimulator() const {
    return this->simulator;
}

void SimulatorWidget::setNbRows(int nbRows) {
    cleanGrid();
    this->nbRows = nbRows;
    regenerateEmptyGrid();
    resetGridDisplay();
}
int SimulatorWidget::getNbCols() const {
    return this->nbCols;
}

void SimulatorWidget::setNbCols(int nbCols) {
    cleanGrid();
    this->nbCols = nbCols;
    regenerateEmptyGrid();
    resetGridDisplay();
}
void SimulatorWidget::setCellSize(int size) {
    this->cellSize = size;
    updateGridDisplay();
}
int SimulatorWidget::getCellSize() const {
    return this->cellSize;
}

void SimulatorWidget::changeCellState(int x, int y) {
    Grid* currentGrid = simulator->getIterator().current();
    int newStateID;
    for (int i = 0; i < simulator->getAutomata()->getNbStates(); i ++) {
        if (currentGrid->getCell(x, y)->getState()->getId() == simulator->getAutomata()->getAvailableState(i)->getId()) {
            newStateID = (i + 1) % (simulator->getAutomata()->getNbStates());
        }
    }
    CellState* newState = simulator->getAutomata()->getAvailableStates()[newStateID];
    currentGrid->getCell(x, y)->setState(newState);

    if (this->simulator->getCurrentGridID() == 0) {
        // Change the start grid if use config the first one
        this->simulator->setStartGrid(new Grid(*currentGrid));
    }
    updateGridDisplay();
}

void SimulatorWidget::changeAnt(int x, int y) {
    Grid* currentGrid = simulator->getIterator().current();
    Direction currentDir = currentGrid->getCell(x, y)->getDirection();
    Direction newDir = static_cast<Direction>((currentDir + 1) % (LEFT + 1));

    for (int r = 0; r < currentGrid->getHeight(); r ++) {
        for (int c = 0; c < currentGrid->getWidth(); c ++) {
            currentGrid->getCell(r, c)->setDirection(NONE);
            cellWidgets[r * nbCols + c]->repaint();
        }
    }
    currentGrid->getCell(x, y)->setDirection(newDir);
    cellWidgets[x * nbCols + y]->repaint();

    if (this->simulator->getCurrentGridID() == 0) {
        // Change the start grid if use config the first one
        this->simulator->setStartGrid(new Grid(*currentGrid));
    }
    updateGridDisplay();
}


void SimulatorWidget::setAutomata(int index) {
    this->simulator->setAutomata(AutomataManager::getAutomataManager()->getAutomata(index));
    cleanGrid();
    regenerateEmptyGrid();
    resetGridDisplay();
}

void SimulatorWidget::setNeighbor(NeighborhoodStrategy* neighbor) {
    this->simulator->getAutomata()->setNeighborhoodStrategy(neighbor);
}

void SimulatorWidget::setTransition(TransitionStrategy* transition) {
    this->simulator->getAutomata()->setTransitionStrategy(transition);
}

void SimulatorWidget::setState(int nb, CellState* c){
    if(nb>simulator->getAutomata()->getNbStates()){
        CellState** newTab = new CellState*[simulator->getAutomata()->getNbStates()+1];
        for(int i=0; i<simulator->getAutomata()->getNbStates();i++){
            newTab[i] = simulator->getAutomata()->getAvailableState(i);
        }
        simulator->getAutomata()->setAvailableStates(newTab,simulator->getAutomata()->getNbStates()+1);
    }
    simulator->getAutomata()->setAvailableState(c,nb);
    emit stateHasChanged();
}

void SimulatorWidget::setConfig(Grid* config) {
    simulator->reset();
    simulator->setStartGrid(config);
    updateGridDisplay();
}

void SimulatorWidget::setBufferSize(int size) {
    this->simulator->setBufferSize(size);
}

void SimulatorWidget::setFrequency(int f) {
    this->frequency = f;
}

int SimulatorWidget::getFrequency() const {
    return this->frequency;
}


void SimulatorWidget::changeFrequency(int f) {
    setFrequency(f);
    if(playing) {
        timer->stop();
        timer->start(1000 / f);
    }
}

SimulatorWidget::SimulatorWidget(QWidget* parent, int nbRows, int nbCols, int cellSize) : QWidget(parent), frequency(1) {
    simulator = new Simulator(nullptr, 100);

    this->nbCols = nbCols;
    this->nbRows = nbRows;
    this->cellSize = cellSize;

    initLayout();
    initButtons();
    resetGridDisplay();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SimulatorWidget::btnNextClicked);

    lblCurrentGeneration = new QLabel("Generation #0");

    simulatorLayout->addWidget(lblCurrentGeneration);
    simulatorLayout->addLayout(gridLayout);
    simulatorLayout->addStretch();
    simulatorLayout->addLayout(controllerLayout);

    setLayout(simulatorLayout);

    adjustSize();
}

void SimulatorWidget::cleanGrid() {
    if (cellWidgets == nullptr) {
        return;
    }
    for (int r = 0; r < nbRows; r ++) {
        for (int c = 0; c < nbCols; c ++) {
            gridLayout->removeWidget(cellWidgets[r * nbCols + c]);
            delete cellWidgets[r * nbCols + c];
        }
    }
    delete [] cellWidgets;
    cellWidgets = nullptr;
}


SimulatorWidget::~SimulatorWidget() {
    cleanGrid();
}
