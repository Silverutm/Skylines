/*
El programa recibe:
n numero de reglas
p profundidad maxima del arbol
las n reglas, 1 por renglon, del tipo S o B
en cada regla se reconocen los simobolos:
_
/
\
u up
d down
e empty

en cada renglon se incluyen tres cosas:
B o S seguido de un espacio los caracteres que representa seguido del peso
verbigratia:
B _B 3
La suma de los pesos es el 100%, esto con el fin de obtener la probabilidad
*/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

vector <string> S, B;
vector <int> PesoS, PesoB;
int n, p, limite, sumapesoS=0, sumapesoB=0;
int x, y,  longitud, altura;
string cadena;
char matriz[503][1003], instanterior;

void crearcadena(char s)
{	
	int proba, i=-1;
	string comodin;	
	if (s=='S')
	{				
		proba = rand() % sumapesoS + 1;
		while (proba> PesoS[ ++i ]);
		comodin = S[i];
		//cout<<"S "<<comodin<<endl;
	}
	else
	{		
		proba = rand() % sumapesoB + 1;		
		while (proba> PesoB[ ++i ]);
		comodin = B[i];
		//cout<<"B "<<comodin<<endl;
	}
	if (limite>p) comodin=B[ B.size()-1 ];
	for ( auto c:comodin )
	{
		if (c=='e') continue;
		if ( c!='B' and c!='S' )
		{	
			cadena += c;
			++limite;
		}
		else crearcadena(c);
	}
}

int min(int a, int b)
{ return a<b ? a:b;}

void crearskyline()
{
	altura= y=500;
	for (auto c: cadena)
	{
		if (c=='u')
		{
			matriz[y][x]='|';
			--y;
		}
		else if (c=='d')
		{
			if (instanterior=='u')			
			{	
				++x;
				++y;	
			}
			else if (instanterior!='d')
				++y;				
			
			matriz[y][x]='|';
			++y;
		}
		else if (c=='_')
		{
			if (instanterior=='u')
				++x;
			else if (instanterior=='d')
			{
				--y;
				++x;
			}			
			matriz[y][x]=c;
			++x;
		}
		else if (c=='/')
		{
			if (instanterior=='u')
				++x;
			else if (instanterior=='d')
			{
				--y;
				++x;
			}			
			matriz[y][x]=c;
			++x;
			--y;
		}
		else if (c=='\\')
		{
			if (instanterior=='u')			
			{	
				++x;
				++y;				
			}
			else if (instanterior!='d')
				++y;	
			else ++x;
			matriz[y][x]=c;
			++x;
		}
		instanterior=c;
		altura=min(altura, y);
		longitud = longitud+x-min(longitud,x);
	}
}

int main()
{
	//cadena="S";
	srand (time(NULL));
	cin>>n>>p;
	string tipo, regla;
	int peso;
	while (n--)
	{
		cin>>tipo>>regla>>peso;
		if (tipo=="S")
		{
			S.push_back(regla);
			PesoS.push_back( peso + sumapesoS );
			sumapesoS += peso;
			//cout<<S[S.size()-1]<<" "<<PesoS[PesoS.size()-1]<<endl;
		}
		else 
		{
			B.push_back(regla);
			PesoB.push_back( peso + sumapesoB );
			sumapesoB += peso;
			//cout<<B[B.size()-1]<<" "<<PesoB[PesoB.size()-1]<<endl;
		}		
	}
	//return 0;
	crearcadena('S');
	cout<<cadena<<endl<<endl;

	crearskyline();

	int i, j;
	for (i=altura; i<=500; ++i)
	{
		for(j=0; j<=longitud; ++j)
		{
			if (matriz[i][j]==0) matriz[i][j]=' ';
			cout<<matriz[i][j];
		}
		cout<<endl;
	}
	return 0;
}
