# tik-tak-toe-ia
A simple tic-tac-toe game featuring an AI that learns from experience using reinforcement learning.  
The AI improves its gameplay by learning from victories and storing knowledge between sessions.  

Ce projet implémente un jeu de morpion (tic-tac-toe) en ligne de commande avec une intelligence artificielle qui apprend par renforcement.
Fonctionnalités:  
-Interface simple : Jeu en ligne de commande avec numérotation des cases de 1 à 9
-Apprentissage par renforcement : L'IA apprend de ses victoires (ou des victoires humaines en cas de défaites) et améliore sa stratégie  
-Sauvegarde persistante : Les connaissances de l'IA sont sauvegardées dans un fichier (ia_donnees.bin) (-> suppression du fichier pour reprendre à 0)
-Chargement des connaissances de l’IA au démarrage.
  
Principe d'apprentissage:  

-L’IA mémorise les configurations du plateau sous forme de hash et associe à chaque coup une valeur. Si deux plateaux sont identiques à une transformation près (ex : rotation ou miroir), ils auront le même hash. Cela évite les doublons, réduit la taille du fichier, et accélère l’apprentissage. 
-Après chaque partie :
    - Si l’IA gagne, elle renforce les coups qu’elle a joués, avec un bonus plus fort pour les derniers coups.
    - Si le joueur humain gagne, l’IA observe ses coups et les valorise.
-Le taux d’exploration diminue progressivement au fil des parties pour favoriser l’exploitation des connaissances acquises.


