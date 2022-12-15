
# methode d'importation de la base de donnees enCSV

import csv
ma_liste= []                                                                    # Creation liste vite

def depuis_csv(nom_fichier_csv):                                                # fonction de lecture fichier csv
	lecteur = csv.reader(open(nom_fichier_csv,'r'))
	return [list(ligne) for ligne in lecteur]

ma_liste = depuis_csv('les-rimains.csv')                                        #importation depuis le fichier source



# methode de filtrage trame MNEA de type $GPGGA


liste_GPGGA = []                                                                #Creation liste vide
Nb_element = len(ma_liste)                                                      #Recherche du nb d'element dans la liste


for ligne in range(Nb_element):                                                 #boucle sur chaque element de ma_liste
	if ma_liste[ligne][0] == '$GPGGA':                                          #Condition sur les elements indice [0] egal à $GPGGA
	  liste_GPGGA.append(ma_liste[ligne])                                       #Si oui on ajoute dans la liste_GPGGA


# methode pour obtenir que la dernière trame $GPGGA


resultat_GPGGA = liste_GPGGA[-1]



# methode pour afficher les resultats de la recherche
#     Afficher votre position est :
#          Latitude  __° __" __ '

Latitude = resultat_GPGGA[2]                                                    #Prise en compte de la latitude
Latitude_deg = str(Latitude[0:2])                                               #Utilisation des deux premières valeurs de la chaîne de caractères (str)
																				#(la valeur de l’indice 2 n'est pas prise en compte)
Latitude_min = str(Latitude[2:4])                                               #Utilisation des valeurs d’indice 2 et 3 de la chaîne de caractères
Latitude_sec = float(Latitude[4:])*60                                           #transformation de la chaîne de caractères en un nombre flottant (float)
																				#puis disvison du nombre pour trouver le nombre de seconde
Latitude_sec_str = str(Latitude_sec)                                            #transformation du nombre flottante en chaîne de caractères
Latitude_sec_aff = Latitude_sec_str[0:4]                                        #Utilisation des quatre premières valeurs de la chaîne de caractères


print("Votre position est :")
print(f"Latitude {Latitude_deg}° {Latitude_min}'' {Latitude_sec_aff}' ")

Longitude = resultat_GPGGA[4]
Longitude_deg = str(Longitude[0:3])
Longitude_min = str(Longitude[3:5])
Longitude_sec = float(Longitude[5:])*60
Longitude_sec_str = str(Longitude_sec)
Longitude_sec_aff = Longitude_sec_str[0:4]


print(f"Longitude {Longitude_deg}° {Longitude_min}'' {Longitude_sec_aff}' ")



# methode pour dissocier la trame $GPGGA


chaine = ','.join(resultat_GPGGA)                                               #transformation de la liste resultat_GPGGA en une chaîne de caratères espaces d'une ","
Champs = chaine.split(',')                                                      #Dissociation de la chaine de caractère en champs