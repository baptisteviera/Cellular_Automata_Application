#ifndef TRANSITION_FACTORY_H
#define TRANSITION_FACTORY_H
#include "transition_strategy.h"
#include <string>

using namespace std;
/**
 * @brief Classe de fabrication de fonction de transition
 */
class TransitionFactory {

public:
    /**
     * @brief production méthode production d'une classe héritant de TransitionStrategy à partir du nom de cette classe
     * @param name nom de la classe à créer
     * @return TransitionStrategy* un pointeur sur une classe de transition
     */
    TransitionStrategy* production(const string name) const;

};
#endif // TRANSITION_FACTORY_H
