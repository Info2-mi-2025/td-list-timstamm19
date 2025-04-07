# Exercice : Manipulation de listes chaînées avec arguments

## Objectif
Écrire un programme en langage C qui lit une liste de nombres entiers depuis un fichier texte,
les stocke dans une liste chaînée (avec un pointeur vers la **tête** et la **queue** de la liste),
et applique différentes transformations ou actions selon les options passées en ligne de commande.

## Utilisation

```bash
./app <fichier> [options]
```

### Argument obligatoire :
- `<fichier>` : chemin vers un fichier texte contenant un nombre par ligne.

### Options possibles :

- `--reverse` : inverse l’ordre des éléments dans la liste.
- `--sum` : calcule et affiche la somme des éléments.
- `--filter <valeur>` : ne garde que les éléments supérieurs ou égaux à `<valeur>`.
- `--add <valeur>` : ajoute la valeur donnée à la fin du fichier.
- `--help` : affiche un message d’aide et termine le programme.
- `--version` ou `-v` : affiche le numéro de version du programme.
- `--min` : affiche la valeur minimale de la liste.
- `--max` : affiche la valeur maximale de la liste.

Les options peuvent être combinées (sauf `--help` et `--version`, qui doivent être utilisées seules).

## Exemple de fichier d'entrée

`data.txt`
```
5
12
8
1
19
```

## Exemples d'exécution et affichages attendus

### 1. Commande :
```bash
./app data.txt
```
### Sortie :
```
Liste : 19 -> 1 -> 8 -> 12 -> 5
```

### 2. Commande :
```bash
./app data.txt --reverse --sum
```
### Sortie :
```
Liste : 19 -> 1 -> 8 -> 12 -> 5
Somme : 45
```

### 3. Commande :
```bash
./app data.txt --filter 10
```
### Sortie :
```
Liste : 12 -> 19
```

### 4. Commande :
```bash
./app data.txt --add 33
```
### Sortie :
```
Valeur 33 ajoutée au fichier.
```

### 5. Commande :
```bash
./app data.txt --help
```
### Sortie :
```
Utilisation : ./app <fichier> [options]

Options disponibles :
  --reverse         Inverse l'ordre des éléments
  --sum             Affiche la somme des éléments
  --filter <val>    Filtre les éléments >= val
  --add <val>       Ajoute une valeur à la fin du fichier
  --help            Affiche ce message d'aide
  --version, -v     Affiche la version du programme
```

### 5. Commande :
```bash
./app data.txt --version
```
### Sortie :
```
version 1.0
```

### 6. Commande :
```bash
./app data.txt --min
```
### Sortie :
```
Liste : 5 -> 12 -> 8 -> 1 -> 19
Minimum : 1
```

## Contraintes techniques

- Utiliser une **liste chaînée** avec un pointeur vers la **tête** et la **queue**.
- Implémenter chaque fonctionnalité via manipulation de la liste.
- Gérer toutes les erreurs (fichier illisible, mauvaise option, etc).
- Ne pas modifier le fichier sauf avec `--add`.

## Erreurs possibles à gérer
- Fichier non trouvé ou illisible : le programe retourne `2`.
- Erreur d'argument : le programme retourne `1`.

## Tests

Le labo est fourni avec un fichier contenant des tests fonctionnels (`test.json`). Tous les tests doivent passer. Pour exécuter les tests, utilisez la commande `make test`. En cas de problème avec un paquet logiciel, installez les éléments manquants avec la commande `sudo apt-get install`.

Le *framework* de test est [Baygon](https://heig-tin-info.github.io/baygon/). Il peut être installé avec la commande `pip install Baygon==0.2.2`, après avoir installé Python avec `sudo apt-get install python3 python3-pip`.

En cas d'erreur, il est possible de devoir ajouter l'option :
`pip install Baygon==0.2.2 --break-system-packages`.

Il se peut que vous ayez un avertissement à propos du `PATH`. En effet, `pip install` install le paquet Baygon dans votre espace utilisateur qui n'est pas pris en compte par votre terminal. Vous pouvez exécuter les commande suivante :

```bash
echo 'export PATH=$HOME/.local/bin:$PATH' >> ~/.bashrc
source ~/.bashrc
```

## Liste des livrables
- `Commit` sur Github en respectant le délai donné sur Cyberlearn.
