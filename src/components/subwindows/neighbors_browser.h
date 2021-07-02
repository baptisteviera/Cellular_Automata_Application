#ifndef NEIGHBORHOODSBROWSER_H
#define NEIGHBORHOODSBROWSER_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QCheckBox>
#include "utils/database.h"
#include "utils/neighborhood_strategy.h"
#include "utils/helpers.h"
#include "utils/database.h"

/**
 * @brief Classe NeighborCreator créer la pop up de création de voisinage
 */
class NeighborCreator : public QDialog {
    Q_OBJECT
    /**
     * @brief width largeur de la grillle de création
     * @brief height hauteur de la grille de création
     * @brief centerR centre des lignes
     * @brief centerC centre des colonnes
     */
    int width, height, centerR, centerC;
    /**
     * @brief txtName champ du nom du voisinage
     */
    QLineEdit* txtName;
    /**
     * @brief spbRadius champs numérique su rayon
     */
    QSpinBox* spbRadius;
    /**
     * @brief neighborsTypeCbb menu déroulant du type de voisinage
     */
    QComboBox* neighborsTypeCbb;
    /**
     * @brief gridLayout disposition de la grille
     */
    QGridLayout* gridLayout;
    /**
     * @brief mainLayout disposition principale
     */
    QVBoxLayout* mainLayout;
    /**
     * @brief buttonsLayout disposition des boutons
     */
    QHBoxLayout* buttonsLayout;
    /**
     * @brief infoLayout disposition des information du voisinage
     */
    QFormLayout* infoLayout;
    /**
     * @brief cellsCheckbox cache à cocher pour créer le voisinage
     */
    QCheckBox*** cellsCheckbox;
    /**
     * @brief btnCreate bouton pour créer le voisinage
     */
    QPushButton* btnCreate;

public:
    /**
     * @brief NeighborCreator Constructeur de la pop-up de création de voisinage
     * @param parent widget à partir duquel est crée AutomatasBrowser
     * @param width largeur de la grille
     * @param height hauteur de la grille
     */
    NeighborCreator(QWidget* parent, int width, int height);
    ~NeighborCreator();
private slots:
    /**
     * @brief createNeighbor permet d'insérer le voisinage dans la bdd
     */
    void createNeighbor();
    /**
     * @brief changeNeighborType change le type de voisnage
     * @param id numéro du voisinage
     */
    void changeNeighborType(int id);
    /**
     * @brief changeRadius change le rayon
     * @param val valeur du rayon
     */
    void changeRadius(int val);
};
/**
 * @brief Classe NeighborsBrowser de la pop-up du parcours des voisinage
 */
class NeighborsBrowser : public QDialog{
    Q_OBJECT
    /**
     * @brief mainLayout dispostion principale
     */
    QVBoxLayout* mainLayout = nullptr;
    /**
     * @brief buttonsLayout disposition des boutons
     */
    QHBoxLayout* buttonsLayout = nullptr;
    /**
     * @brief neighborhoodLayout disposotion des voisinages
     */
    QFormLayout* neighborhoodLayout = nullptr;
    /**
     * @brief neighborhoodCbb menu déroulant des voisinages
     */
    QComboBox* neighborhoodCbb = nullptr;
    /**
     * @brief spbRadius champ numérique des rayons
     */
    QSpinBox* spbRadius = nullptr;
    /**
     * @brief btnConfirm bouton de confirmation
     */
    QPushButton* btnConfirm = nullptr;
    /**
     * @brief btnCreate bouton de création
     */
    QPushButton* btnCreate = nullptr;
    /**
     * @brief neighborCreator pointeur de la création des voisinages
     */
    NeighborCreator* neighborCreator = nullptr;
    /**
     * @brief nbNeighbors nombre de voisins
     */
    int nbNeighbors = 0;
    /**
     * @brief neighbors pointeurs des voisins
     */
    NeighborhoodStrategy** neighbors = nullptr;
    /**
     * @brief selectedNeighbor pointeur de sélection des voisinages
     */
    NeighborhoodStrategy* selectedNeighbor = nullptr;
    /**
     * @brief updateCombobox permet la mise à jour du menu déroulant
     */
    void updateCombobox();

public:
    /**
     * @brief NeighborsBrowser constructeur de la pop-up du parcours des voisinage
     * @param parent widget à partir duquel est crée NeighborsBrowser
     * @param width largeur de la grille
     * @param height hauteur de la grille
     */
    NeighborsBrowser(QWidget* parent, int width = 31, int height = 31);
    ~NeighborsBrowser();
    /**
     * @brief setNeighborhoods modifie le voisinage
     * @param nbNeighbors nombre de voisins
     * @param neighbors tableaux de pointeurs des voisins
     */
    void setNeighborhoods(int nbNeighbors, NeighborhoodStrategy** neighbors);

signals:
    /**
     * @brief neighborChanged change le voisinage
     * @param neighbor pointeur vers le voisinage
     */
    void neighborChanged(NeighborhoodStrategy* neighbor);

public slots:
    /**
     * @brief chooseNeighbor permet de choisir un voisin
     */
    void chooseNeighbor();
    /**
     * @brief neighborCbbChanged change la valeur du menu déroulant du voisinage
     * @param id
     */
    void neighborCbbChanged(int id);
    /**
     * @brief openNeighborsBrowser ouvre la fenêtre de parcours du voisinage
     */
    void openNeighborsBrowser();

private slots:
    /**
     * @brief openNeighborCreator ouvre la fenêtre de création du voisinage
     */
    void openNeighborCreator();

};

#endif // NEIGHBORHOODSBROWSER_H
