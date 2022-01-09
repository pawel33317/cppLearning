#include <iostream>
#include <vector>
using namespace std;
//  /usr/bin/g++-11 -std=c++2a -Wall -O0 -o app templateMetod.cpp && ./app

//definiuje podstawowe kroki algorytmu i pozwala implementacji je zmieniać/definiować
//w odróżnieniu od wzorca "strategia" pozwala zmieniać cześci algorytmu zamiast zastępować go w całości

struct ScoringAlgoritm{//AlgorithmBase - definiuje wszystkie kroku algorytmu, któe mogą być dostosowane
    //przez podklasy, zawiera metodę kontrolującą cały algorytm "getScore"
    int getScore(int maturaPercentage, int examPercentage){
        auto maturaPoints = calculatePointsEarnedForMatura(maturaPercentage);
        auto examPoints = calculatePointsEarnedForMatura(examPercentage);
        return calculateOveralPoints(maturaPoints, examPoints);
    }
    virtual int calculatePointsEarnedForMatura(int maturaPercentage) = 0;
    virtual int calculatePointsEarnedForExam(int examPercentage) = 0;
    virtual int calculateOveralPoints(int maturaPoints, int examPoints) = 0;
    virtual ~ScoringAlgoritm(){}
};

struct ManScoringAlgorithm : public ScoringAlgoritm{
    //ConcreteAlgorithm dostarcza prawdziwą implementację wybranych metod
    int calculatePointsEarnedForMatura(int maturaPercentage) override {
        return maturaPercentage * 1.1; };
    int calculatePointsEarnedForExam(int examPercentage) override {
        return examPercentage * 1.1; };
    int calculateOveralPoints(int maturaPoints, int examPoints) override {
        return maturaPoints + examPoints + 5; };
};
struct WomanScoringAlgorithm : public ScoringAlgoritm{
    int calculatePointsEarnedForMatura(int maturaPercentage) override {
        return maturaPercentage * 1.15; };
    int calculatePointsEarnedForExam(int examPercentage) override {
        return examPercentage * 1.22; };
    int calculateOveralPoints(int maturaPoints, int examPoints) override {
        return maturaPoints + examPoints + 3; };
};
struct ForeignPersonScoringAlgorithm : public ScoringAlgoritm{
    int calculatePointsEarnedForMatura(int maturaPercentage) override {
        return maturaPercentage * 1.22; };
    int calculatePointsEarnedForExam(int examPercentage) override {
        return examPercentage * 1.15; };
    int calculateOveralPoints(int maturaPoints, int examPoints) override {
        return maturaPoints + examPoints + 7; };
};

int main()
{
    ScoringAlgoritm* sa;
    sa = new ManScoringAlgorithm;
    cout << "Wynik faceta: " << sa->getScore(55, 66) << endl;
    delete sa;
    sa = new WomanScoringAlgorithm;
    cout << "Wynik kobiety: " << sa->getScore(55, 66) << endl;
    delete sa;
    sa = new ForeignPersonScoringAlgorithm;
    cout << "Wynik osoby z zagranicy: " << sa->getScore(55, 66) << endl;
    delete sa;
}


