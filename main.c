#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

typedef struct {
    int id;
    char nom[50];
    float prix;
    int quantite;
    char dateExpiration[20];
} Medicament;

typedef struct noeud{
   Medicament info;
   struct noeud* suivant;
} Noeud;

Noeud* tete = NULL;

typedef struct LigneVente {
    int idProduit;
    int quantite;
    float prixUnitaire;
    float prixLigne;
    struct LigneVente *suivant;
} LigneVente;
typedef struct Vente {
    int idVente;
    float prixTotal;
    float montantPaye;
    float reste;
    LigneVente *produits;
    struct Vente *suivant;
} Vente;
Vente *liste = NULL;
Medicament meds[100];
int n = 0;

HANDLE h;
// 11 = Cyan vif      Menu principal
// 10 = Vert vif      Gestion medicaments
//  9 = Bleu vif      Gestion stock
// 14 = Jaune vif     Gestion ventes
//  4 = Rouge         Quitter / erreur
//  7 = Blanc normal  texte par defaut

//1//
void ajouterMedicament() {
    Noeud* nouveau = (Noeud*)malloc(sizeof(Noeud));
    printf("ID: ");
    scanf("%d", &nouveau->info.id);
    printf("Nom: ");
    scanf("%s", nouveau->info.nom);
    printf("Prix: ");
    scanf("%f", &nouveau->info.prix);
    printf("Quantite: ");
    scanf("%d", &nouveau->info.quantite);
    printf("Date expiration: ");
    scanf("%s", nouveau->info.dateExpiration);
    nouveau->suivant = tete;
    tete = nouveau;
    SetConsoleTextAttribute(h, 10);
    printf("Medicament ajoute avec succes!\n");
    SetConsoleTextAttribute(h, 7);
}

//2//
void modifierMedicament(int id) {
    Noeud* courant = tete;
    while(courant != NULL){
        if(courant->info.id == id){
            printf("nouveau id: ");
            scanf("%d", &courant->info.id);
            printf("nouveau nom: "); scanf("%49s", courant->info.nom);
            printf("nouvelle quantite: "); scanf("%d", &courant->info.quantite);
            printf("nouveau prix: "); scanf("%f", &courant->info.prix);
            printf("nouvelle date Expiration: "); scanf("%9s", courant->info.dateExpiration);
            SetConsoleTextAttribute(h, 10);
            printf("Medicament modifie avec succes.\n");
            SetConsoleTextAttribute(h, 7);
            return;
        }
        courant=courant->suivant;
    }
    SetConsoleTextAttribute(h, 4);
    printf("Medicament non trouve\n");
    SetConsoleTextAttribute(h, 7);
}

//3//
void supprimer(int id) {
    Noeud* courant = tete;
    Noeud* prev = NULL;
    if(courant != NULL && courant->info.id == id){
        tete = courant->suivant;
        free(courant);
        SetConsoleTextAttribute(h, 10);
        printf("Medicament supprime avec succes.\n");
        SetConsoleTextAttribute(h, 7);
        return;
    }
    while(courant != NULL && courant->info.id != id){
        prev = courant;
        courant = courant->suivant;
    }
    if(courant == NULL){
        SetConsoleTextAttribute(h, 4);
        printf("Medicament non trouve\n");
        SetConsoleTextAttribute(h, 7);
        return;
    }
    prev->suivant = courant->suivant;
    free(courant);
    SetConsoleTextAttribute(h, 10);
    printf("Medicament supprime avec succes.\n");
    SetConsoleTextAttribute(h, 7);
}

//4//
void afficherMedicamentExpires(char dateAujourdhui[]){
    Noeud* courant = tete;
    SetConsoleTextAttribute(h, 4);
    printf("\nLes medicaments expires sont:\n");
    printf("  +---------------------------------+\n");
    SetConsoleTextAttribute(h, 7);
    while(courant != NULL){
        if(strcmp(courant->info.dateExpiration, dateAujourdhui) < 0){
            printf("  ID: %d | Nom: %s | Prix: %.2f | Exp: %s\n",
                courant->info.id, courant->info.nom,
                courant->info.prix, courant->info.dateExpiration);
        }
        courant = courant->suivant;
    }
    SetConsoleTextAttribute(h, 10);
    printf("\nLes medicaments valides sont:\n");
    printf("  +---------------------------------+\n");
    SetConsoleTextAttribute(h, 7);
    courant = tete;
    while(courant != NULL){
        if(strcmp(courant->info.dateExpiration, dateAujourdhui) >= 0){
            printf("  ID: %d | Nom: %s | Prix: %.2f | Exp: %s\n",
                courant->info.id, courant->info.nom,
                courant->info.prix, courant->info.dateExpiration);
        }
        courant = courant->suivant;
    }
}

