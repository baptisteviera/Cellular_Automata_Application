#ifndef LO21_SIMULATOR_H
#define LO21_SIMULATOR_H

#include "automata.h"
#include "grid.h"
#include "grid_factory.h"

/**
 * @brief The BufferException class gestionnaire d'erreurs lié au buffer
 */
class BufferException{
    /**
     * @brief info  chaine de caractères contenant des informations sur l'erreur
     */
    std::string info;
public:
    /**
     * @brief BufferException   constructeur de la classe BufferException
     * @param s message d'erreur
     */
    BufferException(std::string s):info(s){};
    std::string getInfo() const{return info;}
};

class Simulator {
  public:
    /**
     * @brief getGridFactory le simulateur récupère les grilles crées par la classe GridFactory qui implémente le design pattern factory
     * @return la grille
     */
    static GridFactory& getGridFactory() {
        static GridFactory gridFactory;
        return gridFactory;
    }
  private:
    /**
     * @brief automata un automate quelconque
     */
    Automata* automata;
    /**
     * @brief bufferSize taille du buffer maximale
     */
    int bufferSize;
    /**
     * @brief startGrid grille de départ initialisé par défaut à nullptr
     */
    Grid* startGrid = nullptr;
    /**
     * @brief grids la grille qui va permettre de modéliser et visualiser nos automates, initialisé à nullptr
     */
    Grid** grids = nullptr;
    /**
     * @brief currentGridID il s'agit du rang de la cellule courante
     */
    int currentGridID = 0;
    /**
     * @brief maxID permettra de s'arrêter à la génération 0 ou à la génération actuelle - la taille du buffer lors du retour aux états précédents
     */
    int maxID;

    /**
     * @brief Simulator constructeur par recopie supprimé
     * @param s un simulateur quelconque
     */
    Simulator(const Simulator& s) = delete;
    /**
     * @brief operator = opérateur d'affectation supprimé
     * @param s un simulateur quelconque
     * @return un simulateur
     */
    Simulator& operator=(const Simulator& s) = delete;


  public:
    /**
     * @brief Simulator constructeur du simulateur sans grille de départ avec un buf par défaut égal à 2
     * @param a un automate quelconque
     * @param buf taille du buffer, on peut revenir aux deux générations précédentes par défaut
     */
    Simulator(Automata* a, int buf = 2);
    /**
     * @brief Simulator constructeur du simulateur avec une grille de départ
     * @param a un automate quelconque
     * @param startG la grille de départ
     * @param buf taille du buffer, on peut revenir aux deux générations précédentes par défaut
     */
    Simulator(Automata* a, Grid& startG, int buf = 2);

    // destructeur
    ~Simulator();
    /**
     * @brief allocateBuffer permet de créer le buffer et d'initialiser chaque cellule du buffer à nullptr
     */
    void allocateBuffer();
    /**
     * @brief setStartGrid  permet de définir une grille de départ
     * @param g grille de départ souhaitéé
     */
    void setStartGrid(Grid* g);
    /**
     * @brief reset permet de revenir à la grille de départ
     */
    void reset();
    /**
     * @brief run fait appel à la méthode next() nbSteps fois
     * @param nbSteps nombre de fois que l'on appelle la méthode next()
     */
    void run(int nbSteps = 1);
    /**
     * @brief next permet d'aller à la génration suivante
     */
    void next();
    /**
     * @brief frequency vitesse de passage d'une génération à une autre
     */
    unsigned int frequency;


    /**
     * @brief setAutomata permet d'associer le simulateur à un automate
     * @param automata    automate quelconque qui est utilisé pour notre simulateur
     */
    void setAutomata(Automata* automata);
    /**
     * @brief setBufferSize setteur qui fixe la taille du voisinage
     */
    void setBufferSize(int);
    /**
     * @brief getAutomata permet de récupérer l'automate
     * @return retourne l'automate
     */
    Automata* getAutomata() const;
    /**
     * @brief getBufferSize permet de récupérer la taille du buffer
     * @return la taille du buffer
     */
    int getBufferSize() const;
    /**
     * @brief getCurrentGridID permet de récupérer la grille courante
     * @return la grille courante
     */
    int getCurrentGridID() const;
    /**
     * @brief The Iterator class permet de parcourir le buffer
     */
    class Iterator {
        friend class Simulator;

      private:
        /**
         * @brief sim un objet pointeur de type simulateur initialisé à nullptr
         */
        Simulator* sim = nullptr;
        /**
         * @brief gridID ID de la grille dans le buffer
         */
        int gridID = 0;
        /**
         * @brief Iterator constructeur de recopie
         * @param s le simulateur que l'on recopie
         */
        Iterator(Simulator* s);

      public:
        Iterator();
        /**
         * @brief isDone permet de vérifier si on a atteint la fin du buffer
         * @return True si on a atteint la fin du buffer sinon False
         */
        bool isDone() const;

        /**
         * @brief previousGrid permet de revenir à la génération précédente
         */
        void previousGrid();
        /**
         * @brief nextGrid permet d'aller à la génration suivante
        */
        void nextGrid();
        /**
         * @brief current permet retourner la grille actuelle
         * @return retourne la grille actuelle
         */
        Grid* current() const;

        //operator!=(): bool
    };
    /**
     * @brief getIterator permet de récupérer l'itérateur
     * @return l'itérateur
     */
    Iterator getIterator();
};



#endif //LO21_SIMULATOR_H
