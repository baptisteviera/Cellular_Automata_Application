#ifndef STATES_BROWSER_H
#define STATES_BROWSER_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include "../../utils/automata_manager.h"
#include "Create_State.h"
#include "utils/database.h"

class StatesBrowser : public QDialog {
    Q_OBJECT
    /**
     * @brief statesTable tableau de pointeurs qui contient les types d'états disponibles
     */
    CellState** statesTable;
    /**
     * @brief mainLayout espace (vertical) qui contient l'ensemble des layout
     */
    QVBoxLayout* mainLayout;
    /**
     * @brief buttonsLayout
     */
    QHBoxLayout* buttonsLayout;

    Create_State*  Createstate;

    /**
     * @brief stateTable tableau (visuel) qui contient les états que l'utilisateur peut sélectionner
     */

    QTableWidget* stateTable;
    /**
     * @brief stateItems les états contenus dans le tableau stateTable
     */
    QTableWidgetItem*** stateItems;
    int size;
    /**
     * @brief stateID le numéro de l'ID que doit être changé dans l'automate actuel
     */
    int stateID;

    /**
     * @brief btnChoose btnCreate btnDelete btnSave les boutons de l'interface
     */
    QPushButton *btnChoose, *btnCreate, *btnDelete, *btnSave;

    const int TBL_NB_COLS = 4;
    /**
     * @brief initStateTable permet d'initialiser la table d'état
     */
    void initStateTable(std::pair<int,CellState**>);
    /**
     * @brief initButtons permet d'initialiser les boutons
     */
    void initButtons();
    void completeTable(std::pair<int,CellState**> statetab);

  public:
    /**
     * @brief StatesBrowser constructeur qui prend en argument le tableau d'état avec sa dimension
     * @param parent
     * @param statetab
     */
    StatesBrowser(QWidget* parent,std::pair<int,CellState**> statetab);
    ~StatesBrowser();

  signals:
    /**
     * @brief stateChanged signals qui est utilisé dans chooseState pour appliquer le changement
     */
    void stateChanged(int,CellState*);

  public slots:
    void loadStates();

    /**
     * @brief receiveStateID affecte l'id en paramètre à l'attribut stateID
     * @param id numéro que l'on affecte à stateID
     */

    void receiveStateID(int id);
  private slots:
    /**
     * @brief chooseState appelle stateChanged afin d'appliquer le changement d'état
     */
    void chooseState();
    void openCreateState();
};



#endif // STATES_BROWSER_H
