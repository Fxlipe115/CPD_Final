#ifndef WORD_HPP
#define WORD_HPP

#include<list>
#include<string>

class Word {
    private:
        double sum;
        std::string key;
        int occurrences;
        int pos;
        int neg;
        std::list<int> reviews;
        double wil_lower_bound(int pos, int total);
    public:
        Word(std::string key);
        double mean();
        void set_sum(double sum);
        void add_sum(double value);
        void set_occurrences(int occ);
        void inc_occurrence();
        void set_key(std::string key);
        double get_sum();
        std::string get_key();
        int get_occurrences();
        const std::list<int>& get_reviews();
        void add_review(int key);
        void set_pos(int pos);
        void inc_pos();
        int get_pos();
        void set_neg(int neg);
        void inc_neg();
        int get_neg();
};

#endif