//0//
void sauvegarderDansFichier(const char* nomFichier){
    FILE* f = fopen(nomFichier, "w");
    if(f == NULL){
        SetConsoleTextAttribute(h, 4);
        printf("Erreur ouverture fichier\n");
        SetConsoleTextAttribute(h, 7);
        return;
    }
    Noeud* courant = tete;
    while(courant != NULL){
        fprintf(f, "%d %s %.2f %d %s\n",
                courant->info.id, courant->info.nom,
                courant->info.prix, courant->info.quantite,
                courant->info.dateExpiration);
        courant = courant->suivant;
    }
    fclose(f);
    SetConsoleTextAttribute(h, 10);
    printf("Donnees sauvegardees avec succes.\n");
    SetConsoleTextAttribute(h, 7);
}

//5.a//
void RechercheParNom(char nom_med[]){
    Noeud* courant = tete;
    while (courant != NULL) {
        if (strcmp(courant->info.nom, nom_med) == 0) {
            SetConsoleTextAttribute(h, 9);
            printf("\n  Medicament trouve:\n");
            printf("  +---------------------------+\n");
            SetConsoleTextAttribute(h, 7);
            printf("  Nom:        %s\n", courant->info.nom);
            printf("  ID:         %d\n", courant->info.id);
            printf("  Prix:       %.2f DT\n", courant->info.prix);
            printf("  Quantite:   %d\n", courant->info.quantite);
            printf("  Expiration: %s\n", courant->info.dateExpiration);
            SetConsoleTextAttribute(h, 9);
            printf("  +---------------------------+\n");
            SetConsoleTextAttribute(h, 7);
            return;
        }
        courant = courant->suivant;
    }
    SetConsoleTextAttribute(h, 4);
    printf("Produit introuvable\n");
    SetConsoleTextAttribute(h, 7);
}

//5.b//
void RechercheParID(int id_med){
    Noeud* courant = tete;
    while (courant != NULL) {
        if (courant->info.id == id_med) {
            SetConsoleTextAttribute(h, 9);
            printf("\n  Medicament trouve:\n");
            printf("  +---------------------------+\n");
            SetConsoleTextAttribute(h, 7);
            printf("  Nom:        %s\n", courant->info.nom);
            printf("  ID:         %d\n", courant->info.id);
            printf("  Prix:       %.2f DT\n", courant->info.prix);
            printf("  Quantite:   %d\n", courant->info.quantite);
            printf("  Expiration: %s\n", courant->info.dateExpiration);
            SetConsoleTextAttribute(h, 9);
            printf("  +---------------------------+\n");
            SetConsoleTextAttribute(h, 7);
            return;
        }
        courant = courant->suivant;
    }
    SetConsoleTextAttribute(h, 4);
    printf("Produit introuvable\n");
    SetConsoleTextAttribute(h, 7);
}

//6//
void affichage_stock(){
    Noeud* courant;
    int compteur = 0;
    SetConsoleTextAttribute(h, 9);
    printf("\n  Les medicaments en stock:\n");
    printf("  +-----------------------------------------------+\n");
    SetConsoleTextAttribute(h, 7);
    courant = tete;
    while (courant != NULL) {
        if (courant->info.quantite > 0) {
            printf("  Nom: %-20s | ID: %d | Quantite: %d\n",
                courant->info.nom, courant->info.id, courant->info.quantite);
            compteur++;
        }
        courant = courant->suivant;
    }
    if (compteur == 0)
        printf("  Aucun medicament en stock.\n");

    compteur = 0;
    SetConsoleTextAttribute(h, 4);
    printf("\n  Les medicaments en rupture de stock:\n");
    printf("  +-----------------------------------------------+\n");
    SetConsoleTextAttribute(h, 7);
    courant = tete;
    while (courant != NULL) {
        if (courant->info.quantite == 0) {
            printf("  Nom: %-20s | ID: %d\n",
                courant->info.nom, courant->info.id);
            compteur++;
        }
        courant = courant->suivant;
    }
    if (compteur == 0)
        printf("  Aucun medicament en rupture de stock.\n");
}

