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

# Abstrakti kodo analizė

* Sukuriami du std::map konteineriai, vienas žodžio informacijai saugoti, kitas url adresams saugoti
```c++
  //string will contain words, pair will contain int for counting the frequency of usage of that word and set will be saving
  //the line numbers in which that word is
  std::map<std::string, std::pair<int, std::set<int>>> wordMap;

  std::map<std::string, int>link;
```
* Kiekvieną eilutę nuskaitau su getline, bei transformuoju tekstą į mažąsias raides
```c++
  while(std::getline(in, line))
  {
    //transforming all letters into lower case
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    //reading text
    std::stringstream read(line);
    std::string word;
    .......
```
* Šiame cikle (while(read >> word)) nuskaitau tekstą po žodį
* Naudojant std::regex randama tekste esantys URL adresai
* Ištrinami visi skyrybos ženklai (su erase ir std::remove_if)
* Į std::map (wordMap) įterpiamas žodis kaip first, kiek kartų žodis pasikartoja - second.first, kuriose eilutėse žodis naudojamas - second.second
```c++
  while(std::getline(in, line))
  {
    //transforming all letters into lower case
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    //reading text
    std::stringstream read(line);
    std::string word;

    while(read >> word)
    {

      //finding urls
      if(std::regex_match(word, std::regex("[(http(s)?):\\/\\/(www\\.)?a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)")))
      {
        link.insert(std::pair<std::string, int>(word, numLine));
      }
      //erasing all the punctuation
      word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());

      auto a = wordMap.insert({word, {0, std::set<int>()}});//insert works only if the map's key has a different value

      auto &it = a.first;

      it->second.first++;
      it->second.second.insert(numLine);

    }
    numLine++; //
  }
```
