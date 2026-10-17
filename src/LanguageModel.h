

// Prevent classes for being defined more than once
//  i.e., prevents the header file from being included in teh compiling more than once

#ifndef LANGUAGE_MODEL_H
#define LANGUAGE_MODEL_H

// include the standard libraries
#include <map> // key value pairs
#include <string> // Store strings as sequences of charcters


class LanguageModel{
    
    private:

    int k_;
    double alpha_;
    std::string alphabet_;

    std::map<std::string, int> gramCounts_;
    std::map<std::string, std::map<char, int>> transitions_;

    std::map<std::string, int> followedCounts_;

    public:
    
    // CONSTRUCTORS:

    explicit LanguageModel (int k, double alpha = 0.0);

    // FUNCTIONS:

    // training function passes the string by reference& (std::string) <- type, text <-input
    // const prevents the referensed string from being changed
    // thus this is function train(argument)
    void train(const std::string& text);


    // get the bigrams k
    const std::map<std::string, int>& getGramsCounts() const;
    
    // Letters after each bigram
    const std::map<std::string, std::map<char, int>>& getTransitions() const;

    // Get the number of bigram intervall if a bigram consists of 3 letters its = 3
    int getK() const;

    double getAlpha() const;

    const std::string& getAlphabet() const;

    double getTransitionProbability(
        const std::string& gram,
        char nextChar

    ) const;

};

#endif




