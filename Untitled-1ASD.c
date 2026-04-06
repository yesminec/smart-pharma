#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char nom[50];
    float prix;
    int quantite;
    char dateExpiration[20];
} Medicament;
Medicament meds[100];
int n = 0;
//1//
void ajouterMedicament() {
printf("ID: ");
scanf("%d", &meds[n].id);
printf("Nom: ");
scanf("%s", meds[n].nom);
printf("Prix: ");
scanf("%f", &meds[n].prix);
printf("Quantité: ");
scanf("%d", &meds[n].quantite);
printf("Date expiration: ");
scanf("%s", meds[n].dateExpiration);
n++;
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
        printf("medicament modifié avec succés.\n");
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
            printf("Quantitée expirée: %d\n",meds[i].quantite);
            printf("date expiration: %s\n", meds[i].dateExpiration);
        }
    }
    printf("\n");
}
//5.a//
void RechercheParNom(char nom_med[]){
    int trouve=0;
    int i=0;
    while ((i<n)&&(trouve==0)){
        if (strcmp(meds[i].nom, nom_med) == 0){
            printf("Le médicament est trouvé:\n");
            printf("Nom: %s\n",meds[i].nom);
            printf("ID: %d\n",meds[i].id);
            printf("Prix: %f\n",meds[i].prix);
            printf("Quantitée disponible: %d\n",meds[i].quantite);
            printf("Date d'expiration: %s\n",meds[i].dateExpiration);
            trouve=1;
        }
    i++;
    }
    if (trouve==0){
        printf("Produit introuvable");
    }
}
//5.b//
void RechercheParID(int id_med){
    int trouve=0;int i=0;
    while ((i<n)&&(trouve==0)){
        if (meds[i].id == id_med){
            printf("Le médicament est trouvé:\n");
            printf("Nom: %s\n",meds[i].nom);
            printf("ID: %d\n",meds[i].id);
            printf("Prix: %f\n",meds[i].prix);
            printf("Quantitée disponible: %d\n",meds[i].quantite);
            printf("Date d'expiration: %s\n",meds[i].dateExpiration);
            trouve=1;
        }
    i++;
    }
    if (trouve==0){
        printf("Produit introuvable");
    }
}
//6//
void affichage_stock(){
    printf("Médicaments en stock\n");
    for (int i=0; i<n; i++){
        if (meds[i].quantite>0){
            printf("Nom-ID: %s - %d, Quantité: %d \n",meds[i].nom,meds[i].id,meds[i].quantite);
        }
    }
    printf("Médicaments hors de stock\n");
    for (int i=0; i<n; i++){
        if (meds[i].quantite==0){
            printf("Nom-ID: %s - %d \n",meds[i].nom,meds[i].id);
        }
    }
}
//7//
void MiseAJourApresVente(){
    int i,IDVente, QVendue;
    printf("Donner le ID du médicament vendu"); scanf("%d",&IDVente);
    printf("Donner la quantité du médicament vendu"); scanf("%d",&QVendue);
    for(i=0;i<n;i++){
        if(meds[i].id==IDVente){
            meds[i].quantite-= QVendue;
            printf("Nouvelle Quantité: %d\n", meds[i].quantite);
            return;
        }
    }
    printf("Le Médicament n'existe pas");
}
//8//
void MiseAJourApresApprovisionnement(){
    int i,IDAppro, QAppro;
    printf("Donner le ID du médicament approvisionné"); scanf("%d",&IDAppro);
    printf("Donner la quantité"); scanf("%d",&QAppro);
    for(i=0;i<n;i++){
        if(meds[i].id==IDAppro){
            meds[i].quantite+= QAppro;
            printf("Nouvelle Quantité: %d\n", meds[i].quantite);
            return;
        }
    }
    printf("Le Médicament n'existe pas");
}
int main()
{
    int c1,c2,id_med; 
    char nom_medic[50], date_auj[10]; 
    do{
        printf("Choisir quelle fonctionnalité à appliquer:\n");
        printf("1. Ajouter un médicament\n");
        printf("2. Modifier un médicament\n");
        printf("3. Supprimer un médicament\n");
        printf("4. Afficher tous les médicaments expirés\n");
        printf("5. Rechercher un médicament\n");
        printf("6. Afficher les médicaments en stock et ceux en rupture\n");
        printf("7. Mise à jour après vente\n");
        printf("8. Mise à jour après approvisionnement\n");
        printf("9. Enregistrer une vente\n");
        printf("10. Calculer le prix total\n");
        printf("11. Gestion des paiements\n");
        printf("12. Afficher l’historique des ventes\n");
        printf("13. Quitter\n");
        scanf("%d",&c1);
        if(c1==1){
            ajouterMedicament();
        }
        else if(c1==2){
            printf("Donner le ID du médicament à modifier");
            scanf("%d",&id_med);
            modifierMedicament(id_med);
        }
        else if(c1==3){
            printf("Donner le ID du médicament à supprimer");
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
                printf("donner le nom du médic à chercher");
                scanf("%s",&nom_medic);
                RechercheParNom(nom_medic);
            }
            else if(c2==2){
                printf("donner le ID du médic à chercher");
                scanf("%d",&id_med);
                RechercheParID(id_med);
            }
        }
        else if(c1==6){
            affichage_stock();
        }
        else if(c1==7){
            MiseAJourApresVente();
        }
        else if(c1==8){
            MiseAJourApresApprovisionnement();
        }
    }
    while (c1!=13);
    return 0;
}
