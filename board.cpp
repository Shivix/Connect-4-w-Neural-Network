#include <iostream>
#include <cmath>
#include "board.hpp"

board::board(){
    emptyGameRow.reserve(BOARD_WIDTH);
    for(int i = 0; i < BOARD_WIDTH; i++){
        emptyGameRow.push_back(counter::empty);
    }
    boardVec.reserve(BOARD_HEIGHT);
    for(int i = 0; i < BOARD_HEIGHT; i++){
        boardVec.push_back(emptyGameRow);
    }
}

/*board::board(const board &){

}

board::board(const board &&) noexcept {

}*/

board::~board() = default;

void board::draw(){
    for (auto i = 0; i < BOARD_WIDTH; ++i){
        std::cout << " " << i;
    }
    std::cout << " \n";
    for(auto heightCounter = 0; heightCounter < BOARD_HEIGHT; ++heightCounter){
        for(auto widthCounter = 0; widthCounter < BOARD_WIDTH; ++widthCounter){
            std::cout << "|";
            switch(boardVec[heightCounter][widthCounter]){
                case counter::empty : std::cout << " "; break;
                case counter::red : std::cout << "R"; break;
                case counter::yellow : std::cout << "Y"; break;
                case counter::both : std::cout << "B"; break; // both should never show up in play
                default: std::cout << "X"; break;
            }
        }
        std::cout << "|\n";
    }
    std::cout << "|";
    for(auto baseCounter = 0; baseCounter < BOARD_WIDTH * 2 - 1; ++baseCounter){
        std::cout << "=";
    }
    std::cout << "|\n";

    std::cout << "/";
    for(auto feetCounter = 0; feetCounter < BOARD_WIDTH * 2 - 1; ++feetCounter){
        std::cout << " ";
    }
    std::cout << "\\\n";
}

bool board::applyMove(int movePos, bool isRed){
    if(movePos >= BOARD_WIDTH){
        return false;
    }

    int heightCounter = 0;
    for(heightCounter = 0; heightCounter < BOARD_HEIGHT; ++heightCounter){
        if(boardVec[heightCounter][movePos] != counter::empty){
            break;
        }
    }

    if(heightCounter == 0){
        return false;
    }
    --heightCounter;
    if(isRed){
        boardVec[heightCounter][movePos] = counter::red;
    }
    else{
        boardVec[heightCounter][movePos] = counter::yellow;
    }
    return true;
}





