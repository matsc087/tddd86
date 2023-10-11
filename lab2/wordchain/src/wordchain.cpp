#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <unordered_set>
#include <cstring>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
void loadDictitionary(std::map<int, vector<string>>& map);
void wordChain(const string &startWord, const string &endWord);
bool isNeighbour(const string &startWord, const vector<string> &endWord, const string &currentWord);
int main() {

    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";
    string input1, input2;
    cin >> input1 >> input2;
    cout << endl;

    wordChain(input1, input2);
    return 0;
}


/**
 * @brief loadDictitionary: Loads the textfile
 * dictionary.txt and populates the
 * @param map: map consists of <int, vector<string>> the
 * int is the length of the words in the vector
 */
 void loadDictitionary(map<int, unordered_set<string>>& map){

    string line;

    string fileName = "dictionary.txt";

    ifstream inputFile(fileName);

    while(std::getline(inputFile, line)){
        int length = line.size();
        map[length].insert(line);
    }
    inputFile.close();
}


/**
  * @brief wordChain: Calls loadDictionary() then uses a queue
  * of stacks<string> for all viable wordchains
  * We then try to replace a letter in the word if it's in
  * the unordered_set words then we push the word to the stack
  * aswell as the stack without hte added word to the queue
  * We then take the first stack in the queue and do the same thing
  * until the stack cotains the endWord as the top word
  * @param startWord: the starting word
  * @param endWord: The word we are trying to reach
  */
 void wordChain(const string &startWord, const string &endWord){
    map<int, unordered_set<string>> map;
    loadDictitionary(map);

    int length = startWord.size();
    int endlength = endWord.size();
    if(length != endlength){
        cout << "Words are not the same length" << endl;
        return;
    }

    //Go trough words with the same length as the desired words
    unordered_set<string> words = map[length];
    if(words.find(startWord) == words.end() || words.find(endWord) == words.end())
    {
        cout << "Could not find words in Dictionary" << endl;
        return;
    }

    unordered_set<string> usedWords;
    queue<stack<string>> usedChains;
    stack<string> s1;
    s1.push(startWord);
    usedChains.push(s1);

    while(!usedChains.empty())
    {
        stack<string> wordChain = usedChains.front();
        usedChains.pop();

            // replace a letter in the current word
            for(char letter : ALPHABET){
                string currentWord = wordChain.top();
                int lengthWord = currentWord.length();
                for(int i = 0; i < lengthWord; i++){
                    string currentWordCopy = currentWord;
                    currentWordCopy[i] = letter;

                    // Checks if the created word is a viable word
                    // and the word hasn't been used before
                    if(words.find(currentWordCopy) != words.end()){
                        if(!(usedWords.find(currentWordCopy) != words.end())){
                            usedChains.push(wordChain);
                            stack<string> wordChainCopy = wordChain;
                            wordChainCopy.push(currentWordCopy);
                            usedChains.push(wordChainCopy);
                            usedWords.insert(currentWordCopy);

                            // check if we found the desired word
                            if(wordChainCopy.top() == endWord){
                                while(!wordChainCopy.empty()){
                                    cout << wordChainCopy.top();
                                    wordChainCopy.pop();
                                    if(!wordChainCopy.empty()){
                                        cout << " -> ";
                                    }
                                }
                                cout << endl;
                                return;
                            }
                        }

                    }
                }
            }

    }
    cout << "Found no wordchain" << endl;
}

