#include <math.h>
#include <limits>
#include <string>
#include <map>
#include <set>
#include "myrandom.h"

using namespace std;

constexpr double lowest_double = std::numeric_limits<double>::lowest();

/* Type: Question
 *
 * Type representing a personality quiz question.
 */
struct Question {
    string questionText;  // Text of the question
    map<char, int> factors;   // Map from factors to +1 or -1
    friend bool operator< (const Question& lhs, const Question& rhs) {
        return lhs.questionText < rhs.questionText;
    }
    friend bool operator== (const Question& lhs, const Question& rhs) {
        return lhs.questionText == rhs.questionText;
    }
    friend bool operator!= (const Question& lhs, const Question& rhs) {
        return lhs.questionText != rhs.questionText;
    }
};

/* Type: Person
 *
 * Type representing a person, used to represent people when determining
 * who's the closest match to the user.
 */
struct Person {
    string name;      // Name of the person
    map<char, int> scores;  // Map from factors to +1 or -1
    friend bool operator< (const Person& lhs,   const Person& rhs) {
        return lhs.name < rhs.name;
    }
    friend bool operator== (const Person& lhs, const Person& rhs) {
        return lhs.name == rhs.name;
    }
    friend bool operator!= (const Person& lhs, const Person& rhs) {
        return lhs.name != rhs.name;
    }
};

/* randomElement
 *
 * This function selects, at random, a Question from the inputted questions set
 * and returns the question.  Note, this function does not remove the randomly
 * selected question from the set.
*/
Question randomElement(set<Question>& questions) {
    int ind = randomInteger(0, (int)questions.size()-1);
    int i = 0;
    for (auto e : questions) {
        if (i == ind) {
            return e;
        }
        i++;
    }
    return {};
}

Question randomQuestionFrom(set<Question>& questions) {
    if (questions.empty()) {
      cout<< "Error";
      throw runtime_error("map: empty");
    } else {
      Question question = randomElement(questions);
      questions.erase(question);
      return question;
    }
}

map<char, int> scoresFrom(map<Question, int>& answers) {
    map<char, int> scoresMap;
    for (pair<Question, int> p : answers) {
        int multiplyBy = p.second - 3;
        for (pair<char, int> q : p.first.factors) {
            int questionScore = multiplyBy * q.second;
            if (scoresMap.count(q.first)) {
              scoresMap[q.first] += questionScore;
            } else {
              scoresMap[q.first] = questionScore;
            }
          }
      }
    return scoresMap;
}

map<char, double> normalize(map<char, int>& scores) {
    map<char, double> normalizeMap;
    double dist = 0.0;
    double totalSquare = 0;
    int total = 0;
    for (pair<char, int> p : scores) {
        total += p.second;
    }
    if (total == 0) {
        throw runtime_error("map: empty");
    }
    if (!scores.empty()) {
      for (pair<char, int> p : scores) {
          totalSquare += pow(p.second, 2);
      }
      dist = sqrt(totalSquare);
      for (pair<char, int> p : scores) {
      normalizeMap[p.first] = (p.second / dist);
      }
    } else {
      throw runtime_error("map: empty");
    }
    return normalizeMap;
}

double cosineSimilarityOf(const map<char, double>& lhs,
                          const map<char, double>& rhs) {
    double similarity = 0.0;
    for (const pair<char, double> left : lhs) {
        if (rhs.count(left.first)) {
          double product = 0.0;
          double val = rhs.at(left.first);
          product = left.second * val;
          similarity += product;
        }
      }
    return similarity;
}

Person mostSimilarTo(map<char, int>& scores, set<Person>& people) {
    Person closestCharacter;
    if (people.empty())
    {
      throw runtime_error("set: empty");
    }
    const map<char, double> scoresNormalized = normalize(scores);
    double closest = -1.1;
    for (auto p : people) {
        if (!(people.empty())) {
          const map<char, double> characterNormalized = normalize(p.scores);
          double currentSimilarity = cosineSimilarityOf(scoresNormalized,
          characterNormalized);
          if (currentSimilarity >= closest) {
            closest = currentSimilarity;
            closestCharacter = p;
          }
        } else {
          throw runtime_error("map: empty");
        }
      }
    return closestCharacter;
}
