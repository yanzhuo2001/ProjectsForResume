//
// Created by 16979 on 2022/6/27.
//

#include "player.h"


class simple: public Player{
    int simpleBet;

public:
    simple(){
        simpleBet=0;
    };

    int bet(unsigned int bankroll, unsigned int minimum) override{
        if(bankroll>=minimum){
            simpleBet=minimum;
        }
        else{
            simpleBet=0;
        }
        return simpleBet;
    }

    bool draw(Card dealer,const Hand &player) override{
        bool result=false;
        if(!player.handValue().soft){     //the hand value is hard count
            if(player.handValue().count>=17){  //>17, no draw
                result= false;
            }
            else if(player.handValue().count<=11){   //>11, draw
                result= true;
            }
            else if(player.handValue().count==12){
                if((dealer.spot==FOUR)||(dealer.spot==FIVE)||(dealer.spot==SIX)){  //4 5 6, no draw
                    result= false;
                }
                else{
                    result= true;
                }
            }
            else if((player.handValue().count>=13)&&(player.handValue().count<=16)){
                if((dealer.spot==TWO)||(dealer.spot==THREE)||(dealer.spot==FOUR)||(dealer.spot==FIVE)||(dealer.spot==SIX)){  //2-6, no draw
                    result= false;
                }
                else{
                    result= true;
                }
            }
        }
        else{                           //the hand value is soft count
            if(player.handValue().count<=17){     //<=17, draw
                result= true;
            }
            else if(player.handValue().count==18){
                if((dealer.spot==TWO)||(dealer.spot==SEVEN)||(dealer.spot==EIGHT)){  //2 7 8, draw
                    result= false;
                }
                else{
                    result= true;
                }
            }
            else if(player.handValue().count>=19){  //>=19, no draw
                result= false;
            }
        }
        return result;
    }

    void expose(Card c) override{
    }

    void shuffled() override{
    }

};


class count: public Player{
    int countBet;
    int count1;    //to count the deck
public:
    count(){
        countBet=0;
        count1=0;
    };

    int bet(unsigned int bankroll, unsigned int minimum) override{
        if(bankroll>=minimum){
            if(bankroll<2*minimum){
                countBet=minimum;
            }
            else{                       //enough money
                if(count1>=2){          //enough count1
                    countBet=2*minimum;
                }
                else{
                    countBet=minimum;
                }
            }

        }
        else{
            countBet=0;
        }
        return countBet;
    }

    bool draw(Card dealer,const Hand &player) override{
        bool result=false;
        if(!player.handValue().soft){     //the hand value is hard count
            if(player.handValue().count>=17){  //>17, no draw
                result= false;
            }
            else if(player.handValue().count<=11){   //>11, draw
                result= true;
            }
            else if(player.handValue().count==12){
                if((dealer.spot==FOUR)||(dealer.spot==FIVE)||(dealer.spot==SIX)){  //4 5 6, no draw
                    result= false;
                }
                else{
                    result= true;
                }
            }
            else if((player.handValue().count>=13)&&(player.handValue().count<=16)){
                if((dealer.spot==TWO)||(dealer.spot==THREE)||(dealer.spot==FOUR)||(dealer.spot==FIVE)||(dealer.spot==SIX)){  //2-6, no draw
                    result= false;
                }
                else{
                    result= true;
                }
            }
        }
        else{                           //the hand value is soft count
            if(player.handValue().count<=17){     //<=17, draw
                result= true;
            }
            else if(player.handValue().count==18){
                if((dealer.spot==TWO)||(dealer.spot==SEVEN)||(dealer.spot==EIGHT)){  //2 7 8, draw
                    result= false;
                }
                else{
                    result= true;
                }
            }
            else if(player.handValue().count>=19){  //>=19, no draw
                result= false;
            }
        }
        return result;
    }

    void expose(Card c) override{
        if((c.spot==TWO)||(c.spot==THREE)||(c.spot==FOUR)||(c.spot==FIVE)||(c.spot==SIX)){
            count1++;
        }
        else if((c.spot==TEN)||(c.spot==JACK)||(c.spot==QUEEN)||(c.spot==KING)||(c.spot==ACE)){
            count1--;
        }
    }

    void shuffled() override{
        count1=0;
    }

};

static simple sp;
static count cp;
Player *s1=&sp;
Player *c1=&cp;


Player *get_Simple(){
    return s1;
}

Player *get_Counting(){
    return c1;
}