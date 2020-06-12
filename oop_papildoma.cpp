#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <set>
#include <regex>
#include <exception>


void read_and_find (std::map<std::string, std::pair<int, std::set<int>>> &wordMap, std::map<std::string, int> &link);
void output (std::map<std::string, std::pair<int, std::set<int>>> &wordMap, std::map<std::string, int> &link);

int main ()
{
  //string will contain words, pair will contain int for counting the frequency of usage of that word and set will be saving
  //the line numbers in which that word is
  std::map<std::string, std::pair<int, std::set<int>>> wordMap;

  std::map<std::string, int>link;

  std::cout << "Counting..." << std::endl;

  read_and_find (wordMap, link);
  output(wordMap, link);
  return 0;
}
void read_and_find (std::map<std::string, std::pair<int, std::set<int>>> &wordMap, std::map<std::string, int> &link)
{
  try
  {
    std::ifstream in ("tekstas.txt");
  if (!in.good())
  {
    throw std::runtime_error("File does not exist :/");
  }
  std::string line;
  int numLine = 1; // counting from the first line
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
  in.close();
  }
  catch (const std::exception & e)
  {
      system("cls");
      std::cout << e.what() << std::endl;
      exit(0);
  }

}
void output (std::map<std::string, std::pair<int, std::set<int>>> &wordMap, std::map<std::string, int> &link)
{
  std::ofstream out ("isvestis.txt");
  out << "Words that appear more than once in the text: \n";
  out << std::endl;
  for (auto i : wordMap)
  {
      if (i.second.first > 1)
      {
        out << "The word \"" << i.first << "\" appears " << i.second.first << " times on the following lines: ";
        for (auto j : i.second.second)
        {
          out << j << " ";
        }
        out << std::endl;
      }
  }

  out << std::endl;
  out << "URL addresses: \n";
  for (std::map<std::string, int>::iterator it = link.begin(); it != link.end(); ++it)
  {
    out << it->first << " in the line number " << it->second << std::endl;
  }
  out.close();
  system ("cls");
}
