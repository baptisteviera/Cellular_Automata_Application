#ifndef CONFIGSBROWSER_H
#define CONFIGSBROWSER_H

#include <QDialog>
#include <QObject>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QMessageBox>
#include <utility>
#include "../../utils/grid.h"
#include "../../utils/database.h"

class ConfigsBrowser : public QDialog
{
    Q_OBJECT
    /**
     * @brief mainLayout (vertical) création de la fenêtre principale qui contient tous les layouts
     */
    QVBoxLayout* mainLayout;
    /**
     * @brief buttonsLayout (horizontal) pour accueillir les boutons
     */
    QHBoxLayout* buttonsLayout;
    /**
     * @brief configsTable table qui contient l'ensemble des configs
     */
    QTableWidget* configsTable;
    /**
     * @brief configsItems correspondent aux éléments continus dans la table configsTable
     */
    QTableWidgetItem*** configsItems;
    /**
     * @brief btnLoad btnDelete boutons permettant de load et de delete un automate
     */
    QPushButton *btnLoad, *btnDelete;
    /**
     * @brief TBL_NB_COLS nombre de colonnes
     */
    const int TBL_NB_COLS = 3;

    /**
     * @brief loadedConfigsInfos contient les informations chargées depuis la base de données
     */
    std::pair<int, Grid**> loadedConfigsInfos;
    /**
     * @brief initConfigsTable intialisation de la table des configurations
     */
    void initConfigsTable();
    /**
     * @brief initButtons initialisation des buttons
     */
    void initButtons();

  public:
    /**
     * @brief ConfigsBrowser constructeur
     * @param parent
     */
    ConfigsBrowser(QWidget* parent);
    ~ConfigsBrowser();
    /**
     * @brief openConfigsBrowser permet d'obtenir les configurations associées à l'automate sélectionné
     * @param automata l'automate que l'utilisateur a sélectionné
     */
    void openConfigsBrowser(Automata* automata);

  signals:
    /**
     * @brief configChanged signals qui est appelé dans la fonction chooseConfig pour que le changement soit effectif
     * @param config choix de la config sélectionnée
     */
    void configChanged(Grid* config);

  private slots:
    /**
     * @brief chooseConfig permet de choisir et d'appliquer la configuration sélectionnée
     */
    void chooseConfig();
    void deleteConfig();
};

#endif // CONFIGSBROWSER_H
