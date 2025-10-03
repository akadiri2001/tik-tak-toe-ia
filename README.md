# tik-tak-toe-ia
A simple tic-tac-toe game featuring an AI that learns from experience using reinforcement learning. 
The AI improves its gameplay by learning from victories and storing knowledge between sessions.

Ce projet implémente un jeu de morpion (tic-tac-toe) en ligne de commande avec une intelligence artificielle qui apprend par renforcement. L'IA s'améliore au fil des parties en mémorisant les états du jeu et les coups gagnants.
Fonctionnalités:
-Apprentissage par renforcement : L'IA apprend de ses victoires et améliore sa stratégie 
-Sauvegarde persistante : Les connaissances de l'IA sont sauvegardées dans un fichier local (ia_donnees.bin) (-> suppression du fichier pour reprendre à 0) 
-Interface simple : Jeu en ligne de commande avec numérotation des cases de 1 à 9 
Principe d'apprentissage:
À chaque coup, l'IA mémorise l'état du plateau et l'action choisie. Si l'IA gagne la partie, tous les coups joués sont récompensés (leur valeur augmente de 0.1) Si l'IA perd ou fait match nul, aucune modification n'est apportée. L'IA utilise 10% d'exploration aléatoire pour découvrir de nouvelles stratégies.
Plus vous jouez contre l'IA, plus elle devient forte !
Améliorations possibles:
-Ajouter des statistiques (victoires/défaites/nuls)
-Permettre de régler les paramètres d'apprentissage
-Ajouter un mode entraînement (IA vs IA)
-Implémenter une interface graphique
