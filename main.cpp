#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// ==========================================
// CLASSE PASSAGER
// ==========================================
class Passager {
private:
    int idPassager;
    string nom;
    string prenom;
    string telephone;

public:
    Passager(int id, string n, string p, string tel)
        : idPassager(id), nom(n), prenom(p), telephone(tel) {}

    int getId() const { return idPassager; }
    string getNomComplet() const { return prenom + " " + nom; }
    string getTelephone() const { return telephone; }

    void afficherInfos() const {
        cout << "ID Passager : " << idPassager
             << " | Nom complet : " << getNomComplet()
             << " | Telephone : " << telephone << endl;
    }
};

// ==========================================
// CLASSE VOL
// ==========================================
class Vol {
private:
    string numeroVol;
    string destination;
    string dateDepart;
    int capaciteMax;
    int placesDisponibles;
    double prixBillet;

public:
    Vol(string num, string dest, string date, int cap, double prix)
        : numeroVol(num), destination(dest), dateDepart(date),
          capaciteMax(cap), placesDisponibles(cap), prixBillet(prix) {}

    string getNumeroVol() const { return numeroVol; }
    string getDestination() const { return destination; }
    string getDateDepart() const { return dateDepart; }
    int getPlacesDisponibles() const { return placesDisponibles; }
    double getPrixBillet() const { return prixBillet; }

    bool reserverPlace() {
        if (placesDisponibles > 0) {
            placesDisponibles--;
            return true;
        }
        return false;
    }

    void libererPlace() {
        if (placesDisponibles < capaciteMax) {
            placesDisponibles++;
        }
    }

    void afficherDetails() const {
        cout << "Vol [" << numeroVol << "] -> Destination : " << destination
             << " | Depart : " << dateDepart
             << " | Places dispo : " << placesDisponibles << "/" << capaciteMax
             << " | Prix : " << prixBillet << " FCFA" << endl;
    }
};

// ==========================================
// CLASSE PAIEMENT
// ==========================================
class Paiement {
private:
    int idPaiement;
    double montant;
    string modePaiement;
    string datePaiement;
    string statutRemboursement;

public:
    Paiement(int id, double m, string mode, string date)
        : idPaiement(id), montant(m), modePaiement(mode),
          datePaiement(date), statutRemboursement("Paye") {}

    double getMontant() const { return montant; }
    string getStatutRemboursement() const { return statutRemboursement; }

    void marquerRembourse() {
        statutRemboursement = "Rembourse integralement";
    }

    void afficherRecu() const {
        cout << "   -> Paiement #" << idPaiement
             << " | Montant : " << montant << " FCFA"
             << " | Mode : " << modePaiement
             << " | Date : " << datePaiement
             << " | Statut : " << statutRemboursement << endl;
    }
};

// ==========================================
// CLASSE RESERVATION
// ==========================================
class Reservation {
private:
    int idReservation;
    string dateReservation;
    string statut; // "En attente de paiement", "Confirmee", "Annulee"
    Passager* passager;
    Vol* vol;
    Paiement* paiement;

public:
    Reservation(int id, string date, Passager* p, Vol* v)
        : idReservation(id), dateReservation(date), statut("En attente de paiement"),
          passager(p), vol(v), paiement(nullptr) {}

    ~Reservation() {
        delete paiement;
    }

    int getId() const { return idReservation; }
    string getStatut() const { return statut; }
    Passager* getPassager() const { return passager; }
    Vol* getVol() const { return vol; }

    bool enregistrerPaiement(int idPaiement, string mode, string date) {
        if (statut == "Annulee") {
            cout << "Erreur : Impossible de payer une reservation annulee." << endl;
            return false;
        }
        if (paiement != nullptr) {
            cout << "Erreur : Cette reservation est deja payee." << endl;
            return false;
        }
        paiement = new Paiement(idPaiement, vol->getPrixBillet(), mode, date);
        statut = "Confirmee";
        return true;
    }

    void annulerReservation() {
        if (statut == "Annulee") {
            cout << "Information : Cette reservation est deja annulee." << endl;
            return;
        }
        vol->libererPlace();
        if (paiement != nullptr) {
            paiement->marquerRembourse();
            cout << "Reservation annulee. Le paiement associe a ete marque comme rembourse." << endl;
        } else {
            cout << "Reservation non payee annulee (aucun remboursement requis)." << endl;
        }
        statut = "Annulee";
    }

    void afficherDetails() const {
        cout << "Reservation #" << idReservation
             << " | Date : " << dateReservation
             << " | Statut : [" << statut << "]" << endl;
        cout << "   Passager : " << passager->getNomComplet() << " (ID : " << passager->getId() << ")" << endl;
        cout << "   Vol      : " << vol->getNumeroVol() << " vers " << vol->getDestination()
             << " (" << vol->getDateDepart() << ")" << endl;
        if (paiement != nullptr) {
            paiement->afficherRecu();
        } else {
            cout << "   -> Aucun paiement enregistre." << endl;
        }
    }
};

