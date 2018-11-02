# Astrofysische_Simulaties
main repository of project

# drdenjef-Program-3DVectClass
Op basis van Joren zijn code heb ik de vector klasse 3 dimentionaal gemaakt
Alsook een aparte .cpp voor de 3DVectClass header (hierin worden functies gedefinieerd) waarin de functies geimplementeerd worden.

Er waren ook enkele functies die met vector objecten werken maar die geen member functies moeten/horen zijn, die heb ik dus als friend functions gedefinieerd en geimplementeerd

als laatste uiteraard dan de header van die klasse in de "main" gestoken (wat dus, als dat voor iedereen goed is, onze main.cpp wordt waar we alles oproepen en uitvoeren)

Deze code heb ik even getest en hij leek te werken (als je bvb even test met wat we moesten doen voor de vorige taak, niet vergeten bij de codes van schrijven naar files, er dan bij te zetten dat hij ook z uitschrijft). Als het goed is voor jullie push ik het into de main branch.

Dit zou dan puntje 1 van "Program" (zie projectassignment.pdf van minerva) moeten volbrengen, voor de integratie methodes stel ik ook voor dat we voor elke methode een .h en .cpp bestand maken. In de .h definieer je de functies (en deze include je in de main), en in de .cpp implementeer je de functies.
Aangezien nog niet iedereen cpp kan zal ik een voorbeeldje uploaden in een aparte tak met de naam "voorbeeld" hoe zo een .cpp en .h ding eruit ziet

# drdenjef-uitleg-headers
Hier dus een voorbeeld (is in c ipv c++ dus heeft .c ipv .cpp maar is zelfde principe)

in rekenmodule.h maak je het skelet van de functie (wat geeft het terug, wat is de naam en wat geef je mee)
in rekenmodule.c (bij ons dus .cpp) schrijf je uit wat de functie moet doen met wat het krijgt (je includeert hier ook rekenmodule.h)

in de main.cpp ga je dan rekenmodule.h includen en zo kan je de functie gebruiken

Nu wat is het nut? Overzichtelijkheid, zo zit niet alles in je main gepropt, en in de header kan je vlug een onverzicht van alle functies zien en in de cpp kan je ze dan verder uitwerken
Ik hoop dat het duidelijk is of, indien je dit al wist, ik je tijd niet te veel verprutst heb

