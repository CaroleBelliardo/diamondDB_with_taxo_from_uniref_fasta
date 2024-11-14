#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <cstdlib>

// Fonction pour extraire protID et taxID
std::pair<std::string, std::string> extractProtIDTaxID(const std::string &sequence) {
    std::regex protIDRegex("UniRef\\d+_(\\S+)");
    std::regex taxIDRegex("TaxID=(\\d+)");
    std::smatch match;

    std::string protID, taxID;

    // Extraction de protID
    if (std::regex_search(sequence, match, protIDRegex) && match.size() > 1) {
        protID = match.str(1);
    }

    // Extraction de taxID
    if (std::regex_search(sequence, match, taxIDRegex) && match.size() > 1) {
        taxID = match.str(1);
    }

    return {protID, taxID};
}

// Fonction pour traiter le fichier FASTA
void processFasta(const std::string &inputFile, const std::string &outputFile) {
    std::ifstream inputHandle(inputFile);
    std::ofstream outputHandle(outputFile);

    if (!inputHandle.is_open()) {
        std::cerr << "Error opening input file: " << inputFile << std::endl;
        exit(EXIT_FAILURE);
    }
    if (!outputHandle.is_open()) {
        std::cerr << "Error opening output file: " << outputFile << std::endl;
        exit(EXIT_FAILURE);
    }

    // Écrire l'en-tête dans le fichier de sortie
    outputHandle << "accession.version\ttaxid\n";

    std::string line;
    // Traitement de chaque ligne dans le fichier FASTA
    while (std::getline(inputHandle, line)) {
        line = line.substr(line.find_first_not_of(" \t"));  // Supprimer les espaces de début
        if (line[0] == '>') {
            auto [protID, taxID] = extractProtIDTaxID(line);

            // Vérifie que protID et taxID sont présents
            if (!protID.empty() && !taxID.empty()) {
                outputHandle << protID << "\t" << taxID << "\n";
            } else {
                std::cerr << "Warning: Missing data for line: " << line << std::endl;
            }
        }
    }

    inputHandle.close();
    outputHandle.close();
}

// Fonction principale pour gérer les arguments de la ligne de commande
int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_fasta> <output_file>\n";
        return EXIT_FAILURE;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    // Appel de la fonction de traitement du fichier
    processFasta(inputFile, outputFile);

    return EXIT_SUCCESS;
}
