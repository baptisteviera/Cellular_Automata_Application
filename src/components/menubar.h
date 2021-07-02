#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include <QMainWindow>

class MenuBar : public QMenuBar {
    Q_OBJECT
    QMenu* fileMenu, *editMenu, *runMenu;
  public:
    MenuBar(QMainWindow* parent = nullptr);
    ~MenuBar();
};

#endif // MENUBAR_H
