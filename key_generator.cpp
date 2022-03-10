#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<string.h>

using namespace std;

int x, y, n, t, i, flag;
long int e[50], d[50], temp[50], j;
char en[50], m[50];
char msg[100];
int prime(long int); //function to check for prime number
void encryption_key();
long int cd(long int);

int main()
{
   cout << "\nENTER FIRST PRIME NUMBER\n";
   cin >> x;

   flag = prime(x);
   if(flag == 0)
   {
      cout << "\nINVALID INPUT\n";
      exit(0);
   }

   cout << "\nENTER SECOND PRIME NUMBER\n";
   cin >> y;

   flag = prime(y);
   if(flag == 0 || x == y)
   {
      cout << "\nINVALID INPUT\n";
      exit(0);
   }

   n = x * y;
   t = (x - 1) * (y - 1);

   encryption_key();

   cout << "\nn: " << n << endl;
   cout << "\nPOSSIBLE VALUES OF e AND d:\n";

   for(i = 0; i < j - 1; i++)
      cout << "\n" << e[i] << "\t" << d[i];

   return 0;
}

int prime(long int pr)
{
   int i;
   j = sqrt(pr);
   for(i = 2; i <= j; i++)
   {
      if(pr % i == 0)
         return 0;
   }
   return 1;
 }

//function to generate encryption key
void encryption_key()
{
   int k;
   k = 0;
   for(i = 2; i < t; i++)
   {
      if(t % i == 0)
         continue;
      flag = prime(i);
      if(flag == 1 && i != x && i != y)
      {
         e[k] = i;
         flag = cd(e[k]);
         if(flag > 0)
         {
            d[k] = flag;
            k++;
         }
         if(k == 99)
         break;
      }
   }
}

long int cd(long int a)
{
   long int k = 1;
   while(1)
   {
      k = k + t;
      if(k % a == 0)
         return(k/a);
   }
}