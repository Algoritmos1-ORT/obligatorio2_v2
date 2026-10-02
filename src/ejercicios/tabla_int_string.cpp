#include "TablaIntString.h"

struct _representacionTablaIntString {
    int placeholder;
};

TablaIntString crearTablaIntString(unsigned int) { throw "NoImplementado"; }
void agregar(TablaIntString&, int, const char*) { throw "NoImplementado"; }
bool estaDefinida(TablaIntString, int) { throw "NoImplementado"; }
const char* recuperar(TablaIntString, int) { throw "NoImplementado"; }
void borrar(TablaIntString&, int) { throw "NoImplementado"; }
int elemento(TablaIntString) { throw "NoImplementado"; }
bool esVacia(TablaIntString) { throw "NoImplementado"; }
unsigned int cantidadElementos(TablaIntString) { throw "NoImplementado"; }
void destruir(TablaIntString&) { throw "NoImplementado"; }
TablaIntString clon(TablaIntString) { throw "NoImplementado"; }