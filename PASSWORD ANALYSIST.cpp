/*******************************************************************************
Yaniel Molina
George Melendez
11/ 18 / 2024
Password analysist
*******************************************************************************/
/*Yaniel*/
//George//
#include <iostream>
#include <string>
#include <random>  
#include <cctype>
#include <algorithm>
using namespace std;

/*esta porcion fue echa por Yaniel y George, de un tamplate de:*/
/*sitema de recomendacion con patrones random las asigancion de valores abajo*/
string passRecomende(int largo) {
    string lttmayor = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lttmenor = "abcdefghijklmnopqrstuvwxyz";
    string digitnm = "0123456789";
    string specialcar = "!@#$%^&*?()<>?";
    string alltogheter = lttmayor + lttmenor + digitnm + specialcar;
    /*Aqui vemos la semilla de la funcion donde los valores tiene parametros de size*/
    random_device rd;
    mt19937 pas(rd());
    uniform_int_distribution<> distlttmay(0, lttmayor.size() - 1);
    uniform_int_distribution<> distlttmen(0, lttmenor.size() - 1);
    uniform_int_distribution<> distdig(0, digitnm.size() - 1);
    uniform_int_distribution<> distspec(0, specialcar.size() - 1);
    uniform_int_distribution<> distallt(0, alltogheter.size() - 1);
    /*La sumatoria de las variables con valor de las semillias*/
    string pasword;
    pasword += lttmayor[distlttmay(pas)];
    pasword += lttmenor[distlttmen(pas)];
    pasword += digitnm[distdig(pas)];
    pasword += specialcar[distspec(pas)];

    for (int i = 4; i < largo; ++i) {
        pasword += alltogheter[distallt(pas)];
    }
    /* usamos una funcion de algorithim llamda para hacer un shuffle en los valores*/
    shuffle(pasword.begin(), pasword.end(), pas);
    return pasword;

}

int main()
{
    string password;
    int fuerza = 0;
    /*Interfase que vera el ususario con los requisistos para el password*/
    cout << "Los parametros para cumplir son:\n";
    cout << "Su Password debe tener minimo 12 caracteres.\n";
    cout << "Letra mayuscula y minuscula.\n";
    cout << "Debe tener un digito(numero).\n";
    cout << "Caracteres especuiales.\n";
    cout << "************************************************************************************************************************\n";
    cout << "Entra tu password: \n";
    cin >> password;

    //se pone en false para luego ver si cumple y de ser asi lo cambia a true mas adelante//
    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;

    //aqui ponemos password como caracter c para evaluar si cumple y cambiar de falso a true
    //libreria de cctype
    for (char c : password) {
        if (islower(c)) hasLower = true;
        else if (isupper(c)) hasUpper = true;
        else if (isdigit(c)) hasDigit = true;

        else hasSpecial = true;

        if (hasLower && hasUpper && hasDigit && hasSpecial)
            break;
    }

    //sistema de puntuaje para el strength del password
    if (password.length() >= 12) fuerza++;
    if (hasLower) fuerza++;
    if (hasUpper) fuerza++;
    if (hasDigit) fuerza++;
    if (hasSpecial) fuerza++;


    cout << "Su nivel de fuerza es: " << fuerza << "/5 \n";
    cout << "Luego de analizar su password, determinamos que es: \n";


    /*Estos son los niveles de fuerza que le saldra al ususario*/
     //si no cumple con los requisitos
    if (fuerza == 5) {
        cout << "muy seguro.";
    }
    else if (fuerza == 4) {
        cout << "Parcialmente Moderada.";
    }
    else if (fuerza == 3) {
        cout << "Moderada.\n";
    }
    else if (fuerza == 2) {
        cout << "Parcialmente inestable.\n";
    }
    else if (fuerza == 1) {
        cout << "completamente inestable.\n";
    }
    /*Aqui en caso que no cumpla con un 4/5 como minimo le dara este menu */
   //En  se le dara un segundo intento al menos que la perdona escoja el recomendado//
    if (fuerza <= 3) {
        int opt;
        cout << "Desea Intentar otro password o uno recomendado:para intentar 1, para recomendado 2.\n";
        cin >> opt;
        cout << "************************************************************************************************************************\n";
        if (opt>3) {
            cout << "input invalido";
        }
        switch (opt) {
        case 1:
            cout << "Entra tu password: \n";
            cin >> password;
            if (password.length() >= 12) fuerza++;
            if (hasLower) fuerza++;
            if (hasUpper) fuerza++;
            if (hasDigit) fuerza++;
            if (hasSpecial) fuerza++;
            cout << "Su nivel de fuerza es: " << fuerza << "/5 \n";
            cout << "Luego de analizar su password por segunda vez, determinamos que: \n";

            if (fuerza == 5 or fuerza == 4) {
                cout << "Su password es seguro.";
            }
            else if (fuerza == 3) {
                cout << "Su password es moderado.";
            }
            else if (fuerza == 2 or fuerza == 1) {
                cout << "su password sigue siendo debil.\n";
                cout << "Debido a que su password sigue siendo debil le daremos uno recomendado:\n";
                cout << passRecomende(12);
            }
            break;

        case 2:
            cout << "password recomendado\n";
            cout << "Su password recomendado es:\n";
            cout << passRecomende(12);
            break;
        }
    }


    return 0;
}
