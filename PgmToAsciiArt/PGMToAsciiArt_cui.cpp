#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

#include <iostream>
#include <fstream>
#include <iomanip>
#include "PGMToAsciiArt_cui.h"

std::string askFileName()
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif // _WIN32

	std::cout << "Saisissez le nom du fichier à ouvrir : ";
	std::string fileName;
	std::cin >> fileName;

	return fileName;
}


std::string askFileOutput()
{
	std::string fileName;
	std::cout << "Entrez le nom du fichier de sortie : ";
	std::cin >> fileName;

	return fileName;
}

std::string askForPalette()
{
	std::string palette;
	std::cout << "Entrez le nom de la palette a utiliser : ";
	std::cin >> palette;

	return palette;
}

void showHelp()
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif // _WIN32
	const unsigned int widthOptions = 20;
	std::cout << "Usage :\n"
		<< "PgmToASciiArt [options]\n\n"
		<< "Options :\n"
		<< std::setw(widthOptions) << std::left << "--input fichier" << std::right << "Spécifie le fichier image à convertir\n"
		<< std::setw(widthOptions) << " " << std::right << "Si ce paramètre n'est pas spécifié, le fichier est demandé via la console.\n\n"
		<< std::setw(widthOptions) << std::left << "--output fichier" << std::right << "Spécifie le nom du fichier texte qui contiendra l'Ascii Art.\n"
		<< std::setw(widthOptions) << " " << std::right << "Si ce paramètre n'est pas spécifié, l'Ascii Art est sortie dans la console.\n\n"
		<< std::setw(widthOptions) << std::left << "--palette fichier" << std::right << "Spécifie un fichier texte contenant la palette de couleur Ascii\n"
		<< std::setw(widthOptions) << " " << std::right << "Chaque ligne du fichier contient un charactère en UTF-8, du plus sombre au plus clair\n"
		<< std::setw(widthOptions) << " " << std::right << "Si ce paramètre n'est pas spécifié, la palette par défaut est \"W\", \"w\", \"l\", \"i\", \":\", \",\", \".\", \" \"\n\n"
		<< std::setw(widthOptions) << std::left << "--width nombre" << std::right << "Spécifie la largeur max de l'Ascii Art.\n"
		<< std::setw(widthOptions) << " " << std::right << "Si ce paramètre n'est pas spécifié, aucune limite n'est fixée.\n"
		<< std::setw(widthOptions) << " " << std::right << "Voir Remarques.\n\n"
		<< std::setw(widthOptions) << std::left << "--height nombre" << std::right << "Spécifie la hauteur max de l'Ascii Art.\n"
		<< std::setw(widthOptions) << " " << std::right << "Si ce paramètre n'est pas spécifié, aucune limite n'est fixée.\n"
		<< std::setw(widthOptions) << " " << std::right << "Voir Remarques.\n\n"
		<< std::setw(widthOptions) << std::left << "--help" << std::right << "Affiche cette aide\n\n"
		<< "Remarques :\n"
		<< "Quelles que soient les valeurs des options --width et --height, la taille de l'Ascii Art\n"
		<< "est bornée par la taille de l'image en entrée. La taille de l'ascii art conserve\n"
		<< "toujours le même ratio que l'image d'entrée, les valeurs des options --width et --height\n"
		<< "ne sont que des maximums.\n";
}

void showChar(std::string c)
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif // _WIN32
	std::cout << c;
}
