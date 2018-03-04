#include<iostream>
#include<math.h>
using namespace std;

class complex{
    double re,im;
public:
    complex(double a=0,double b=0){re=a;im=b;}
    complex(const complex &c){ this->re=c.re;this->im=c.im;}  //constructor copiere
    ~complex(){}


    void citire(){cin>>re>>im;}
    void copiere(complex a){re=a.re; im=a.im;}
    void afisare();


    double modul(){return sqrt(re*re+im*im);}


    complex operator +(complex);
    complex operator *(complex);
    void operator =(complex c){re=c.re;im=c.im;}


    friend std::ostream &operator << (std::ostream &output, complex &c);
    friend std ::istream &operator >> (std::istream &input, complex &c){input>>c.re>>c.im; return input;}

};

     std::ostream &operator<< (std::ostream &output, complex &c)
     {
        if(c.im>0)
        {output << c.re <<" + "<< c.im << "i";
        return output;}
        else if(c.im<0)
        {
        output << c.re << c.im << "i";
        return output;
        }
     }


     void complex :: afisare()
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


    complex complex :: operator +(complex c)
    {
               complex tmp;
               tmp.re=this->re+c.re;
               tmp.im=this->im+c.im;
               return tmp;
    }

     complex complex :: operator *(complex c)
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
    vector_complex(int n=0) {dim=n;v=new complex[dim];}
    vector_complex(complex a=0, int n=0){dim=n;v=new complex[dim]; for(int i=0;i<dim;i++)  v[i]=a;}
    vector_complex(const vector_complex &a){v=new complex[a.dim]; dim=a.dim; for(int i=0;i<dim;i++) v[i]=a.v[i];}   //constructor copiere
    ~vector_complex(){dim=0;delete []v;}


    void citire(){cin>>dim;v= new complex[dim]; for(int i=0;i<dim;i++) cin>>v[i];}
    void afisare(){for(int i=0;i<dim;i++) cout<<v[i]<<endl;}


    void vector_module(){vmod= new double[dim]; for(int i=0;i<dim;i++) vmod[i]=v[i].modul();}
    void sort_vector_module();
    void afisare_vmod(){for(int i=0;i<dim;i++) cout<<vmod[i]<<" "; cout<<endl;}



    complex suma();
    complex produs_scalar(vector_complex a,vector_complex b,int dim);
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
    complex a(1,1);                                                                       //constructor normal
    cin>>a;                                                                               //overload >>
    cout<<a<<endl;                                                                        //overload <<
    complex b(a);                                                                         //constructor copiere
    cout<<b<<endl;


    cout<<"Modulul lui a este: "<<a.modul()<<"\n\n";                                       //modul



    vector_complex d(3);                                                                    //constructor initializare simplu
    vector_complex c(a,3);                                                                 //constructor pt initializare cu un numar dat pe toate componentele
    c.afisare();


    d.citire();
    vector_complex e(d);
    e.afisare();                                                                            //constructor copiere



    e.vector_module();
    e.sort_vector_module();
    cout<<"\nModulele numerelor complexe introduse, in ordine crescatoare, sunt:\n";         //metodele publice pentru determinarea vectorului modulelor
    e.afisare_vmod();                                                                       //folosind metoda modulului din clasa nr complex
    cout<<"\n\n";                                                                           //sortarea lor crescatoare si afisarea



    cout<<"Suma elementelor vectorului este:\n";
    e.suma().afisare();                                                                     //metoda publica pentru afisarea sumei tuturor elementelor
    cout<<"\n\n";                                                                           // dintr-un vector complex (foloseste overloadul lui + din clasa complex)



    cout<<"Produsul scalar este:\n";
    vector_complex prod(1);
    prod.produs_scalar(d,e,3).afisare();                                                    //metoda publica pt calculul produsului scalar intre 2 vectori de lungimi egale
    cout<<"\n\n";                                                                           //foloseste overloadul lui + si * din clasa complex





}


