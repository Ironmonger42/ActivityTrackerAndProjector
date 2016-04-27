#include <iostream>
#include <fstream>

using namespace std;

//When called, the file storedData.txt will be opened as an input file and used to fill the values
//of the variables provided. When done, the file is closed. References are used so that nothing
//needs to be returned.
void importData(int &RProspect, int &PIE, int &FLI, int &PI, int &NCC,
     double &TProspect, double &ProspectToPIE, double &PIEToFLI, double &FLIToPI, double &PIToNCC)
{
     ifstream inputFile ("storedData.txt");
     if(!inputFile.is_open())
     {
          cout << "File faied to open" << endl;
     }
     else
     {
          inputFile >> RProspect;
          inputFile >> PIE;
          inputFile >> FLI;
          inputFile >> PI;
          inputFile >> NCC;
          inputFile >> TProspect;
          inputFile >> ProspectToPIE;
          inputFile >> PIEToFLI;
          inputFile >> FLIToPI;
          inputFile >> PIToNCC;
     }

     inputFile.close();
}


//When called, the file storedData.txt will be opened as an output file and sent the values
//of the variables provide. when done, the file is closed.
void exportData(int RProspect, int PIE, int FLI, int PI, int NCC,
     double TProspect, double ProspectToPIE, double PIEToFLI, double FLIToPI, double PIToNCC)
{
     ofstream outputFile ("storedData.txt");
     if(!outputFile.is_open())
     {
          cout << "File faied to open" << endl;
     }
     else
     {
          outputFile << RProspect << endl;
          outputFile << PIE << endl;
          outputFile << FLI << endl;
          outputFile << PI << endl;
          outputFile << NCC << endl;
          outputFile << TProspect << endl;
          outputFile << ProspectToPIE << endl;
          outputFile << PIEToFLI << endl;
          outputFile << FLIToPI << endl;
          outputFile << PIToNCC << endl;
     }

     outputFile.close();
}

int main()
{
     //Real data: represents what the person has accomplished in the field
     int RProspect, PIE, FLI, PI, NCC;
     //Theoretical data: starts with an inivial value and then has 4 % that represent the % that made it to the next category
     double TProspect, ProspectToPIE, PIEToFLI, FLIToPI, PIToNCC;
     importData(RProspect, PIE, FLI, PI, NCC, TProspect, ProspectToPIE, PIEToFLI, FLIToPI, PIToNCC);
     exportData(RProspect, PIE, FLI, PI, NCC, TProspect, ProspectToPIE, PIEToFLI, FLIToPI, PIToNCC);

     return 0;
}
