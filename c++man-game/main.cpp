#include <iostream>
#include <vector>
#include <cassert>
#include "Random.h"


//This is a game called c++ man, the rules of the game is in the following:
//High level:

//The computer will pick a word at random and draw an underscore for each letter in the word.
//The player wins if they guess all the letters in the word before making X wrong guesses (where X is configurable).
//Each turn:

//The player will guess a single letter.
//If the player has already guessed that letter, it doesn’t count, and play continues.
//If any of the underscores represent that letter, those underscores are replaced with that letter, and play continues.
//If no underscores represent that letter, the player uses up one of their wrong guesses.
//Status:

//The player should know how many wrong guesses they have left.
//The player should know what letters they have guessed incorrectly (in alphabetical order).


namespace Wordlist
{
const std::vector<std::string_view> animals {"tiger", "lion", "monkey", "duck", "elephant", "fox", "ostrich", "gorilla", "sloth"};
const std::vector<std::string_view> countries{"kenya", "saudi arabia", "kongo", "thailand", "america", "argentina", "somal", "indonesia", "afghanistan"};
const std::vector<std::string_view> food {"cake", "maqluba", "mansaf", "lasagna", "apple", "kiwi", "pizza", "spaghetti", "tapas"};

const std::vector<std::vector<std::string_view>> words{animals, countries, food};


std::string_view getRandomWord(){
    std::vector randomVector = words[Random::get<std::size_t>(0, words.size() - 1)];
    
    if(randomVector == animals){
        std::cout << "What's the animal?\n";
    }
    else if(randomVector == countries){
        std::cout << "What's the country?\n";
    }
    else{
        std::cout << "What's the food?\n";
    }
    return randomVector[Random::get<std::size_t>(0, randomVector.size() - 1)];
}
}

class Session{
private:
    std::size_t remainingTries;
    std::string pluses = "++++++";
    
public:
    Session(){
        remainingTries = 5;
    }
    
    void remainingGuesses(bool found,[[maybe_unused]] char letter){
        if(found == false && letter >= 'a' && letter <= 'z'){
            pluses[remainingTries] = letter;
            std::cout << pluses << "\n";
            if(remainingTries == 0)return;
            remainingTries--;
        }
            
        
        else{
            std::cout << pluses << "\n";
        }
    }
    
    std::string underscores(std::string_view randomWord){
        std::string emptyString{};
        for(std::size_t index = 0; index < std::size(randomWord); index++){
            emptyString.push_back('_');
        }
        return emptyString;
    }
    
    void ignoreLine(){
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "That wasn't a valid input. Try again.\n";
        }
        else{
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
    }
    
    void displayStatus(const std::string& emptyString, bool found, char letter){
        std::cout << emptyString << ".";
        remainingGuesses(found, letter);

    }
    
    void getInput(std::string_view randomWord)  //get input from user, it only accepts small letters
    {
        char letter{};
        std::size_t index = 0;
        bool found{false};
        std::string emptyString = underscores(randomWord);
        std::vector<char> inputtedLetters{};
        
        while(true)
        {
            if(remainingTries == 0){
                std::cout << "You're out of guesses, the word was: " << randomWord << '\n';
                return;
            }
            
            std::cout << "The word: "; //display status
            if(found == true){
                displayStatus(emptyString, found, letter);
                found = false;
            }
            else{
                displayStatus(emptyString, found, letter);
            }
            
            if(emptyString == randomWord){ //was the entire word guessed correctly?
                std::cout << "Congrats, you guessed the word correctly!\n";
                return;
            }
            
            std::cout << "Enter your next letter: "; //ask for input
            std::cin >> letter;
            
            ignoreLine(); //validate input
            if(letter < 'a' || letter > 'z'){
                std::cout << "That wasn't a valid input. Try again.\n";
                continue;
            }
            
            index = 0;
            for(; index < std::size(randomWord); ++index)//check if the guessed letter is in the word
            {
                if (randomWord[index] == letter)
                {
                    emptyString[index] = letter;
                    found = true;
                }
                
            }
            
                for(const auto& c : inputtedLetters) //check if letter was guessed before
                {
                    if(c == letter)
                    {
                        std::cout << "You already guessed this letter \n";
                        found = true;
                        break;
                    }
                }
            inputtedLetters.push_back(letter);
            
        }
    }
    
    

};

int main() {
    
    Session s;

    std::cout << "Welcome to C++man (a variant of Hangman)\n";
    std::cout << "To win: guess the word. To lose: run out of pluses.\n\n";
    
    std::string_view randomWord = Wordlist::getRandomWord();
    
    s.getInput(randomWord);
    
    
    return 0;
}
