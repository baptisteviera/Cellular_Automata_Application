#include "menubar.h"

MenuBar::MenuBar(QMainWindow* parent) : QMenuBar(parent) {
    fileMenu = new QMenu("File", this);
    editMenu = new QMenu("Edit", this);
    runMenu = new QMenu("Run", this);

    addMenu(fileMenu);
    addMenu(editMenu);
    addMenu(runMenu);
}

MenuBar::~MenuBar() {
}
