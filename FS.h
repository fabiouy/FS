#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <string>
#include <ctime>

#define MAX_ARCHIVOS 16
#define MAX_LINEAS 20


using namespace std;
int contador = 0;
string clave = "SIMULADOR";

typedef struct ArchivoTexto{
    vector <string> lineas;
    bool encriptado;
} ArchivoTexto;

typedef struct FS{
        string nombreFS;
        bool directory;
        bool atributo_Solo_Lectura = false;
        bool atributo_Oculto = false;
        FS *padre;
        vector <FS> listadehijos;
        ArchivoTexto contenidoArchivo;
        string fecha;
        string autor;
} FS;

string encrypt(string toEncrypt, string key) {
    string output = toEncrypt;
    for (unsigned int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key[(i % key.size())];

    return output;
}

string obtenernfs(FS *archivo){
    return archivo->nombreFS;
}

void hacerOcultofs(FS *archivo){
    archivo->atributo_Oculto = !archivo->atributo_Oculto;
}

void hacerSoloLecturafs(FS *archivo){
    archivo->atributo_Solo_Lectura = !archivo->atributo_Solo_Lectura;
}

void hacerEncriptadofs(FS *archivo, string aut){
    string linea_aux;
    if (archivo->directory)
        cout << "Esto no es un archivo." << endl;
    else{
        if ((aut.compare(archivo->autor) == 0)){
            archivo->contenidoArchivo.encriptado = !archivo->contenidoArchivo.encriptado;
            for(unsigned int i = 0; i < archivo->contenidoArchivo.lineas.size(); i++){
                    linea_aux = encrypt(archivo->contenidoArchivo.lineas[i], clave);
                    archivo->contenidoArchivo.lineas[i] = linea_aux;
            }
        }
        else
            cout << "Usted no es el dueño del archivo." << endl;
    }
}

void asignarAutor(FS *archivo, string user){
    archivo->autor = user;
}

string datarFS(){
    string fechaactual = "";
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int aux_fecha;
    aux_fecha = 1 + ltm->tm_mday;
    fechaactual.append(to_string(aux_fecha));
    fechaactual.append("/");
    aux_fecha = 1 + ltm->tm_mon;
    fechaactual.append(to_string(aux_fecha));
    fechaactual.append("/");
    aux_fecha = 1900 + ltm->tm_year;
    fechaactual.append(to_string(aux_fecha));
    fechaactual.append(" ");
    aux_fecha = 1 + ltm->tm_hour;
    fechaactual.append(to_string(aux_fecha));
    fechaactual.append(":");
    aux_fecha = 1 + ltm->tm_min;
    fechaactual.append(to_string(aux_fecha));
    fechaactual.append(":");
    aux_fecha = 1 + ltm->tm_sec;
    fechaactual.append(to_string(aux_fecha));
    fechaactual.append(" ");
    return fechaactual;
}

void dfs_tree(FS *directorio, int cont){
    vector <FS> hijos;
    hijos = directorio->listadehijos;

    for(unsigned int i = 0; i < hijos.size(); i++){
        cout << "|" ;
        for (int j = 0; j < cont; j++){
            cout << "___" ;
        }
        cout << hijos[i].nombreFS << '\n';
        dfs_tree(&hijos[i], cont + 1);
    }
}

void listarhijos(FS *directorio, bool mostrartodo){
    vector <FS> hijos;
    hijos = directorio->listadehijos;
    for(unsigned int i = 0; i < hijos.size(); i++){
        if(!hijos[i].atributo_Oculto || mostrartodo){
            cout << hijos[i].fecha << " ";
            if (hijos[i].directory){
                cout << "<DIR>  ";
            }
            else{
                cout << "       ";
            }
            cout << hijos[i].nombreFS << '\n';
        }
    }
}

void agregarHijo(FS *padre, FS hijo){
    if (padre->listadehijos.size() < MAX_ARCHIVOS)
        padre->listadehijos.push_back(hijo);
    else
        cout << "Directorio lleno." << endl;
}

void sacarHijo(FS *padre, string hijo){
    unsigned int ubicacion;
    unsigned int i;
    for(i = 0; i < padre->listadehijos.size(); i++){
        if (padre->listadehijos[i].nombreFS.compare(hijo) == 0)
            ubicacion = i;
    }
    if (ubicacion < padre->listadehijos.size()){
        padre->listadehijos.erase(padre->listadehijos.begin() + ubicacion);
    }
    else
        cout << "Archivo no existe." << endl;
}

void crearArchivo(string nombre, FS *padre){
    FS nuevo;
    nuevo.nombreFS = nombre;
    nuevo.directory = false;
    nuevo.padre = padre;
    nuevo.contenidoArchivo = ArchivoTexto();
    nuevo.contenidoArchivo.encriptado = false;
    nuevo.fecha = datarFS();
    agregarHijo(padre, nuevo);
}

void crearDirectorio(string nombre, FS *padre){
    FS nuevo = FS();
    nuevo.nombreFS = nombre;
    nuevo.directory = true;
    nuevo.padre = padre;
    nuevo.fecha = datarFS();
    agregarHijo(padre, nuevo);
}

bool esDirectorio(FS* actual){
    return ((actual != nullptr) && (actual->directory == true));
}

FS* obtenernHijo(string nombre, FS* padre){
    FS *punterocarpeta = padre;
    string carpeta_actual;
    for(unsigned int i = 0; i < padre->listadehijos.size(); i++){
        carpeta_actual = obtenernfs(&padre->listadehijos[i]);
        if ((carpeta_actual.compare(nombre) == 0)){
            punterocarpeta = &padre->listadehijos[i];
        }
    }
    if (punterocarpeta == padre){
        cout << "No existe archivo o directorio." << endl;
    }
    return punterocarpeta;
}

bool existeArchivo(string nombre, FS* padre){
    FS *punterocarpeta = padre;
    string carpeta_actual;
    for(unsigned int i = 0; i < padre->listadehijos.size(); i++){
        carpeta_actual = obtenernfs(&padre->listadehijos[i]);
        if (carpeta_actual.compare(nombre) == 0){
            punterocarpeta = &padre->listadehijos[i];
        }
    }
    return (punterocarpeta != padre);
}

FS* obtenerPadre(FS* actual){
    if(actual->padre != nullptr){
        return actual->padre;
    }
    else{
        cout << "Usted se encuentra en la raiz." << endl;
        return actual;
    }
}

void agregarLineaArchivo(FS* actual, string linea){
    if (esDirectorio(actual)){
        cout << "No se pueden agregar lineas a un directorio." << endl;
    }
    else {
        if (!actual){
            cout << "No existe el archivo" << endl;
        }
        else {
            if (actual->atributo_Solo_Lectura){
                cout << "Archivo de solo lectura o bloqueado." << endl;
            }
            else{
                if (actual->contenidoArchivo.lineas.size() < MAX_LINEAS){
                    actual->contenidoArchivo.lineas.push_back(linea);
                }
                else
                    cout << "Archivo lleno." << endl;
            }
        }
    }
}

void removerLineaArchivo(FS* actual, int linea){
    actual->contenidoArchivo.lineas.erase(actual->contenidoArchivo.lineas.begin() + (linea - 1));
}

void mostrarArchivo(FS* actual){
    if (esDirectorio(actual)){
        cout << "No se puede mostrar un directorio." << endl;
    }
    else {
        string linea_aux;
        cout << "********" << actual->nombreFS << "********" << endl;
        cout << "" << endl;
        for(unsigned int i = 0; i < actual->contenidoArchivo.lineas.size(); i++){
            cout << actual->contenidoArchivo.lineas[i] << endl;
        }
        cout << "" << endl;
        cout << "********Fin de archivo********" << endl;
    }
}

void mostrarAtributos(FS* actual){
    if (!actual){
            cout << "No existe el archivo o directorio." << endl;
    }
    else {
        cout << "Atributos de archivo " << actual->nombreFS << ": ";
        cout << "H";
        if(actual->atributo_Oculto)
            cout << "+";
        else
            cout << "-";
        cout << "W";
        if(actual->atributo_Solo_Lectura)
            cout << "-";
        else
            cout << "+";
        cout << "C";
        if(actual->contenidoArchivo.encriptado)
            cout << "+";
        else
            cout << "-";
        cout << "" << endl;
    }
}

FS copiarFS(FS* hijo){
    FS nuevo = FS();
    nuevo.nombreFS = hijo->nombreFS;
    nuevo.directory = hijo->directory;
    nuevo.padre = hijo->padre;
    unsigned int i;
    string linea_aux;
    for(i = 0; i < hijo->listadehijos.size(); i++){
        nuevo.listadehijos.push_back(copiarFS(&hijo->listadehijos[i]));
    }
    nuevo.listadehijos = hijo->listadehijos;
    nuevo.atributo_Solo_Lectura = hijo->atributo_Solo_Lectura;
    nuevo.atributo_Oculto = hijo->atributo_Oculto;
    nuevo.autor = hijo->autor;
    nuevo.fecha = hijo->fecha;
    nuevo.contenidoArchivo.encriptado = hijo->contenidoArchivo.encriptado;
    for(i = 0; i < hijo->contenidoArchivo.lineas.size(); i++){
        linea_aux = hijo->contenidoArchivo.lineas[i];
        cout << linea_aux << endl;
        agregarLineaArchivo(&nuevo, linea_aux);
    }
    return nuevo;
}

void renombrarFS(FS* actual, string nuevonombre){
    if(actual->atributo_Solo_Lectura)
        cout << "Archivo bloqueado!" << endl;
    else{
        actual->nombreFS = nuevonombre;
        cout << "Se cambia nombre correctamente." << endl;
    }
}

string pathFS(FS* actual){
    string ruta;
    if (actual->padre != nullptr){
        ruta = pathFS(actual->padre);
        ruta.append("\\");
        return ruta.append(actual->nombreFS);
    }
    else
        return ruta;
}
