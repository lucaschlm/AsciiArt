#pragma once

#include <string>
#include <vector>
#include <array>

enum class OutputMethod
{
	Console,
	TextFile
};

//Type pour stocker les tableaux de valeurs des pixels
using asciiTab = std::vector<std::vector<int>>;
//Type assemblant le tableau de valeurs des pixels avec les dimensions de l'image
using donneesEtInfos = std::pair<asciiTab, std::array<int, 2>>;

// Fonction permettant de lire un fichier PGM
donneesEtInfos readFile(std::string fileName);

//Fonction generant l'ascii art
void generateAscii(asciiTab tab, OutputMethod om, std::string filePalette, std::string fileOutput = "");

//Fonction retournant la palette a utiliser
std::vector<std::string> paletteSelect(std::string filePalette);

//Fonction reduisant la taille de l'image
asciiTab imageReduction(donneesEtInfos donnees, unsigned int largeurUtilisateur, unsigned int hauteurUtilisateur);