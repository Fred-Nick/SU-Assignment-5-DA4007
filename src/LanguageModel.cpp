

#include "LanguageModel.h"

#include <stdexcept>

// constructor
LanguageModel::LanguageModel(int k, double alpha): k_(k), alpha(alpha){

    if (k_ <= 0){
        throw std::invalid_argument("k must be a positive integer");
    }

    if (alpha_ <0.0){

        throw std::invalid_argument("alpha must be non-negative")

    }
}

void LanguageModel::train(const std::string& text){

    if (text.size() <= static_cast<std::size_t>(k_)){
        throw std::runtime_error("Training text is too short to contain a k-gram follwed by a character");
        
    }

    gramCounts_.clear();
    Transitions_.clear();
    alphabet_.clear();

    for ( char c : text) {
        if (alphabet_.find(c) == std::string::npos){
            alphabet_ +=c;
        }

    }

    for (std::size_t i = 0; i + k_ <= text.size(); ++i){

        std::string gram = text.substr(i,k_);
        ++gramCounts_[gram];

        if (i + k_ < text.size()){
            char next = text[i + k_];
            ++Transitions_[gram][next];

        }

    }

 } // end bracket

const std::map<std::string, int>& LanguageModel::getGramsCounts() const {

    return gramCounts_;
}

const std::map<std::string, std::map<char, int>>& LanguageModel::getTransitions() const{
    return Transitions_;
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





