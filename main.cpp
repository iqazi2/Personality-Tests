#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "driver.h"

using namespace std;

void loadFile(string filename, set<Question> &questions, set<Person> &people);
void parseLine(Question &question, string line);
void parsePeople(Person &character, string line);

void parseFactor(Question &question, string factor);

void loadFile(string filename, set<Question> &questions, set<Person> &people) {
  ifstream inputFile;
  inputFile.open(filename);
  if (inputFile.fail()) {
    cout << "\nError: unable to open "
         << "'" << filename << "'" << endl;
    return;
  }
  while (!inputFile.eof()) {
      if (filename == "questions.txt") {
        string line;
        Question question;
        getline(inputFile, line);
        if (line.empty()) {
            break;
        }
        parseLine(question, line);
        questions.insert(question);
      } else {
        string line;
        Person character;
        getline(inputFile, line);
        if (line.empty()) {
            break;
        }
        parsePeople(character, line);
        people.insert(character);
      }
    }
}

void parsePeople(Person &character, string line) {
  stringstream ss(line);
  getline(ss, character.name, '.');
  while (!ss.eof()) {
      string factor;
      getline(ss, factor, ' ');
      if (!factor.empty()) {
        size_t position = factor.find(":");
        string keyString = factor.substr(0 , position);
        string valueString;
        char key = keyString[0];
        int value = stoi(factor.substr(position + 1));
        character.scores[key] = value;
      }
    }
}

void parseLine(Question &question, string line) {
  stringstream ss(line);
  getline(ss, question.questionText, '.');
  while (!ss.eof()) {
      string factor;
      getline(ss, factor, ' ');
      if (!factor.empty()) {
        size_t position = factor.find(":");
        string keyString = factor.substr(0 , position);
        string valueString;
        char key = keyString[0];
        int value = stoi(factor.substr(position + 1));
        question.factors[key] = value;
      }
    }
}

int main() {
  cout << "Welcome to the Personality Quiz!" << endl << endl;
  cout << "Choose number of questions: ";
  set<Question> questions;
  set<Person> people;
  map<Question, int> enteredScores;
  map<char, int> computedScores;

  int questionQuantityChoice;
  cin >> questionQuantityChoice;
  string filename = "questions.txt";
  loadFile(filename,questions , people);
  char quote = '"';
  
  for (int i = 0; i<questionQuantityChoice; i++) {
      Question question;
      question = randomQuestionFrom(questions);
      cout << "\nHow much do you agree with this statement?"
        << endl;
      cout << quote << question.questionText
      << "." << quote << endl;
      cout << "\n1. Strongly disagree" << endl
        << "2. Disagree" << endl
        << "3. Neutral" << endl
        << "4. Agree" << endl
        << "5. Strongly agree" << endl;
      int agreeabilty;
      cout << "\nEnter your answer here (1-5): ";
      cin >> agreeabilty;
      enteredScores[question] = agreeabilty;
    }

  computedScores = scoresFrom(enteredScores);
  int choice = 10;
  while (choice != 0) {
      cout << "\n1. BabyAnimals" << endl
        << "2. Brooklyn99" << endl
        << "3. Disney" << endl
        << "4. Hogwarts" << endl
        << "5. MyersBriggs" << endl
        << "6. SesameStreet" << endl
        << "7. StarWars" << endl
        << "8. Vegetables" << endl
        << "9. mine" << endl
        << "0. To end program." << endl << endl;
      cout << "Choose test number (1-9, or 0 to end): ";
      cin >> choice;
      if (choice == 1) {
        Person person;
        filename = "BabyAnimals.people";
        loadFile(filename, questions, people);
        person = mostSimilarTo(computedScores, people);
        cout<< "\nYou got " << person.name << "!" << endl;
      }
      if (choice == 2) {
        Person person;
        filename = "Brooklyn99.people";
        loadFile(filename, questions, people);
        person = mostSimilarTo(computedScores, people);
        cout<< "\nYou got " << person.name << "!" << endl;
      }
      if (choice == 3) {
        Person person;
        filename = "Disney.people";
        loadFile(filename, questions, people);
        person = mostSimilarTo(computedScores, people);
        cout<< "\nYou got " << person.name << "!" << endl;
      }
      if (choice == 4) {
        Person person;
        filename = "Hogwarts.people";
        loadFile(filename, questions, people);
        person = mostSimilarTo(computedScores, people);
        cout<< "\nYou got " << person.name << "!" << endl;
      }
      if (choice == 5) {
        Person person;
        filename = "MyersBriggs.people";
        loadFile(filename, questions, people);
        person = mostSimilarTo(computedScores, people);
        cout<< "\nYou got " << person.name << "!" << endl;
      }
      if (choice == 6) {
        Person person;
        filename = "SesameStreet.people";
        loadFile(filename, questions, people);
        person = mostSimilarTo(computedScores, people);
        cout<< "\nYou got " << person.name << "!" << endl;
      }
      if (choice == 7) {
        Person person;
        filename = "Starwars.people";
        loadFile(filename, questions, people);
        person = mostSimilarTo(computedScores, people);
        cout<< "\nYou got " << person.name << "!" << endl;
      }
      if (choice == 8) {
        Person person;
        filename = "Vegetables.people";
        loadFile(filename, questions, people);
        person = mostSimilarTo(computedScores, people);
        cout<< "\nYou got " << person.name << "!" << endl;
      }
      if (choice == 9) {
        Person person;
        filename = "mine.people";
        loadFile(filename, questions, people);
        person = mostSimilarTo(computedScores, people);
        cout<< "\nYou got " << person.name << "!" << endl;
      }
      if (choice == 0) {
        cout<< "Goodbye!" << endl;
        exit(0);
      }
    }
  return 0;
}
