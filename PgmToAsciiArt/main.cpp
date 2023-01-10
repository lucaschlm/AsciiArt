#include "PgmToAsciiArt.h"
#include "PGMToAsciiArt_cui.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>

int main(int argc, char* argv[])
{

    std::string fileName = "";
    std::string filePalette = "";
    std::string fileOutput = "";

    int width = std::numeric_limits<int>::max();
    int height = std::numeric_limits<int>::max();

    std::string valeur;
    for (int i = 1; i < argc; ++i) //i=1 au debut car premiere ligne inutile
    {
        // passage du tableau de char en string pour comparaisons
        valeur = argv[i];
        if (valeur == "--input")
        {
            i++;
            valeur = argv[i];
            fileName = valeur;
            continue;
        }  
        if (valeur == "--output")
        {  
            i++;
            valeur = argv[i];
            fileOutput = valeur;
            continue;
        }
        if (valeur == "--palette")
        {
            i++;
            valeur = argv[i];
            filePalette = valeur;

            continue;
        }
       if (valeur == "--width")
        {
            i++;
            valeur = argv[i];
            width = std::stoi(valeur);

            continue;
        }
        if (valeur == "--height")
        {
            i++;
            valeur = argv[i];
            height = std::stoi(valeur);

            continue;
        }
        if (valeur == "--help")
        {
            showHelp();
            return 1;
        }
    }

    if (fileName == "") //si fileName pas renseigne
        fileName = askFileName();
    
    auto donnees = readFile(fileName);


    auto file = donnees.first;
    if (width < donnees.second[0] || height < donnees.second[1]) //si largeur demande par utilisateur inferieur a la largeur de l'image ou hauteur demande par utilisateur inferieur a la hauteur de l'image
        file = imageReduction(donnees, width, height);

    if (fileOutput == "") //si nom du fichier de sortie non renseigne par utilisateur afficher dans la console
        generateAscii(file, OutputMethod::Console, filePalette, fileOutput);
    else
        generateAscii(file, OutputMethod::TextFile, filePalette, fileOutput);
}
