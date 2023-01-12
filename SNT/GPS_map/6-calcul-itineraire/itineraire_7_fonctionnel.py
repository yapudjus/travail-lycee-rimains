"""
détermination d'un intinéraire
"""

"""
Variables
"""

Liste_villes = ("Montpellier","Clermont-Ferrand","Lyon","Saint-Etienne","Avignon","Valence") #Tuple des villes



                                                                                #Tableau des distances separant les villes abscisses et ordonnées suivant Liste_villes
Tab_distance = [                                                                #                   "Montpellier","Clermont-Ferrand","Lyon","Saint-Etienne","Avignon","Valence"
                [0, 196, 0, 188, 71, 0],                                        # "Montpellier"
                [196, 0, 102, 0, 0, 0],                                         # Clermont-Ferrand"
                [0, 102, 0, 54, 0, 68],                                         # "Lyon"
                [188, 0 , 54, 0, 0, 0],                                         # "Saint-Etienne",
                [71, 0, 0, 0, 0, 77],                                           # "Avignon"
                [0, 0, 68, 0, 77, 0]                                            #"Valence"
                ]
                                                                                #0 pas de liaison



"""
Fonction assurant la recherche de la ville la plus proche

"""

def distance_mini_ligne(Ville_actuelle) :                                       # fonction de recherehe distance mini

    Distance_ligne = Tab_distance[Ville_actuelle]                               #selection de la ligne des distances entre la ville actuelle
    distance_av = 20000
    Val_min = 0
    k=0


    for distance in Distance_ligne :                                            #rechercher dans toutes les distances de la ville actuelle
        if distance != 0:                                                       #vérification de l'existance de la route
                if distance < distance_av :                                     #vérification distance plus petite
                   distance_av = distance
                   Val_min = int(k)                                             #prise en compte de l'indice
                   distancek = distance                                         #Prise en compte de la distance mini

        k = k+1



    Tab_distance[Val_min][Ville_actuelle] = 0                                   #effacement de la distance pour ne pas revenir dessus

    return Val_min, distancek                                                   #retour des informations


"""
Prog principal
"""

"""
Appel de l'itinéraire
"""

print("Liste_villes :", Liste_villes)
Ville_origine = input("entrée la ville d'origine dans la liste des villes")     #Entrée des données
Ville_arrivee = input("entrée la ville d'arrivée dans la liste des villes")


"""
Recherche des indices du tableau
"""

i = 0
j = 0

for Ville in Liste_villes :                                                     #i : ligne
    if Ville == Ville_origine:
        Incide_origine = i
    i = i+1


for Ville in Liste_villes :                                                     #j : colone
    if Ville == Ville_arrivee:
        Incide_arrivee = j
    j = j+1




"""
Boucle de recherche
"""

Route = []                                                                      #initalisation
Ville_actuelle = Incide_origine
Distance_à_parourir = 0

while Ville_actuelle != Incide_arrivee :                                        #boucle de recherche tant que l'on n'a pas atteint la ville d'arrivée
    Val_min, distancek = distance_mini_ligne(Ville_actuelle)                    #Demander la fonction de recherche de la plus petite distance
    Route.append(Ville_actuelle)                                                #Inserer la ville dans la route
    Ville_actuelle = Val_min                                                    #affecter la ville atteinte
    Distance_à_parourir = Distance_à_parourir + distancek                       #mesurer la distance de la route à parcourrir

Route.append(Incide_arrivee)                                                    #Inserer la ville d'arrivé dans la route

"""
boucle d'impression
"""
for ville in Route :                                                            #Boucle pour afficher toutes les étapes
    print(Liste_villes[ville])

print(Distance_à_parourir)                                                      #Affichage de la distance de la route







