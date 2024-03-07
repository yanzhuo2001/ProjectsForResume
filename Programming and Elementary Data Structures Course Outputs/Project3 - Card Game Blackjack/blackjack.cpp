#include <iostream>
#include <cstdlib>
#include <string>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "rand.h"

using namespace std;

string coutSpot(Card c){
    if(c.spot==TWO){
        return "Two";
    }
    else if(c.spot==THREE){
        return "Three";
    }
    else if(c.spot==FOUR){
        return "Four";
    }
    else if(c.spot==FIVE){
        return "Five";
    }
    else if(c.spot==SIX){
        return "Six";
    }
    else if(c.spot==SEVEN){
        return "Seven";
    }
    else if(c.spot==EIGHT){
        return "Eight";
    }
    else if(c.spot==NINE){
        return "Nine";
    }
    else if(c.spot==TEN){
        return "Ten";
    }
    else if(c.spot==JACK){
        return "Jack";
    }
    else if(c.spot==QUEEN){
        return "Queen";
    }
    else if(c.spot==KING){
        return "King";
    }
    else if(c.spot==ACE){
        return "Ace";
    }
    else{
        return "None";
    }
}

string coutSuit(Card c){
    if(c.suit==SPADES){
        return "Spades";
    }
    else if(c.suit==HEARTS){
        return "Hearts";
    }
    else if(c.suit==DIAMONDS){
        return "Diamonds";
    }
    else if(c.suit==CLUBS){
        return "Clubs";
    }
    else{
        return "None";
    }
}

