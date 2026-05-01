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
    printf("Quantit�: ");
    scanf("%d", &nouveau->info.quantite);
    printf("Date expiration: ");
    scanf("%s", nouveau->info.dateExpiration);
    nouveau->suivant = tete;
    tete = nouveau;
    printf("M�dicament ajout� avec succ�s!\n");
}
//2//
void modifierMedicament (int id) {
for(int i=0;i<n;i++) {
    if (meds[i].id==id) {
        printf("nouveau id:");
        scanf("%d", &meds[i].id);
        printf("nouveau nom:");
        scanf("%s", meds[i].nom);
        printf("nouvelle quantite:");
        scanf("%d", &meds[i].quantite);
        printf("nouveau prix:");
        scanf("%f", &meds[i].prix);
        printf("nouvelle date Expiration:");
        scanf("%s", meds[i].dateExpiration);
        printf("medicament modifi� avec succ�s.\n");
        return;
    }
}
printf("medicament non trouver");
}
//3//
void supprimer (int id) {
    for (int i=0;i<n;i++) {
        if (meds[i].id==id) {
            for(int j=i;j<n-1;j++){
                meds[j] = meds[j+1];
            }
        n--;
        printf("medicament supprimer avec succes.\n");
        return;}
    }
    printf("medicament non trouver");
}
//4//
void afficherMedicamentExpires (char dateAujourdhui[])
{
    for (int i=0; i<n;i++) {
        if (strcmp(meds[i].dateExpiration, dateAujourdhui) <0){
            printf("medicament expire:\n");
            printf("id: %d\n", meds[i].id);
            printf("nom: %s\n", meds[i].nom);
            printf("prix: %.2f\n", meds[i].prix);
            printf("Quantit�e expir�e: %d\n",meds[i].quantite);
            printf("date expiration: %s\n", meds[i].dateExpiration);
        }
    }
    printf("\n");
}
//5.a//
void RechercheParNom(char nom_med[]){
    Noeud* courant = tete;
    while (courant != NULL) {
        if (strcmp(courant->info.nom, nom_med) == 0) {
            printf("M�dicament trouv�:\n");
            printf("Nom: %s\n",  courant->info.nom);
            printf("ID: %d\n",   courant->info.id);
            printf("Prix: %.2f\n", courant->info.prix);
            printf("Quantit�: %d\n", courant->info.quantite);
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
           printf("M�dicament trouv�:\n");
           printf("Nom: %s\n",  courant->info.nom);
           printf("ID: %d\n",   courant->info.id);
           printf("Prix: %.2f\n", courant->info.prix);
           printf("Quantit�: %d\n", courant->info.quantite);
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
    printf("Les m�dicaments en stock:\n");
    courant = tete;
    while (courant != NULL) {
        if (courant->info.quantite > 0) {
            printf("Nom: %s | ID: %d | Quantit�: %d\n",
                courant->info.nom,
                courant->info.id,
                courant->info.quantite);
            compteur++;
        }
        courant = courant->suivant;
    }
    if (compteur == 0)
        printf("Aucun m�dicament en stock.\n");

    compteur = 0;  // r�initialise pour le 2�me passage

    printf("Les m�dicaments en rupture de stock: \n");
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
        printf("Aucun m�dicament en rupture de stock.\n");
}
//7//
void MiseAJourApresVente(){
    int IDVente, QVendue;
    printf("Donner le ID du m�dicament vendu"); scanf("%d",&IDVente);
    printf("Donner la quantit� du m�dicament vendu"); scanf("%d",&QVendue);
    Noeud* courant = tete;
    while (courant != NULL) {
        if (courant->info.id == IDVente) {
            if (QVendue > courant->info.quantite) {
                printf("Stock insuffisant ! Stock actuel: %d\n",
                        courant->info.quantite);
            } else {
                courant->info.quantite -= QVendue;
                printf("Vente effectu�e. Nouvelle quantit�: %d\n",
                        courant->info.quantite);
            }
            return;
        }
        courant = courant->suivant;
    }
    printf("M�dicament introuvable.\n");
}
//8//
void MiseAJourApresApprovisionnement(){
    int IDAppro, QAppro;
    printf("Donner le ID du m�dicament approvisionn�"); scanf("%d",&IDAppro);
    printf("Donner la quantit�"); scanf("%d",&QAppro);
    Noeud* courant = tete;
    while (courant != NULL) {
        if (courant->info.id == IDAppro) {
            courant->info.quantite += QAppro;
            printf("Stock mis � jour. Nouvelle quantit�: %d\n",
                    courant->info.quantite);
            return;
        }
        courant = courant->suivant;
    }
    printf("M�dicament introuvable.\n");
}
int main()
{
    int c1,c2,id_med;
    char nom_medic[50], date_auj[10];
    do{
        system("cls");
        printf("Choisir quelle fonctionnalit� � appliquer:\n");
        printf("1. Ajouter un m�dicament\n");
        printf("2. Modifier un m�dicament\n");
        printf("3. Supprimer un m�dicament\n");
        printf("4. Afficher tous les m�dicaments expir�s\n");
        printf("5. Rechercher un m�dicament\n");
        printf("6. Afficher les m�dicaments en stock et ceux en rupture\n");
        printf("7. Mise � jour apr�s vente\n");
        printf("8. Mise � jour apr�s approvisionnement\n");
        printf("9. Enregistrer une vente\n");
        printf("10. Calculer le prix total\n");
        printf("11. Gestion des paiements\n");
        printf("12. Afficher l�historique des ventes\n");
        printf("13. Quitter\n");
        scanf("%d",&c1);
        while(getchar() != '\n');
        if(c1==1){
            ajouterMedicament();
        }
        else if(c1==2){
            printf("Donner le ID du m�dicament � modifier");
            scanf("%d",&id_med);
            modifierMedicament(id_med);
        }
        else if(c1==3){
            printf("Donner le ID du m�dicament � supprimer");
            scanf("%d",&id_med);
            supprimer(id_med);
        }
        else if(c1==4){
            printf("Donner la date d'aujourdhui");
            scanf("%s", date_auj);
            afficherMedicamentExpires(date_auj);
        }
        else if(c1==5){
            printf("Choisir: 1.Par Nom ou 2.Par ID\n");
            scanf("%d",&c2);
            if(c2==1){
                printf("donner le nom du m�dic � chercher");
                scanf("%s",&nom_medic);
                RechercheParNom(nom_medic);
            }
            else if(c2==2){
                printf("donner le ID du medicament à chercher");
                scanf("%d",&id_med);
                RechercheParID(id_med);
            }
        }
        else if(c1==6){
            affichage_stock();
        }
        else if(c1==7){
            MiseAJourApresVente();}
        else if(c1==8){
            MiseAJourApresApprovisionnement();
        }
        system("pause");
    }
    while (c1!=13);

    typedef struct Vente {
    int idVente;
    int idProduit;
    int quantite;
    float prixUnitaire;
    float prixTotal;
    float montantPaye;
    float reste;
    struct Vente *suivant;
} Vente;

/* Fonction qui calcule le prix total */
float calculerTotal(int quantite, float prixUnitaire) {
    return quantite * prixUnitaire;
}

/* Procedure pour ajouter une vente dans la liste */
Vente* ajouterVente(Vente *liste) {
    Vente *nouvelleVente;

    nouvelleVente = (Vente*) malloc(sizeof(Vente));

    printf("\n--- Nouvelle vente ---\n");

    printf("ID vente: ");
    scanf("%d", &nouvelleVente->idVente);

    printf("ID produit: ");
    scanf("%d", &nouvelleVente->idProduit);

    printf("Quantite: ");
    scanf("%d", &nouvelleVente->quantite);

    printf("Prix unitaire: ");
    scanf("%f", &nouvelleVente->prixUnitaire);

    nouvelleVente->prixTotal = calculerTotal(
        nouvelleVente->quantite,
        nouvelleVente->prixUnitaire
    );

    printf("Montant donne par le client: ");
    scanf("%f", &nouvelleVente->montantPaye);

    printf("\nMontant total a payer: %.2f DT\n", nouvelleVente->prixTotal);
    printf("Montant donne par le client: %.2f DT\n", nouvelleVente->montantPaye);

    if (nouvelleVente->montantPaye >= nouvelleVente->prixTotal) {
        nouvelleVente->reste = nouvelleVente->montantPaye - nouvelleVente->prixTotal;

        printf("Paiement suffisant.\n");
        printf("Reste a rendre: %.2f DT\n", nouvelleVente->reste);
    } else {
        nouvelleVente->reste = nouvelleVente->prixTotal - nouvelleVente->montantPaye;

        printf("Paiement insuffisant.\n");
        printf("Reste a payer: %.2f DT\n", nouvelleVente->reste);
    }

    nouvelleVente->suivant = liste;
    liste = nouvelleVente;

    return liste;
}

/* Procedure pour afficher l'historique des ventes */
void afficherHistorique(Vente *liste) {
    Vente *p;
    int i = 1;

    if (liste == NULL) {
        printf("\nAucune vente enregistree.\n");
    } else {
        printf("\n--- Historique des ventes ---\n");

        p = liste;

        while (p != NULL) {
            printf("\nVente numero %d\n", i);
            printf("ID vente: %d\n", p->idVente);
            printf("ID produit: %d\n", p->idProduit);
            printf("Quantite: %d\n", p->quantite);
            printf("Prix unitaire: %.2f DT\n", p->prixUnitaire);
            printf("Montant total: %.2f DT\n", p->prixTotal);
            printf("Montant donne: %.2f DT\n", p->montantPaye);

            if (p->montantPaye >= p->prixTotal) {
                printf("Paiement: suffisant\n");
                printf("Reste a rendre: %.2f DT\n", p->reste);
            } else {
                printf("Paiement: insuffisant\n");
                printf("Reste a payer: %.2f DT\n", p->reste);
            }

            p = p->suivant;
            i++;
        }
    }
}

int main() {
    Vente *liste = NULL;
    int choix;

    do {
        printf("\n===== SmartPharma =====\n");
        printf("1. Enregistrer une vente\n");
        printf("2. Afficher historique\n");
        printf("0. Quitter\n");
        printf("Donner votre choix: ");
        scanf("%d", &choix);

        if (choix == 1) {
            liste = ajouterVente(liste);
        } else if (choix == 2) {
            afficherHistorique(liste);
        } else if (choix == 0) {
            printf("Fin du programme.\n");
        } else {
            printf("Choix invalide.\n");
        }

    } while (choix != 0);

    return 0;
}
