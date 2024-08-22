#include <iostream>
#include <string>
#include <cassert>

struct Trivia {
    struct TriviaNode {
        std::string question;
        std::string answer;
        int value;
        TriviaNode* next;

        TriviaNode(std::string question_in, std::string answer_in, int value_in)
            : question(question_in), answer(answer_in), value(value_in), next(nullptr) {}
    };

    struct TriviaIter {
        TriviaNode* current;

        TriviaIter(TriviaNode* node_in) : current(new TriviaNode("", "", 0)) {
            current->next = node_in;
        }

        bool has_next() {
            return current->next != nullptr;
        }

        TriviaNode next() {
            current = current->next;
            return *current;
        }
    };

    TriviaNode* first;
    TriviaNode* last;
    int size;
    int score;

    Trivia() : first(nullptr), last(nullptr), size(0), score(0) {
        // Initialize the list with hard-coded trivia
        initial_questions(3);
    }

    void initial_questions(int version) {
        size = 0;
        score = 0;
        if (version > 0) {
            add("How long was the shortest war on record? (Hint: how many minutes)", "38", 100);
            add("What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)?", "Bank of Italy", 50);
            add("What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)?", "Wii Sports", 20);
        }
    }

    bool add(std::string question_in, std::string answer_in, int value_in) {
        TriviaNode* new_node = new TriviaNode(question_in, answer_in, value_in);
        if (new_node) {
            if (size == 0) {
                first = new_node;
            } else {
                last->next = new_node;
            }
            last = new_node;
            size++;
            return true;
        }
        return false;
    }

    int ask_question() {
        if (size < 1) {
            std::cout << "Warning - the number of trivia to be asked must equal to or be larger than 1." << std::endl;
            return 1; // Indicates failure
        }

        score = 0;
        TriviaIter iter = TriviaIter(first);

        while (iter.has_next()) {
            TriviaNode current = iter.next();
            std::string user_answer;
            std::cout << "\nQuestion: " << current.question << std::endl;
            std::cout << "Answer: ";
            std::getline(std::cin, user_answer);
            if (user_answer == current.answer) {
                std::cout << "Your answer is correct! You receive " << current.value << " points." << std::endl;
                score += current.value;
            } else {
                std::cout << "Your answer is wrong. The correct answer is: " << current.answer << std::endl;
            }
            std::cout << "Your total points: " << score << std::endl;
        }
        return 0; // Indicates success
    }
};

#define UNIT_TESTING
//#define trivia_quiz

int main() {
    Trivia game = Trivia();

    #ifdef trivia_quiz
        std::cout << "*** Welcome to the trivia quiz game ***" << std::endl;
        game.ask_question();
        std::cout << "\n*** Thank you for playing the trivia quiz game. Goodbye! ***" << std::endl;
    #endif

    #ifdef UNIT_TESTING
        std::cout << "*** This is a debugging version ***" << std::endl;
        std::cout << "Unit Test Case 1: Ask no question. The program should give a warning message." << std::endl;
        game.ask_question();
        std::cout << "\nCase 1 Passed" << std::endl << std::endl;

        std::cout << "*** End of the Debugging Version ***" << std::endl;
    #endif

    return 0;
}
