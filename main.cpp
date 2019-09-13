#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

int main()
{
    int num,producto,codigo,dia,mes,anho,signo;
    float monto,costo,cantidad;
    char mov,tipo,c;


    /*
     * Archivos de Lectura de datos
     * */
    ifstream archmov("movimientos.txt", ios::in);
    if(!archmov) {
        cout<<"ERROR: no se abrio el archivo movimientos.txt"<<endl;
        exit(1);
    }
    ifstream archext("exterior.txt", ios::in);
    if(!archext) {
        cout<<"ERROR: no se abrio el archivo movimientos.txt"<<endl;
        exit(1);
    }
    ifstream archnac("nacional.txt", ios::in);
    if(!archnac) {
        cout<<"ERROR: no se abrio el archivo movimientos.txt"<<endl;
        exit(1);
    }


    /*
     * Archivo de Escritura de datos
     */
    ofstream archrep("reporte.txt", ios::out);
    if(!archrep) {
        cout<<"ERROR: no se abrio el archivo reporte.txt"<<endl;
        exit(1);
    }




    while(1)
    {
        //Leo el producto
        archmov >> producto;

        //Si se levanta la bandera de EOF() Termino el programa
        if(archmov.eof()) break;

        //Nueva linea en el reporte y escribo el producto con su codigo
        archrep << endl;
        archrep <<"Producto:"<< producto << endl;


        while(1)
        {
            //Lectura del dia
            if(archmov >> dia >> c >> mes >> c >> anho){
                archrep <<setfill('0') <<setw(2) << dia<<'/' <<setfill('0') << setw(2)<< mes<<'/'  << setw(4) << anho;
                archrep.fill(' ');
                archmov >> mov >> cantidad >> tipo;

                if(mov=='I')
                    signo=1;
                else
                    signo=-1;

                if(tipo=='E')
                {   archext.clear();
                    archext.seekg(0,ios::beg);
                    while(1)
                    {
                        archext >> codigo >> costo;
                        if(archext.eof()) break;
                        if(codigo==producto)
                        {
                            archrep <<setprecision(2)<<fixed<<  setw(10) << signo*cantidad << setw(10) <<costo << setw(10) << signo*costo*cantidad << endl;
                            break;
                        }
                        else
                            costo=-1;

                    }
                    if(costo==-1)
                        archrep <<setprecision(2)<<fixed << setw(10) << signo*cantidad << setw(20) << "sin costo" << endl;
                }
                if(tipo=='P')
                {   archnac.clear();
                    archnac.seekg(0,ios::beg);
                    while(1)
                    {
                        archnac >> codigo >> costo;
                        if(archnac.eof()) break;
                        if(codigo==producto)
                        {
                            archrep << setprecision(2) <<fixed << setw(10) << signo*cantidad << setw(10) <<costo << setw(10) << signo*costo*cantidad << endl;
                            break;
                        }
                        else
                            costo=-1;
                    }
                    if(costo==-1)
                        archrep <<setprecision(2)<<fixed << setw(10) << signo*cantidad << setw(20) << "sin costo" << endl;
                }
                c=archmov.get();
                if(c=='\n') break;

            }
        }
    }
}

