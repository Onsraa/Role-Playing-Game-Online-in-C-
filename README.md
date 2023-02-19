# Role-Playing-Game-Online-in-C
RPG project in C, year 2022.

Dépendances à installer :

- Librairie mysql
$ sudo apt install default-libmysqlclient-dev

- Librairie json
$ sudo apt-get install -y libjson-c-dev

Commande pour compiler le projet :
gcc -o main.o $(mysql_config --cflags) main.c menu.c sql.c Settings/settings.c Actions/actions.c Struct/*/* $(mysql_config --libs) -lncurses -ljson-c

Le programme se lancera avec le fichier main.o


Ce projet est un rpg du type DeadCells mais en plus cheap et sans inteface graphique. Sur ce jeu on peut incarner des personnages typiques d'un D&D classique.
On y compte un guerrier, un assassin, un archer et un mage.

Vous pourrez créer plusieurs classes de personnages ou même les supprimer. Les choisir à volonter pour les lancer dans les donjons.

Les donjons se font d'une traite, vous mourrez et c'est le point de départ qui vous attend mais pas d'inquiétude, vous gardez tout le stuff droppé et les niveaux accumulés pendant ce run dans le donjon. Dans ce donjon on peut tomber contre des mobs mais aussi attérir dans des zones calmes comme l'auberge qui vous permet de passer un stage (Le donjon se joue en plusieurs étapes, à chaque étape on peut choisir entre 2 voies qui se sont générées pendant la création du donjon, c'est notre arbre binaire) ou la fontaine qui vous régénère vos barres de vies et de mana.

On peut drop du stuff sur les mobs et les équipper. Plusieurs niveaux de raretés (Divine c'est 1% de chance de drop)

Technique :

Fichier conf/json modifiable depuis l'interface du terminal. On peut modifier :
- le niveau de difficulté des donjons
- le mode automatique de combat 
- le passage des dialogues pendant les combats.

Une base de données a été mise en place depuis les serveurs OVH.
- on peut créer un utilisateur
- se connecter avec
- récupérer ses anciennes données 