//8//
void MiseAJourApresApprovisionnement(){
    int IDAppro, QAppro;
    printf("Donner le ID du medicament approvisionne: "); scanf("%d",&IDAppro);
    printf("Donner la quantite: "); scanf("%d",&QAppro);
    Noeud* courant = tete;
    while (courant != NULL) {
        if (courant->info.id == IDAppro) {
            courant->info.quantite += QAppro;
            SetConsoleTextAttribute(h, 10);
            printf("Stock mis a jour. Nouvelle quantite: %d\n", courant->info.quantite);
            SetConsoleTextAttribute(h, 7);
            return;
        }
        courant = courant->suivant;
    }
    SetConsoleTextAttribute(h, 4);
    printf("Medicament introuvable.\n");
    SetConsoleTextAttribute(h, 7);
}

void chargerDepuisFichier(const char* nomFichier) {
    FILE* f = fopen(nomFichier, "r");
    if (f == NULL) {
        SetConsoleTextAttribute(h, 4);
        printf("  Erreur ouverture fichier !\n");
        SetConsoleTextAttribute(h, 7);
        return;}
    Medicament temp;
    while (fscanf(f, "%d %s %f %d %s",&temp.id,temp.nom,&temp.prix,&temp.quantite,temp.dateExpiration) == 5){
        Noeud* nouveau = (Noeud*) malloc(sizeof(Noeud));
        if (nouveau == NULL) {
            SetConsoleTextAttribute(h, 4);
            printf("  Erreur d'allocation memoire.\n");
            SetConsoleTextAttribute(h, 7);
            break;}
        nouveau->info = temp;
        nouveau->suivant = tete;
        tete = nouveau;}
    fclose(f);
    SetConsoleTextAttribute(h, 10);
    printf("  Donnees chargees avec succes.\n");
    SetConsoleTextAttribute(h, 7);}

//10//
float calculerTotal(int quantite, float prixUnitaire) {
    return quantite * prixUnitaire;
}