// ==========================================
// PROGRAMME PRINCIPAL
// ==========================================
int main() {
    vector<Passager*> passagers;
    vector<Vol*> vols;
    vector<Reservation*> reservations;

    int choix = 0;
    int compteurPassager = 1;
    int compteurReservation = 100;
    int compteurPaiement = 500;

    do {
        cout << "
=================================================" << endl;
        cout << "     GESTION AGENCE DE VOYAGE - COTONOU          " << endl;
        cout << "=================================================" << endl;
        cout << "1. Enregistrer un passager" << endl;
        cout << "2. Ajouter un vol" << endl;
        cout << "3. Afficher les vols disponibles" << endl;
        cout << "4. Rechercher un vol" << endl;
        cout << "5. Effectuer une reservation" << endl;
        cout << "6. Enregistrer un paiement" << endl;
        cout << "7. Annuler une reservation" << endl;
        cout << "8. Consulter les reservations" << endl;
        cout << "9. Afficher les informations d'une reservation" << endl;
        cout << "10. Quitter" << endl;
        cout << "Votre choix : ";

        if (!(cin >> choix)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entree invalide. Veuillez saisir un nombre entre 1 et 10." << endl;
            continue;
        }

        if (choix == 1) {
            string nom, prenom, tel;
            cout << "Nom : "; cin >> nom;
            cout << "Prenom : "; cin >> prenom;
            cout << "Telephone : "; cin >> tel;
            passagers.push_back(new Passager(compteurPassager, nom, prenom, tel));
            cout << "Succes : Passager enregistre avec l'ID " << compteurPassager++ << "." << endl;
        }
        else if (choix == 2) {
            string num, dest, date;
            int cap;
            double prix;
            cout << "Numero du vol (ex: AF804) : "; cin >> num;
            cout << "Destination : "; cin >> dest;
            cout << "Date de depart (JJ/MM/AAAA) : "; cin >> date;
            cout << "Capacite maximale : "; cin >> cap;
            cout << "Prix du billet (FCFA) : "; cin >> prix;
            vols.push_back(new Vol(num, dest, date, cap, prix));
            cout << "Succes : Vol ajoute au catalogue." << endl;
        }
        else if (choix == 3) {
            cout << "
--- LISTE DES VOLS DISPONIBLES ---" << endl;
            bool dispo = false;
            for (Vol* v : vols) {
                if (v->getPlacesDisponibles() > 0) {
                    v->afficherDetails();
                    dispo = true;
                }
            }
            if (!dispo) cout << "Aucun vol disponible pour le moment." << endl;
        }
        else if (choix == 4) {
            string dest;
            cout << "Destination recherchee : "; cin >> dest;
            bool trouve = false;
            for (Vol* v : vols) {
                if (v->getDestination() == dest) {
                    v->afficherDetails();
                    trouve = true;
                }
            }
            if (!trouve) cout << "Aucun vol trouve pour cette destination." << endl;
        }
        else if (choix == 5) {
            int idP;
            string numV, dateRes;
            cout << "ID du passager : "; cin >> idP;
            cout << "Numero du vol : "; cin >> numV;
            cout << "Date de reservation (JJ/MM/AAAA) : "; cin >> dateRes;

            Passager* pTrouve = nullptr;
            for (Passager* p : passagers) {
                if (p->getId() == idP) pTrouve = p;
            }

            Vol* vTrouve = nullptr;
            for (Vol* v : vols) {
                if (v->getNumeroVol() == numV) vTrouve = v;
            }

            if (pTrouve == nullptr || vTrouve == nullptr) {
                cout << "Erreur : Passager ou Vol introuvable." << endl;
            } else {
                bool dejaReserve = false;
                for (Reservation* r : reservations) {
                    if (r->getPassager()->getId() == idP &&
                        r->getVol()->getNumeroVol() == numV &&
                        r->getStatut() != "Annulee") {
                        dejaReserve = true;
                    }
                }

                if (dejaReserve) {
                    cout << "Erreur : Ce passager possede deja une reservation active sur ce vol." << endl;
                } else if (vTrouve->reserverPlace()) {
                    reservations.push_back(new Reservation(compteurReservation, dateRes, pTrouve, vTrouve));
                    cout << "Succes : Reservation #" << compteurReservation++ << " creee (En attente de paiement)." << endl;
                } else {
                    cout << "Erreur : Plus aucune place disponible sur ce vol." << endl;
                }
            }
        }
        else if (choix == 6) {
            int idRes;
            string mode, dateP;
            cout << "ID de la reservation a payer : "; cin >> idRes;
            cout << "Mode de paiement (Especes/Carte/MobileMoney) : "; cin >> mode;
            cout << "Date du paiement (JJ/MM/AAAA) : "; cin >> dateP;

            bool trouve = false;
            for (Reservation* r : reservations) {
                if (r->getId() == idRes) {
                    if (r->enregistrerPaiement(compteurPaiement++, mode, dateP)) {
                        cout << "Succes : Paiement valide. Place definitivement confirmee." << endl;
                    }
                    trouve = true;
                }
            }
            if (!trouve) cout << "Erreur : Reservation introuvable." << endl;
        }
        else if (choix == 7) {
            int idRes;
            cout << "ID de la reservation a annuler : "; cin >> idRes;
            bool trouve = false;
            for (Reservation* r : reservations) {
                if (r->getId() == idRes) {
                    r->annulerReservation();
                    trouve = true;
                }
            }
            if (!trouve) cout << "Erreur : Reservation introuvable." << endl;
        }
        else if (choix == 8) {
            cout << "
--- LISTE DES RESERVATIONS ---" << endl;
            if (reservations.empty()) {
                cout << "Aucune reservation enregistree." << endl;
            }
            for (Reservation* r : reservations) {
                r->afficherDetails();
                cout << "-------------------------------------------------" << endl;
            }
        }
        else if (choix == 9) {
            int idRes;
            cout << "Entrez l'ID de la reservation : "; cin >> idRes;
            bool trouve = false;
            for (Reservation* r : reservations) {
                if (r->getId() == idRes) {
                    r->afficherDetails();
                    trouve = true;
                }
            }
            if (!trouve) cout << "Erreur : Reservation introuvable." << endl;
        }

    } while (choix != 10);

    for (Passager* p : passagers) delete p;
    for (Vol* v : vols) delete v;
    for (Reservation* r : reservations) delete r;

    cout << "Fermeture de l'application." << endl;
    return 0;
}
