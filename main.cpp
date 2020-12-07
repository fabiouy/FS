#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <conio.h>
#include "Usuario.h"
#include "FS.h"
//#include "RSA.h"

using namespace std;

typedef struct usuario{
        string nombre;
        string password;
        bool esadmin = false;
} usuario;

string p, u;
vector <usuario> listadeusuarios;
FS *archivoactual;
FS archiv_aux;

void crear_root(void){
    usuario u;
    u.nombre = "root";
    u.password = "root";
    u.esadmin = true;
    listadeusuarios.push_back(u);
}

bool existeNombreUsuario(string u){
    bool existe = false;
    usuario usuario_intermedio;
    for(unsigned int j = 0; j < listadeusuarios.size(); j++){
        usuario_intermedio = listadeusuarios[j];
        existe = existe || ((usuario_intermedio.nombre.compare(u) == 0));
    }
    if (existe) {
        cout << endl;
        cout << "Nombre de usuario ya existe." << endl;
        cout << endl;
    }
    return existe;
}

void passwd(string u){
    string nuevopass;
    char ch;
    cout << "Introduzca nuevo pass:" << endl;
    ch = '*';
    ch = _getch();
    while(ch != 13){
        nuevopass.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    cout << "" << endl;
    unsigned int corredor = 0;
    while ((corredor < listadeusuarios.size()) && (listadeusuarios[corredor].nombre.compare(u) != 0)){
        corredor = corredor + 1;
    }
    listadeusuarios[corredor].password = nuevopass;
}

bool analizarcomando(vector <string> comando, bool &salida){ //analiza el comando partido mas abajo
    string s = comando[0];
    if ((s.compare("exit") == 0) || (s.compare("salir") == 0)){
        salida = true;
        return true;
    }
    if (s.compare("logout") == 0){
        salida = false;
        return false;
    }
    if (s.compare("user") == 0){
        string s1 = comando[1];
        string s2 = comando[2];
        string s3 = comando[3];
        usuario u;
        u.nombre = s1;
        u.password = s2;
        u.esadmin = false;
        if (s.compare("admin") == 0)
            u.esadmin = true;

        salida = false;
        if (!existeNombreUsuario(s1))
            listadeusuarios.push_back(u);
        return true;
    }
    if (s.compare("mkdir") == 0){
        string s1 = comando[1];
        if(!existeArchivo(s1, archivoactual)){
            crearDirectorio(s1, archivoactual);
            asignarAutor(obtenernHijo(s1, archivoactual), u);
        }
        else{
            cout << "Ya existe directorio o archivo." << endl;
        }
        return true;
    }
    if (s.compare("tree") == 0){
        dfs_tree(archivoactual, contador);
        return true;
    }
    if (s.compare("dir") == 0){
        listarhijos(archivoactual, false);
        return true;
    }
    if (s.compare("passwd") == 0){
        passwd(u);
        return true;
    }
    if (s.compare("every") == 0){
        listarhijos(archivoactual, true);
        return true;
    }
    if (s.compare("mkfile") == 0){
        string s1 = comando[1];
        if(!existeArchivo(s1, archivoactual)){
            crearArchivo(s1, archivoactual);
            asignarAutor(obtenernHijo(s1, archivoactual), u);
        }
        else{
            cout << "Ya existe directorio o archivo." << endl;
        }
        return true;
    }
    if (s.compare("cp") == 0){
        string s1 = comando[1];
        archiv_aux = copiarFS(obtenernHijo(s1, archivoactual));
        archiv_aux.nombreFS.append("_Copia");
        agregarHijo(archivoactual, archiv_aux);
        return true;
    }
    if (s.compare("rm") == 0){
        string s1 = comando[1];
        sacarHijo(archivoactual, s1);
        return true;
    }
    if (s.compare("rename") == 0){
        string s1 = comando[1];
        string s2 = comando[2];
        renombrarFS(obtenernHijo(s1, archivoactual), s2);
        return true;
    }
    if (s.compare("sl") == 0){
        string s1 = comando[1];
        hacerSoloLecturafs(obtenernHijo(s1, archivoactual));
        return true;
    }
    if (s.compare("crypt") == 0){
        string s1 = comando[1];
        hacerEncriptadofs(obtenernHijo(s1, archivoactual), u);
        return true;
    }
    if (s.compare("hd") == 0){
        string s1 = comando[1];
        hacerOcultofs(obtenernHijo(s1, archivoactual));
        return true;
    }
    if (s.compare("addline") == 0){
        string s1 = comando[1];
        string s2;
        cout << "Escriba el texto de la linea: ";
        std::getline(std::cin, s2);
        agregarLineaArchivo(obtenernHijo(s1, archivoactual), s2);
        return true;
    }
    if (s.compare("rmline") == 0){
        string s1 = comando[1];
        int s2;
        cout << "Escriba el numero de linea a eliminar: ";
        cin >> s2;
        removerLineaArchivo(obtenernHijo(s1, archivoactual), s2);
        return true;
    }
    if (s.compare("attrib") == 0){
        string s1 = comando[1];
        mostrarAtributos(obtenernHijo(s1, archivoactual));
        return true;
    }
    if (s.compare("show") == 0){
        string s1 = comando[1];
        mostrarArchivo(obtenernHijo(s1, archivoactual));
        return true;
    }
    if (s.compare("path") == 0){
        cout << pathFS(archivoactual) << endl;
        return true;
    }
    if (s.compare("cd") == 0){
        string s1 = comando[1];
        if (s1.compare("..") == 0){
            archivoactual = obtenerPadre(archivoactual);
        }
        else{
            archivoactual = obtenernHijo(s1, archivoactual);
        }
        return true;
    }
    if (s.compare("listar") == 0){ // Lista usuarios
        usuario usuario_intermedio;
        for(unsigned int j = 0; j < listadeusuarios.size(); j++){
            usuario_intermedio = listadeusuarios[j];
            cout << usuario_intermedio.nombre << '\n';
        }
        salida = false;
        return true;
    }
    if ((s.compare("?") == 0) || (s.compare("help") == 0)){
        cout << "Comandos permitidos:" << endl;
        cout << "   exit, salir - Salida del sistema." << endl;
        cout << "   logout - Sale de sesion." << endl;
        cout << "   user xxx yyy zzz - crear usuario con nombre xxx pass yyy y tipo zzz." << endl;
        cout << "   listar - Lista usuarios del sistema." << endl;
        cout << "   mkdir DIR1 - crea directorio DIR1." << endl;
        cout << "   mkfile FILE1 - crea archivo FILE1." << endl;
        cout << "   addline FILE1- Agrega linea de texto a un archivo al final." << endl;
        cout << "   rmline FILE1- Elimina una linea especifica de un archivo." << endl;
        cout << "   show FILE - Muestra contenido de archivos." << endl;
        cout << "   dir - Lista archivos de la carpeta actual." << endl;
        cout << "   tree - Muestra arbol de directorios." << endl;
        cout << "   cd FOLDER - Accede a la carpeta FOLDER o con .. sube un nivel." << endl;
        cout << "   hd FILE1 - Deja un archivo File oculto." << endl;
        cout << "   sl FILE1 - Deja un archivo como solo lectura." << endl;
        cout << "   every - muestra todos los archivos esten o no ocultos." << endl;
        cout << "   crypt FILE1- Encripta el archivo FILE o lo desencripta." << endl;
        cout << "   attrib FILE1- Muestra atributos de archivo/carpeta FILE1." << endl;
        cout << "   rename FILE1- Renombra archivo/carpeta FILE1." << endl;
        cout << "   cp FILE1- Copia el recurso FILE1 en la carpeta actual a FILE1_Copia." << endl;
        cout << "   rm FILE1- Borra el recurso FILE1 y su contenido." << endl;
        cout << "   passwd - Cambia la clave del usuario actual." << endl;
        cout << "   path - Muestra la ruta actual." << endl;
        cout << "   lock FILE1 - Bloquea/desbloquea FILE1." << endl;
        cout << "   ?, help - Muestra esta ayuda." << endl;
        salida = false;
        return true;
    }
    else{
        cout << "*****¡¡¡Comando incorrecto!!!*****" << endl;
        salida = false;
        return true;
    }
}

bool existe_usuario(string u, string p){
    bool existe = false;
    usuario usuario_intermedio;
    for(unsigned int j = 0; j < listadeusuarios.size(); j++){
        usuario_intermedio = listadeusuarios[j];
        existe = existe || ((usuario_intermedio.nombre.compare(u) == 0) && (usuario_intermedio.password.compare(p) == 0));
    }
    if (existe) {
        cout << endl;
        cout << "Login correcto" << endl;
        cout << endl;
    }
    return existe;
}

bool loginroot(string usuario, string pass){ //login
    return (existe_usuario(usuario, pass));
}

vector <string> comandocompleto(string comando){ //toma el comando y lo mete en un vector partido
    vector <string> comandoenvector;
    stringstream partido(comando);
    string partecomando;
    while (getline(partido, partecomando, ' ')) {
        comandoenvector.push_back(partecomando);
        //cout << partecomando << endl;
    }
    return comandoenvector;
}

void cls(void){ //limpia pantalla
    system("cls||clear");
}

int main(){
    string comando;
    comando = "";
    char ch;
    vector <string> comandovector;
    crear_root();
    bool exit = false;
    FS filenuevo;
    filenuevo.nombreFS = "\\"; // Se crea el directorio raiz
    filenuevo.padre = NULL;
    filenuevo.directory = true;
    archivoactual = &filenuevo;
    while (!exit){
        bool comandovalido = true;
        p = "";
        cls();
        cout << "LOGIN" << endl;
        cout << "Usuario:" << endl;
        cin >> u;
        cout << "Password:" << endl;
        ch = '*';
        ch = _getch();
        while(ch != 13){
            p.push_back(ch);
            cout << '*';
            ch = _getch();
        }
        bool log = loginroot(u, p);
        while(!log){
            cout << "Credenciales invalidas! Reintente..." << endl;
            p = "";
            cout << "Usuario:" << endl;
            cin >> u;
            cout << "Password:" << endl;
            ch = '*';
            ch = _getch();
            while(ch != 13){
                p.push_back(ch);
                cout << '*';
                ch = _getch();
            }
            log = loginroot(u, p);
        }
        while (comandovalido && !exit){
            cout << "Comando ::  ";
            cin.clear(); cin.sync();
            std::getline(std::cin, comando);
            if (comando.size() > 0){
                comandovector = comandocompleto(comando);
                comandovalido = analizarcomando(comandovector, exit);
            }
        }
    }
    return 0;
}