//9//
Vente* ajouterVente(Vente *liste) {
    Vente *nouvelleVente;
    LigneVente *nouveauProduit;
    int nbProduits, i;
    nouvelleVente = (Vente*) malloc(sizeof(Vente));
    if (nouvelleVente == NULL) {
        SetConsoleTextAttribute(h, 4);
        printf("Erreur d'allocation memoire.\n");
        SetConsoleTextAttribute(h, 7);
        return liste;
    }
    SetConsoleTextAttribute(h, 14);
    printf("\n  +========================================+\n");
    printf("  |            NOUVELLE VENTE              |\n");
    printf("  +========================================+\n");
    SetConsoleTextAttribute(h, 7);
    printf("\n  ID vente: ");
    scanf("%d", &nouvelleVente->idVente);
    nouvelleVente->prixTotal = 0;
    nouvelleVente->produits = NULL;
    printf("  Combien de produits voulez-vous vendre ? ");
    scanf("%d", &nbProduits);
    for (i = 1; i <= nbProduits; i++) {
        nouveauProduit = (LigneVente*) malloc(sizeof(LigneVente));
        if (nouveauProduit == NULL) {
            SetConsoleTextAttribute(h, 4);
            printf("  Erreur d'allocation memoire.\n");
            SetConsoleTextAttribute(h, 7);
            return liste;
        }
        SetConsoleTextAttribute(h, 14);
        printf("\n  +------------------------------------------+\n");
        printf("  |            Produit numero %-3d            |\n", i);
        printf("  +------------------------------------------+\n");
        SetConsoleTextAttribute(h, 7);
        printf("  ID produit: ");
        scanf("%d", &nouveauProduit->idProduit);
        Noeud *courant = tete;
        int trouve = 0;
        while (courant != NULL) {
            if (courant->info.id == nouveauProduit->idProduit) {
                trouve = 1;
                SetConsoleTextAttribute(h, 10);
                printf("\n  Medicament trouve : %s\n", courant->info.nom);
                printf("  Prix unitaire     : %.2f DT\n", courant->info.prix);
                printf("  Quantite dispo    : %d\n", courant->info.quantite);
                SetConsoleTextAttribute(h, 7);
                nouveauProduit->prixUnitaire = courant->info.prix;
                printf("\n  Quantite a vendre : ");
                scanf("%d", &nouveauProduit->quantite);
                if (nouveauProduit->quantite <= 0) {
                    SetConsoleTextAttribute(h, 4);
                    printf("  Quantite invalide !\n");
                    SetConsoleTextAttribute(h, 7);
                    free(nouveauProduit);
                    i--;
                    break;}
                if (nouveauProduit->quantite > courant->info.quantite) {
                    SetConsoleTextAttribute(h, 4);
                    printf("  Stock insuffisant ! Stock actuel : %d\n", courant->info.quantite);
                    SetConsoleTextAttribute(h, 7);
                    free(nouveauProduit);
                    i--;
                    break;}
                courant->info.quantite = courant->info.quantite - nouveauProduit->quantite;
                SetConsoleTextAttribute(h, 10);
                printf("  Stock mis a jour. Nouvelle quantite : %d\n", courant->info.quantite);
                SetConsoleTextAttribute(h, 7);
                nouveauProduit->prixLigne = calculerTotal(nouveauProduit->quantite,nouveauProduit->prixUnitaire);
                nouvelleVente->prixTotal = nouvelleVente->prixTotal + nouveauProduit->prixLigne;
                nouveauProduit->suivant = nouvelleVente->produits;
                nouvelleVente->produits = nouveauProduit;
                SetConsoleTextAttribute(h, 14);
                printf("  Total de ce produit : %.2f DT\n", nouveauProduit->prixLigne);
                SetConsoleTextAttribute(h, 7);
                break;
            }
            courant = courant->suivant;
        }
        if (trouve == 0) {
            SetConsoleTextAttribute(h, 4);
            printf("  Medicament ID %d introuvable !\n", nouveauProduit->idProduit);
            SetConsoleTextAttribute(h, 7);
            free(nouveauProduit);
            i--;
            continue;}
    }
    SetConsoleTextAttribute(h, 14);
    printf("\n  +========================================+\n");
    printf("  |              RECAPITULATIF               |\n");
    printf("  +==========================================+\n");
    printf("  Montant total a payer    : %.2f DT\n", nouvelleVente->prixTotal);
    SetConsoleTextAttribute(h, 7);
    printf("  Montant donne par le client : ");
    scanf("%f", &nouvelleVente->montantPaye);
    SetConsoleTextAttribute(h, 14);
    printf("\n  Montant total a payer    : %.2f DT\n", nouvelleVente->prixTotal);
    printf("  Montant donne par client : %.2f DT\n", nouvelleVente->montantPaye);
    SetConsoleTextAttribute(h, 7);
    if (nouvelleVente->montantPaye >= nouvelleVente->prixTotal) {
        nouvelleVente->reste = nouvelleVente->montantPaye - nouvelleVente->prixTotal;
        SetConsoleTextAttribute(h, 10);
        printf("  Paiement suffisant.\n");
        printf("  Reste a rendre : %.2f DT\n", nouvelleVente->reste);
    }
    else {
        nouvelleVente->reste = nouvelleVente->prixTotal - nouvelleVente->montantPaye;
        SetConsoleTextAttribute(h, 4);
        printf("  Paiement insuffisant.\n");
        printf("  Reste a payer  : %.2f DT\n", nouvelleVente->reste);}
    SetConsoleTextAttribute(h, 7);
    nouvelleVente->suivant = liste;
    liste = nouvelleVente;
    return liste;
}
void afficherHistorique(Vente *liste) {
    Vente *p;
    LigneVente *prod;
    int i = 1, j;
    if (liste == NULL) {
        SetConsoleTextAttribute(h, 4);
        printf("\nAucune vente enregistree.\n");
        SetConsoleTextAttribute(h, 7);
        return;
    }
    SetConsoleTextAttribute(h, 14);
    printf("\n  +========================================+\n");
    printf("  |        HISTORIQUE DES VENTES             |\n");
    printf("  +==========================================+\n");
    SetConsoleTextAttribute(h, 7);

    p = liste;
    while (p != NULL) {
        SetConsoleTextAttribute(h, 14);
        printf("\n  ---- Vente numero %d ----\n", i);
        SetConsoleTextAttribute(h, 7);
        printf("  ID vente: %d\n", p->idVente);
        printf("\n  Produits vendus:\n");
        SetConsoleTextAttribute(h, 14);
        printf("  +------------------------------------------+\n");
        SetConsoleTextAttribute(h, 7);
        prod = p->produits;
        j = 1;
        while (prod != NULL) {
            printf("  Produit %d:\n", j);
            printf("    ID produit:    %d\n",      prod->idProduit);
            printf("    Quantite:      %d\n",      prod->quantite);
            printf("    Prix unitaire: %.2f DT\n", prod->prixUnitaire);
            printf("    Total produit: %.2f DT\n", prod->prixLigne);
            prod = prod->suivant;
            j++;
        }
        SetConsoleTextAttribute(h, 14);
        printf("  +------------------------------------------+\n");
        printf("  Montant total: %.2f DT\n", p->prixTotal);
        printf("  Montant donne: %.2f DT\n", p->montantPaye);
        SetConsoleTextAttribute(h, 7);
        if (p->montantPaye >= p->prixTotal) {
            SetConsoleTextAttribute(h, 10);
            printf("  Paiement: suffisant\n");
            printf("  Reste a rendre: %.2f DT\n", p->reste);
        }
        else {
            SetConsoleTextAttribute(h, 4);
            printf("  Paiement: insuffisant\n");
            printf("  Reste a payer: %.2f DT\n", p->reste);}
        SetConsoleTextAttribute(h, 7);
        p = p->suivant;
        i++;
    }
}

