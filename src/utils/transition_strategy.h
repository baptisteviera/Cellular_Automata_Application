#ifndef TRANSITION_STRATEGY_H
#define TRANSITION_STRATEGY_H

#include <string>
#include <map>
#include "neighborhood_strategy.h"
#include "cell_state.h"
#include "grid.h"

/**
 * @brief The TransitionException class gestion des erreurs pour les Transition
 */
class TransitionException {
    /**
     * @brief info chaine de caractères contenant des informations sur l'erreur
     */
    std::string info;
  public:
    /**
     * @brief TransitionException   constructeur de la classe TransitionException
     * @param s message d'erreur
     */
    TransitionException(std::string s): info(s) {}
    /**
     * @brief getInfo   accesseur de type getter pour retourner le message d'erreur
     * @return message d'erreur
     */
    std::string getInfo() {
        return info;
    }
};

////Implementation of the Strategy design pattern./////

///Basic interface///
/**
 * @brief The TransitionStrategy class Implementation of the Strategy design pattern
 */
class TransitionStrategy { //interface
    /**
     * @brief name  nom de la transition
     */
    std::string name;
  public:
    /**
     * @brief TransitionStrategy    constructeur de la classe TransitionStrategy
     * @param name  nom de la transition
     */
    TransitionStrategy(std::string name) : name(name) {};
    /**
     * @brief getStatePosFromId    permet de retourner la position d'un état dans un tableau d'état à partir de l'id de l'état
     * @param nbStates  nombre d'états dans le tableau d'états
     * @param availableStates   tableau d'états
     * @param id identificateur de l'état
     * @return la position de l'état dans le tableau d'états
     */
    int getStatePosFromId(int nbStates, CellState** availableStates, int id) const;
    /**
     * @brief calcNextCell  méthode virtuelle pure que l'on définit dans les classes filles qui correspondent aux différents types de transitions
     * @param c cellule étudiée que l'on modifiera ou non
     * @param neighbors tableau de voisin de la cellule
     * @param neighborSize  nombre de voisins de la cellule
     * @param availableStates  tableau d'états disponibles
     * @param nbStates  nombre d'états possibles
     * @return une nouvelle cellule (identique à c ou différente) suivant les règles de transition
     */
    virtual Cell* calcNextCell(Cell* c, Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const = 0;
    /**
     * @brief getName   accesseur de type getter
     * @return le nom de la transition
     */
    std::string getName() const {
        return name;
    }
};

/**
 * @brief The TotalisticTransition class    classe fille qui hérite de TransitionStrategy
 */
class TotalisticTransition : public TransitionStrategy {
  public:
    /**
     * @brief TotalisticTransition  constructeur de TotalisticTransition
     * @param name  nom spécifique de la Totalistic Transition si non spécifié par défaut égale à "Totalistic Transition"
     */
    TotalisticTransition(std::string name = "Totalistic Transition") : TransitionStrategy(name) {}
    /**
     * @brief calcNextCell  méthode virtuelle pure que l'on définit dans les classes filles qui correspondent aux différents types de transitions
     * @param c cellule étudiée que l'on modifiera ou non
     * @param neighbors tableau de voisin de la cellule
     * @param neighborSize  nombre de voisins de la cellule
     * @param availableStates  tableau d'états disponibles
     * @param nbStates  nombre d'états possibles
     * @return une nouvelle cellule (identique à c ou différente) suivant les règles de transition
     */
    virtual Cell* calcNextCell(Cell* c, Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const = 0;
};

/**
 * @brief The StochasticTransition class classe fille qui hérite de TransitionStrategy
 */
class StochasticTransition : public TransitionStrategy {
  public:
    /**
     * @brief StochasticTransition  constructeur de StochasticTransition
     * @param name  nom spécifique de la Totalistic Transition si non spécifié par défaut égale à "Stochastic Transition"
     */
    StochasticTransition(std::string name = "Stochastic Transition") : TransitionStrategy(name) {}
    /**
     * @brief calcNextCell  méthode virtuelle pure que l'on définit dans les classes filles qui correspondent aux différents types de transitions
     * @param c cellule étudiée que l'on modifiera ou non
     * @param neighbors tableau de voisin de la cellule
     * @param neighborSize  nombre de voisins de la cellule
     * @param availableStates  tableau d'états disponibles
     * @param nbStates  nombre d'états possibles
     * @return une nouvelle cellule (identique à c ou différente) suivant les règles de transition
     */
    virtual Cell* calcNextCell(Cell* c, Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const = 0;
};

class OuterTotalisticTransition : public TotalisticTransition {
  public:
    /**
     * @brief isDestination Verifier si c est la destination de la fourmi dans neighbor
     * @param a une cellule quelconque
     * @param b une cellule quelconque
     * @return  True si c est la destination de la fourmi dans neighbor et False si ce n'est pas le cas
     */
    bool isDestination(Cell* a, Cell* b) const;
    /**
     * @brief isUnder  Verifier si a est au-dessus de b ou non
     * @param a une cellule quelconque
     * @param b une cellule quelconque
     * @return True si a au-dessus de b et False si a non au-dessus de b
     */
    bool isUnder(Cell* a, Cell* b) const;
    /**
     * @brief isLeft Verifier si a est a gauche de b ou non
     * @param a une cellule quelconque
     * @param b une cellule quelconque
     * @return True si a est à gauche de b et False si a n'est pas à a gauche de b
     */
    bool isLeft(Cell* a, Cell* b) const;
    /**
     * @brief OuterTotalisticTransition  constructeur de OuterTotalisticTransition
     * @param name  nom spécifique de la OuterTotalisticTransition si non spécifié par défaut égale à "OuterTotalistic Transition"
     */
    OuterTotalisticTransition(std::string name = "OuterTotalistic Transition") : TotalisticTransition(name) {}
    /**
     * @brief calcNextCell  méthode virtuelle pure que l'on définit dans les classes filles qui correspondent aux différents types de transitions
     * @param c cellule étudiée que l'on modifiera ou non
     * @param neighbors tableau de voisin de la cellule
     * @param neighborSize  nombre de voisins de la cellule
     * @param availableStates  tableau d'états disponibles
     * @param nbStates  nombre d'états possibles
     * @return une nouvelle cellule (identique à c ou différente) suivant les règles de transition
     */
    virtual Cell* calcNextCell(Cell* c, Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const = 0;
};

///Concrete strategies///
class GOLTransition : public OuterTotalisticTransition {
  public:
    /**
    * @brief GOLTransition constructeur de GOF
    * @param name nom de la transition, si non spécifié égale à "Game Of Life Transition"
    */
    GOLTransition(std::string name = "Game of Life Transition Rule") : OuterTotalisticTransition(name) {}
    /**
     * @brief calcNextCell  méthode concrète qui définit la fonction virtuelle pure de la classe mère pour la GOLTransition
     * @param c cellule étudiée que l'on modifiera ou non
     * @param neighbors tableau de voisin de la cellule
     * @param neighborSize  nombre de voisins de la cellule
     * @param availableStates  tableau d'états disponibles
     * @param nbStates  nombre d'états possibles
     * @return une nouvelle cellule (identique à c ou différente) suivant les règles de transition
     */
    Cell* calcNextCell(Cell* c, Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const override;
};

class BBTransition : public OuterTotalisticTransition {
  public:

