#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32


#include "PgmToAsciiArt.h"
#include "PGMToAsciiArt_cui.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <ostream>

donneesEtInfos readFile(std::string fileName)
{
	//Ouverture du fichier
	std::ifstream fichier(fileName, std::ios_base::binary);
	if (!fichier.is_open())
	{
		std::cerr << "Probleme d'ouverture du fichier\n";
	}

	//Lecture de l'entete
	std::string ligne;

	//Lecture des 2 premieres ligne "dans le vide" car inutile
	std::getline(fichier, ligne);
	std::getline(fichier, ligne);

	//Recuperation de la largeur et de la hauteur
	std::getline(fichier, ligne);


	//Recuperation largeur et hauteur dans des variables
	std::string largeurStr;
	std::string hauteurStr;
	std::stringstream ssLigne(ligne);	
	std::getline(ssLigne, largeurStr, ' ');
	std::getline(ssLigne, hauteurStr);

	
	//conversion hauteur et largeur en int
	int largeur = std::stoi(largeurStr);
	int hauteur = std::stoi(hauteurStr);

	//Lecture de la derniere ligne de l'entete "dans le vide"
	std::getline(fichier, ligne);


	

	//Initialisation tableau avec valeurs en int
	asciiTab donneesFinales;
	donneesFinales.resize(hauteur, std::vector<int>(largeur));

	//Lecture des donnees binaires de l'image
	for (size_t i = 0; i < hauteur; i++)
	{
		//Lecture d'1 ligne
		std::vector<char> donnees(largeur);
		fichier.read(donnees.data(), largeur);

		//Conversion donnees en unsigned char
		std::vector<unsigned char> donneesUnsigned;
		for (const auto s : donnees)
			donneesUnsigned.push_back(static_cast<unsigned char>(s));

		//Conversion des donnees en int pour qu'elles soient exploitables
		for (size_t j = 0; j < donneesUnsigned.size(); j++)
		{
			donneesFinales[i][j] = static_cast<int>(donneesUnsigned[j]);
		}
	}
	
	fichier.close();

	//stockage des dimensions dans un tableau
	std::array<int, 2> dimensions{ largeur, hauteur };

	donneesEtInfos donneesCompletes(donneesFinales, dimensions);

	return donneesCompletes;
}

void generateAscii(asciiTab tab, OutputMethod om, std::string filePalette, std::string fileOutput)
{
	auto tabCouleurs = paletteSelect(filePalette);

	//variable contenant l'intervalle entre chaque nuance de couleurs
	size_t pas = 256 / tabCouleurs.size();

	std::ofstream fichierOutput(fileOutput);

	for (size_t i = 0; i < tab.size(); i++) //lecture de chaques lignes
	{
		for (size_t j = 0; j < tab[i].size(); j++) //lecture de chaque valeur de la ligne
		{
			size_t indicateurCouleur = 0;
			size_t cpt = 0;
			for (size_t k = 0; k < tabCouleurs.size(); k++) //parcours du tableau tabCouleurs pour voir a quel caractere appartient la valeur
			{
				indicateurCouleur += pas;
				cpt++;

				if (tab[i][j] <= indicateurCouleur)
				{
					switch (om)
					{
					case OutputMethod::Console:
						showChar(tabCouleurs[k]);
						break;
					case OutputMethod::TextFile:
						fichierOutput << tabCouleurs[k];
						break;
					}
					break;
				}
			}
		}
		switch (om)
		{
		case OutputMethod::Console:
			showChar("\n");
			break;
		case OutputMethod::TextFile:
			fichierOutput << "\n";
			break;
		}
	}
	fichierOutput.close();
}

std::vector<std::string> paletteSelect(std::string filePalette)
{
	std::vector<std::string> tabCouleurs;

	if (filePalette == "") //si aucune palette renseigne definir une par defaut
	{
		tabCouleurs = { "W", "w", "l", "i", ":", ",", ".", " " };
	}

	else //si palette renseigne par utlisateur alors analyse de celle-ci
	{
		std::ifstream palette(filePalette);

		if (!palette.is_open())
		{
			std::cerr << "Probleme d'ouverture du fichier\n";
		}

		std::string ligne;


		while (std::getline(palette, ligne))
			/*
			getline 'recupere' chaque ligne dans palette et les stocks dans la variable ligne.
			Utilisation de getline possible comme condition car retourne false lorsque le parcous de palette est fini
			*/
		{
			tabCouleurs.push_back(ligne); //ajout du caractere au tableau
		}
		palette.close();
	}

	return tabCouleurs;
}

asciiTab imageReduction(donneesEtInfos donnees, unsigned int largeurUtilisateur, unsigned int hauteurUtilisateur)
{
	//calcul du facteur a utiliser (en fonction de la reduction la plus importante pour conserver le ratio
	unsigned int facteur;
	if (largeurUtilisateur < hauteurUtilisateur)
	{
		facteur = donnees.second[0] / largeurUtilisateur;
	}
	else
	{
		facteur = donnees.second[1] / hauteurUtilisateur;
	}

	//Calcul de la nouvelle largeur pour resize le tableau au bon nombre de lignes
	unsigned int nouvelleLargeur = donnees.second[0] / facteur;

	asciiTab donneesReduite;
	donneesReduite.resize(nouvelleLargeur, std::vector<int>(0)); //resize du tableau (pas de resize du tableau interieur car utilisation de push_back...)

	unsigned int moyenne = 0;
	unsigned int cpt;

	for (size_t i = 0; i < donnees.first.size() / facteur; i++) //parcours d'un bloc de ligne a reduire en 1 case
	{

		for (size_t k = 0; k < donnees.first[i].size() / facteur; k++) //parcours d'un bloc de valeurs dans le bloc de lignes a reduire en 1 case
		{
			cpt = 0;
			moyenne = 0;
			for (size_t j = 0; j < facteur; j++) //parcours de chaque ligne du bloc
			{
				for (size_t l = 0; l < facteur; l++) //parcours de chaque valeurs de chaque ligne du bloc
				{
					//calcul de la moyenne des cases
					moyenne += donnees.first[facteur * i + j][facteur * k + l];
					cpt++;
				}
			}
			moyenne /= cpt;
			donneesReduite[i].push_back(moyenne);
		}
		
	}


	return donneesReduite;

}


