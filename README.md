# CMKV

## 1. Objectifs

Le but est de résoudre à l'ordinateur un problème combinatoire basé sur le jeu [Tetravex](https://fr.wikipedia.org/wiki/Tetravex) (paquet gnome-tetravex).

:warning: Le rendu se fait par mail à thierry.geraud@epita.fr avant le 20 janvier 2023 (à 23h51)

## 2. Membres du groupe

| Nom              | Email (@epita.fr)         | Pseudo  Github |
| ---------------- | ------------------------- | -------------- |
| Corentin Duchêne | corentin.duchene          | `Nigiva`       |
| Adrien Merat     | adrien.merat              | `Timelessprod` |
| Théo Perinet     | theo.perinet              | `TheoPeri`  ,  |
| Henri Jamet      | henri.jamet               | `hjamet`       |

## 3. Consignes

En entrée, on dispose d'un fichier texte qui donne les tuiles d'un tetravex ; ce peut-être une configuration de 2x2 tuiles à 6x6 tuiles.

En sortie, on écrit un fichier texte qui donne la configuration solution du problème.

Le projet doit compiler avec `g++ *.cc -DNDEBUG -O5 -std=c++17 -lpthread -Wl,--no-as-needed` mais un Makefile ou une configuration CMake est possible.

La méthode de résolution doit être un algorithme de recuit de type Metropolis-Hastings.

Le projet est à réaliser par groupe de 3 ou 4.

L'évaluation prendra en compte quatre aspects :
- facilité de compilation (les difficultés de compilation donnent des malus) ;
- justesse des solutions (pour avoir des points) ;
- rapidité d'exécution (pour avoir des bonus et pouvoir dépasser la note de 14) ;
- qualité et détail du rapport en PDF fourni dans votre archive (sur quelques points).

Les données d'entrée sont dans le répertoire data/input/.  Les fichiers de sortie (pour que vous puissiez vérifier votre code) sont dans data/ref/.

Le chiffre en 2e caractère donne la taille de la grille.

Un temps de référence (qu'il faut essayer d'approcher) est de :
- moins d'1 sec pour résoudre 70 grilles de taille 4x4
- moins de 30 sec pour 10 grilles de taille 6x6
(sur un Intel Core i7 8x @ 3.6 GHz)

Les fichiers d'entrée comporteront au moins un @ (tuile fixée).

Néanmoins, le programme sera aussi testé  avec des fichiers dont aucune tuile n'est fixée (sans `@`) ce qui fera des points bonus si notre programme résoud le puzzle.

Le nom du fichier zip est le nom de famille d'un des membres du groupe. Il doit contenir à la racine, un fichier `AUTHORS` et `README.pdf` (rapport). Pas de binaires ni de sous-dossiers.

Le rapport présente la démarche de recherche et le fonctionnement de l'algorithme : quelle modélisation probabiliste utiliser ? Pourquoi ? etc. La moitié de la note porte sur ces explications, la note augmente avec des explications détaillées, pertinentes et compréhensibles.

## 4. Exemple

### 4.1. Fichier en entrée

C'est un fichier texte avec une ligne par tuile, les tuiles étant listées dans l'ordre matriciel / vidéo classique (pour chaque ligne, pour chaque colonne).

Une tuile est décrite par ses 4 chiffres dans l'ordre de leur position : nord, ouest, est, sud.

Le symbole '@' en fin de ligne signifie qu'une tuile est à sa place ; sa place étant connue, cette tuile ne doit pas être "déplacée". Il peut y avoir de 1 à plusieurs tuiles bien déplacées.

Exemple de ficher de 4 lignes, correspondant donc à une configuration 2x2 :

```
0986 @ 
6524
5283
3805
```

représente l'entrée :

```
+-----+-----+
|  0  |  6  |
| 9 8 | 5 2 |
|  6  |  4  |
+-----+-----+
|  5  |  3  |
| 2 8 | 8 0 |
|  3  |  5  |
+-----+-----+
```

avec la tuile en haut à gauche restant fixée (elle reste à sa place).

Un fichier d'entrée correspondant à une grille de 6x6 aura donc 36 lignes.

### 4.2. Fichier en sortie

Le fichier solution attendu est de 4 lignes :

```
0986
3805
6524
5283
```

qui représente :

```
+-----+-----+
|  0  |  3  |
| 9 8 | 8 0 |
|  6  |  5  |
+-----+-----+
|  6  |  5  |
| 5 2 | 2 8 |
|  4  |  3  |
+-----+-----+
```
