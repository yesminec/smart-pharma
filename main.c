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
   struct noeud* suivant;} Noeud;
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
//1//
void ajouterMedicament() {
Noeud* nouveau = (Noeud*)malloc(sizeof(Noeud));
    printf("ID: ");
    scanf("%d", &nouveau->info.id);
    printf("Nom: ");
    scanf("%s", nouveau->info.nom);
    printf("Prix: ");
    scanf("%f", &nouveau->info.prix);
    printf("Quantité: ");
    scanf("%d", &nouveau->info.quantite);
    printf("Date expiration: ");
    scanf("%s", nouveau->info.dateExpiration);
    nouveau->suivant = tete;
    tete = nouveau;
    printf("Médicament ajouté avec succés!\n");
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
            printf("medicament modifié avec succes.\n");
            return;
        }
        courant=courant->suivant;
    }
    printf("medicament non trouve\n");
}
//3//
void supprimer (int id) {
    Noeud* courant = tete;
    Noeud* prev = NULL;
    if(courant != NULL && courant->info.id == id){
        tete = courant->suivant;
        free(courant);
        printf("Médicament supprimé avec succès.\n");
        return;
    }
    while(courant != NULL && courant->info.id != id){
        prev = courant;
        courant = courant->suivant;
    }
    if(courant == NULL){
        printf("medicament non trouve\n");
        return;
    }
    prev->suivant = courant->suivant;
    free(courant);
    printf("Médicament supprimé avec succès.\n");
}
//4//
void afficherMedicamentExpires(char dateAujourdhui[]){
    Noeud* courant = tete;
    printf("Les médicaments expirés sont: \n");
    while(courant != NULL){
        if(strcmp(courant->info.dateExpiration, dateAujourdhui) < 0){
            printf("ID: %d\n", courant->info.id);
            printf("nom: %s\n", courant->info.nom);
            printf("prix: %.2f\n", courant->info.prix);
            printf("date expiration: %s\n\n", courant->info.dateExpiration);
        }
        courant = courant->suivant;
    }
    courant = tete;
    printf("Les médicaments valides sont: \n");
    while(courant != NULL){
        if(strcmp(courant->info.dateExpiration, dateAujourdhui) >= 0){
            printf("ID: %d\n", courant->info.id);
            printf("nom: %s\n", courant->info.nom);
            printf("prix: %.2f\n", courant->info.prix);
            printf("date expiration: %s\n\n", courant->info.dateExpiration);
        }
        courant = courant->suivant;
    }
}
//0//
void sauvegarderDansFichier(const char* nomFichier){
    FILE* f = fopen(nomFichier, "w");
    if(f == NULL){
        printf("Erreur ouverture fichier\n");
        return;
    }
    Noeud* courant = tete;
    while(courant != NULL){
        fprintf(f, "%d %s %.2f %d %s\n",courant->info.id,courant->info.nom,courant->info.prix,courant->info.quantite,courant->info.dateExpiration);
        courant = courant->suivant;
    }
    fclose(f);
    printf("Données sauvegardées avec succés.\n");
}
//5.a//
void RechercheParNom(char nom_med[]){
    Noeud* courant = tete;
    while (courant != NULL) {
        if (strcmp(courant->info.nom, nom_med) == 0) {
            printf("Médicament trouvé:\n");
            printf("Nom: %s\n",  courant->info.nom);
            printf("ID: %d\n",   courant->info.id);
            printf("Prix: %.2f\n", courant->info.prix);
            printf("Quantité: %d\n", courant->info.quantite);
            printf("Expiration: %s\n", courant->info.dateExpiration);
            return;
        }
        courant = courant->suivant;
        }
    printf("Produit introuvable");
}
//5.b//
void RechercheParID(int id_med){
    Noeud* courant = tete;
    while (courant != NULL) {
        if (courant->info.id == id_med) {
           printf("Médicament trouvé:\n");
           printf("Nom: %s\n",  courant->info.nom);
           printf("ID: %d\n",   courant->info.id);
           printf("Prix: %.2f\n", courant->info.prix);
           printf("Quantité: %d\n", courant->info.quantite);
           printf("Expiration: %s\n", courant->info.dateExpiration);
           return;
        }
        courant=courant->suivant;
        }
    printf("Produit introuvable");
}
//6//
void affichage_stock(){
    Noeud* courant;
    int compteur = 0;
    printf("Les médicaments en stock:\n");
    courant = tete;
    while (courant != NULL) {
        if (courant->info.quantite > 0) {
            printf("Nom: %s | ID: %d | Quantité: %d\n",
                courant->info.nom,
                courant->info.id,
                courant->info.quantite);
            compteur++;
        }
        courant = courant->suivant;
    }
    if (compteur == 0)
        printf("Aucun médicament en stock.\n");
    compteur = 0;
    printf("Les médicaments en rupture de stock: \n");
    courant = tete;
    while (courant != NULL) {
        if (courant->info.quantite == 0) {
            printf("Nom: %s | ID: %d\n",
                courant->info.nom,
                courant->info.id);
            compteur++;
        }
        courant = courant->suivant;
    }
    if (compteur == 0)
        printf("Aucun médicament en rupture de stock.\n");
}
//8//
void MiseAJourApresApprovisionnement(){
    int IDAppro, QAppro;
    printf("Donner le ID du médicament approvisionné"); scanf("%d",&IDAppro);
    printf("Donner la quantité"); scanf("%d",&QAppro);
    Noeud* courant = tete;
    while (courant != NULL) {
        if (courant->info.id == IDAppro) {
            courant->info.quantite += QAppro;
            printf("Stock mis à jour. Nouvelle quantité: %d\n",
                    courant->info.quantite);
            return;
        }
        courant = courant->suivant;
    }
    printf("Médicament introuvable.\n");
}
//9//
float calculerTotal(int quantite, float prixUnitaire) {
    return quantite * prixUnitaire;
}
//10//
Vente* ajouterVente(Vente *liste) {
    Vente *nouvelleVente;
    LigneVente *nouveauProduit;
    int nbProduits, i;
    nouvelleVente = (Vente*) malloc(sizeof(Vente));
    if (nouvelleVente == NULL) {
        printf("Erreur d'allocation memoire.\n");
        return liste;
    }
    printf("\n--- Nouvelle vente ---\n");
    printf("ID vente: ");
    scanf("%d", &nouvelleVente->idVente);
    nouvelleVente->prixTotal = 0;
    nouvelleVente->produits = NULL;
    printf("Combien de produits voulez-vous vendre ? ");
    scanf("%d", &nbProduits);
    for (i = 1; i <= nbProduits; i++) {
        nouveauProduit = (LigneVente*) malloc(sizeof(LigneVente));
        if (nouveauProduit == NULL) {
            printf("Erreur d'allocation memoire.\n");
            return liste;
        }
        printf("\n--- Produit numero %d ---\n", i);
        printf("ID produit: ");
        scanf("%d", &nouveauProduit->idProduit);
        Noeud *courant = tete;
        int trouve = 0;
        while (courant != NULL) {
            if (courant->info.id == nouveauProduit->idProduit) {
                trouve = 1;
                printf("Medicament trouve: %s\n", courant->info.nom);
                printf("Prix unitaire automatique: %.2f DT\n", courant->info.prix);
                printf("Quantite disponible: %d\n", courant->info.quantite);
                nouveauProduit->prixUnitaire = courant->info.prix;
                printf("Quantite: ");
                scanf("%d", &nouveauProduit->quantite);
                if (nouveauProduit->quantite <= 0) {
                    printf("Quantite invalide.\n");
                    free(nouveauProduit);
                    i--;
                    break;}
                if (nouveauProduit->quantite > courant->info.quantite) {
                    printf("Stock insuffisant.\n");
                    printf("Quantite disponible: %d\n", courant->info.quantite);
                    free(nouveauProduit);
                    i--;
                    break;}
                courant->info.quantite = courant->info.quantite - nouveauProduit->quantite;
                printf("Stock mis a jour. Nouvelle quantite: %d\n", courant->info.quantite);
                nouveauProduit->prixLigne = calculerTotal(nouveauProduit->quantite,nouveauProduit->prixUnitaire);
                nouvelleVente->prixTotal = nouvelleVente->prixTotal + nouveauProduit->prixLigne;
                nouveauProduit->suivant = nouvelleVente->produits;
                nouvelleVente->produits = nouveauProduit;
                printf("Total de ce produit: %.2f DT\n", nouveauProduit->prixLigne);
                break;}
            courant = courant->suivant;}
        if (trouve == 0) {
            printf("Medicament introuvable.\n");
            free(nouveauProduit);
            i--;
            continue;}
    }
    printf("\nMontant total a payer: %.2f DT\n", nouvelleVente->prixTotal);
    printf("Montant donne par le client: "); scanf("%f", &nouvelleVente->montantPaye);
    printf("\nMontant total a payer: %.2f DT\n", nouvelleVente->prixTotal);
    printf("Montant donne par le client: %.2f DT\n", nouvelleVente->montantPaye);
    if (nouvelleVente->montantPaye >= nouvelleVente->prixTotal){
        nouvelleVente->reste = nouvelleVente->montantPaye - nouvelleVente->prixTotal;
        printf("Paiement suffisant.\n");
        printf("Reste a rendre: %.2f DT\n", nouvelleVente->reste);}
    else {
        nouvelleVente->reste = nouvelleVente->prixTotal - nouvelleVente->montantPaye;
        printf("Paiement insuffisant.\n");
        printf("Reste a payer: %.2f DT\n", nouvelleVente->reste);}
    nouvelleVente->suivant = liste;
    liste = nouvelleVente;
    return liste;}

