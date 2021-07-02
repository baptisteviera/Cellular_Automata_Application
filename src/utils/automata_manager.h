#ifndef LO21_AUTOMATAMANAGER_H
#define LO21_AUTOMATAMANAGER_H
#include "automata.h"
#include "transition_strategy.h"
#include "neighborhood_strategy.h"
#include "cell_state.h"
#include "grid.h"

#define MAX_AUTOMATA 1000

using namespace std;

/**
 * @brief Singleton AutomateManager gérant les automates
 */
class AutomataManager {
  private:
    /**
     * @brief instance instance unique d'AutomateManager
     */
    static AutomataManager* instance; //Instance unique (singleton)
    /**
     * @brief nbAutomatas nombre courant d'automate stockés
     */
    int nbAutomatas;
    /**
     * @brief nbMaxAutomatas nombre maximal d'automate pouvant être stocké (1000 par défaut)
     */
    const int nbMaxAutomatas = MAX_AUTOMATA;
    /**
     * @brief automatas tableau de pointeur d'automates
     */
    Automata** automatas;

    /**
     * @brief AutomataManager Constructeur de recopie désactivé pour implémenté le design pattern Singleton
     * @param automateManager AutomateManager sur lequel recopier
     */
    AutomataManager(const AutomataManager& automateManager) = delete;
    /**
     * @brief AutomataManager Constructeur privé pour implémenter le design pattern Singleton
     */
    AutomataManager();
    /**
    * @brief ~AutomataManager Destructeur privé pour implémenter le design pattern Singleton
    **/
    ~AutomataManager();
    /**
     * @brief operator = opérateur d'affectation privé pour implémenté le design pattern Singleton
     * @param automateManager AutomateManager sur lequel recopier
     */
    void operator=(const AutomataManager& automateManager) = delete;

  public:
    /**
     * @brief getAutomataManager Accesseur en lecture de l'instance unique
     * @return l'instance unique AutomateManager
     */
    static AutomataManager* getAutomataManager();
    /**
     * @brief destroyAutomataManager Destructeur de l'instance unique AutomateManager
     */
    static void destroyAutomataManager();

    /**
     * @brief getAutomata Acesseur en lecture d'un élément du tableau d'automate
     * @param id Numéro de l'automate à retourner
     * @return Automata* l'automate demandé
     */
    Automata* getAutomata(int id) const;
    /**
     * @brief changeAutomata modifier un automate dont le numéro est donné en entrée
     * @param id le numéro de l'automate à modifier
     * @param availableStates liste des états possibles de l'automate
     * @param transition la stratégie de transition pour générer les nouvelles générations
     * @param neighborhood la stratégie de retrouver les voisins
     * @param nbStates le nombre d'états possbiles
     * @param name le nom de l'automate
     * @param desc la description de l'automate
     * @param author l'auteur
     * @param year l'année de création
     */
    void changeAutomata(int id, CellState** availableStates, TransitionStrategy* transition, NeighborhoodStrategy* neighborhood, int nbStates = 0, string name = "", string desc = "", string author = "", int year = 2021);
    /**
     * @brief addAutomata ajoute un automate à la liste des automates
     * @param availableStates liste des états possibles de l'automate
     * @param transition la stratégie de transition pour générer les nouvelles générations
     * @param neighborhood la stratégie de retrouver les voisins
     * @param nbStates le nombre d'états possbiles
     * @param name le nom de l'automate
     * @param desc la description de l'automate
     * @param author l'auteur
     * @param year l'année de création
     */
    void addAutomata(CellState** availableStates, TransitionStrategy* transition, NeighborhoodStrategy* neighborhood, int nbStates = 0, string name = "", string desc = "", string author = "", int year = 2021);
    /**
     * @brief removeAutomata supprime l'automate à l'indice donné
     * @param id indice de l'automate à supprimer
     */
    void removeAutomata(int id);
    /**
     * @brief getNbAutomatas accesseur en lecture du nombre courant d'automates
     * @return int nombre courant d'automates
     */
    int getNbAutomatas() const {
        return nbAutomatas;
    }
    /**
     * @brief Supprimer toutes les automates dans memoires
     */
    void clear();
};

#endif //LO21_AUTOMATAMANAGER_H
