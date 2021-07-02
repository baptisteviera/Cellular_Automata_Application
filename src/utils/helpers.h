#ifndef HELPERS_H
#define HELPERS_H


template<typename Base, typename T>
/**
 * @brief instanceof vérifier si la variable est une instance d'une classe
 * @param ptr la varaible
 * @return vrai si c'est la bonne instance faux sinon
 */
inline bool instanceof(const T* ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}


#endif // HELPERS_H
