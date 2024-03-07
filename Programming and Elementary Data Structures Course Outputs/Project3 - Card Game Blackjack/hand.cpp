//
// Created by 16979 on 2022/6/27.
//

#include "hand.h"



Hand::Hand() {
    curValue.count=0;
    curValue.soft= false;
}

void Hand::discardAll() {
    curValue.count=0;
    curValue.soft=false;
}

void Hand::addCard(Card c) {
    if(c.spot!=ACE){
        if((c.spot!=JACK)&&(c.spot!=QUEEN)&&(c.spot!=KING)){
            curValue.count=curValue.count+c.spot+2;
        }
        else{
            curValue.count=curValue.count+10;
        }
        curValue.soft= false;
    }
    else{
        curValue.count++;                                   //just regard ACE as 1
        curValue.soft= true;
    }
}

HandValue Hand::handValue() const {
    HandValue result{};
    result.count=curValue.count;
    result.soft=curValue.soft;
    if(result.soft){
        if(result.count>21){    //consider all ace to be 1, if still too large, just abandon
            result.soft=false;
        }
        else if(10+result.count>21){  //at most consider one ace to be 11, then the sum will add 10, if failure
            result.soft=false;
        }
        else{
            result.count=result.count+10;  //consider one ace to be 10, if success
            result.soft=true;
        }
    }
    else{
        result.count=curValue.count;
        result.soft=false;
    }
    return result;
}


