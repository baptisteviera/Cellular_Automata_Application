#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QWidget>
#include <components/simulator_widget.h>
#include <components/control_panel.h>
/**
 * @brief Classe MainWindow permet de créer la fenêtre principale
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
    /**
     * @brief centralWidget widget où on l'on place la disposition principal
     */
    QWidget* centralWidget;
    /**
     * @brief mainLayout disposition principale
     */
    QHBoxLayout* mainLayout;
    /**
     * @brief simulatorWidget widget du simulateur
     */
    SimulatorWidget* simulatorWidget;
    /**
     * @brief controlPanel panneau de configuration
     */
    ControlPanel* controlPanel;
  public:
    /**
     * @brief MainWindow constructeur de création de la fenêtre principale
     * @param parent widget à partir duquel est crée MainWindow
     */
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  signals:

};

#endif // MAIN_WINDOW_H
