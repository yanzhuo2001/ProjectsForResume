//
// Created by 16979 on 2022/6/27.
//

#include "deck.h"

Deck::Deck() {
    next=0;
    int i;
    int j;
    for(j=0;j<4;j++){
        for(i=0;i<13;i++){
            if(i==0){
                deck[i+13*j].spot=TWO;
            }
            else if(i==1){
                deck[i+13*j].spot=THREE;
            }
            else if(i==2){
                deck[i+13*j].spot=FOUR;
            }
            else if(i==3){
                deck[i+13*j].spot=FIVE;
            }
            else if(i==4){
                deck[i+13*j].spot=SIX;
            }
            else if(i==5){
                deck[i+13*j].spot=SEVEN;
            }
            else if(i==6){
                deck[i+13*j].spot=EIGHT;
            }
            else if(i==7){
                deck[i+13*j].spot=NINE;
            }
            else if(i==8){
                deck[i+13*j].spot=TEN;
            }
            else if(i==9){
                deck[i+13*j].spot=JACK;
            }
            else if(i==10){
                deck[i+13*j].spot=QUEEN;
            }
            else if(i==11){
                deck[i+13*j].spot=KING;
            }
            else if(i==12){
                deck[i+13*j].spot=ACE;
            }

            if(j==0){
                deck[i+13*j].suit=SPADES;
            }
            else if(j==1){
                deck[i+13*j].suit=HEARTS;
            }
            else if(j==2){
                deck[i+13*j].suit=CLUBS;
            }
            else if(j==3){
                deck[i+13*j].suit=DIAMONDS;
            }
        }
    }
}

void Deck::reset() {   //reset n=0
    next=0;
}

void Deck::shuffle(int n) {
    Card deckLeft[n];
    Card deckRight[52-n];
    int i;
    int j;
    if(n==0||n==52){
        for(i=0;i<52;i++){                 //n=0 or 52, don't need to shuffle
            deck[i]=deck[i];
        }
    }
    else{
        for(i=0;i<n;i++){                 //left deck is from deck[0] to deck[n-1]
            deckLeft[i]=deck[i];
        }
        for(i=n;i<52;i++){                //right deck is from deck[n] to deck[51]
            deckRight[i-n]=deck[i];
        }
        if(n==26){                        //left and right have the same size
            j=0;
            for(i=0;i<2*n;i++){
                deck[i]=deckRight[j];
                deck[i++]=deckLeft[j];
                j++;
            }
        }
        else if(n>26){                  //left with larger size
            j=0;
            for(i=0;i<52-n;i++){    // if one round is defined by get one from right and another from left, then there is 52-n round
                deck[j]=deckRight[i];
                deck[j+1]=deckLeft[i];  //deck[0]=right[0], deck[1]=left[0], deck[2]=right[1], deck[3]=left[1]
                j=j+2;
            }
            int m=52-n;
            for(i=(52-n)*2;i<52;i++){
                deck[i]=deckLeft[m];
                m++;
            }
        }
        else if(n<26){     //right with larger size
            j=0;
            for(i=0;i<n;i++){
                deck[j]=deckRight[i];
                deck[j+1]=deckLeft[i];
                j=j+2;
            }
            int m=n;
            for(i=n*2;i<52;i++){
                deck[i]=deckRight[m];
                m++;
            }
        }
    }
}

Card Deck::deal() {
    Card final{};
    final=deck[next];
    next++;
    return final;
}

int Deck::cardsLeft() {
    int left;
    left=52-next;
    return left;
}

