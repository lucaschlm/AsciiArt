#pragma once

#include "PgmToAsciiArt.h"
#include <string>

// Fonction demandant le nom du fichier PGM
std::string askFileName();

//Fonction demandant le nom du fichier de sortie
std::string askFileOutput();

//Fonction demandant le choix de palette
std::string askForPalette();

//Fonction qui affiche l'aide
void showHelp();

//Fonction affichant un caractère
void showChar(std::string c);