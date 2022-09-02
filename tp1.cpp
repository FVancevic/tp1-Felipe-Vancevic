#include <iostream>
#include <fstream>

using namespace std;

void mostrar(string vec1[],int vec2[], int dim){
    for(int i=0;i<dim;++i)
        cout<<vec2[i]<<": "<<vec1[i]<<endl;
}

void mostrarmat(float mat[][5],int nfil){
    const int ncol{5};
    for(int i=0;i<nfil;++i){
        for(int j=0;j<ncol;j++){
            cout<<mat[i][j]<<'\t';
        }
        cout<<endl;
    }
}

void copiar(string vec1[],string vec2[], int dim){      //para no alterar el valor del vector de nombres de productos
    for(int i=0;i<dim;++i){
        vec1[i]=vec2[i];
    }
}

void mayor13(float mat[][5],int nfil, string veccli[],string vecprod[]){    //mostrar para el punto 1 los productos que por cliente superan los 13000kg
    const int ncol{5};

    for(int i=0;i<nfil;++i){
        cout<<veccli[i]<<": ";
        for(int j=0;j<ncol;++j){
            if(mat[i][j]>13000){
                cout<<vecprod[j]<<", ";
            }
        }
        cout<<endl;
    }
}

void cantmay13(float mat[][5],int nfil, int vec[]){     //cantidad de productos que superan 13000kg por cliente
    const int ncol{5};
    for(int i=0;i<nfil;++i){
        for(int j=0;j<ncol;j++){
            if(mat[i][j]>13000){
                vec[i]++;
            }
        }
    }
}

int mayor(int vec[],int dim){   //para encontrar cual es el cliente con mayor cantidad de productos que superen los 13000kg
    int may{0};
    for(int i=1;i<dim;++i){
        if(vec[i]>vec[may]){
            may=i;
        }
    }
    return may;
}

void kmrecor(float mat[][5],int maycant,float vec[]){       //para pasar los valores de los km acumulados por producto a un vector para el cliente con mayor cantidad de tipos de productos que superen los 13000kg
    const int ncol{5};

    for(int j=0;j<ncol;j++){
        vec[j]=mat[maycant][j];
    }
}

void ordxbur(string prod[],float vec[], int dim){           //para ordenar de manera ascendente los nombres de los productos con los km para el punto 2
    float aux1{};
    string aux2{};
    for(int i=0;i<dim-1;++i){
        for(int j=0;j<dim-1;++j){
            if(vec[j]>vec[j+1]){
                aux1=vec[j];
                vec[j]=vec[j+1];
                vec[j+1]=aux1;
                aux2=prod[j];
                prod[j]=prod[j+1];
                prod[j+1]=aux2;
            }
        }
    }
}

void ordxbur(int cod[],float vec[], int dim){           //para ordenar de manera ascendente los codigos de los productos con los km para el punto 3
    float aux1{};
    int aux2{};
    for(int i=0;i<dim-1;++i){
        for(int j=0;j<dim-1;++j){
            if(vec[j]>vec[j+1]){
                aux1=vec[j];
                vec[j]=vec[j+1];
                vec[j+1]=aux1;
                aux2=cod[j];
                cod[j]=cod[j+1];
                cod[j+1]=aux2;
            }
        }
    }
}

void mostrarp2(string vec1[],float vec2[],int dim){     //para mostrar en pantalla el nuevo orden para el punto 2
    for(int i=0;i<dim;++i){
        cout<<vec1[i]<<": "<<vec2[i]<<endl;
    }
}

int main(){
    const int ncli{8};              //cantidad de clientes
    const int nprod{5};             //cantidad de productos
    float kgcliprod[ncli][nprod]{}; //matriz para almacenar los kg de cada prod por cliente
    float kmcliprod[ncli][nprod]{}; //matriz para almacenar los km de cada prod por cliente
    int cantprodcli[ncli]{};        //vector para almacenar la cantidad de productos que superan 13000kg por cliente

    string cliente[ncli];           //vector para almacenar los nombres de los clientes
    string producto[nprod];         //vector para almacenar los nombres de los productos

    int veccli[ncli]{};
    for(int i=0;i<ncli;++i){
        veccli[i]=i;
    }

    //Leo el archivo de clientes y productos
    ifstream archilec;
    archilec.open("Nombres.txt");
    if(!archilec){
        cout<<"Error al tratar de abrir el archivo de nombres"<<endl;
        return 1;
    }
    for(int i=0;i<ncli;++i){
        archilec>>cliente[i];
    }
    for(int i=0;i<nprod;++i){
        archilec>>producto[i];
    }

    mostrar(cliente,veccli,ncli);
    cout<<"\n=====================================\n"<<endl;
    mostrar(producto,veccli,nprod);

    archilec.close();

    //Leo el archivo de los datos de produccion
    archilec.open("Datos.txt");
    if(!archilec){
        cout<<"Error al tratar de abrir el archivo de produccion"<<endl;
        return 1;
    }

    int icli,iprod;
    float peso,dist;
    while(archilec>>icli>>iprod>>peso>>dist){
        kgcliprod[icli][iprod]+=peso;
        kmcliprod[icli][iprod]+=dist;
    }
    archilec.close();

    cout<<"\n=================Peso Cli/Prod====================\n"<<endl;
    mostrarmat(kgcliprod,ncli);
    cout<<"\n=================Dist Cli/Prod====================\n"<<endl;
    mostrarmat(kmcliprod,ncli);
    cout<<endl;

    //Punto 1
    cout<<"\n=====================================\n"<<endl;
    cout<<"\nListado por Clientes, de los tipos de productos que superen los 13000kg acumulados: "<<endl;
    mayor13(kgcliprod,ncli,cliente,producto);
    cout<<endl;

    //Punto 2
    cantmay13(kgcliprod,ncli,cantprodcli); //cantidad de productos que superan 13000 kg por cliente

    int imay=mayor(cantprodcli,ncli);
    cout<<"El cliente con mayor cantidad de productos con peso superior a 13000 es: "
        <<cliente[imay]<<endl;
    
    float veckmacum[nprod];     //vector de km acumulados para el cliente con mayor tipos de productos que superen los 13000kg
    string prodnom[nprod]{};    //para no alterar el vector de nombre de productos

    cout<<"\nListado de km recorridos por tipo de producto (ascendente): "<<endl;
    copiar(prodnom,producto,nprod);     
    kmrecor(kmcliprod,imay,veckmacum);
    ordxbur(prodnom,veckmacum,nprod);
    mostrarp2(prodnom,veckmacum,nprod);
    cout<<endl;
    
    //Punto 3
    float v2kmacum[nprod];      //Nueva variable similar a veckmacum para ordenarla junto con el vector de codigo de prod, necesitaba que se ordene para esto **
    kmrecor(kmcliprod,imay,v2kmacum); //podria haberme ahorrado esta nueva variable ordenando codprod cuando ordene veckmacum en el punto 2
    int cont{};
    int codprod[nprod];
    for(int i=0;i<nprod;++i){
        codprod[i]=i;
    }
    ordxbur(codprod,v2kmacum,nprod);
    ifstream archn;
    archn.open("Datos.txt");
    while(archn>>icli>>iprod>>peso>>dist){
        if(iprod==codprod[nprod-1]){   //**
            cont++;
        }
    }
    archn.close();
    cout<<"\nCantidad de entregas para el tipo de producto "<<prodnom[nprod-1]<<": "<<cont<<endl;

    return 0;
}