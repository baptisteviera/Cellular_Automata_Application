#include "configs_browser.h"
/**
 * @brief ConfigsBrowser
 * @param parent
 */
ConfigsBrowser::ConfigsBrowser(QWidget* parent) : QDialog(parent) {
    loadedConfigsInfos = {0, nullptr};

    mainLayout = new QVBoxLayout(this);

    initConfigsTable();
    initButtons();

    mainLayout->addWidget(configsTable);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

    adjustSize();
}

void ConfigsBrowser::initConfigsTable() {
    configsTable = new QTableWidget(loadedConfigsInfos.first, TBL_NB_COLS, this);

    configsTable->setHorizontalHeaderLabels(QStringList({"name", "width", "height"}));
    configsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    configsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void ConfigsBrowser::initButtons() {
    buttonsLayout = new QHBoxLayout(this);
    btnLoad = new QPushButton("Load", this);
    btnDelete = new QPushButton("Delete", this);

    buttonsLayout->addWidget(btnLoad);
    buttonsLayout->addWidget(btnDelete);


    connect(btnLoad, &QPushButton::clicked, this, &ConfigsBrowser::chooseConfig);
    connect(btnDelete,&QPushButton::clicked,this,&ConfigsBrowser::deleteConfig);
}

void ConfigsBrowser::openConfigsBrowser(Automata* automata) {
    if (!automata) {
        return;
    }
    // Clean current table
    if (loadedConfigsInfos.first > 0) {
        for (int r = 0; r < loadedConfigsInfos.first; r ++) {
            for (int c = 0; c < TBL_NB_COLS; c ++) {
                delete configsItems[r][c];
            }
            delete[] configsItems[r];
            configsItems[r] = nullptr;
        }
        delete[] configsItems;
        configsItems = nullptr;
    }

    try{
        DBManager dbMan = DBManager::getDB();
        loadedConfigsInfos = dbMan.loadConfigsFromDB(automata);
    }
    catch(DBException e){
        QMessageBox window;
        window.setText(QString::fromStdString(e.getInfo()));
        window.open();
    }
    configsTable->setRowCount(loadedConfigsInfos.first);

    configsItems = new QTableWidgetItem** [loadedConfigsInfos.first];
    for (int i = 0; i < loadedConfigsInfos.first; i ++) {
        configsItems[i] = new QTableWidgetItem*[TBL_NB_COLS];
        configsItems[i][0] = new QTableWidgetItem(loadedConfigsInfos.second[i]->getName().c_str());
        configsItems[i][1] = new QTableWidgetItem(std::to_string(loadedConfigsInfos.second[i]->getWidth()).c_str());
        configsItems[i][2] = new QTableWidgetItem(std::to_string(loadedConfigsInfos.second[i]->getHeight()).c_str());

        for (int j = 0; j < TBL_NB_COLS; j ++) {
            configsTable->setItem(i, j, configsItems[i][j]);
        }
    }

    configsTable->resizeColumnToContents(0);
    configsTable->resizeColumnToContents(1);
    configsTable->resizeColumnToContents(2);

    int totalWidth = 20;
    for (int j = 0; j < TBL_NB_COLS; j ++) {
        totalWidth += configsTable->columnWidth(j);
    }

    configsTable->setFixedWidth(totalWidth);
    configsTable->selectRow(0);

    adjustSize();

    open();
}

void ConfigsBrowser::deleteConfig(){
    QMessageBox window;
    window.setText("Réponse à la boutade : c'est l'exponentielle, parce que le logarithme népérien (ne paie rien) !");
    window.exec();
}

/*
 *          SLOTS
 */
void ConfigsBrowser::chooseConfig() {
    if (configsTable->selectionModel()->selectedIndexes().size() > 0) {
        emit configChanged(loadedConfigsInfos.second[configsTable->selectionModel()->selectedIndexes().at(0).row()]);
        close();
    }
}

ConfigsBrowser::~ConfigsBrowser() {
    if (loadedConfigsInfos.first > 0) {
        for (int r = 0; r < loadedConfigsInfos.first; r ++) {
            for (int c = 0; c < TBL_NB_COLS; c ++) {
                delete configsItems[r][c];
            }
            delete[] configsItems[r];
            configsItems[r] = nullptr;
        }
        delete[] configsItems;
        configsItems = nullptr;
    }
}