void afficherHistorique(Vente *liste) {
    Vente *p;
    LigneVente *prod;
    int i = 1;
    int j;
    if (liste == NULL) {
        printf("\nAucune vente enregistree.\n");}
    else {
        printf("\n--- Historique des ventes ---\n");
        p = liste;
        while (p != NULL) {
            printf("\n============================\n");
            printf("Vente numero %d\n", i);
            printf("ID vente: %d\n", p->idVente);
            printf("\nProduits vendus:\n");
            prod = p->produits;
            j = 1;
            while (prod != NULL) {
                printf("\nProduit numero %d\n", j);
                printf("ID produit: %d\n", prod->idProduit);
                printf("Quantite: %d\n", prod->quantite);
                printf("Prix unitaire: %.2f DT\n", prod->prixUnitaire);
                printf("Total produit: %.2f DT\n", prod->prixLigne);
                prod = prod->suivant;
                j++;}
            printf("\nMontant total de la vente: %.2f DT\n", p->prixTotal);
            printf("Montant donne: %.2f DT\n", p->montantPaye);
            if (p->montantPaye >= p->prixTotal) {
                printf("Paiement: suffisant\n");
                printf("Reste a rendre: %.2f DT\n", p->reste);}
            else {
                printf("Paiement: insuffisant\n");
                printf("Reste a payer: %.2f DT\n", p->reste);}
            p = p->suivant;
            i++;
        }
    }
}
int main(){
    int c1=0,c2=0,c3=0,id_med=0,q=0; float pUnitaire=0;
    char nom_medic[50], date_auj[10];
    do{
        system("chcp 65001");
        system("cls");
        printf("Choisir quelle fonctionnalité à appliquer:\n");
        printf("1. Gestion de médicaments\n");
        printf("2. Gestion de stock\n");
        printf("3. Gestion de ventes\n");
        printf("4. Enregistrement dans un fichier\n");
        printf("5. Quitter\n");
        scanf("%d",&c1);
        while(getchar() != '\n');
        system("cls");
        if(c1==1){
            do{
                system("cls");
                printf("Gestion de médicaments:\n");
                printf("1. Ajouter un médicament\n");
                printf("2. Modifier un médicament\n");
                printf("3. Supprimer un médicament\n");
                printf("4. Afficher tous les médicaments expirés\n");
                printf("0. Retour au menu principal\n");
                scanf("%d", &c2);
                while(getchar() != '\n');
                system("cls");
                if(c2==1)
                    ajouterMedicament();
                else if(c2==2){
                    printf("Donner le ID du médicament à modifier: \n");
                    scanf("%d", &id_med);
                    while(getchar() != '\n');
                    modifierMedicament(id_med);
                }
                else if(c2==3){
                    printf("Donner le ID du médicament à supprimer: \n");
                    scanf("%d", &id_med);
                    while(getchar() != '\n');
                    supprimer(id_med);
                }
                else if(c2==4){
                    printf("Date d'aujourd'hui: \n");
                    scanf("%9s", date_auj);
                    while(getchar() != '\n');
                    afficherMedicamentExpires(date_auj);
                }
                else if(c2 != 0)
                    printf("Choix invalide!\n");
                if(c2 != 0) system("pause");
            } while(c2 != 0); 
        }

        else if(c1==2){
            do{
                system("cls");
                printf("Gestion de stock:\n");
                printf("1. Rechercher un médicament\n");
                printf("2. Afficher les médicaments en stock et ceux en rupture\n");
                printf("3. Mise à jour après approvisionnement\n");
                printf("0. Retour au menu principal\n");
                scanf("%d", &c2);
                while(getchar() != '\n');
                system("cls");
                if(c2==1){
                    printf("Choisir: 1.Par Nom ou 2.Par ID\n");
                    scanf("%d",&c3);
                    while(getchar() != '\n');
                    if(c3==1){
                        printf("Donner le nom du médicament à chercher: ");
                        scanf("%49s", nom_medic);
                        while(getchar() != '\n');
                        RechercheParNom(nom_medic);
                    }
                    else if(c3==2){
                        printf("Donner le ID du médicament à chercher: ");
                        scanf("%d",&id_med);
                        while(getchar() != '\n');
                        RechercheParID(id_med);
                    }
                    else
                        printf("Choix invalide!\n");
                }
                else if(c2==2)
                    affichage_stock();
                else if(c2==3)
                    MiseAJourApresApprovisionnement();
                else if(c2 != 0)
                    printf("Choix invalide!\n");
                if(c2 != 0) system("pause");
            } while(c2 != 0);
        }
        else if(c1==3){
            do{
                system("cls");
                printf("Gestion de ventes:\n");
                printf("1. Enregistrer une vente\n");
                printf("2. Afficher l'historique des ventes\n");
                printf("0. Retour au menu principal\n");
                printf("Votre choix: ");
                scanf("%d", &c2);
                while(getchar() != '\n');
                system("cls");
                if(c2==1)
                    liste = ajouterVente(liste);
                else if(c2==2)
                    afficherHistorique(liste);
                else if(c2 != 0)
                    printf("Choix invalide!\n");
                if(c2 != 0)
                    system("pause");
            } while(c2 != 0);
        }
        else if(c1==4){
            sauvegarderDansFichier("medicaments.txt");
            system("pause");
        }
        else if(c1 != 5)
            printf("Choix invalide!\n");
    } while(c1 != 5);
}
