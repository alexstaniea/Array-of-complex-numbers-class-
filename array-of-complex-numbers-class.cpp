//STANIEA ALEXANDRU -- PROIECT 1 POO -- GRUPA 132

#include<iostream>
#include<math.h>
using namespace std;

class complex{
    double re,im;
public:
    complex(double a=0,double b=0){re=a;im=b;}                                                             //constructor pe valori
    complex(const complex &c){ this->re=c.re;this->im=c.im;}                                               //constructor copiere
    ~complex(){}                                                                                          //destructor


    void citire(){cin>>re>>im;}                                                                           //alternative de afisare si scriere
    void afisare();


    double modul(){return sqrt(re*re+im*im);}                                                              //metoda pt modul


    complex operator +(complex);                                                                           //supraincarcari operatii
    complex operator *(complex);
    void operator =(complex c){re=c.re;im=c.im;}


    friend std::ostream &operator << (std::ostream &output, complex &c);
    friend std ::istream &operator >> (std::istream &input, complex &c){input>>c.re>>c.im; return input;}    //supraincarcare >>

};

     std::ostream &operator<< (std::ostream &output, complex &c)                                             //supraincarcare <<
     {
        if(c.im>0)
        {
            if(c.re==0)
            {
                output << c.im << "i";
                return output;
            }
            else
            {
                output << c.re <<" + "<< c.im << "i";
                return output;
            }
        }
        else if(c.im<0)
        {
            if(c.re==0)
            {
                output << c.im << "i";
                return output;
            }
            else
            {
                output << c.re << c.im << "i";
                return output;
            }
        }
        else if(c.re!=0 && c.im==0)
        {
            output << c.re;
            return output;
        }
        else if(c.re==0 && c.im==0)
        {
            output<<"0";
            return output;
        }
     }


     void complex :: afisare()                                                                        //alternativa de afisare
     {
            if(re==0 && im!=0)
            {
                if(im>0)
                cout<<"+ "<<im<<"*i\n";
                else
                cout<<"- "<<-im<<"*i\n";
            }
            else if(re!=0 && im==0)
                cout<<re<<"\n";
            else if(re!=0 && im!=0)
            {
            if(im>0)
                cout<<re<<" + "<<im<<"*i\n";
            else
                cout<<re<<" - "<<-im<<"*i\n";
            }
            else if(re==0 && im==0)
                cout<<"0"<<"\n";
     }


    complex complex :: operator +(complex c)                                                                 //supraincarcare +
    {
               complex tmp;
               tmp.re=this->re+c.re;
               tmp.im=this->im+c.im;
               return tmp;
    }

     complex complex :: operator *(complex c)                                                               //supraincarcare *
    {
               complex tmp;
               tmp.re=(re*c.re)-(im*c.im);
               tmp.im=(re*c.im)+(im*c.re);
               return tmp;
    }


class vector_complex{

friend class complex;

    int dim;
    complex *v;
    double *vmod;    //vector module

public:
    vector_complex(int n=0) {dim=n;v=new complex[dim];}                                                             //constructor simplu
    vector_complex(complex a, int n=0){dim=n;v=new complex[dim]; for(int i=0;i<dim;i++)  v[i]=a;}                   //constructor al unui vector initializat cu un element
    vector_complex(const vector_complex &a){v=new complex[a.dim]; dim=a.dim; for(int i=0;i<dim;i++) v[i]=a.v[i];}   //constructor copiere
    ~vector_complex(){dim=0;delete []v;}                                                                            //destructor


    void citire(){cout<<"dim="<<endl; cin>>dim;v= new complex[dim]; for(int i=0;i<dim;i++) cin>>v[i];}                //alternative la citire si scriere
    void afisare(){for(int i=0;i<dim;i++) cout<<v[i]<<endl;}
    int getdim(){return dim;}                                                                                       //metoda ce returneaza dimensiunea

    void vector_module(){vmod= new double[dim]; for(int i=0;i<dim;i++) vmod[i]=v[i].modul();}                          //metoda ce calculeaza vectorul modulelor
    void sort_vector_module();                                                                                          //metoda ce sorteaza crescator modulele
    void afisare_vmod(){for(int i=0;i<dim;i++) cout<<vmod[i]<<" "; cout<<endl;}                                         //metoda de afisare a vectorului modulelor


    friend istream& operator >>(istream& i,vector_complex &a){i>>a.dim; for(int j=0;j<a.dim;j++) i>>a.v[j]; return i;}     //supraincarcare >>
    friend ostream& operator <<(ostream& o,vector_complex &a){for(int j=0;j<a.dim;j++) o<<a.v[j]<<endl; return o;}          //supraincarcare <<


    complex suma();                                                                                                         //metoda pt calculul sumei a doi vectori
    complex produs_scalar(vector_complex a,vector_complex b,int dim);                                                       //metoda pt calculul produsului scalar a doi vectori
};


    void  vector_complex :: sort_vector_module()
    {
        for(int i=0;i<dim-1;i++)
         for(int j=i+1;j<dim;j++)
            if(vmod[i]>vmod[j])
               swap(vmod[i],vmod[j]);
    }


    complex vector_complex :: suma()
    {
        complex sum(0,0);
        for(int i=0;i<dim;i++)
            sum=sum+v[i];
        return sum;
    }


    complex vector_complex :: produs_scalar(vector_complex a,vector_complex b,int dim)
    {
        complex *c=new complex[dim];
        complex suma(0,0);
         for(int i=0;i<dim;i++)
            c[i]=a.v[i]*b.v[i];
         for(int i=0;i<dim;i++)
            suma=suma+c[i];
         return suma;
    }


