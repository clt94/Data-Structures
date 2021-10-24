// Connor Taylor
// Assignment 2: Takes the first and last word to a word ladder and attempts 
// to create a word ladder with a dictionary through recursion.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ios>
#include <unordered_set>

// Precondition: constant string by reference
// Validates user input for only alphabetical characters
// Postcondition: true if valid
bool validateString(const std::string&);

// Precondition: constant string by reference, constant string by reference
// Validates that two strings are of the same length
// Postcondition: true if both words are the same length
bool matchLength(const std::string&, const std::string&);

// Precondition: ifstream by reference, constant string by reference
// Checks that the word exists in the dictionary
// Postcondition: true if the word is in the dictionary
bool wordExists(std::ifstream&, const std::string&);

// Precondition: string by reference
// Converts a string to be all lower case
// Postcondition: none
void toLowerCase(std::string&);

// Precondition: ifstream by reference
// Opens a texts file and verifies it is opened successfully
// Postcondition: true if it is opened properly
bool openFile(std::ifstream&);

// Precondition: ifstream by reference, unordered set of strings by reference, string by reference, string by reference
// Creates a vector of all the words of the same length form the dictionary in the vector
// Postcondition: None
void getDictWords(std::ifstream&, std::unordered_set<std::string>&, const std::string&);

// Precondition: string by reference, string by reference, unordered set of strings by reference
// Recursive function that makes a word ladder
// Postcondition: true if word ladder is found, otherwise false
bool findWordLadder(std::string&, const std::string&, std::unordered_set<std::string>&, int&);

// Precondition: string by reference, string by reference
// Gets the number of different letters between two strings
// Postcondition: Returns the number of different letters 
int getNumDiffLetters(const std::string&, const std::string&);

int main()
{
    std::ifstream file;
    std::string again;
    std::string word1;
    std::string word2;
    std::unordered_set<std::string> dict;
    int size;
    
    // opens file, ends program if file fails to open
    if (!openFile(file))
    {
        return -1;
    }

    // Sentinel loop, y to continue, n to exit
    do
    {
        // Takes and validates user input for first word in ladder
        std::cout << "Enter the first word in the word ladder: ";
        std::getline(std::cin, word1);
        toLowerCase(word1);
        while (!validateString(word1) || !wordExists(file, word1))
        {
            std::cout << "Enter the first word in the word ladder: ";
            std::getline(std::cin, word1);
            toLowerCase(word1);
        }
        std::cout << std::endl;

        // Takes and validates user input for final word in ladder
        std::cout << "Enter the second word in the word ladder: ";
        std::getline(std::cin, word2);
        toLowerCase(word2);
        while (!validateString(word2) || !matchLength(word1, word2) || !wordExists(file, word2))
        {
            std::cout << "Enter the second word in the word ladder: ";
            std::getline(std::cin, word2);
            toLowerCase(word2);
        }
        std::cout << std::endl;

        // Creates a vector of all the words of the same length from the text file
        getDictWords(file, dict, word1);

        //findWordLadder(dict, ladder, word2, word1.length());
        size = dict.size();
        if (!findWordLadder(word1, word2, dict, size))
        {
            std::cout << "No word ladder exists between " << word1 << " and " << word2 << "." << std::endl;
        }
        std::cout << std::endl;

        // Takes input to find another word ladder
        std::cout << "Would you like to check for another ladder (Y or N): ";
        std::getline(std::cin, again);
        while (again != "y" && again != "Y" && again != "n" && again != "N")
        {
            std::cout << "Please enter either Y or N." << std::endl;
            std::cout << "Would you like to check for another ladder (Y or N): ";
            std::getline(std::cin, again);
        }
        std::cout << std::endl;

        // clears dictionary and ladder for next use
        dict.clear();
    } while (again == "y" || again == "Y");

    file.close();

    return 0;
}