int main(){
    int c1=0, c2=0, c3=0, id_med=0;
    char nom_medic[50], date_auj[20];
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    chargerDepuisFichier("medicaments.txt");  // ✅ chargement au démarrage
    do {
        system("cls");
        SetConsoleTextAttribute(h, 11);
        printf("\n");
        printf("          +=========================================+\n");
        printf("          |         GESTION DE PHARMACIE            |\n");
        printf("          +=========================================+\n");
        SetConsoleTextAttribute(h, 7);
        printf("          |                                         |\n");
        printf("          |   1. Gestion de medicaments             |\n");
        printf("          |   2. Gestion de stock                   |\n");
        printf("          |   3. Gestion de ventes                  |\n");
        printf("          |   4. Sauvegarder dans un fichier        |\n");
        printf("          |   5. Charger depuis un fichier          |\n");  // ✅ nouvelle option
        SetConsoleTextAttribute(h, 4);
        printf("          |   6. Quitter                            |\n");  // ✅ était 5
        SetConsoleTextAttribute(h, 11);
        printf("          |                                         |\n");
        printf("          +=========================================+\n");
        SetConsoleTextAttribute(h, 7);
        printf("          Votre choix : ");
        scanf("%d", &c1);
        while(getchar() != '\n');
        system("cls");
        if(c1 == 1) {
            do {
                system("cls");
                SetConsoleTextAttribute(h, 10);
                printf("\n");
                printf("          +=========================================+\n");
                printf("          |        GESTION DE MEDICAMENTS           |\n");
                printf("          +=========================================+\n");
                SetConsoleTextAttribute(h, 7);
                printf("          |                                         |\n");
                printf("          |   1. Ajouter un medicament              |\n");
                printf("          |   2. Modifier un medicament             |\n");
                printf("          |   3. Supprimer un medicament            |\n");
                printf("          |   4. Afficher medicaments expires       |\n");
                SetConsoleTextAttribute(h, 4);
                printf("          |   0. Retour au menu principal           |\n");
                SetConsoleTextAttribute(h, 10);
                printf("          |                                         |\n");
                printf("          +=========================================+\n");
                SetConsoleTextAttribute(h, 7);
                printf("          Votre choix : ");
                scanf("%d", &c2);
                while(getchar() != '\n');
                system("cls");
                if(c2 == 1)
                    ajouterMedicament();
                else if(c2 == 2){
                    printf("Donner le ID du medicament a modifier: ");
                    scanf("%d", &id_med);
                    while(getchar() != '\n');
                    modifierMedicament(id_med);}
                else if(c2 == 3){
                    printf("Donner le ID du medicament a supprimer: ");
                    scanf("%d", &id_med);
                    while(getchar() != '\n');
                    supprimer(id_med);}
                else if(c2 == 4){
                    printf("Date d'aujourd'hui (AAAA-MM-JJ): ");
                    scanf("%19s", date_auj);
                    while(getchar() != '\n');
                    afficherMedicamentExpires(date_auj);}
                else if(c2 != 0){
                    SetConsoleTextAttribute(h, 4);
                    printf("Choix invalide!\n");
                    SetConsoleTextAttribute(h, 7);}
                if(c2 != 0) system("pause");
            } while(c2 != 0);}
        else if(c1 == 2) {
            do {
                system("cls");
                SetConsoleTextAttribute(h, 9);
                printf("\n");
                printf("          +=========================================+\n");
                printf("          |           GESTION DE STOCK              |\n");
                printf("          +=========================================+\n");
                SetConsoleTextAttribute(h, 7);
                printf("          |                                         |\n");
                printf("          |   1. Rechercher un medicament           |\n");
                printf("          |   2. Afficher stock et ruptures         |\n");
                printf("          |   3. Mise a jour apres approvisionnement|\n");
                SetConsoleTextAttribute(h, 4);
                printf("          |   0. Retour au menu principal           |\n");
                SetConsoleTextAttribute(h, 9);
                printf("          |                                         |\n");
                printf("          +=========================================+\n");
                SetConsoleTextAttribute(h, 7);
                printf("          Votre choix : ");
                scanf("%d", &c2);
                while(getchar() != '\n');
                system("cls");
                if(c2 == 1){
                    SetConsoleTextAttribute(h, 9);
                    printf("  Rechercher par : 1. Nom   2. ID\n");
                    SetConsoleTextAttribute(h, 7);
                    printf("  Votre choix : ");
                    scanf("%d", &c3);
                    while(getchar() != '\n');
                    if(c3 == 1){
                        printf("  Nom du medicament : ");
                        scanf("%49s", nom_medic);
                        while(getchar() != '\n');
                        RechercheParNom(nom_medic);}
                    else if(c3 == 2){
                        printf("  ID du medicament : ");
                        scanf("%d", &id_med);
                        while(getchar() != '\n');
                        RechercheParID(id_med);}
                    else {
                        SetConsoleTextAttribute(h, 4);
                        printf("Choix invalide!\n");
                        SetConsoleTextAttribute(h, 7);}
                }
                else if(c2 == 2)
                    affichage_stock();
                else if(c2 == 3)
                    MiseAJourApresApprovisionnement();
                else if(c2 != 0){
                    SetConsoleTextAttribute(h, 4);
                    printf("Choix invalide!\n");
                    SetConsoleTextAttribute(h, 7);
                }
                if(c2 != 0) system("pause");
            } while(c2 != 0);
        }

        else if(c1 == 3) {
            do {
                system("cls");
                SetConsoleTextAttribute(h, 14);
                printf("\n");
                printf("          +=========================================+\n");
                printf("          |           GESTION DE VENTES             |\n");
                printf("          +=========================================+\n");
                SetConsoleTextAttribute(h, 7);
                printf("          |                                         |\n");
                printf("          |   1. Enregistrer une vente              |\n");
                printf("          |   2. Afficher l'historique des ventes   |\n");
                SetConsoleTextAttribute(h, 4);
                printf("          |   0. Retour au menu principal           |\n");
                SetConsoleTextAttribute(h, 14);
                printf("          |                                         |\n");
                printf("          +=========================================+\n");
                SetConsoleTextAttribute(h, 7);
                printf("          Votre choix : ");
                scanf("%d", &c2);
                while(getchar() != '\n');
                system("cls");
                if(c2 == 1)
                    liste = ajouterVente(liste);
                else if(c2 == 2)
                    afficherHistorique(liste);
                else if(c2 != 0){
                    SetConsoleTextAttribute(h, 4);
                    printf("Choix invalide!\n");
                    SetConsoleTextAttribute(h, 7);
                }
                if(c2 != 0) system("pause");}
            while(c2 != 0);}
        else if(c1 == 4){
            sauvegarderDansFichier("medicaments.txt");
            system("pause");}
        else if(c1 == 5){                               
            chargerDepuisFichier("medicaments.txt");
            system("pause");}
        else if(c1 != 6){                             
            SetConsoleTextAttribute(h, 4);
            printf("Choix invalide!\n");
            SetConsoleTextAttribute(h, 7);
            system("pause");}
    } while(c1 != 6);                                  
    SetConsoleTextAttribute(h, 11);
    printf("\n          Au revoir !\n\n");
    SetConsoleTextAttribute(h, 7);
    return 0;
}
