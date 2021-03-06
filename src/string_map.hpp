template <typename T>
string_map<T>::string_map():raiz(NULL),_size(0){
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() {
    *this = aCopiar;
} // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
void string_map<T>::destruirDic(Nodo*& root) {
    if(root == NULL){
        _size = 0;
        return;
    }
    Nodo* raizOriginal = root;
    for (int i = 0; i < 256; ++i) {
        root = raizOriginal->siguientes[i];
        destruirDic(root);
    }
    if(raizOriginal != NULL){
        delete raizOriginal->definicion;
        raizOriginal->definicion = NULL;
        delete raizOriginal;
        raizOriginal = NULL;
    }
}

/*template <typename T>
vector<string> string_map<T>::claves(string camino) {
    if(raiz == NULL){
        return vector<string>();
    }
    Nodo* exRaiz = raiz;
    for (int i = 0; i < 256; ++i) {
        raiz = exRaiz->siguientes[i];
        string exCamino = camino;
        camino.push_back(char(i));
        return exRaiz->definicion != NULL ? claves(exCamino).push_back(camino) : claves(exCamino);
    }
}*/

template <typename T>
void string_map<T>::copiarHijos(Nodo** destino, Nodo** fuente) {
    if(*fuente == NULL) {
        return;
    }

    *destino = new Nodo();

    (*destino)->definicion = ((*fuente)->definicion == NULL) ? NULL : new T(*((*fuente)->definicion));
    for (int i = 0; i < 256; ++i) {
        copiarHijos(&((*destino)->siguientes[i]), &((*fuente)->siguientes[i]));
    }
}


template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    destruirDic(raiz);
    _size = d._size;
    if(d.raiz == NULL){
        raiz = NULL;
        return *this;
    }

    raiz = new Nodo();

    raiz->definicion = (d.raiz->definicion == NULL) ? NULL : new T(*d.raiz->definicion);

    for (int i = 0; i < 256; ++i) {
        copiarHijos(&(raiz->siguientes[i]), &(d.raiz->siguientes[i]));
    }
}

template <typename T>
string_map<T>::~string_map(){
    destruirDic(raiz);
    raiz = NULL;
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    if(raiz == NULL){
        raiz = new Nodo();
    }
    Nodo* actual = raiz;
    for (int i = 0; i < clave.size(); ++i) {
        int charNum = int(clave[i]);
        Nodo** punteroAlSiguiente = &(actual->siguientes[charNum]);
        if(*punteroAlSiguiente == NULL){
            (*punteroAlSiguiente) = new Nodo();
        }
        actual =actual->siguientes[charNum];
    }
    if(actual->definicion == NULL){
        actual->definicion = new T();
        _size++;
    }
    return *actual->definicion;
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    if(raiz == NULL){
        return 0;
    }

    int i = 0;
    Nodo* actual = raiz;
    int charNum = int(clave[0]);
    while (i < clave.size() && actual->siguientes[charNum] != NULL){
        i++;
        actual = actual->siguientes[charNum];
        charNum = int(clave[i]);
    }
    return (i==clave.size() && actual->definicion != NULL ) ? 1 : 0;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    //obs: por pre la raiz no es null.
    Nodo* actual = raiz;
    for (int i = 0; i < clave.size(); ++i) {
        int charNum = int(clave[i]);
        Nodo** punteroAlSiguiente = &(actual->siguientes[charNum]);
        actual = actual->siguientes[charNum];
        //obs: por pre actual->siguientes[charNum] != NULL siempre que i < clave.size()-1.
    }
    return *actual->definicion;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    //obs: por pre la raiz no es null.
    Nodo* actual = raiz;
    for (int i = 0; i < clave.size(); ++i) {
        int charNum = int(clave[i]);
        Nodo** punteroAlSiguiente = &(actual->siguientes[charNum]);
        actual = actual->siguientes[charNum];
        //obs: por pre actual->siguientes[charNum] != NULL siempre que i < clave.size()-1.
    }
    return *actual->definicion;
}

template <typename T>
bool string_map<T>::borrarDef(Nodo* n, string clave){
    if(n == NULL){
        return false;
    }

    if(clave == ""){
        bool tieneHijos = false;
        for (int i = 0; i < 256; ++i) {
            tieneHijos = tieneHijos || n->siguientes[i] != NULL;
        }
        if(tieneHijos){
            delete (n->definicion);
            n->definicion = NULL;
            _size--;
            return false;
        } else {
            delete (n->definicion);
            delete n;
            _size--;
            return true;
        }
    } else {
        int cantHijos = 0;
        for (int i = 0; i < 256; ++i) {
            if(n->siguientes[i] != NULL){
                cantHijos++;
            }
        }
        bool tieneHijos = cantHijos > 1;
        bool borre = borrarDef(n->siguientes[int(clave[0])], clave.substr(1));

        if(borre){
            n->siguientes[int(clave[0])] = NULL;
            if(!tieneHijos && n->definicion == NULL){
                delete n;
                if(raiz == n){
                    raiz = NULL;
                }
                return true;
            }
        }
    }
    return false;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    borrarDef(raiz, clave);
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return (_size == 0);
}