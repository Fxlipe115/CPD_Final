#include<string>

class Word {
    private:
        double sum;
        std::string key;
        int occurrences;
    public:
        Word(std::string key);
        double mean();
        void set_sum(double sum);
        void inc_sum(double add);
        void set_occurrences(int occ);
        void inc_occurrence();
        void set_key(std::string key);
        double get_sum();
        std::string get_key();
        int get_occurrences();
};
