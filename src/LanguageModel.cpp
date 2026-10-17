

#include "LanguageModel.h"

#include<cmath>
#include <stdexcept>

// constructor
LanguageModel::LanguageModel(int k, double alpha): k_(k), alpha_(alpha){

    if (k_ <= 0){
        throw std::invalid_argument("k must be a positive integer");
    
    }

    if (!std::isfinite(alpha_) || alpha_ <0.0){

        throw std::invalid_argument("alpha must be non-negative");

    }
}

void LanguageModel::train(const std::string& text){

    if (text.size() <= static_cast<std::size_t>(k_)){
        throw std::runtime_error("Training text is too short to contain a k-gram follwed by a character");
        
    }

    
    gramCounts_.clear();
    followedCounts_.clear();
    transitions_.clear();
    alphabet_.clear();

    for ( char c : text) {
        if (alphabet_.find(c) == std::string::npos){
            alphabet_ +=c;
        }

    }

    for (std::size_t i = 0; i + k_ <= text.size(); ++i){

        std::string gram = text.substr(i,k_);
        ++gramCounts_[gram];

        if (i + static_cast<std::size_t>(k_)< text.size()){
            char next = text[i + k_];
            ++followedCounts_[gram];
            ++transitions_[gram][next];

        }

    }

 } // end bracket

const std::map<std::string, int>& LanguageModel::getGramsCounts() const {

    return gramCounts_;
}

const std::map<std::string, std::map<char, int>>& LanguageModel::getTransitions() const{
    return transitions_;
}

int LanguageModel:: getK() const {

    return k_;

}

double LanguageModel::getAlpha() const {

    return alpha_;

}

const std::string& LanguageModel::getAlphabet() const{
    return alphabet_;

}

double LanguageModel::getTransitionProbability(
    
    const std::string& gram,
    char nextChar
) const  {

    // The charcter must be in the alphabet
    if (alphabet_.find(nextChar) == std::string::npos){
        return 0.0;
    }

    // count how often nextChar follows gram
    int count = 0;

    auto gramIT = transitions_.find(gram);

    if (gramIT != transitions_.end()) {
        auto charIT = gramIT->second.find(nextChar);

        if (charIT != gramIT->second.end()){
            count = charIT->second;
        }
    }

    // count occurrences of gram that have a following charcter
    int total = 0;

    auto totalIT = followedCounts_.find(gram);
        
        if(totalIT != followedCounts_.end()){
            total = totalIT->second;
        }
    
     // apply pseudocount smoothing (laplace smoothing)
     double numerator = count + alpha_;
     double denominator = total+alpha_ * alphabet_.size();
        
        if (denominator == 0.0){
            return 0.0;
        }

        return numerator/denominator;
}