    BBTransition(std::string name = "Brian Brain Transition Rule") : OuterTotalisticTransition(name) {}
    /**
     * @brief calcNextCell  méthode concrète qui définit la fonction virtuelle pure de la classe mère pour la BBTransition
     * @param c cellule étudiée que l'on modifiera ou non
     * @param neighbors tableau de voisin de la cellule
     * @param neighborSize  nombre de voisins de la cellule
     * @param availableStates  tableau d'états disponibles
     * @param nbStates  nombre d'états possibles
     * @return une nouvelle cellule (identique à c ou différente) suivant les règles de transition
     */
    Cell* calcNextCell(Cell* c, Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const override;
};

class DGTransition : public OuterTotalisticTransition {
    public:
    DGTransition(std::string name = "David Griffeath Transition") : OuterTotalisticTransition(name) {}

    /**
     * @brief calcNextCell  méthode concrète qui définit la fonction virtuelle pure de la classe mère pour la DGTransition
     * @param c cellule étudiée que l'on modifiera ou non
     * @param neighbors tableau de voisin de la cellule
     * @param neighborSize  nombre de voisins de la cellule
     * @param availableStates  tableau d'états disponibles
     * @param nbStates  nombre d'états possibles
     * @return une nouvelle cellule (identique à c ou différente) suivant les règles de transition
     */
    Cell* calcNextCell(Cell* c, Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const override;
};

class LLTransition : public OuterTotalisticTransition {
    public:
    LLTransition(std::string name = "Langton Loop Transition") : OuterTotalisticTransition(name) {}

    /**
     * @brief calcNextCell  méthode concrète qui définit la fonction virtuelle pure de la classe mère pour la LLTransition
     * @param c cellule étudiée que l'on modifiera ou non
     * @param neighbors tableau de voisin de la cellule
     * @param neighborSize  nombre de voisins de la cellule
     * @param availableStates  tableau d'états disponibles
     * @param nbStates  nombre d'états possibles
     * @return une nouvelle cellule (identique à c ou différente) suivant les règles de transition
     */
    Cell* calcNextCell(Cell* c, Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const override;
};


class LATransition : public OuterTotalisticTransition {
  public:
    LATransition(std::string name = "Langton Ant Transition") : OuterTotalisticTransition(name) {}

    /**
     * @brief calcNextCell  méthode concrète qui définit la fonction virtuelle pure de la classe mère pour la LATransition
     * @param c cellule étudiée que l'on modifiera ou non
     * @param neighbors tableau de voisin de la cellule
     * @param neighborSize  nombre de voisins de la cellule
     * @param availableStates  tableau d'états disponibles
     * @param nbStates  nombre d'états possibles
     * @return une nouvelle cellule (identique à c ou différente) suivant les règles de transition
     */
    Cell* calcNextCell(Cell* c, Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const override;
};


#endif
