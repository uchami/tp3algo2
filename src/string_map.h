#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>
#include <vector>

using namespace std;

template<typename T>
class string_map {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    string_map();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    string_map(const string_map<T>& aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    string_map& operator=(const string_map& d);

    /**
    DESTRUCTOR
    **/
    ~string_map();

    /**
    operator[]
    * Acceso o definición de pares clave/valor
    **/

    T &operator[](const string &key);

    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/

    int count(const string &key) const;

    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión modificable y no modificable
    **/
    const T& at(const string& key) const;
    T& at(const string& key);

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void erase(const string& key);

    /**
     SIZE
     * Devuelve cantidad de claves definidas */
    int size() const;

    /**
     EMPTY
     * devuelve true si no hay ningún elemento en el diccionario */
    bool empty() const;
    vector<string> claves(string camino);

private:

    struct Nodo {
        vector<Nodo*> siguientes;
        T* definicion;
        Nodo():siguientes(256, NULL), definicion(NULL){
        }
    };

    void copiarHijos(Nodo** destino, Nodo** fuente);
    void destruirDic(Nodo*& root);
    bool borrarDef(Nodo* n, string clave);

    Nodo* raiz;
    int _size;
};

#include "string_map.hpp"

#endif // STRING_MAP_H_
