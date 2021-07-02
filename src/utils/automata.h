#ifndef LO21_AUTOMATA_H
#define LO21_AUTOMATA_H
#include <string>
#include "transition_strategy.h"
#include "neighborhood_strategy.h"
#include "cell_state.h"
#include "grid.h"
using namespace std;

/**
 * @brief La classe qui représente une automate
 */
class Automata {
  private:
    /**
     * @brief name nom de l'automate
     */
    string name;
    /**
     * @brief description description de l'automate
     */
    string description;
    /**
     * @brief author créateur de l'automate
     */
    string author;
    /**
     * @brief creationYear année de création de l'automate
     */
    int creationYear;
    /**
     * @brief availableStates tableau des états utilisés par l'automate
     */
    CellState** availableStates = nullptr; //Différents états que les cellules peuvent prendre pour cet automate
    /**
     * @brief nbStates nombre d'états utilisés par l'automate
     */
    int nbStates;
    /**
     * @brief transitionStrategy fonction de transition utilisée par l'automate
     */
    TransitionStrategy* transitionStrategy; //Interface fonction de transition de l'automate
    /**
     * @brief neighborStrategy description du voisinage utilisé par l'automate
     */
    NeighborhoodStrategy* neighborStrategy; //Interface voisinage de l'automate

    // Methodes privées car gérées par AutomataManager
    Automata& operator=(const Automata& a) = default;
    Automata(const Automata&) = default;

    /**
     * @brief Construire une nouvelle instace de la class Automata
     * 
     * @param availableStates liste des états possibles de l'automate
     * @param transition la stratégie de transition pour générer les nouvelles générations
     * @param neighborhood la stratégie de retrouver les voisins
     * @param nbStates le nombre d'états possbiles
     * @param name le nom de l'automate
     * @param desc la description de l'automate
     * @param author l'auteur
     * @param year l'année de création
     */
    Automata(CellState** availableStates, TransitionStrategy* transition, NeighborhoodStrategy* neighborhood, int nbStates = 0, string name = "", string desc = "", string author = "", int year = 2021);
    ~Automata();

    friend class AutomataManager;

  public:
    /**
     * @brief Calculer et renvoyer la génération suivante d'une grille.
     * 
     * @param src la grille source
     * @return Grid* la génération suivante
     */
    Grid* applyTransition(Grid *src) const;

    /**
     * @brief Changer le nom d'automate
     * 
     * @param name le nouveau nom d'automate
     */
    void setName(const string name) {
        this->name = name;
    }
    /**
     * @brief Renvoyer le nom d'automate
     * 
     * @return string le nom d'automate
     */
    string getName() const {
        return name;
    }
    /**
     * @brief Changer la description d'automate
     * 
     * @param description la nouvelle description d'automate
     */
    void setDescription(const string description) {
        this->description = description;
    }
    /**
     * @brief Renvoyer la description d'automate
     * 
     * @return string la description d'automate
     */
    string getDescription() const {
        return this->description;
    }
    /**
     * @brief Changer l'auteur d'automate
     * 
     * @param author le nouveau nom de l'auteur
     */
    void setAuthor(const string author) {
        this->author = author;
    }
    /**
     * @brief Renvoyer le nom d'auteur
     * 
     * @return string 
     */
    string getAuthor() const {
        return this->author;
    }
    /**
     * @brief Changer l'année de création
     * 
     * @param year l'année de création
     */
    void setCreationYear(const int year) {
        this->creationYear = year;
    }
    /**
     * @brief Renvoyer l'année de création
     * 
     * @return int l'année de création
     */
    int getCreationYear() const {
        return this->creationYear;
    }
    /**
     * @brief Affecter la liste des états possibles
     * 
     * @param availableStates un tableau des pointeurs vers des états possibles
     * @param nbStates le nombre d'états dans la liste
     */
    void setAvailableStates(CellState** availableStates, int nbStates);
    /**
     * @brief Renvoyer la liste des états possibles
     * 
     * @return CellState**
     */ 
    CellState** getAvailableStates() const {
        return availableStates;
    }
    /**
     * @brief Modifier/Changer un état dans la liste actuelle des états
     * 
     * @param state l'état nouvel
     * @param id l'indice à changer
     */
    void setAvailableState(CellState* state, const int id);
    /**
     * @brief Renvoyer un état particulier
     * 
     * @param id l'indice de l'état
     * @return CellState* 
     */
    CellState* getAvailableState(const int id) const;
    /**
     * @brief Changer le nombre d'états possibles
     * 
     * @param nbStates le nombre d'états possibles
     */
    void setNbStates(const int nbStates) {
        this->nbStates = nbStates;
    }
    /**
     * @brief Renvoyer le nombre d'états possibles
     * 
     * @return int 
     */
    int getNbStates() const {
        return this->nbStates;
    }

    /**
     * @brief Changer la stratégie de transition
     * 
     * @param transition la nouvelle stratégie de transition
     */
    void setTransitionStrategy(TransitionStrategy* transition) {
        transitionStrategy = transition;
    }
    /**
     * @brief Renvoyer la stratégie de transition
     * 
     * @return TransitionStrategy* 
     */
    TransitionStrategy* getTransitionStrategy() const {
        return transitionStrategy;
    }
    /**
     * @brief Changer la stratégie de voisinage
     * 
     * @param neighborhood la nouvelle stratégie de voisinage
     */
    void setNeighborhoodStrategy(NeighborhoodStrategy* neighborhood) {
        neighborStrategy = neighborhood;
    }
    /**
     * @brief Renvoyer la stratégie de voisinage
     * 
     * @return NeighborhoodStrategy* 
     */
    NeighborhoodStrategy* getNeighborhoodStrategy() const {
        return neighborStrategy;
    }

};

#endif //LO21_AUTOMATA_H
