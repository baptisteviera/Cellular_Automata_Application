#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QColor>
#include <map>
#include "../constants.h"
#include "automata_manager.h"
#include "neighborhood_factory.h"
#include "transition_factory.h"
#include "grid_factory.h"

/**
 * @brief The DBException class gestionnaire d'erreurs
 */

class DBException{
    /**
     * @brief info message d'erreur
     */
    std::string info;
public:
    /**
     * @brief DBException constructeur de la classe DBException
     * @param s chaine de caractères concernant le message d'erreur
     */
    DBException(const std::string& s) : info(s){}
    /**
     * @brief getInfo récupère l'information (message d'erreur)
     * @return le message d'erreur
     */
    const std::string& getInfo() const{return info;}
};
/**
 * @brief The DBManager class gestionnaire de la BDD (singleton)
 */
class DBManager{
    /**
     * @brief DBManager  Constructeur de la classe DBManager
     */
    DBManager(const QString&);
    /**
     * @brief db la base de donnée
     */
    QSqlDatabase db;
    /**
     * @brief DBManager supressiondu constructeur par recopie
     */
    DBManager(const DBManager*) = delete;
    /**
     * @brief operator = supression de l'opération d'affectation
     * @return DBManager
     */
    DBManager operator=(const DBManager*) = delete;
    /**
     * @brief DBManInstance implémentation du singleton
     */
    static DBManager* DBManInstance;
    /**
     * @brief transitionFac gestionnaire de la créer des transitions
     */
    TransitionFactory transitionFac;
    /**
     * @brief neighborFac gestionnaire de la création de voisinage
     */
    NeighborhoodFactory neighborFac;
    /**
     * @brief gridFac gestionnaire de la création de la grille
     */
    GridFactory gridFac;

public:
    //destructeur de la classe DBManager()
    ~DBManager();
    /**
     * @brief getDB récupérer la BDD
     * @return la BDD
     */
    static DBManager& getDB();
    /**
     * @brief closeDB ferme la BDD
     */
    static void closeDB();
    /**
     * @brief loadAutomatasFromDB permet de charger des automates à partir de la BDD
     */
    void loadAutomatasFromDB() const;


    /**
     * @brief toColor transforme un Qstring en Qcolor pour l'appliquer à l'interface graphique
     * @param col couleur récupérée dans la BDD
     * @return une couleur de type QColor
     */
    QColor toColor(const QString& col) const;



    void DbaddState(const QString label, const int id , const QString color) const;




    /**
     * @brief insertAutomataIntoDB permet d'ajouter des automates dans la BDD
     * @param name nom de l'automate
     * @param nbStates  nombre d'états disponibles
     * @param transitionName nom de la transition souhaitée
     * @param neighborhoodName nom du voisinage souhaitée
     * @param chosenStates types d'états sélectionnés
     * @param description description de l'automate
     * @param author l'auteur de l'automate
     * @param year l'année de création
     */
    void insertAutomataIntoDB(QString name,int nbStates, QString transitionName, QString neighborhoodName,CellState** chosenStates,QString description = "",QString author = "",int year = 0);


    /**
     * @brief insertNeighborhoodIntoDB permet d'insérer un voisinage généralisé
     * @param name nom du voisinage
     * @param radius rayon nécessaire au voisinage généralisée
     */
    void insertNeighborhoodIntoDB(const QString name, const int radius) const;
    /**
     * @brief insertNeighborhoodIntoDB permet d'insérer un voisinage non généralisé
     * @param name nom du voisinage
     * @param nbNeighbors nombre de voisins
     * @param dx abscisse de la cellule
     * @param dy ordonnée de la cellule
     */
    void insertNeighborhoodIntoDB(const QString name, int nbNeighbors, const int* dx,const int *dy)const;
    /**
     * @brief loadNeighborhoodsFromDB permet de charger un voisinage dans la BDD
     * @return un couple avec la dimension du tableau  et le tableau
     */
    std::pair<int, NeighborhoodStrategy**> loadNeighborhoodsFromDB() const;
    /**
     * @brief loadStatesfromDB charge des états depuis la base de données
     * @return  un couple avec la dimension du tableau  et le tableau
     */
    std::pair<int,CellState**> loadStatesfromDB() const;
    /**
     * @brief loadTransitionsFromDB charge les transitions depuis la base de données
     * @return un couple avec la dimension du tableau  et le tableau
     */

    std::pair<int, TransitionStrategy**>loadTransitionsFromDB() const;
    /**
     * @brief insertConfigIntoDB permet d'ajouter des configurations dans la BDD
     * @param name  nom donné à la configuration
     * @param config correspond à la configuration créée par l'utilisateur
     * @param automata automate auquel la configuration est associée
     */
    void insertConfigIntoDB(const QString& name, Grid* config, Automata* automata) const;
    /**
     * @brief loadConfigsFromDB permet de charger une configuration après avoir sélectionné un automate
     * @param automata
     * @return un couple qui contient le nombre de configurations et la table qui contient l'ensemble des configurations
     */
    std::pair<int, Grid**> loadConfigsFromDB(Automata* automata) const;
};


#endif // DATABASE_H
