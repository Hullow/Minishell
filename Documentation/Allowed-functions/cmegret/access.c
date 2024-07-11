#include <unistd.h>
#include <stdio.h>

void test_access(const char *filepath) {
	// Tester le droit de lecture
	if (access(filepath, R_OK) == 0) {
		printf("L'acces en lecture au fichier %s est autorisé.\n", filepath);
	} else {
		// Afficher le message d'erreur si l'accès est refusé
		perror("ecriture refuse");
	}
}

int main() {
	// Remplacer '/chemin/vers/le/fichier' par le chemin réel du fichier à tester
	const char *test_file = "/Users/corentin/Documents/Minishell/Documentation/Allowed-functions/cmegret/test.txt";
	test_access(test_file);
	return 0;
}