
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#define LIGNES  10
#define COLONNES 20
#define TEMPS_MAX 120 // Durée du jeu en secondes

int pause_time;
int mouvement_result = 999;
int compteur = 3;
int vies = 3; // Nombre initial de vies

#define NB_OISEAUX 4 // Nombre d'oiseaux dans le jeu

// Structure pour les coordonnees du personnage
struct Personnage {
    int x;
    int y;
};

// Structure pour gérer le chronomètre
struct Chronometre {
    int secondes;
};

// Structure pour gérer les vies de Snoopy
struct Vies {
    int nombre;
};

// Structure pour représenter un oiseau
struct Oiseau {
    int x;
    int y;
    int attrape;
};

// Structure pour représenter un bloc mouvant pour le niveau 3
struct BlocMouvant {
    int x;
    int y;
    int dx; // Déplacement horizontal
    int dy; // Déplacement vertical
};
// Structure pour représenter un bloc Fixe pour le niveau 2
struct BlocFixe {
    int x;
    int y;
};
struct Balle {
    int x;
    int y;
    int directionX;
    int directionY;
};

void Color(int couleurDuTexte,int couleurDeFond);
///////////////////////////////////////
// Nom du sous-programme : COLOR
// Rôle : change la couleur du texte dans la console, ainsi que la couleur du fond pour la ligne
// Compatibilité : windows XP
///////////////////////////////////////
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage decouleurs
{
HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
int check_mouvent(int posX, int posY, int balX, int balY) {
    if (posX == balX && posY == balY) {
        return 0;
    }
    return 999;
}

int calculateLevelScore(double temps_restant) {
    // Assuming Sniveau = temps restant * 100
    return (int)(temps_restant * 100);
}
// Fonction pour afficher les cœurs
void displayHearts(int vies) {
    for (int i = 0; i < vies; ++i) {
        Color(12,0);
        printf("%c", 0x03); // 0x pour le codage hexadécimal
    }
    printf("\n");
}

// Fonction pour afficher la matrice
void displayMatrix(char matrix[LIGNES][COLONNES]) {
    for (int i = 0; i < LIGNES; ++i) {
        for (int j = 0; j < COLONNES; ++j) {
            printf("%c ", matrix[i][j]); // Affichage du caractère à la position (i, j)
        }
        printf("\n");
    }
}

// Fonction pour déplacer la balle de manière aléatoire
void moveBall(char matrix[LIGNES][COLONNES], int *ballX, int *ballY, int *dx, int *dy) {
    // Efface l'ancienne position de la balle
    matrix[*ballX][*ballY] = ' ';

    // Déplacement de la balle
    if (*ballX + *dx == 0 || *ballX + *dx == LIGNES - 1) {
        *dx = -*dx; // Change la direction de la balle en x
    }
    if (*ballY + *dy == 0 || *ballY + *dy == COLONNES - 1) {
        *dy = -*dy; // Change la direction de la balle en y
    }
    *ballX += *dx;
    *ballY += *dy;

    // Met à jour la position de la balle sur la matrice
    matrix[*ballX][*ballY] = 0xB;
}
bool checkPassword(char correctPassword[5]) {
    char enteredPassword[5];
    printf("Enter the password: ");
    scanf("%s", enteredPassword);

    // Compare entered password with the correct password
    if (strcmp(enteredPassword, correctPassword) == 0) {
        printf("Password correct!\n");
        return true;
    } else {
        printf("Incorrect password. Exiting...\n");
        return false;
    }
}

void changerCouleur(int couleur) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), couleur);
}
int leaderboardNiveau1[5] = {0};
int leaderboardNiveau2[5] = {0};
int leaderboardNiveau3[5] = {0};
void afficherLeaderboard(int niveau) {
    int *leaderboard;
    switch(niveau) {
        case 1: leaderboard = leaderboardNiveau1; break;
        case 2: leaderboard = leaderboardNiveau2; break;
        case 3: leaderboard = leaderboardNiveau3; break;
        default: return;  // Niveau inconnu
    }

    printf("LEADERBOARD NIVEAU %d :\n", niveau);
    for (int i=0; i<5 ;i++) {
        if (leaderboard[i]>0) {
            printf("%de place : %d\n", i + 1, leaderboard[i]);
        }
    }
}
void afficherPlateauballe(struct Personnage personnage, struct Vies vies, struct Chronometre chronometre, struct Oiseau oiseaux[], int oiseauxAttrapes, struct Balle balle) {
    system("cls");

    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            int oiseauAttrape = 0;
            for (int k = 0; k < NB_OISEAUX; k++) {
                if (oiseaux[k].x == j && oiseaux[k].y == i && oiseaux[k].attrape == 0) {
                    changerCouleur(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\x1F ");
                    changerCouleur(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    oiseauAttrape = 1;
                    break;
                }
            }
            if (!oiseauAttrape) {
                if (i == personnage.y && j == personnage.x) {
                    changerCouleur(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    printf("\x01 "); // Caractère ANSI pour le visage souriant
                    changerCouleur(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else if (i == balle.y && j == balle.x) {
                    changerCouleur(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("O ");
                    changerCouleur(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                } else {
                    printf(". ");
                }
            }
        }
        printf("\n");
    }

    printf("OISEAUX ATTRAPES : %d\n", oiseauxAttrapes);
    printf("Vies : ");
    for (int i = 0; i < vies.nombre; i++) {
        printf("\x03 ");
    }
    printf("\n");
    printf("Chronomètre : %02d SECONDES\n", chronometre.secondes);
}

int main() {
    int totalScore = 0; // Initialize total score
    int choix;
    do {
        /*system("cls");*/
        Color(1,0);
        printf("1. Regles du jeu\n");
        printf("2. Lancer un nouveau jeu\n");
        printf("3. Charger une partie\n");
        printf("4. Lancer un niveau avec un mot de passe\n");
        printf("5. Scores\n");
        printf("6. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);
        if (choix == 2 || choix == 4) {
            break;
        } else if (choix  == 6) {
            return 0; // Quitter le programme
        } else {

            Sleep(2000);
        }
        Color(15,0);
        while (1){
            printf("Le but de Snoopy est de recuperer 4 oiseaux aux 4 coins du niveau en un temps imparti (2 minutes pa niveau). Le probleme est que ces 4 oiseaux ne sont pas si faciles a recuperer. Une balle rebondiconstamment dans le niveau afin de freiner Snoopy dans sa quete. Mais ce n est pas tout, d autres pieges sont presents comme des teleporteurs que la balle peut emprunter ou des cases piegees, voir meme des blocs a pousser ou a casser... Le jeu original comporte 120 niveaux. Un mot de passe est disponible pour chaque niveau" );

            break;
        }
    } while (2 || 4);

    Color(9,0);
    char matrix[LIGNES][COLONNES];
    int posX = 6; // Position initiale en x (ligne)
    int posY = 6; // Position initiale en y (colonne)
    int score = 0; // Score initial
    time_t debut, fin;
    double temps_restant;
    // Passwords for each level
    char level1_password[5] = "1111";
    char level2_password[5] = "2222";
    char level3_password[5] = "3333";

    char entered_password[5];

    // Initialisation de la matrice avec des espaces
    for (int i = 0; i < LIGNES; ++i) {
        for (int j = 0; j < COLONNES; ++j) {
            if (i == 0 || i == LIGNES - 1 || j == 0 || j == COLONNES - 1) {
                matrix[i][j] = 127; // Bords représentés par des blocs
            } else if (i == posX && j == posY) {
                Color(14,0);
                matrix[i][j] = 1 ; // Position de Snoopy
            } else if ((i == 1 && j == 1) || (i == 1 && j == COLONNES - 2) || (i == LIGNES - 2 && j == 1) || (i == LIGNES - 2 && j == COLONNES - 2)) {
                Color(6,0);
                matrix[i][j] = 0xE; // Position des oiseaux
            } else if (i == 2 && j == 2) {
                Color(15,0);
                matrix[i][j] = ' '; // Position des blocs cassables
            } else if (i == 3 && j == 3) {
                matrix[i][j] = ' '; // Position des blocs poussables à déplacement auto
            } else {
                matrix[i][j] = ' '; // Espaces vides dans le niveau
            }
        }
    }
    if (!checkPassword(level1_password)) {
        return 0;
    }




    char action = ' ';
    bool gameRunning = true;
    bool paused = false;
    double temps_pause = 0;

    printf("Utilisez les touches 'A' (gauche), 'D' (droite), 'W' (haut) et 'S' (bas) pour déplacer Snoopy. Appuyez sur 'Q' pour quitter. Appuyez sur 'P' pour mettre en pause.\n");

    debut = time(NULL); // Début du chronomètre

    // Initialisation de la balle
    int ballX = LIGNES / 2;
    int ballY = COLONNES / 2;
    int dx = 1; // Direction de la balle en x
    int dy = 1; // Direction de la balle en y

    while (gameRunning) {
        if (!paused) {
            // Efface l'ancienne position de Snoopy
            matrix[posX][posY] = ' ';

            // Déplacement de Snoopy en fonction de la touche pressée
            if (action == 'A' || action == 'a') {
                if (posY > 1) {
                    if (matrix[posX][posY - 1] == 0xE) {
                        score += 1; // Augmente le score si Snoopy mange un oiseau
                        matrix[posX][posY - 1] = ' '; // Efface l'oiseau mangé
                    } else if (matrix[posX][posY - 1] == ' ') {
                        matrix[posX][posY - 1] = ' '; // Casse le bloc
                    } else if (matrix[posX][posY - 1] == ' ') {
                        matrix[posX][posY - 2] = ' '; // Pousse le bloc
                        matrix[posX][posY - 1] = ' '; // Efface l'ancienne position du bloc
                    }
                    matrix[posX][--posY] = 1; // Déplace Snoopy vers la gauche
                }
            } else if (action == 'D' || action == 'd') {
                if (posY < COLONNES - 2) {
                    if (matrix[posX][posY + 1] == 0xE) {
                        score += 1; // Augmente le score si Snoopy mange un oiseau
                        matrix[posX][posY + 1] = ' '; // Efface l'oiseau mangé
                    } else if (matrix[posX][posY + 1] == ' ') {
                        matrix[posX][posY + 1] = ' '; // Casse le bloc
                    } else if (matrix[posX][posY + 1] == ' ') {
                        matrix[posX][posY + 2] = ' '; // Pousse le bloc
                        matrix[posX][posY + 1] = ' '; // Efface l'ancienne position du bloc
                    }
                    matrix[posX][++posY] = 1; // Déplace Snoopy vers la droite
                }
            } else if (action == 'W' || action == 'w') {
                if (posX > 1) {
                    if (matrix[posX - 1][posY] == 0xE) {
                        score += 1; // Augmente le score si Snoopy mange un oiseau
                        matrix[posX - 1][posY] = ' '; // Efface l'oiseau mangé
                    } else if (matrix[posX - 1][posY] == ' ') {
                        matrix[posX - 1][posY] = ' '; // Casse le bloc
                    } else if (matrix[posX - 1][posY] == ' ') {
                        matrix[posX - 2][posY] = ' '; // Pousse le bloc
                        matrix[posX - 1][posY] = ' '; // Efface l'ancienne position du bloc
                    }
                    matrix[--posX][posY] = 1; // Déplace Snoopy vers le haut
                }
            } else if (action == 'S' || action == 's') {
                if (posX < LIGNES - 2) {
                    if (matrix[posX + 1][posY] == 0xE) {
                        score += 1; // Augmente le score si Snoopy mange un oiseau
                        matrix[posX + 1][posY] = ' '; // Efface l'oiseau mangé
                    } else if (matrix[posX + 1][posY] == ' ') {
                        matrix[posX + 1][posY] = ' '; // Casse le bloc
                    } else if (matrix[posX + 1][posY] == ' ')
                    {
                        matrix[posX + 2][posY] = ' '; // Pousse le bloc
                        matrix[posX + 1][posY] = ' '; // Efface l'ancienne position du bloc
                    }
                    matrix[++posX][posY] = 1; // Déplace Snoopy vers le bas
                }
            }

            // Déplacement de la balle
            moveBall(matrix, &ballX, &ballY, &dx, &dy);
            // Vérifie si la balle touche Snoopy
            if (posX == ballX && posY == ballY) {
                // Si Snoopy est touché, retire une vie
                vies--;

                // Si plus de vies, le jeu est terminé
                if (vies == 0) {
                    gameRunning = false;
                    break;
                }

                printf("Snoopy a été touché ! Il vous reste ");
                displayHearts(vies);
            }

            // ...

            printf("Vies restantes : ");
            displayHearts(vies);

            // ...
        }

        // mouvement_result=check_mouvent(posX,posY,ballX,ballY);

        // if(mouvement_result==0 ){
        //     compteur--;
        //     break;
        // }

        // Affiche la matrice
        displayMatrix(matrix);

        fin = time(NULL); // Fin du chronomètre
        temps_restant = TEMPS_MAX - difftime(fin, debut);

        printf("Temps restant : %.0f secondes\n", temps_restant);
        printf("Score : %d\n", score);

        if (temps_restant <= 0) {
            printf("Temps écoulé. Fin du jeu.\n");
            break;
        }

        printf("Choisissez une action ('P' pour mettre en pause) : ");
        scanf(" %c", &action);

        // Gestion de la pause
        if (action == 'P' || action == 'p') {
            if (paused) {
                // Reprendre le temps au moment de la pause
                temps_pause += difftime(time(NULL), fin);
                printf("fin %d", fin);
                debut += (time(NULL) - pause_time);
            } else {
                pause_time = time(NULL);
                printf("Le jeu est en pause.\n");
            }

            printf("temps_pause: %f\n", temps_pause);
            paused = !paused; // Inverse l'état de la pause

            // usleep(500000); // Attendez un instant pour éviter la relecture rapide de la touche 'P'
        } else if (action == 'Q' || action == 'q') {
            gameRunning = false; // Quitter le jeu
        }
    }
    /*compteur--;*/
    if (compteur < 1) gameRunning = false;
    printf("Fin du jeu. Merci d'avoir joué !\n");
    totalScore += calculateLevelScore(TEMPS_MAX - temps_restant);
    // Rest of the game logic for level 2...
    printf("Starting level 2...\n");

// Initialisation de la matrice avec des espaces
    for (int i = 0; i < LIGNES; ++i) {
        for (int j = 0; j < COLONNES; ++j) {
            if (i == 0 || i == LIGNES - 1 || j == 0 || j == COLONNES - 1) {
                matrix[i][j] = 127; // Bords représentés par des blocs
            } else if (i == posX && j == posY) {
                matrix[i][j] = '1'; // Position de Snoopy
            } else if ((i == 1 && j == 1) || (i == 1 && j == COLONNES - 2) || (i == LIGNES - 2 && j == 1) || (i == LIGNES - 2 && j == COLONNES - 2)) {
                matrix[i][j] = 0xE; // Position des oiseaux
            } else if ((i == 6 && j == 2)||(i == 2 && j == 2) ||(i == 2 && j == 7)|| (i == 5 && j == 2) ) {
                matrix[i][j] = 6 ; // Position des blocs cassables
            } else if (i == 3 && j == 3) {
                matrix[i][j] = 0xA ; // Position des blocs poussables à déplacement auto
            } else {
                matrix[i][j] = ' '; // Espaces vides dans le niveau
            }
        }
    }


    if (!checkPassword(level2_password)) {
        return 0;
    }

    char action2 = ' ';
    bool gameRunning2 = true;
    bool paused2 = false;
    double temps_pause2 = 0;

    printf("Utilisez les touches 'A' (gauche), 'D' (droite), 'W' (haut) et 'S' (bas) pour déplacer Snoopy. Appuyez sur 'Q' pour quitter. Appuyez sur 'P' pour mettre en pause.\n");

    debut = time(NULL); // Début du chronomètre

// Initialisation de la balle
    int ballX2 = LIGNES / 2;
    int ballY2 = COLONNES / 2;
    int dx2 = 1; // Direction de la balle en x
    int dy2 = 1; // Direction de la balle en y
    while (gameRunning2) {
        if (!paused2) {
            // Efface l'ancienne position de Snoopy
            matrix[posX][posY] = ' ';

            // Déplacement de Snoopy en fonction de la touche pressée
            if (action2 == 'A' || action2 == 'a') {
                if (posY > 1) {
                    if (matrix[posX][posY - 1] == 0xE) {
                        score += 1; // Augmente le score si Snoopy mange un oiseau
                        matrix[posX][posY - 1] = ' '; // Efface l'oiseau mangé
                    } else if (matrix[posX][posY - 1] == 'X') {
                        matrix[posX][posY - 1] = ' '; // Casse le bloc
                    } else if (matrix[posX][posY - 1] == 'M') {
                        matrix[posX][posY - 2] = 'M'; // Pousse le bloc
                        matrix[posX][posY - 1] = ' '; // Efface l'ancienne position du bloc
                    }
                    matrix[posX][--posY] = 1; // Déplace Snoopy vers la gauche
                }
            } else if (action2 == 'D' || action2 == 'd') {
                if (posY < COLONNES - 2) {
                    if (matrix[posX][posY + 1] == 0xE) {
                        score += 1; // Augmente le score si Snoopy mange un oiseau
                        matrix[posX][posY + 1] = ' '; // Efface l'oiseau mangé
                    } else if (matrix[posX][posY + 1] == 'X') {
                        matrix[posX][posY + 1] = ' '; // Casse le bloc
                    } else if (matrix[posX][posY + 1] == 'M') {
                        matrix[posX][posY + 2] = 'M'; // Pousse le bloc
                        matrix[posX][posY + 1] = ' '; // Efface l'ancienne position du bloc
                    }
                    matrix[posX][++posY] = 1; // Déplace Snoopy vers la droite
                }
            } else if (action2 == 'W' || action2 == 'w') {
                if (posX > 1) {
                    if (matrix[posX - 1][posY] == 0xE) {
                        score += 1; // Augmente le score si Snoopy mange un oiseau
                        matrix[posX - 1][posY] = ' '; // Efface l'oiseau mangé
                    } else if (matrix[posX - 1][posY] == 'X') {
                        matrix[posX - 1][posY] = ' '; // Casse le bloc
                    } else if (matrix[posX - 1][posY] == 'M') {
                        matrix[posX - 2][posY] = 'M'; // Pousse le bloc
                        matrix[posX - 1][posY] = ' '; // Efface l'ancienne position du bloc
                    }
                    matrix[--posX][posY] = 1; // Déplace Snoopy vers le haut
                }
            } else if (action2 == 'S' || action2 == 's') {
                if (posX < LIGNES - 2) {
                    if (matrix[posX + 1][posY] == 0xE) {
                        score += 1; // Augmente le score si Snoopy mange un oiseau
                        matrix[posX + 1][posY] = ' '; // Efface l'oiseau mangé
                    } else if (matrix[posX + 1][posY] == 'X') {
                        matrix[posX + 1][posY] = ' '; // Casse le bloc
                    } else if (matrix[posX + 1][posY] == 'M')
                    {
                        matrix[posX + 2][posY] = 'M'; // Pousse le bloc
                        matrix[posX + 1][posY] = ' '; // Efface l'ancienne position du bloc
                    }
                    matrix[++posX][posY] = 1; // Déplace Snoopy vers le bas
                }
            }

            // Déplacement de la balle
            moveBall(matrix, &ballX2, &ballY2, &dx2, &dy2);
            // Vérifie si la balle touche Snoopy
            if (posX == ballX2 && posY == ballY2) {
                // Si Snoopy est touché, retire une vie
                vies--;

                // Si plus de vies, le jeu est terminé
                if (vies == 0) {
                    gameRunning = false;
                    break;
                }

                printf("Snoopy a été touché ! Il vous reste ");
                displayHearts(vies);
            }

            // ...

            printf("Vies restantes : ");
            displayHearts(vies);

            // ...
        }

        // mouvement_result=check_mouvent(posX,posY,ballX,ballY);

        // if(mouvement_result==0 ){
        //     compteur--;
        //     break;
        // }

        // Affiche la matrice
        displayMatrix(matrix);

        fin = time(NULL); // Fin du chronomètre
        temps_restant = TEMPS_MAX - difftime(fin, debut);

        printf("Temps restant : %.0f secondes\n", temps_restant);
        printf("Score : %d\n", score);

        if (temps_restant <= 0) {
            printf("Temps écoulé. Fin du jeu.\n");
            break;
        }

        printf("Choisissez une action ('P' pour mettre en pause) : ");
        scanf(" %c", &action2);

        // Gestion de la pause
        if (action2 == 'P' || action2 == 'p') {
            if (paused2) {
                // Reprendre le temps au moment de la pause
                temps_pause2 += difftime(time(NULL), fin);
                printf("fin %d", fin);
                debut += (time(NULL) - pause_time);
            } else {
                pause_time = time(NULL);
                printf("Le jeu est en pause.\n");
            }

            printf("temps_pause: %f\n", temps_pause);
            paused2 = !paused2; // Inverse l'état de la pause

            // usleep(500000); // Attendez un instant pour éviter la relecture rapide de la touche 'P'
        } else if (action2 == 'Z' || action2 == 'z') {
            gameRunning2 = false; // Quitter le jeu
        }
    }
    /*compteur--;*/
    if (compteur < 1) gameRunning2 = false;
    printf("Fin du jeu. Merci d'avoir joué !\n");
    totalScore += calculateLevelScore(TEMPS_MAX - temps_restant);

    printf("Starting level 3...\n");

// Initialisation de la matrice avec des espaces
    for (int i = 0; i < LIGNES; ++i) {
        for (int j = 0; j < COLONNES; ++j) {
            if (i == 0 || i == LIGNES - 1 || j == 0 || j == COLONNES - 1) {
                matrix[i][j] = 127; // Bords représentés par des blocs
            } else if (i == posX && j == posY) {
                matrix[i][j] = '1'; // Position de Snoopy
            } else if ((i == 1 && j == 1) || (i == 1 && j == COLONNES - 2) || (i == LIGNES - 2 && j == 1) || (i == LIGNES - 2 && j == COLONNES - 2)) {
                matrix[i][j] = 0xE; // Position des oiseaux
            } else if ((i == 6 && j == 2)||(i == 2 && j == 2) ||(i == 2 && j == 7)|| (i == 5 && j == 2) ) {
                matrix[i][j] = 6 ; // Position des blocs cassables
            } else if ((i == 3 && j == 3)||(i==5&& j==3)||(i == 10 && j == 10)|| (i == 5 && j == 7)){
                matrix[i][j] = 4 ; // Position des blocs poussables à déplacement auto
            } else if ((i == 3 && j == 15)||(i==5&& j==15)||(i == 10 && j == 15)|| (i == 5 && j == 14)){
                matrix[i][j] = 5 ;
            } else {
                matrix[i][j] = ' '; // Espaces vides dans le niveau
            }
        }
    }
    if (!checkPassword(level3_password)) {
        return 0;
    }

    char action3 = ' ';
    bool gameRunning3 = true;
    bool paused3 = false;
    double temps_pause3 = 0;

    printf("Utilisez les touches 'A' (gauche), 'D' (droite), 'W' (haut) et 'S' (bas) pour déplacer Snoopy. Appuyez sur 'Q' pour quitter. Appuyez sur 'P' pour mettre en pause.\n");

    debut = time(NULL); // Début du chronomètre

// Initialisation de la balle
    int ballX3 = LIGNES / 2;
    int ballY3 = COLONNES / 2;
    int dx3 = 1; // Direction de la balle en x
    int dy3 = 1; // Direction de la balle en y
    while (gameRunning3) {
        if (!paused3) {
            // Efface l'ancienne position de Snoopy
            matrix[posX][posY] = ' ';

            // Déplacement de Snoopy en fonction de la touche pressée
            if (action3 == 'A' || action3 == 'a') {
                if (posY > 1) {
                    if (matrix[posX][posY - 1] == 0xE) {
                        score += 1; // Augmente le score si Snoopy mange un oiseau
                        matrix[posX][posY - 1] = ' '; // Efface l'oiseau mangé
                    } else if (matrix[posX][posY - 1] == 'X') {
                        matrix[posX][posY - 1] = ' '; // Casse le bloc
                    } else if (matrix[posX][posY - 1] == 'M') {
                        matrix[posX][posY - 2] = 'M'; // Pousse le bloc
                        matrix[posX][posY - 1] = ' '; // Efface l'ancienne position du bloc
                    }
                    matrix[posX][--posY] = 1; // Déplace Snoopy vers la gauche
                }
            } else if (action3 == 'D' || action3 == 'd') {
                if (posY < COLONNES - 2) {
                    if (matrix[posX][posY + 1] == 0xE) {
                        score += 1; // Augmente le score si Snoopy mange un oiseau
                        matrix[posX][posY + 1] = ' '; // Efface l'oiseau mangé
                    } else if (matrix[posX][posY + 1] == 'X') {
                        matrix[posX][posY + 1] = ' '; // Casse le bloc
                    } else if (matrix[posX][posY + 1] == 'M') {
                        matrix[posX][posY + 2] = 'M'; // Pousse le bloc
                        matrix[posX][posY + 1] = ' '; // Efface l'ancienne position du bloc
                    }
                    matrix[posX][++posY] = 1; // Déplace Snoopy vers la droite
                }
            } else if (action3 == 'W' || action3 == 'w') {
                if (posX > 1) {
                    if (matrix[posX - 1][posY] == 0xE) {
                        score += 1; // Augmente le score si Snoopy mange un oiseau
                        matrix[posX - 1][posY] = ' '; // Efface l'oiseau mangé
                    } else if (matrix[posX - 1][posY] == 'X') {
                        matrix[posX - 1][posY] = ' '; // Casse le bloc
                    } else if (matrix[posX - 1][posY] == 'M') {
                        matrix[posX - 2][posY] = 'M'; // Pousse le bloc
                        matrix[posX - 1][posY] = ' '; // Efface l'ancienne position du bloc
                    }
                    matrix[--posX][posY] = 1; // Déplace Snoopy vers le haut
                }
            } else if (action3 == 'S' || action3 == 's') {
                if (posX < LIGNES - 2) {
                    if (matrix[posX + 1][posY] == 0xE) {
                        score += 1; // Augmente le score si Snoopy mange un oiseau
                        matrix[posX + 1][posY] = ' '; // Efface l'oiseau mangé
                    } else if (matrix[posX + 1][posY] == 'X') {
                        matrix[posX + 1][posY] = ' '; // Casse le bloc
                    } else if (matrix[posX + 1][posY] == 'M')
                    {
                        matrix[posX + 2][posY] = 'M'; // Pousse le bloc
                        matrix[posX + 1][posY] = ' '; // Efface l'ancienne position du bloc
                    }
                    matrix[++posX][posY] = 1; // Déplace Snoopy vers le bas
                }
            }

            // Déplacement de la balle
            moveBall(matrix, &ballX3, &ballY3, &dx3, &dy3);
            // Vérifie si la balle touche Snoopy
            if (posX == ballX3 && posY == ballY3) {
                // Si Snoopy est touché, retire une vie
                vies--;

                // Si plus de vies, le jeu est terminé
                if (vies == 0) {
                    gameRunning = false;
                    break;
                }

                printf("Snoopy a été touché ! Il vous reste ");
                displayHearts(vies);
            }

            // ...

            printf("Vies restantes : ");
            displayHearts(vies);

            // ...
        }

        // mouvement_result=check_mouvent(posX,posY,ballX,ballY);

        // if(mouvement_result==0 ){
        //     compteur--;
        //     break;
        // }

        // Affiche la matrice
        displayMatrix(matrix);

        fin = time(NULL); // Fin du chronomètre
        temps_restant = TEMPS_MAX - difftime(fin, debut);

        printf("Temps restant : %.0f secondes\n", temps_restant);
        printf("Score : %d\n", score);

        if (temps_restant <= 0) {
            printf("Temps écoulé. Fin du jeu.\n");
            break;
        }

        printf("Choisissez une action ('P' pour mettre en pause) : ");
        scanf(" %c", &action3);

        // Gestion de la pause
        if (action3 == 'P' || action3 == 'p') {
            if (paused3) {
                // Reprendre le temps au moment de la pause
                temps_pause3 += difftime(time(NULL), fin);
                printf("fin %d", fin);
                debut += (time(NULL) - pause_time);
            } else {
                pause_time = time(NULL);
                printf("Le jeu est en pause.\n");
            }

            printf("temps_pause: %f\n", temps_pause);
            paused3 = !paused3; // Inverse l'état de la pause

            // usleep(500000); // Attendez un instant pour éviter la relecture rapide de la touche 'P'
        } else if (action3 == 'Q' || action3 == 'q') {
            gameRunning3 = false; // Quitter le jeu
        }
    }
    /*compteur--;*/
    if (compteur < 1) gameRunning3 = false;
    printf("Fin du jeu. Merci d'avoir joué !\n");
    totalScore += calculateLevelScore(TEMPS_MAX - temps_restant);

    while (5) {
        printf("Choisissez le niveau pour lequel vous voulez voir le leaderboard (1, 2, 3) : ");
        int niveauChoisi;
        scanf("%d", &niveauChoisi);
        afficherLeaderboard(niveauChoisi);
    }
    return 0;
}
