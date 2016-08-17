/* Universidade Presbiteriana Mackenzie
 * Ciencia da Computacao 4N - Noturno
 * Trabalho de Analise Numerica II - Paulino 
 * Antonio Costa Carnaiba Filho  TIA: 3066456-1
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TOL 0.0001
#define e 2.7182818284590452353602874

//y´=f(t,y)
double f(double t, double y, int *eq);
double freal(double t, int *eq);


int main(int argc, char *argv[])
{
    //Parametros a serem atribuidos para cada equação.
    double t,w,h,b; 
    //Parametros dado do exercicio
    double hmax,hmin;
    hmax = 0.25;
    hmin = 0.05;
    
    double k1,k2,k3,k4,k5,k6;
    
    //Parametros a serem calculado para cada iteração.
    double R,deltag;    
    int FLAG;
    
    /*Qual equação a ser calculada,
     *Conjunto 5.5, p.250
     *eq: 0, 1, 2, 3 (item a, b, c, d) 
     */
    int eq;
    //Conta quantas iterações feita para cada equação
    int i = 0;
    for(eq = 0; eq < 4; eq++)
    {
        R = 0.0;        
        deltag = 0.0;
        
        if(eq == 0)
        {
           t = 0.0; w = 0.0; h = hmax; b = 1.0;   
        }
        else if(eq == 1)
        {
            t = 2.0;  w = 1.0;  h = hmax; b = 3.0;
        }
        else if(eq == 2)
        {
           t = 1.0; w = 2.0; h = hmax; b = 2.0;
        }    
        else if(eq == 3)
        {
           t = 0.0; w = 1.0; h = hmax; b = 1.0;   
        }
    
        FLAG = 1;
        i = 1;
        while(FLAG == 1)
        {
           k1 = h*f(t,w,&eq);    
           k2 = h*f(t+(1.0/4.0)*h,w+(1.0/4.0)*k1,&eq);    
           k3 = h*f(t+(3.0/8.0)*h,w+(3.0/32.0)*k1+(9.0/32.0)*k2,&eq);
           k4 = h*f(t+(12.0/13.0)*h,w+(1932.0/2197.0)*k1-(7200.0/2197.0)*k2+(7296.0/2197.0)*k3,&eq);    
           k5 = h*f(t+h,w+(439.0/216.0)*k1-8*k2+(3680.0/513.0)*k3-(845.0/4104.0)*k4,&eq);
           k6 = h*f(t+0.5*h,w-(8.0/27.0)*k1+2*k2-(3544.0/2565.0)*k3+(1859.0/4104.0)*k4-0.275*k5,&eq);
           R = abs((1.0/360.0)*k1-(128.0/4275.0)*k3-(2197.0/75240.0)*k4+0.02*k5+(2.0/55.0)*k6);
           if(R <= TOL)
           {
             t = t + h;
             w = w + (25.0/216.0)*k1+(1408.0/2565.0)*k3+(2197.0/4104.0)*k4-0.2*k5;
             printf("\n i: %d \n t: %0.7f \n w: %0.7f \n h: %0.7f\n y: %0.7f\n ",i,t,w,h,freal(t,&eq));
             i++;
           }
           deltag = 0.84*pow((TOL/R),0.25);
           
           if(deltag <= 0.1)
             h = 0.1*h;         
           else if(deltag >= 4)
             h = 4*h;
           else         
              h=deltag*h;                              
           if(h > hmax)
             h = hmax;
           if(t >= b)
             FLAG = 0;
           if((t+h)>b)
             h = b-t;
           if(h < hmin)
           {
             FLAG = 0;
             printf("\n h min ultrapassado\n ");               
           }
       
         }


    }
  system("PAUSE");	
  return 0;
}


double f(double t, double y, int *eq)
{
   if(*eq == 0)
   {
       if(t == 0)
         return 0;  
       else
           return ((y/t) - pow((y/t),2));
   }

   else if (*eq == 1)
      return (1 + pow((t-y),2));  
   else if(*eq == 2)
       return (1 + (y/t));
   else
       return (cos(2.0*t) + sin(3.0*t));       
}

double freal(double t, int *eq)
{  
   if(*eq == 0)
     return((1.0/5.0)*t*pow(e,3.0*t) - (1.0/25.0)*pow(e,3.0*t) + (1.0/25.0)*pow(e,-2.0*t));
   else if(*eq == 1)
      return(t+(1.0/(1-t)));  
   else if(*eq == 2)
       return((t*log(t) + 2.0*t));
    else 
       return((1.0/2.0)*sin(2.0*t)-(1.0/3.0)*cos(2.0*t)+(4.0/3.0));
}

