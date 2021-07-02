#include "neighbors_browser.h"

NeighborsBrowser::NeighborsBrowser(QWidget* parent, int width, int height) : QDialog(parent) {
    mainLayout = new QVBoxLayout(this);
    neighborhoodLayout = new QFormLayout(this);
    buttonsLayout = new QHBoxLayout(this);
    neighborhoodCbb = new QComboBox(this);

    neighborCreator = new NeighborCreator(this, width, height);

    btnConfirm = new QPushButton("Confirm", this);
    btnCreate = new QPushButton("Create", this);

    neighborhoodLayout->addRow("Neighborhood", neighborhoodCbb);

    connect(btnCreate, &QPushButton::clicked, this, &NeighborsBrowser::openNeighborCreator);
    connect(btnConfirm, &QPushButton::clicked, this, &NeighborsBrowser::chooseNeighbor);
    connect(neighborhoodCbb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &NeighborsBrowser::neighborCbbChanged);
    connect(neighborCreator, &QDialog::finished, this, &NeighborsBrowser::openNeighborsBrowser);

    mainLayout->addLayout(neighborhoodLayout);

    buttonsLayout->addWidget(btnConfirm);
    buttonsLayout->addWidget(btnCreate);

    mainLayout->addLayout(buttonsLayout);

    adjustSize();
}

NeighborsBrowser::~NeighborsBrowser() {
    delete spbRadius;
}

void NeighborsBrowser::setNeighborhoods(int nbNeighbors, NeighborhoodStrategy** neighbors) {
    if (this->neighbors) {
        delete[] this->neighbors;
    }
    this->nbNeighbors = nbNeighbors;
    this->neighbors = neighbors;
    updateCombobox();
}

void NeighborsBrowser::openNeighborsBrowser() {
    std::pair<int, NeighborhoodStrategy**> loadedNeighborsInfos;
    try {
        loadedNeighborsInfos = DBManager::getDB().loadNeighborhoodsFromDB();
        setNeighborhoods(loadedNeighborsInfos.first, loadedNeighborsInfos.second);
    } catch(DBException e) {
        QMessageBox window;
        window.setText(QString::fromStdString(e.getInfo()));
        window.show();
    }

    this->open();
}

void NeighborsBrowser::updateCombobox() {
    if (neighborhoodCbb == nullptr || neighbors == nullptr) {
        return;
    }
    neighborhoodCbb->clear();
    for (int i = 0; i < nbNeighbors; i ++) {
        if (neighbors[i]) {
            neighborhoodCbb->addItem(neighbors[i]->getName().c_str());
        }
    }
}

void NeighborsBrowser::neighborCbbChanged(int id) {
    if (id < 0) {
        return;
    }
    selectedNeighbor = neighbors[id];
    if (instanceof<VonNeumannNeighborhoodGeneralized>(selectedNeighbor) || instanceof<MooreNeighborhoodGeneralized>(selectedNeighbor)) {
        spbRadius = new QSpinBox();
        if (instanceof<VonNeumannNeighborhoodGeneralized>(selectedNeighbor)) {
            spbRadius->setValue(static_cast<const VonNeumannNeighborhoodGeneralized*>(selectedNeighbor)->getRadius());
        } else if (instanceof<MooreNeighborhoodGeneralized>(selectedNeighbor)) {
            spbRadius->setValue(static_cast<const MooreNeighborhoodGeneralized*>(selectedNeighbor)->getRadius());
        }
        if (neighborhoodLayout->rowCount() < 2) {
            neighborhoodLayout->addRow("Radius", spbRadius);
        }
    } else if (neighborhoodLayout->rowCount() >= 2) {
        neighborhoodLayout->removeRow(1);
    }
}

void NeighborsBrowser::chooseNeighbor() {
    if (instanceof<VonNeumannNeighborhoodGeneralized>(selectedNeighbor) || instanceof<MooreNeighborhoodGeneralized>(selectedNeighbor)) {
        if (instanceof<VonNeumannNeighborhoodGeneralized>(selectedNeighbor)) {
            selectedNeighbor = new VonNeumannNeighborhoodGeneralized("Von Neumann Neighborhood Generalized, radius = " + std::to_string(spbRadius->value()), spbRadius->value());
        } else if (instanceof<MooreNeighborhoodGeneralized>(selectedNeighbor)) {
            selectedNeighbor = new MooreNeighborhoodGeneralized("Moore Neighborhood Generalized, radius = " + std::to_string(spbRadius->value()), spbRadius->value());
        }
    }
    emit neighborChanged(selectedNeighbor);
    selectedNeighbor = nullptr;
    close();
}

