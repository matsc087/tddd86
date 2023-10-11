#include <iostream>
#include <string>
#include <map>
#include <unordered_set>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
void loadDictitionary(map<int, vector<string>>& map);
vector<string> startSequence(bool &showRemaining, int &guesses);
string generatePattern(const string& word, const string& guessedCharacters);
void findBiggestGroup(vector<string>& wordPool, string& guessedCharacters, string& pattern);

/**
 * @brief main: contains mainloop and will ask the user to play again
 * if they desire
 * @return 0
 */
int main() {
    bool playing = true;
    while(playing){

    bool showRemaining = false;
    string pattern;
    int guesses = 0;
    // Takes user inputs as in number of guesses, length of word and
    // if the user wants to see the remaining words
    vector<string> wordPool = startSequence(showRemaining, guesses);

    // gameloop
    string guessedCharacters;
    while (guesses > 0) {
        if(wordPool.size() == 1){
            if(wordPool[0] == pattern){
                cout << "YOU WIN THE WORD WAS " << wordPool[0] << endl;
                break;
            }
        }

        char guess;
        int length = guessedCharacters.size();

        for(int usedGuesses = 0; usedGuesses < length; usedGuesses++)
            {
                cout << guessedCharacters[usedGuesses] << " ";
            }

        cout << endl;
        cout << "you have " << guesses << " guesses left!" << endl;
        cout << endl;

        // Loop until a correct input is given
        while(true)
        {
        cout << "make a guess: ";
        cin >> guess;
        cout << endl;

        if(ALPHABET.find(guess) != string::npos)
        {

            bool alreadyGuessed = false;

            for(char character : guessedCharacters){
                if(character == guess){
                    cout << "character already guessed" << endl;
                    alreadyGuessed = true;
                }
            }
            if(!alreadyGuessed){
                break;
            }

        }
        }

        // make new wordlist with the guess
        guessedCharacters.push_back(guess);
        findBiggestGroup(wordPool, guessedCharacters, pattern);
        guesses -= 1;
        if(showRemaining)
        {
            for(string word : wordPool)
            {
                cout << word << endl;
            }
        }
        cout << pattern << endl;

    }
    if(guesses == 0){
        cout << "YOU LOSE!" << endl << "The word was " << wordPool[0] << endl;
        cout << "Do you wanna play again? If yes press y" << endl;
        string choice;
        cin >> choice;
        if(choice != "y")
        {
            playing = false;
        }

    }
    }

    return 0;
    // TODO: Finish the program!
}

/**
 * @brief startSequence: Is meant for launching the programming and getting all the user
 * input parameters.
 * @param showRemaining: Is meant for the main game loop where it will
 * show all the remaining words to the player.
 * @param guesses: Is an int for the number of guesses the user wants
 * @return wordpool: is a vector<string> of all the word with the 
 * length the user has chosen.
 */
vector<string>  startSequence(bool &showRemaining, int &guesses){
    map<int, vector<string>> map;
    loadDictitionary(map);

    vector<string> wordPool;

    cout << "Welcome to Hangman." << endl;

    while(true)
    {
    cout << "Enter a number for the length of the word" << endl;
    int wordLength;
    cin >> wordLength;
    if(map.find(wordLength) != map.end())
    {
        wordPool = map[wordLength];
        break;
    }
    }


    while(guesses <= 0)
    {
    cout << "Enter a number of guesses" << endl;
    cin >> guesses;
    }

    cout << "If you want to see the remaining words, press y" << endl;
    string choice;
    cin >> choice;
    if(choice == "y")
    {
        showRemaining = true;
        cout << "We will show the remaining words" << endl;
    }

    return wordPool;
}

/**
 * @brief loadDictitionary: Loads the textfile 
 * dictionary.txt and populates the 
 * @param map: map consists of <int, vector<string>> the 
 * int is the length of the words in the vector
 */
void loadDictitionary(map<int, vector<string>>& map){

   string line;

   string fileName = "dictionary.txt";

   ifstream inputFile(fileName);

   while(std::getline(inputFile, line)){
       int length = line.size();
       map[length].push_back(line);
   }
   inputFile.close();
}

/**
 * @brief generatePattern: Generates a pattern that corresponds
 * to that word and if the user hasn't guessed that letter yet
 * it's replaced with a '_' 
 * @param word: the word we are generating a pattern for
 * @param guessedCharacters: a string of all characters the
 * user has guessed.
 * @return a string of the same word but none guessed letters are '_'
 */
string generatePattern(const string& word, const string& guessedCharacters)
{
    string pattern = word;
    int length = word.length();
    for(int i = 0; i < length; i++)
    {
        if(guessedCharacters.find(word[i]) == string::npos){
            pattern[i] = '_';
        }
    }
    return pattern;
}

/**
 * @brief findBiggestGroup: iterates trough the current wordPool and
 * uses generatePattern() to genereate a pattern for each word
 * it then sorts the words by pattern and updates wordpool "the remaining words
 * we can choose from" to the largest pattern group and the pattern that correspond
 * to those words.
 * @param wordPool: a vector of strings containing all viable words
 * @param guessedCharacters: a string of all guessedletters
 * @param pattern: the pattern that we display to the user
 */
void findBiggestGroup(vector<string>& wordPool,string& guessedCharacters, string& pattern){
    unordered_map<string, vector<string>> patternMap;
    //sort word by current pattern
    unordered_set<string> patternMapKey;

    //create patternMap which then gets analyzed by the length.
    for(string word : wordPool){
        string patternKey = generatePattern(word, guessedCharacters);
        if(patternMap.find(patternKey) == patternMap.end()){
            patternMap[patternKey] = {word};
        }else{
            patternMap[patternKey].push_back(word);
        }

        if(patternMapKey.find(word) == patternMapKey.end()){
            patternMapKey.insert(patternKey);
        }


    }
    vector<string> biggestWordPool;

    int Iterations = 0;
    //checks for the longest wordPool in patternMap which is supposed
    //to save the wordPools based on their pattern.
    for(const auto& elem: patternMapKey)
    {
        if(Iterations == 0)
        {
            biggestWordPool = patternMap[elem];
            pattern = elem;
        }

        else if(patternMap[elem].size() > biggestWordPool.size())
        {
            biggestWordPool = patternMap[elem];
            pattern = elem;
        }
        Iterations ++;

    }
    wordPool = biggestWordPool;
}




