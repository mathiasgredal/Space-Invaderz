### Logbog 2020/12/01

I dette miniprojekt skal vi lave et spil, som benytter SFML samt de mere avanceret funktioner i det objekt orienteret paradigme. Jeg har valgt det klassiske space invader spil, da det er relativt simpelt at lave, samtidig med at være et sjovt spil at spille. I spillet har hver komponent sin egen klasse, altså spilleren, aliens og shields'ne. Man kunne bruge nedarvning til at have en basis spilkomponentklasse med nogle abstrakte funktioner, som Draw og Handle_Event. Disse komponenter kunne så være i et komponenttræ, og alle komponenterne kunne så tegnes i draw funktionenen, på en måde hvor øverste draw funktion ikke skal kende til draw implementeringen for hver underklasse.

Denne ide blev dog ikke anvendt i programmet, da der ikke var nok forskellige klasser til at det kunne betale sig.  

For at implementere destruktionen i shields, blev hver shield sprite splittet op og texturen blev kopieret over, så de individuelle pixels kunne fjernes ved destruktion, uden at påvirke de andre shields. Derefter havde hvert segment blot et antal liv, og når segmentet løb tør for liv kunne det blive slettet. Antallet af segmenter pr. skjold kan modificeres med variabler og er ikke hardcoded. 

Spillet kompileres statisk og bibliotekerne kompileres fra kildekoden med CMake, assetsne kompileres ind i den eksekverbare fil, så den ikke skal transporteres ved siden af. På den måde er spillet kun afhængig af systembibliotekerne, desuden er den også mindre, da kompileren kan fjerne unødvendige symboler fra biblioteket modsat dynamiske biblioteker, som skal beholde alle symboler.



