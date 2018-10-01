#include "EasyBMP.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

typedef double NUMERO;
typedef vector<double> VEC;

NUMERO** crear_matriz(int n, int m)
{
    NUMERO** X = new NUMERO*[n];
    for(int i=0; i < n; i++)
      {
        X[i] = new NUMERO[m];
      };
    return X;
};

VEC CalculateCentroid(BMP img)
{
  NUMERO X_mean = 0, Y_mean = 0, total = 0, pixel = 0;
  VEC cent(2);
  
  for(NUMERO ii = 0; ii < img.TellHeight(); ii++)
    {
      for(NUMERO jj = 0; jj < img.TellWidth(); jj++)
	{
	  pixel = (NUMERO)img(jj,ii)->Green;
	  
	  X_mean += jj * pixel;
	  Y_mean += ii * pixel;
	  
	  total += pixel;
	}
    }
  
  cent[0] = X_mean / total;
  cent[1] = Y_mean / total;

  return cent;
}

VEC Uncertainty(BMP img, NUMERO Ndata, char *argv[])
{
  NUMERO X_prom = 0, Y_prom = 0, X_desv = 0, Y_desv = 0;
  
  VEC cent(2);
  VEC prom(4);
  
  for(int ii = 1; ii < Ndata; ii++)
    {
      img.ReadFromFile(argv[ii]);
      cent = CalculateCentroid(img);
      cout << argv[ii] << "\n" << cent[0] << "," << cent[1] << endl;
      X_prom += cent[0];
      Y_prom += cent[1];
    }

  for(int jj = 1; jj < Ndata; jj++)
    {
      img.ReadFromFile(argv[jj]);
      cent = CalculateCentroid(img);
      X_desv += pow((cent[0]-X_prom),2.);
      Y_desv += pow((cent[1]-Y_prom),2.);
    }

  prom[0] = X_prom / Ndata;
  prom[1] = Y_prom / Ndata;
  prom[2] = pow(X_desv / (Ndata-1),0.5);
  prom[3] = pow(Y_desv / (Ndata-1),0.5);

  return prom;
}

/*void PrintData(BMP img, int Ndata, char* argv[])
{
  VEC cent(2);
  
  for(int ii = 1; ii < Ndata; ii++)
    {
      img.ReadFromFile(argv[ii]);
      cent = CalculateCentroid(img);
      cout << cent[0] << "\t" << cent[1] << endl;
    }
    }*/

void PrintImageMatrix(BMP img)
{
  cout.precision(5);
  for(int ii = 0; ii < img.TellWidth(); ii++)
    {
      for(int jj = 0; jj < img.TellHeight(); jj++)
	{
	  cout << (NUMERO)img(ii,jj)->Green
	       << ".000\t";
	    };
      cout << "\n";
    };
}

NUMERO** ReadFromMatrix(string fileName, int width, int height)
{
  ifstream file;
  file.open(fileName);
  NUMERO** A0 = crear_matriz(height,width);
  for(int ii = 0; ii < height; ii++)
    for(int jj = 0; jj < width; jj++)
     file >> A0[ii][jj];
  file.close();
  return A0;
}

VEC CentroidFromMatrix(NUMERO** M, int width, int height)
{
  NUMERO cent_x = 0, cent_y = 0, total = 0, MM = 0;
  VEC cent(2);
  
  for(int ii = 0; ii < height; ii++)
    {
    for(int jj = 0; jj < width; jj++)
      {
	MM=M[ii][jj]-16;
	cent_x += ii*MM;
	cent_y += jj*MM;
	total += MM;
      }
    }
  
  cent[0] = cent_x / total;
  cent[1] = cent_y / total;

  return cent;
}

int main(int argc, char* argv[])
{
  BMP image;	
  BMP image1;
  BMP image2;
  
  image.ReadFromFile(argv[1]);
  
  VEC CC = CalculateCentroid(image);	
  
  cout.precision(3);
  
  if(argv[2]!=NULL && argv[3]!=NULL)
    {
      image1.ReadFromFile(argv[2]);
      image2.ReadFromFile(argv[3]);
      
      VEC CC1 = CalculateCentroid(image1);
      VEC CC2 = CalculateCentroid(image2);
      
      cout << CC[0] << "\t" << CC[1] << "\n";
      cout << CC1[0] << "\t" << CC1[1] << "\n";
      cout << CC2[0] << "\t" << CC2[1] << "\n" << "\n";
      cout << "d 0-1" << "\t" << "d 0-2" << "\n";
      cout << abs(CC[0]-CC1[0]) << "\t" << abs(CC[0]-CC2[0]) << "\n"; 
    }
  
  else
    {
      cout << CC[0] << "\t" << CC[1] << "\n";	
    }
  
  //NUMERO** M = ReadFromMatrix(argv[1],1280,1024);
  //VEC centImageJ = CentroidFromMatrix(M,1280,1024);
  
  return 0;
}