// Precondition: constant string by reference
// Validates user input for only alphabetical characters
// Postcondition: true if valid
bool validateString(const std::string& word) 
{
    // iterates through a word and checks ASCII valuus for only upper and lowercase letters
    for (unsigned int i = 0; i < word.length(); ++i)
    {
        if ((int)word[i] < 65 || ((int)word[i] > 90 && (int)word[i] < 97) || (int)word[i] > 122) 
        {
            std::cout << "Please enter only alphabetical characters." << std::endl;

            return false;
        }
    }

    return true;
}


// Precondition: constant string by reference, constant string by reference
// Validates that two strings are of the same length
// Postcondition: true if both words are the same length
bool matchLength(const std::string& word1, const std::string& word2) 
{
    // compares the lengths of each word and outputs an error message if of differing lengths
    if (word1.length() != word2.length())
    {
        std::cout << "The second word must be " << word1.length() << " letters long." << std::endl;

        return false;
    }

    return true;
}

// Precondition: ifstream by reference, constant string by reference
// Checks that the word exists in the dictionary
// Postcondition: true if the word is in the dictionary
bool wordExists(std::ifstream& file, const std::string& word)
{
    std::string temp;

    // brings buffer back to beginning of file
    file.clear();
    file.seekg(0, std::ios::beg);
    
    // iterates through file until word is found
    while (std::getline(file, temp))
    {
        if (temp == word)
        {
            return true;
        }
    }
    std::cout << "This word is not in our dictionary." << std::endl;

    return false;
}

// Precondition: string by reference
// Converts a string to be all lower case
// Postcondition: none
void toLowerCase(std::string& word)
{
    // iterates through the word and changes each character to be lowercase
    for (unsigned int i = 0; i < word.length(); ++i)
    {
        word[i] = std::tolower(word[i]);
    }
}

// Precondition: ifstream by reference
// Opens a texts file and verifies it is opened successfully
// Postcondition: true if it is opened properly
bool openFile(std::ifstream& file)
{
    file.open("Dictionary.txt");

    // verifies file successfully opened and outputs error message if it did not open.
    if (!file.is_open())
    {
        std::cout << "File failed to open. Please check file name." << std::endl;

        return false;
    }

    return true;
}

// Precondition: ifstream by reference, vector of strings by reference, string by reference, string by reference
// Creates a vector of all the words of the same length from the dictionry in the vector
// Postcondition: None
void getDictWords(std::ifstream& file, std::unordered_set<std::string>& dict, const std::string& word)
{
    int length = word.length();
    std::string tempWord;

    // starts text file at the beginning
    file.clear();
    file.seekg(0, std::ios::beg);

    // Iterates through the file
    while (std::getline(file, tempWord, '\n'))
    {
        // adds all words of the same length
        if (tempWord.length() == length)
        {
            dict.insert(tempWord);
        }
    }
}

// Precondition: string by reference, string by reference, vector of strings by reference
// Recursive function that makes a word ladder
// Postcondition: true if word ladder is found, otherwise false
bool findWordLadder(std::string& currWord, const std::string& finalWord, std::unordered_set<std::string>& dict, int& size)
{
    std::vector<std::string> similarWords;
    int diff;

    // removes the currWord from the dict, breaks from loop when found
    for (const std::string& dictWord : dict)
    {
        if (dictWord == currWord)
        {
            dict.erase(dictWord);
            --size;
            break;
        }
    }

    // adds words with only one character different to similarWords
    for (const std::string& dictWord : dict)
    {
        diff = getNumDiffLetters(dictWord, currWord);

        if (diff == 1)
        {
            similarWords.push_back(dictWord);
        }
    }

    // iteratates through similarWords
    for (unsigned int i = 0; i < similarWords.size(); ++i)
    {
        // Base condition: if word is found outputs word
        if (currWord == finalWord)
        {
            std::cout << currWord << std::endl;

            return true;
        }
        // Calls function to check next words in dictionary
        else if (findWordLadder(similarWords[i], finalWord, dict, size))
        {
            std::cout << currWord << std::endl;

            return true;
        }
    }

    return false;
}

int getNumDiffLetters(const std::string& word1, const std::string& word2)
{
    int diff = 0;

    for (unsigned int i = 0; i < word1.length(); ++i)
    {
        if (word1[i] != word2[i])
        {
            ++diff;
        }
    }

    return diff;
}