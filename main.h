#pragma once
#include <iostream>
#include "electionRound.h"
#include "fstream"


using namespace election;
enum menuOptions { zero, one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve };

void menu(electionRound* s);
void mainMenu();
void printMenu();
void printMenu2();
void optionOne(electionRound* s);
void optionTwo(electionRound* s);
void optionThree(electionRound* s);
void optionFour(electionRound* s);
void optionFive(electionRound* s);
void optionSix(electionRound* s);
void optionSeven(electionRound* s);
void optionEight(electionRound* s);
void optionNine(electionRound* s);
void optionEleven(electionRound* s);
void optionTwelve(electionRound* s);
void checkValidInputCitizen(electionRound* s, string _name, string _id, int _year, int disSerial);
void checkValidInputDistrict(electionRound* s, string _name, int _electors, int dType);
void checkValidInputParty(electionRound* s, string _name, string _leaderId);
void checkValidInputRep(electionRound* s, string _id, int _party, int _district);
void checkValidInputVote(electionRound* s, string _id, int _party);
void checkRepp(electionRound* s);
void checkNine(electionRound* s);