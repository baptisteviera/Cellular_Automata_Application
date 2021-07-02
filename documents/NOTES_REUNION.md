# Notes de réunions

## Vendredi 02/04

### Reprise des éléments principaux du sujet
* Le plus important va être de définir l'architecture de l'application, les classes utilisées, les interactions entre elles, bref l'UML.
    * Etape cruciale à réaliser en plusieurs temps : d'abord, chacun s'approprie la structure de données en rédigeant un UML (version light) dans son coin, puis on les compare pour faire ressortir les points communs que l'on est sûrs de pouvoir retenir, et les différences parmi lesquelles il faudra trouver le meilleur compromis, le plus cohérent avec le sujet. On identifiera également les design pattern utiles au fur et à mesure de la conception. A mesure que la conception avance, on peut à la rigueur penser à quelques éléments de code, pour anticiper la partie pratique.
    * Cette tâche est assurément la plus difficile. Il faut définir rigoreusement une architecture qui tienne debout, où toutes les interactions sont définies, avant d'écrire la moindre ligne de code.
    * Au niveau des dates : 2 scenarios : si les médians sont maintenus la semaine du 12/04, présentation du premier jet d'UML le 23/04. Sinon, à faire avant les médians (9/04 ou 16/04). Ensuite, on le retravaille jusqu'à avoir un modèle qui tienne parfaitement debout. On peut envisager une phase hybride où certains commencent à coder les parties sur lesquelles on est absolument sûrs. Ensuite, dernière échéance pour essayer de ne plus modifier le modèle logique : dernier rapport du 31 mai. Ensuite, on se concentre uniquement sur le code, le débogage, etc. Il faut aussi penser au lien avec l'interface graphique : on peut tester l'implémentation en console dans un premier temps, mais il faudra penser à passer assez vite sur l'interface graphique. On essaiera autant que possible de maintenir faible le couplage entre backend et frontend dans l'application pour que la GUI puisse être développée assez tôt, quand l'avancement du backend le permet. Ce n'est pas la partie la plus importante mais on veut éviter la perte de temps engendrée par des tests mis en place en console, qui devraient ensuite être retirés du code, etc. On peut tabler sur 1 à 2 personne(s). Pour le reste, on imagine que tout le monde intervient sur la conception logique au début du projet, puis que certaines tâches plus ou moins indépendantes (l'implémentation des différents automates demandés dans le sujet, basée sur le modèle logique qu'on aura conçu au préalable). On se renseignera sur les design pattern mentionnés dans le sujet pour anticiper la conception du modèle logique.

* On ne perdra jamais de vue l'aspect modulaire de ce que l'on doit développer. On doit construire une architecture générique et fonctionnelle pour permettre l'implémentation de n'importe quel automate par l'utilisateur. C'est seulement après que l'on s'intéressera à l'implémentation des quelques cas particuliers que constituent les automates demandés. Par exemple pour le choix du voisinage, on peut imaginer une GUI où l'utilisateur doit cliquer sur certaines des 8 cases autour d'une cellule pour définir son propre voisinage. Cette GUI serait accompagnée d'un menu déroulant où il peut choisir parmi certains voisinages existant, on les affiche dans la grille pour qu'il puisse encore les personnaliser (dans l'idée). On mettra quand même quelques limites à la personnalisation : une configuration enregistrée sur un pavage d'une certaine dimension par exemple ne pourra pas être ouvert sur un pavage de dimension différents (parce qu'on peut se foutre de la gueule du monde mais pas trop non plus).

* Définition de la fonction de transition : est-ce que la fonction de transition ne prend en compte que le nombre de cellules dans un certain état pour calculer l'état suivant pour la cellule centrale, ou est-ce que la disposition de ces cellules autour intervient aussi ? La fonction de transition va être un enfer à décrire en extension dans le 2ème cas : dans un automate avec un voisinage de 4 et deux états possibles, on a 2*2⁴ possibilités à énumérer...

* Gestion des données : on garde le choix entre fichiers (XML) et SGBD pour plus tard, quand on se rendra compte de la complexité des données à gérer.

:question: quand on choisit de charger une configuration prédéfinie, est-ce qu'elle doit pouvoir s'adapter à la taille du pavage ?

### Liste de priorités et répartition des tâches :
1. Conception du modèle logique : UML
    * Tout le monde participe sur les différentes étapes décrites précédemment. Des groupes pourront se dessiner au fur et à mesure qu'on y verra plus clair.
2. Implémentation des premières fonctionnalités (classes essentielles) du backend. En parallèle, début de développement du frontend : bases de l'architecture graphique. On ne laisse pas tomber l'UML pour autant : ce sera une phase où on code de son côté, mais on continue à parler du modèle logique en réunion.
    * Front : Bang.
    * Back : on pourra se répartir les tâches pour commencer à coder, en groupant par ensembles de classes à fort couplage. On évitera de séparer le travail entre personnes différentes pour des classes fortement couplées.
    * UML : travail collectif, évoqué surtout en réunion.
3. Implémentation des fonctionnalités plus avancées. On essaie d'avoir une architecture parfaitement fonctionnelle qui puisse être personnalisée par l'utilisateur. Il faut que cette architecture soit prête à accueillir les modèles sauvegardés.
4. Implémentation dans un dernier temps des options poussées : sauvegarde de modèles surtout.

### Notes sur l'UML (en vue de la réunion du 17/04)
* Est-ce que les voisinages de Von Neuman et de Moore peuvent être transformés en une classe héritée de la classe abstraite `NeighborStrategy`, regroupant tous les voisinages caractérisés par un rayon, et devenir des instances de cette classe (cf syntaxe UML vue en TD cette semaine) ?
* Réfléchir aux compositions/agrégations.