int main()
{
    int ok=0,nr,num,number,i;


    cout<<"LISTA OPTIUNI:\n\n";
    cout<<"\tMENIU VECTOR NUMERE COMPLEXE:\n\n";
    cout<<"0) Creati un vector de vectori;"<<endl;
    cout<<"1) Creati un vector de numere complexe initializat cu un singur element;"<<endl;
    cout<<"2) Creati un vector de numere complexe cu elemente diferite;"<<endl;
    cout<<"3) Afisati vectorul modulelor;"<<endl;
    cout<<"4) Afisati vectorul modulelor in ordine crescatoare;"<<endl;
    cout<<"5) Afisati suma tuturor elementelor din vectorul complex;"<<endl;
    cout<<"6) Creati doi vectori cu numere complexe de lungimi egale si calculati produsul scalar;"<<endl;
    cout<<"7) Copiati vectorul in alt vector de numere complexe;\n\n"<<endl;
    cout<<"\tMENIU NUMERE COMPLEXE:\n\n";
    cout<<"8) Creati un numar complex;"<<endl;
    cout<<"9) Copiati numarul complex;"<<endl;
    cout<<"10) Afisati modulul numarului complex;"<<endl;
    cout<<"11) Faceti suma a doua numere complexe;"<<endl;
    cout<<"12) Faceti produsul a doua numere complexe;"<<endl;
    cout<<"13) Atribuiti unui alt numar complex, numarul dat;\n\n"<<endl;
    cout<<"-----------------------------------------------------------------------------------------\n\n";

    complex a,s;
    vector_complex d(100);
    vector_complex *f;

    while(ok==0)
    {
        cout<<"Selectati optiunea dorita:"<<endl;
        int n;
        cin>>n;


        switch(n)
        {
            case 0:
            {
                cout<<"Cati vectori doriti sa creati?\n";
                cin>>number;

                f=new vector_complex[number];

                cout<<"Introduceti numarul de elemente ale vectorilor in ordine, si dupa fiecare dimensiune elementele lor (parte reala si imaginara)\n";
                for(i=0;i<number;i++)
                {
                    cin>>f[i];
                }

                cout<<"Vectorii sunt: \n";
                for(i=0;i<number;i++)
                {
                    cout<<f[i];
                }

                cout<<"\n\n";
                break;
            }

            case 1:
            {
                cout<<"Introduceti numarul de elemente ale vectorului:"<<endl;
                cin>>nr;
                cout<<"Introduceti elementul de initializare (parte reala si imaginara):\n";
                cin>>a;
                vector_complex c(a,nr);
                d=c;
                cout<<"Vectorul de numere complexe este:\n";
                cout<<d;
                break;
            }

            case 2:
            {
                cout<<"Introduceti numarul de elemente ale vectorului si apoi elementele lui in ordine (parte reala si imaginara)"<<endl;
                cin>>d;
                cout<<"Vectorul de numere complexe este:\n";
                cout<<d;
                break;
            }

            case 3:
            {
                d.vector_module();
                cout<<"\nModulele numerelor complexe introduse sunt:\n";
                d.afisare_vmod();
                break;
            }

            case 4:
            {

                d.vector_module();
                d.sort_vector_module();
                cout<<"\nModulele numerelor complexe introduse, in ordine crescatoare, sunt:\n";
                d.afisare_vmod();
                break;
            }

            case 5:
            {
                cout<<"Suma elementelor vectorului este:\n";
                d.suma().afisare();
                cout<<"\n";
                break;
            }

            case 6:
            {
                cout<<"Introduceti numarul de elemente ale celui de-al doilea vector si apoi elementele lui in ordine (parte reala si imaginara)\n\n"<<endl;
                vector_complex h(100);
                cin>>h;

                if(h.getdim()<=d.getdim())
                {
                    num=h.getdim();
                }
                else
                {
                    num=d.getdim();
                }

                cout<<"Produsul scalar al celor doi vectori este:\n";
                vector_complex prod(1);
                prod.produs_scalar(d,h,num).afisare();
                cout<<"\n\n";
                break;
            }

            case 7:
            {
                    vector_complex e(d);
                    cout<<"Noul vector este: "<<endl;
                    cout<<e;
                    cout<<"\n\n";
                    break;
            }

            case 8:
            {
                    cout<<"Introduceti un numar complex (parte reala si imaginara):\n";
                    cin>>a;
                    cout<<"Numarul este:\n";
                    cout<<a<<"\n\n";
                    break;
            }

            case 9:
            {
                complex b;
                b=a;
                cout<<"Noul numar complex este:\n"<<b<<"\n\n";
                break;
            }

            case 10:
            {
                    cout<<"Modulul numarului complex este:\n"<<a.modul()<<"\n\n";
                    break;
            }

            case 11:
            {
                    complex sum(0,0);
                    cout<<"Introduceti al doilea numar complex (parte reala si imaginara):\n";
                    cin>>s;
                    sum=a+s;
                    cout<<"Suma celor 2 numere este:\n"<<sum<<"\n\n";
                    break;
            }

            case 12:
            {
                    complex pr(0,0);
                    pr=a*s;
                    cout<<"Produsul celor 2 numere este:\n"<<pr<<"\n\n";
                    break;
            }

            case 13:
            {
                    complex q;
                    q=a;
                    cout<<"Noul numar complex este: "<<q<<"\n\n";
                    break;
            }

            default:
            {
                cout<<"Optiune indisponibila!\n";
                break;
            }
        }

        cout<<"Doriti sa iesiti din program? (0/1)"<<endl;
        cin>>ok;
    }
}
