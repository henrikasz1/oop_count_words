# OOP papildoma užduotis
# Asociatyvių konteinerių naudojimas
------------------------

# Užduoties formuluotė

Suskaičiuokite, kiek kartų kiekvienas skirtingas žodis pasikartoja Jūsų tekste. Realizacijos output'e (išoriniame faile) išveskite skirtingus žodžius (kableliai, taškai ir kiti skyrybos ženklai nėra žodžiu dalis!), kurie pasikartojo dažniau negu 1 kartą, o taip pat ir count'erį, nurodantį kiek kartų konkretus žodis pasikartojo. Sukurkite cross-reference tipo lentelę kurioje būtų nurodyta, kurioje teksto vietoje (kurioje(-iose) teksto eilutėse) kiekvienas iš daugiau negu vieną kartą pasikartojantis žodis buvo paminėtas. Rasti tekste paminėtus URL adresus.

# Užduoties funkcionalumas:

* Randa žodį, kuris pasikartoja daugiau nei kartą tekste
* Randa, kuriose eilutėse tas žodis yra naudojamas
* Suskaičiuoja kiek kartų tas pats žodis yra panaudotas tekste
* Randa tekste esančius URL adresus

# Programoje naudojau šiuos asociatyvius konteinerius:

* std::set -> naudojamo žodžio vietoms rasti 
* std::map -> saugoti žodžio informaciją (žodis yra konteinerio raktas)

# Kodo analizė

* Sukuriami du std::map konteineriai, vienas žodžio informacijai saugoti, kitas url adresams saugoti
```c++
  //string will contain words, pair will contain int for counting the frequency of usage of that word and set will be saving
  //the line numbers in which that word is
  std::map<std::string, std::pair<int, std::set<int>>> wordMap;

  std::map<std::string, int>link;