int board::evaluateBoard(){
    int evaluation = 0;
    gameWon = false;

    // loop through all game positions
    for(int heightCounter = 0; heightCounter < BOARD_HEIGHT; ++heightCounter){
        for(int widthCounter = 0; widthCounter < BOARD_WIDTH; ++widthCounter){
            //                          check for east connect

            if((widthCounter + BOARD_CONNECT - 1) < BOARD_WIDTH){

                int groupCount = 0;
                counter groupType = counter::empty;
                for(int emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){
                    if(boardVec[(heightCounter)][(widthCounter + emptyCounter)] != counter::empty){ // if test area is not empty, skip
                        ++groupCount;

                        if(groupType == counter::empty){
                            if(boardVec[heightCounter][widthCounter + emptyCounter] == counter::red){
                                groupType = counter::red;
                            }
                            else{
                                groupType = counter::yellow;
                            }
                        }
                        else{
                            if((groupType == counter::red && boardVec[heightCounter][widthCounter + emptyCounter] == counter::yellow)
                               ||(groupType == counter::yellow && boardVec[heightCounter][widthCounter + emptyCounter] == counter::red)){
                                groupType = counter::both;
                            }
                        }
                    }
                }

                // calculate score (- for yellow + for red)

                if(groupCount > 0 && groupType != counter::both){
                    int groupScore = static_cast<int>(pow(groupCount, 4));

                    if(groupCount == BOARD_CONNECT){
                        groupScore = WINNING_SCORE;
                        gameWon = true;
                    }

                    if(groupType == counter::yellow){
                        groupScore = -groupScore;
                    }
                    evaluation += groupScore;
                }
            }

            //                                                  check for south connect                                                                

            if((heightCounter + BOARD_CONNECT - 1) < BOARD_HEIGHT){

                int groupCount = 0;
                counter groupType = counter::empty;
                for(auto emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){
                    if(boardVec[heightCounter + emptyCounter][widthCounter] != counter::empty){
                        ++groupCount;

                        if(groupType == counter::empty){
                            if(boardVec[heightCounter + emptyCounter][widthCounter] == counter::red){
                                groupType = counter::red;
                            }
                            else{
                                groupType = counter::yellow;
                            }
                        }
                        else{
                            if((groupType == counter::red && boardVec[heightCounter + emptyCounter][widthCounter] == counter::yellow)
                               ||(groupType == counter::yellow && boardVec[heightCounter + emptyCounter][widthCounter] == counter::red)){
                                groupType = counter::both;
                            }
                        }
                    }
                }

                // calculate score (-for yellow + for red)

                if(groupCount > 0 && groupType != counter::both){
                    int groupScore = static_cast<int>(pow(groupCount, 2));

                    if(groupCount == BOARD_CONNECT){
                        groupScore = WINNING_SCORE;
                        gameWon = true;
                    }

                    if(groupType == counter::yellow){
                        groupScore = -groupScore;
                    }
                    evaluation += groupScore;
                }
            }

            //                                      check for south east connect                                     
            if(((heightCounter + BOARD_CONNECT - 1) < BOARD_HEIGHT) && ((widthCounter + BOARD_CONNECT - 1) < BOARD_WIDTH)){

                int groupCount = 0;
                counter groupType = counter::empty;
                for(auto emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){

                    if(boardVec[heightCounter + emptyCounter][widthCounter + emptyCounter] != board::counter::empty){     // if test area is not empty, skip
                        ++groupCount;

                        if(groupType == counter::empty){
                            if(boardVec[heightCounter + emptyCounter][widthCounter + emptyCounter] == counter::red){
                                groupType = counter::red;
                            }
                            else{
                                groupType = counter::yellow;
                            }
                        }
                        else{
                            if((groupType == counter::red && boardVec[heightCounter + emptyCounter][widthCounter + emptyCounter] == counter::yellow)
                               ||(groupType == counter::yellow && boardVec[heightCounter + emptyCounter][widthCounter + emptyCounter] == counter::red)){
                                groupType = counter::both;
                            }
                        }
                    }
                }

                // calculate score (-for yellow + for red)

                if(groupCount > 0 && groupType != counter::both){
                    int groupScore = static_cast<int>(pow(groupCount, 2));

                    if(groupCount == BOARD_CONNECT){
                        groupScore = WINNING_SCORE;
                        gameWon = true;
                    }

                    if(groupType == counter::yellow){
                        groupScore = -groupScore;
                    }
                    evaluation += groupScore;
                }
            }
            //                                          check for south west connect                                                
            if(((heightCounter + BOARD_CONNECT - 1) < BOARD_HEIGHT) && ((widthCounter - BOARD_CONNECT + 1) >= 0)){

                int groupCount = 0;
                counter groupType = counter::empty;
                for(auto emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){
                    // if test area is not empty, skip
                    if(boardVec[heightCounter + emptyCounter][widthCounter + -emptyCounter] != counter::empty){
                        ++groupCount;

                        if(groupType == counter::empty){
                            if(boardVec[heightCounter + emptyCounter][widthCounter + -emptyCounter] == counter::red){
                                groupType = counter::red;
                            }
                            else{
                                groupType = counter::yellow;
                            }
                        }
                        else{
                            if((groupType == counter::red && boardVec[heightCounter + emptyCounter][widthCounter + -emptyCounter] == counter::yellow)
                               ||(groupType == counter::yellow && boardVec[heightCounter + emptyCounter][widthCounter + -emptyCounter] == counter::red)){
                                groupType = counter::both;
                            }
                        }
                    }
                }

                // calculate score (-for yellow + for red)

                if(groupCount > 0 && groupType != counter::both){
                    int groupScore = static_cast<int>(pow(groupCount, 2));

                    if(groupCount == BOARD_CONNECT){
                        groupScore = WINNING_SCORE;
                        gameWon = true;
                    }

                    if(groupType == counter::yellow){
                        groupScore = -groupScore;
                    }
                    evaluation += groupScore;
                }
            }
        }
    }

    //                  Check if game won - makes the score an arbitrarily high number to ensure winning is always prioritised 
    if(gameWon){
        if(evaluation > 0){
            evaluation = WINNING_SCORE;
        }
        else{
            evaluation = -WINNING_SCORE;
        }
    }
    return evaluation;
}