int main(int argc,char* argv[]) {
    const int minimumBet=5;
    int bankroll;
    int hands;
    int thishand=0;
    string mode;
    bankroll=atoi(argv[1]);
    hands=atoi(argv[2]);
    mode=argv[3];
    Deck deck1;           // creat a new deck
    int cuts[7];
    int i;
    for(i=0;i<7;i++){      //generate 7 cuts
        cuts[i]=get_cut();
    }
    cout << "Shuffling the deck\n";
    for(i=0;i<7;i++){
        deck1.shuffle(cuts[i]);
        cout << "cut at " << cuts[i] << endl;
    }
    int bet;
    int cut;
    int income=0;
    bool drawCard;
    Player *p1=get_Simple();                   //simple player
    Player *p2=get_Counting();                 //counting player
    while((bankroll>=5)&&(thishand<hands)){
        Hand handPlayer1;
        Hand handDealer1;
        handPlayer1.discardAll();
        handDealer1.discardAll();
        thishand++;
        cout << "Hand " << thishand << " bankroll " << bankroll << endl;
        if(deck1.cardsLeft()<20){
            deck1.reset();
            cut=get_cut();
            deck1.shuffle(cut);
            if(mode=="count"){
                p2->shuffled();      //return count=0
            }
            cout << "Shuffling the deck\n";
            cout << "cut at " << cut << endl;
        }
        int judgeNatural=0;                                   //judge if it is natural 21
        Card c{};                                             //use as the buffer
        Card dealer{};                                        //the first card of the dealer
        if(mode=="simple"){          //mode simple
            bet=p1->bet(bankroll,minimumBet);        //get the bet
            cout << "Player bets " << bet << endl;
            c=deck1.deal();
            cout<<"Player dealt "<<coutSpot(c)<<" of "<<coutSuit(c)<<endl;
            handPlayer1.addCard(c);
            c=deck1.deal();
            dealer=c;
            cout<<"Dealer dealt "<<coutSpot(c)<<" of "<<coutSuit(c)<<endl;
            handDealer1.addCard(c);
            c=deck1.deal();
            cout<<"Player dealt "<<coutSpot(c)<<" of "<<coutSuit(c)<<endl;
            handPlayer1.addCard(c);
            Card hole{};
            c=deck1.deal();
            hole.suit=c.suit;
            hole.spot=c.spot;                               // the initialization, player two cards
            handDealer1.addCard(hole);                              // the initialization, dealer one card and one hole card
            if(handPlayer1.handValue().count==21){
                judgeNatural=1;
                income=bet*3/2;
                cout << "Player dealt natural 21\n";                   // the situation of natural 21
            }
            if(judgeNatural==0){                                           // the situation of not natural 21
                drawCard=p1->draw(dealer,handPlayer1);              // judge whether drawing a card
                while(drawCard){                                          //  drawCard is true, then keep drawing
                    c=deck1.deal();
                    cout<<"Player dealt "<<coutSpot(c)<<" of "<<coutSuit(c)<<endl;
                    handPlayer1.addCard(c);
                    drawCard=p1->draw(dealer,handPlayer1);
                }
                cout << "Player's total is " << handPlayer1.handValue().count << endl;
                if(handPlayer1.handValue().count>21){                     //player busts
                    cout << "Player busts\n";
                    income=-bet;
                }
                else{
                    cout<<"Dealer's hole card is "<<coutSpot(hole)<<" of "<<coutSuit(hole)<<endl;   //player not bust, need to show the hole
                    while(handDealer1.handValue().count<17){
                        c=deck1.deal();                                                  //player need to reach at least 17
                        cout<<"Dealer dealt "<<coutSpot(c)<<" of "<<coutSuit(c)<<endl;
                        handDealer1.addCard(c);
                    }
                    if(handDealer1.handValue().count>21){                                //dealer busts
                        cout << "Dealer's total is " << handDealer1.handValue().count << endl;
                        cout << "Dealer busts\n";
                        income=bet;
                    }
                    else{                                                                //dealer not busts, need to compare
                        cout << "Dealer's total is " << handDealer1.handValue().count << endl;
                        if(handPlayer1.handValue().count>handDealer1.handValue().count){
                            cout << "Player wins\n";
                            income=bet;
                        }
                        else if(handPlayer1.handValue().count<handDealer1.handValue().count){
                            cout << "Dealer wins\n";
                            income=-bet;
                        }
                        else{
                            cout << "Push\n";
                            income=0;
                        }
                    }
                }
            }
        }

        else if(mode=="counting"){     //mode count
            bet=p2->bet(bankroll,minimumBet);
            cout << "Player bets " << bet << endl;
            c=deck1.deal();
            cout<<"Player dealt "<<coutSpot(c)<<" of "<<coutSuit(c)<<endl;
            p2->expose(c);
            handPlayer1.addCard(c);
            c=deck1.deal();
            dealer=c;
            cout<<"Dealer dealt "<<coutSpot(c)<<" of "<<coutSuit(c)<<endl;
            handDealer1.addCard(c);
            p2->expose(c);
            c=deck1.deal();
            cout<<"Player dealt "<<coutSpot(c)<<" of "<<coutSuit(c)<<endl;
            handPlayer1.addCard(c);
            p2->expose(c);
            Card hole{};
            c=deck1.deal();
            hole.suit=c.suit;
            hole.spot=c.spot;                          //the hole card, initially not exposed
            handDealer1.addCard(c);
            if(handPlayer1.handValue().count==21){
                judgeNatural=1;
                income=bet*3/2;
                cout << "Player dealt natural 21\n";                   // the situation of natural 21
            }
            if(judgeNatural==0){                                            // the situation of not natural 21
                drawCard=p2->draw(dealer,handPlayer1);    // judge whether drawing a card
                while(drawCard){                                          //  drawCard is true, then keep drawing
                    c=deck1.deal();
                    cout<<"Player dealt "<<coutSpot(c)<<" of "<<coutSuit(c)<<endl;
                    handPlayer1.addCard(c);
                    p2->expose(c);                           //expose the card each time
                    drawCard=p2->draw(dealer,handPlayer1);
                }
                cout << "Player's total is " << handPlayer1.handValue().count << endl;
                if(handPlayer1.handValue().count>21){                     //player busts
                    cout << "Player busts\n";
                    income=-bet;
                }
                else{
                    cout<<"Dealer's hole card is "<<coutSpot(hole)<<" of "<<coutSuit(hole)<<endl;   //player not bust, need to show the hole
                    p2->expose(hole);
                    while(handDealer1.handValue().count<17){
                        c=deck1.deal();                                                  //player need to reach at least 17
                        cout<<"Dealer dealt "<<coutSpot(c)<<" of "<<coutSuit(c)<<endl;
                        handDealer1.addCard(c);
                        p2->expose(c);
                    }
                    if(handDealer1.handValue().count>21){                                //dealer busts
                        cout << "Dealer's total is " << handDealer1.handValue().count << endl;
                        cout << "Dealer busts\n";
                        income=bet;
                    }
                    else{                                                                //dealer not busts, need to compare
                        cout << "Dealer's total is " << handDealer1.handValue().count << endl;
                        if(handPlayer1.handValue().count>handDealer1.handValue().count){
                            cout << "Player wins\n";
                            income=bet;
                        }
                        else if(handPlayer1.handValue().count<handDealer1.handValue().count){
                            cout << "Dealer wins\n";
                            income=-bet;
                        }
                        else{
                            cout << "Push\n";
                            income=0;
                        }
                    }
                }
            }
        }
        bankroll=bankroll+income;
    }
    cout << "Player has " << bankroll<< " after " << thishand << " hands\n";
    return 0;
}
