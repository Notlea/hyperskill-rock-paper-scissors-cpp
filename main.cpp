#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <sstream>
#include <string>

struct PlayerInput {
    std::string name;
    int repetitions;
    std::vector<std::string> moves;
};

namespace moveList { 
    const std::vector<std::string> moves{"Rock", "Paper", "Scissors"}; 
}

PlayerInput parsePlayerInput(const std::string& input) {
    std::stringstream ss(input);
    PlayerInput playerInput;

    ss >> playerInput.name >> playerInput.repetitions;
    
    std::string action;
    while(ss >> action) {
        playerInput.moves.push_back(action);
    }

    return playerInput;
}

void printWelcomeMessage() {
    std::cout << "Welcome to Rock, Paper, Scissors Game!\n"                    << std::endl; 
    std::cout << "Please enter your name, number of repetitions,\nand your chosen steps" << std::endl;
    std::cout << "1 - Rock,\n2 - Paper,\n3 - Scissors:" << std::endl;
    std::cout << std::endl;
}

std::string checkPlayerMove(std::string& input) {
   return (input == "1" || input == "rock" || input == "Rock") ? "Rock" :
    (input == "2" || input == "paper" || input == "Paper") ? "Paper" :
    (input == "3" || input == "scissors" || input == "Scissors") ? "Scissors" : "Invalid move";
}

std::string fixComputerMove(std::string playerMove, std::string computerMove) {
    return (playerMove == computerMove && playerMove == "Rock") ? "Scissors" :
           (playerMove == computerMove && playerMove == "Paper") ? "Rock" :
           (playerMove == computerMove && playerMove == "Scissors") ? "Paper" : computerMove;
    
}

std::string compareMove(std::string computerMove, std::string playerMove, std::string playerName, int& playerScore, int& computerScore) {
    if (computerMove == "Rock" && playerMove == "Scissors") {
        computerScore += 1;
        return "Winner: Computer.";
    } else if (computerMove == "Scissors" && playerMove == "Paper") {
        computerScore += 1;
        return "Winner: Computer.";
    } else if (computerMove == "Paper" && playerMove == "Rock") {
        computerScore += 1;
        return "Winner: Computer.";
    } else if (playerMove == "Rock" && computerMove == "Scissors") {
        playerScore += 1;
        return "Winner: " + playerName;
    } else if (playerMove == "Scissors" && computerMove == "Paper") {
        playerScore += 1;
        return "Winner: " + playerName;
    } else if (playerMove == "Paper" && computerMove == "Rock") {
        playerScore += 1;
        return "Winner: " + playerName;
    } else {
        playerScore = std::max(0, playerScore - 1);
        computerScore = std::max(0, computerScore - 1);
        return "It's a draw.";
    }
}

int main() {
    std::string playerMove, computerMove;

    printWelcomeMessage();
    std::getline(std::cin, playerMove);

    PlayerInput playerInput = parsePlayerInput(playerMove);
    
    std::cout << "> " << playerMove << std::endl;
    std::cout << std::endl;
    std::cout << "Game Start!" << std::endl;

    std::string playerAction;
    int playerScore = 0;
    int computerScore = 0;
    
    for (int i; i < playerInput.repetitions; i++) {
        std::cout << "Round " << i + 1 << ": ";
        auto selectComputerMove{ []() { thread_local std::mt19937 gen(1); 
                                        return moveList::moves[gen() % 3]; } };
            
        playerAction = checkPlayerMove(playerInput.moves[i]);
        computerMove = fixComputerMove(playerAction, selectComputerMove());
               
        if (std::find(moveList::moves.begin(), moveList::moves.end(), playerAction) != moveList::moves.end()) {
            std::cout << "Computer chose " << computerMove << ", " << playerInput.name <<" chose " << playerAction << ". " << compareMove(computerMove, playerAction, playerInput.name, playerScore, computerScore) << std::endl;
        }       
    }
    std::cout << std::endl;
    std::cout << "Game Over!" << std::endl;
    std::cout << "Total Score - " << playerInput.name << ": " << playerScore << ", " << "Computer: " << computerScore << std::endl;
    std::cout << "Would you like to play again? (yes/no)" << std::endl;
   
  return 0;
 }