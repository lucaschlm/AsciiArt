#pragma once

#include "PgmToAsciiArt.h"
#include <string>

// Fonction demandant le nom du fichier PGM
std::string askFileName();

//Fonction demandant le nom du fichier de sortie
std::string askFileOutput();

//Fonction demandant le choix de palette
std::string askForPalette();

//Fonction affichant l'ascii art
void showAscii(asciiTab tab, std::string filePalette);

//Fonction qui affiche l'aide
void showHelp();