void NeighborsBrowser::openNeighborCreator() {
    this->neighborCreator->open();
    close();
}


// ================================== Creation ===================================
NeighborCreator::NeighborCreator(QWidget* parent, int width, int height) : QDialog(parent) {
    this->width = width;
    this->height = height;
    if (this->width % 2 == 0) {
        this->width ++;
    }
    if (this->height % 2 == 0) {
        this->height ++;
    }

    this->centerR = this->height / 2;
    this->centerC = this->width / 2;
    mainLayout = new QVBoxLayout(this);
    infoLayout = new QFormLayout(this);
    gridLayout = new QGridLayout(this);
    buttonsLayout = new QHBoxLayout(this);

    txtName = new QLineEdit(this);
    neighborsTypeCbb = new QComboBox(this);
    spbRadius = new QSpinBox(this);

    cellsCheckbox = new QCheckBox** [height];
    for (int r = 0; r < height; r ++) {
        cellsCheckbox[r] = new QCheckBox*[width];
        for (int c = 0; c < width; c ++) {
            cellsCheckbox[r][c] = new QCheckBox();
            if (r == centerR && c == centerC) {
                gridLayout->addWidget(new QLabel("X"), r, c);
            } else {
                gridLayout->addWidget(cellsCheckbox[r][c], r, c);
            }
        }
    }

    btnCreate = new QPushButton("Create");
    connect(btnCreate, &QPushButton::clicked, this, &NeighborCreator::createNeighbor);

    buttonsLayout->addWidget(btnCreate);

    connect(neighborsTypeCbb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &NeighborCreator::changeNeighborType);
    neighborsTypeCbb->addItems({"Von Neumann Neighborhood Generalized", "Moore Neighborhood Generalized", "Arbitrary Neighborhood"});

    connect(spbRadius, QOverload<int>::of(&QSpinBox::valueChanged), this, &NeighborCreator::changeRadius);
    spbRadius->setValue(1);

    infoLayout->addRow("Name", txtName);
    infoLayout->addRow("Radius", spbRadius);

    mainLayout->addWidget(neighborsTypeCbb);
    mainLayout->addLayout(infoLayout);
    mainLayout->addWidget(new QLabel("Choose neighbors"));
    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
}

void NeighborCreator::changeNeighborType(int id) {
    if (id < 0) {
        return;
    }
    if (neighborsTypeCbb->currentText() == "Arbitrary Neighborhood") {
        for (int r = 0; r < height; r ++) {
            for (int c = 0; c < width; c ++) {
                cellsCheckbox[r][c]->setDisabled(false);
            }
        }
        txtName->clear();
        txtName->setDisabled(false);
        spbRadius->setDisabled(true);
    } else {
        for (int r = 0; r < height; r ++) {
            for (int c = 0; c < width; c ++) {
                cellsCheckbox[r][c]->setDisabled(true);
            }
        }
        txtName->setDisabled(true);
        spbRadius->setDisabled(false);
        txtName->setText(neighborsTypeCbb->currentText() + ", radius = " + std::to_string(spbRadius->value()).c_str());
    }
}

void NeighborCreator::changeRadius(int val) {
    txtName->setText(neighborsTypeCbb->currentText() + ", radius = " + std::to_string(val).c_str());
}

void NeighborCreator::createNeighbor() {
    if (neighborsTypeCbb->currentText() == "Arbitrary Neighborhood") {
        DBManager db = DBManager::getDB();
        int nbNeighbors = 0;
        int* dx, *dy;
        for (int r = 0; r < height; r ++) {
            for (int c = 0; c < width; c ++) {
                if (r != centerR || c != centerC) {
                    if (cellsCheckbox[r][c]->isChecked())
                        nbNeighbors ++;
                }
            }
        }
        dx = new int[nbNeighbors];
        dy = new int[nbNeighbors];
        int i = 0;
        for (int r = 0; r < height; r ++) {
            for (int c = 0; c < width; c ++) {
                if (r != centerR || c != centerC) {
                    if (cellsCheckbox[r][c] && cellsCheckbox[r][c]->isChecked()) {
                        dx[i] = r - centerR;
                        dy[i] = c - centerC;
                        i ++;
                    }
                }
            }
        }
        db.insertNeighborhoodIntoDB(txtName->text(), nbNeighbors, dx, dy);
        delete[] dx;
        delete[] dy;
    } else {
        DBManager db = DBManager::getDB();
        db.insertNeighborhoodIntoDB(txtName->text(), spbRadius->value());
    }
    close();
}

NeighborCreator::~NeighborCreator() {

}
