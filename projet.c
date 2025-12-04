#include <stdio.h>
#include <stdlib.h>
typedef struct Noeud {
    int donnee;
    struct Noeud* suivant;
    struct Noeud* precedent;
} Noeud;

Noeud* creerNoeud(int valeur) {
    Noeud* nouveau = (Noeud*)malloc(sizeof(Noeud));
    if (nouveau == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        exit(1);
    }
    nouveau->donnee = valeur;
    nouveau->suivant = nouveau;
    nouveau->precedent = nouveau;
    return nouveau;
}

void ajouterFin(Noeud** tete, int valeur) {
    Noeud* nouveau = creerNoeud(valeur);
    if (*tete == NULL) {
        *tete = nouveau;
        return;
    }
    Noeud* dernier = (*tete)->precedent;
    dernier->suivant = nouveau;
    nouveau->precedent = dernier;
    nouveau->suivant = *tete;
    (*tete)->precedent = nouveau;
}

void afficherListe(Noeud* tete) {
    if (tete == NULL) {
        printf("Liste vide.\n");
        return;
    }
    Noeud* courant = tete;
    do {
        printf("%d ", courant->donnee);
        courant = courant->suivant;
    } while (courant != tete);
    printf("\n");

}

Noeud* Trier(Noeud* tete) {
    if (tete == NULL || tete->suivant == tete) return tete;

    Noeud* triee = NULL;
    Noeud* courant = tete;

    do {
        Noeud* suivant = courant->suivant;

        if (triee == NULL) {
            triee = courant;
            triee->suivant = triee;
            triee->precedent = triee;
        } else {
            Noeud* pos = triee;
            while (pos->suivant != triee && pos->suivant->donnee < courant->donnee) {
                pos = pos->suivant;
            }
            courant->suivant = pos->suivant;
            courant->precedent = pos;
            pos->suivant->precedent = courant;
            pos->suivant = courant;

            if (courant->donnee < triee->donnee) {
                triee = courant;
            }
        }

        courant = suivant;
    } while (courant != tete);

    return triee;
}


void Separer(Noeud* tete, Noeud** positifs, Noeud** negatifs) {
    if (tete == NULL) return;
    Noeud* courant = tete;
    do {
        if (courant->donnee >= 0) {
            ajouterFin(positifs, courant->donnee);
        } else {
            ajouterFin(negatifs, courant->donnee);
        }
        courant = courant->suivant;
    } while (courant != tete);
}

Noeud* Doublons(Noeud* tete) {
    if (tete == NULL) return NULL;

    Noeud* nouvelleTete = NULL;
    Noeud* courant = tete;
    do {

        int dejaExiste = 0;
        Noeud* verif = nouvelleTete;
        if (verif != NULL) {
            do {
                if (verif->donnee == courant->donnee) {
                    dejaExiste = 1;
                    break;
                }
                verif = verif->suivant;
            } while (verif != nouvelleTete);
        }
        if (!dejaExiste) {
            ajouterFin(&nouvelleTete, courant->donnee);
        }
        courant = courant->suivant;
    } while (courant != tete);

    return nouvelleTete;
}

Noeud* Inverser(Noeud* tete) {
    if (tete == NULL || tete->suivant == tete) return tete;

    Noeud* inversee = NULL;
    Noeud* courant = tete;

    do {
        Noeud* nouveau = creerNoeud(courant->donnee);
        if (inversee == NULL) {
            inversee = nouveau;
            inversee->suivant = inversee;
            inversee->precedent = inversee;
        } else {
            Noeud* dernier = inversee->precedent;
            nouveau->suivant = inversee;
            nouveau->precedent = dernier;
            dernier->suivant = nouveau;
            inversee->precedent = nouveau;
            inversee = nouveau;
        }
        courant = courant->suivant;
    } while (courant != tete);

    return inversee;
}

int main() {
    Noeud* liste = NULL;

    int n;
    printf("Entrez le nombre d'elements dans la liste : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int valeur;
        printf("Entrez l'element %d : ", i + 1);
        scanf("%d", &valeur);
        ajouterFin(&liste, valeur);
    }

    printf("Liste originale :\n");
    afficherListe(liste);
    Noeud* triee = Trier(liste);
    printf("Liste triée :\n");
    afficherListe(triee);

    Noeud* positifs = NULL;
    Noeud* negatifs = NULL;
    Separer(liste, &positifs, &negatifs);
    printf("Éléments positifs :\n");
    afficherListe(positifs);
    printf("Éléments négatifs :\n");
    afficherListe(negatifs);

    Noeud* sansDoublons = Doublons(liste);
    printf("Liste sans doublons :\n");
    afficherListe(sansDoublons);

    Noeud* inversee = Inverser(liste);
    printf("Liste inversée :\n");
    afficherListe(inversee);

    return 0;
}