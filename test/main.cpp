#include <iostream>
#include <string>
#include <algorithm>
using namespace std;



class Card {
  public:
    int value;
    int suit;
    string color;
    Card(int v, int s, string c) : value(v), suit(s), color(c) {}
    Card(): value(0), suit(0), color(""){}
    bool operator==(const Card& a){
      return (value == a.value && suit == a.suit && color == a.color);
    }
    friend ostream& operator<<(ostream& os, const Card& a){
      os << a.value << " " << a.suit << " " << a.color << endl;
      return os;
    }
};

class Deck{
  Card *deckOfCard;
  int size;
  public:
  Deck(){
    size = 52;
    deckOfCard = new Card[size];
    int index = 0;
    for(int i = 0; i < 2; i++ ){
      for(int j = 0; j < 13; j++){
        deckOfCard[index].value = j;
        deckOfCard[index].suit = i;
        deckOfCard[index++].color = "red";
      }
    }
    for(int i = 0; i < 2; i++ ){
      for(int j = 0; j < 13; j++){
        deckOfCard[index].value = j;
        deckOfCard[index].suit = i;
        deckOfCard[index++].color = "black";
      }
    }
    random_shuffle(deckOfCard, deckOfCard+size);

  }
  Card randomCard(){
    return deckOfCard[rand() % size];
  }
  void removeCard(Card card){
    Card* newDeckOfCard = new Card[--size];
    int index = 0;
    for(int i = 0; i < size; i++){
      if(deckOfCard[i] == card) continue;
      newDeckOfCard[index++] = deckOfCard[i];
    }
    delete[] deckOfCard;
    deckOfCard = newDeckOfCard;
  }
  void printDeck(){
    for(int i = 0; i < size; i++){
      cout << deckOfCard[i].value << " " << deckOfCard[i].suit << " " << deckOfCard[i].color << endl;
    }
  }
};


class Passiange : public Deck{
  public:
  Passiange(){
    Deck();
  }
  int run(int round = 1){
    int rem = 0;
    for(int i = 0; i < round; i++){
    Card card1 = randomCard();
    Card card2 = randomCard();
    Card card3 = randomCard();

    if(card1.color == card3.color){
      rem++;
      removeCard(card1);
      removeCard(card3);
      std::cout << "Removed - " << rem << " :\n"<< card1 << card3;
    }
    std::cout << "Removed - " << rem<< endl;
    return rem;
    }
  }
};


void card_unit() {
  srand(time(nullptr));
  Passiange passiange = Passiange();
  cout << "Deck:\n";
  passiange.printDeck();
  int res = passiange.run(3);
  if (res > 0){
  cout << "\nDeck:\n";
  passiange.printDeck();
  cout <<"result: " <<res;
  }  
}
