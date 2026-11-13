# Gestion d'une Agence de Voyage (Projet POO C++ & UML)

**Auteur :** Abraham Eliud Santos  
**Établissement :** UNSTIM — Faculté des Sciences et Techniques (FAST)  

## Présentation du Projet
Application console développée en **C++** selon les principes de la **Programmation Orientée Objet (POO)** pour informatiser la gestion des vols, des passagers, des réservations et des paiements d'une agence de voyage basée à Cotonou.

## Structure des Fichiers
* `main.cpp` : Code source complet en C++ (classes `Passager`, `Vol`, `Reservation`, `Paiement` et menu interactif à 10 options).
* `Rapport_Projet_Agence_Voyage.pdf` : Dossier d'analyse, dictionnaire des classes, diagramme UML, trace d'exécution et code documenté.
* `Diagramme_Classes_UML.puml` : Script PlantUML importable directement dans **Lucid.app** pour générer le diagramme de classes officiel.

## Fonctionnalités Implémentées
1. Enregistrer un passager
2. Ajouter un vol
3. Afficher les vols disponibles
4. Rechercher un vol par destination
5. Effectuer une réservation (avec contrôle d'unicité et de capacité)
6. Enregistrer un paiement et confirmer la réservation
7. Annuler une réservation (libération automatique de place et gestion du remboursement)
8. Consulter toutes les réservations
9. Afficher les détails d'une réservation spécifique
10. Quitter l'application

## Compilation et Exécution
```bash
g++ -std=c++17 main.cpp -o agence_voyage
./agence_voyage
```
