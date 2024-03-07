#include <iostream>
#include "constants.h"
#include "image.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int n_255=0;    //255
string mode_ppm;   //in the project, mode is P6
string command_cin;   //the whole command line "./mip ..."
int len1=0;           //the length of command_cin, and will be used in the loop
int judgeHelp=0;      //judge if there will be --help or -h
int judgeFile=0;      //judge if the file exists
int height1=1;        //store the height of the input
int width1=1;         //store the width of the input
int judge_i=0;        //judge if there is -i

void readImage(std::istream &is,Image &imI){
    int i;
    int j;
    int judge=0;
    string str1;
    string filename;
    len1=command_cin.size();
    for(i=0;i<len1;i++){
        //judge if there is --help or -h, to avoid the situation like --help1 and -hh, need to check ' ' at the front and back
        if(((command_cin[i-1]==' ')||(i==0))&&(command_cin[i]=='-')&&(command_cin[i+1]=='-')&&(command_cin[i+2]=='h')&&(command_cin[i+3]=='e')&&(command_cin[i+4]=='l')&&(command_cin[i+5]=='p')&&((command_cin[i+6]==' ')||(i+5==len1-1))){
            judgeHelp=1;
            break;
        }
        if(((command_cin[i-1]==' ')||(i==0))&&(command_cin[i]=='-')&&(command_cin[i+1]=='h')&&((command_cin[i+2]==' ')||(i+1==len1-1))){
            judgeHelp=1;
            break;
        }
    }
    if(judgeHelp==1){           //if --help or -h exists, then just print the help_message
        cout<<HELP_MESSAGE<<endl;
    }
    else{
        for(i=0;i<len1;i++){
            //find if there is the option -i
            if(((command_cin[i-1]==' ')||(i==0))&&(command_cin[i]=='-')&&(command_cin[i+1]=='i')&&(command_cin[i+2]==' ')){
                judge=1;
                judge_i=1;
                break;
            }
        }
        if(judge==1){ //if -i exists, then get the filename
            for(j=i+3;j<len1;j++){
                //j starts at i+3 because command_cin[i-1]==' ', command_cin[i]=='-', command_cin[i+1]=='i', command_cin[i+2]==' '
                if(command_cin[j]!=' '){
                    filename += command_cin[j];
                }
                else{
                    break;
                }
            }
            ifstream ifs(filename, ios_base::in | ios_base::binary);
            if(!ifs){ //open failed
                cout<<FILE_NOT_EXIST_ERROR<<endl;
                judge_i=-1;
            }
            else{
                int len2=filename.size();
                for(i=0;i<len2;i++){  //judge if it is .ppm file
                    if((filename[i]=='.')&&(filename[i+1]=='p')&&(filename[i+2]=='p')&&(filename[i+3]=='m')&&((filename[i+4]==' ')||(i+3==len2-1))){
                        judgeFile=1;
                        break;
                    }
                }
                if(judgeFile!=1){
                    cout<<FILE_TYPE_ERROR<<endl;
                    judge_i=-1;
                }
                else{  //open the file if the file exists
                    ifs>>mode_ppm;
                    ifs>>imI.w;
                    ifs>>imI.h;
                    height1=imI.h;
                    width1=imI.w;
                    ifs>>n_255;
                    ifs.get();
                    for (i = 0; i < height1; i++){
                        for (j = 0; j < width1; j++){
                            ifs.read((char*)&(imI.image[i][j].red),1);
                            ifs.read((char*)&(imI.image[i][j].green),1);
                            ifs.read((char*)&(imI.image[i][j].blue),1);
                        }
                    }
                }
                ifs.close();
                }
            }
        else{   //if -i doesn't exist, then use the cin to get the input
            is>>mode_ppm;
            is>>imI.w;
            is>>imI.h;
            height1=imI.h;
            width1=imI.w;
            cin>>n_255;
            is.get();
            for (i = 0; i < height1; i++){
                for (j = 0; j < width1; j++){
                    is.read((char*)&(imI.image[i][j].red),1);      // red
                    is.read((char*)&(imI.image[i][j].green),1);
                    is.read((char*)&(imI.image[i][j].blue),1);
                }
            }
        }
    }
}

void OutputImage(std::ostream &os,Image &imI){
    string filename;
    int i;
    int j;
    int judge=0;
    if(judge_i!=-1){
        for(i=0;i<len1;i++){
            if(((command_cin[i-1]==' ')||(i==0))&&(command_cin[i]=='-')&&(command_cin[i+1]=='o')&&(command_cin[i+2]==' ')){//find the option -o
            judge=1;
            break;
            }
        }
        if(judge==1){  //if -o exists, then find the filename
            for(j=i+3;j<len1;j++){
                if(command_cin[j]!=' '){
                    filename += command_cin[j];
                }
                else{
                    break;
                }
            }
        }
        if(judge==1){
            ofstream ofs(filename, ios_base::out | ios_base::binary);
            ofs << mode_ppm << endl << imI.w << ' ' << imI.h << endl << n_255 << endl;
            for (i = 0; i < height1; i++)
                for (j = 0; j < width1; j++)
                    ofs << (char) imI.image[i][j].red        // red
                        << (char) imI.image[i][j].green        // green
                        << (char) imI.image[i][j].blue; // red, green, blue
            ofs.close();
        }
        else {   //if -o doesn't exist, use the cout to get the output
            os << mode_ppm << endl << imI.w << ' ' << imI.h << endl << n_255 << endl;
            for (i = 0; i < height1; i++)
                for (j = 0; j < width1; j++)
                    os << (char) imI.image[i][j].red        // red
                       << (char) imI.image[i][j].green        // green
                       << (char) imI.image[i][j].blue; // red, green, blue
        }
    }
}

void verticalFlip(const Image &imI1,Image &imI2){
    int i;
    int j;
    imI2.h=imI1.h;
    imI2.w=imI1.w;
    for (i = 0; i < height1; i++) {
        for (j = 0; j < width1; j++) {    //J(i,j)=I(i,h-j)
            imI2.image[i][j].red=imI1.image[height1-1-i][j].red;        // red
            imI2.image[i][j].green=imI1.image[height1-1-i][j].green;        // green
            imI2.image[i][j].blue=imI1.image[height1-1-i][j].blue; // red, green, blue
        }
    }
}

void rotate90(const Image &imI1,Image &imI2){    //J(i,j)=I(h-j,i)
    int i;
    int j;
    imI2.h=imI1.w;
    imI2.w=imI1.h;
    for (i = 0; i < height1; i++) {
        for (j = 0; j < width1; j++) {
            imI2.image[j][height1-1-i].red=imI1.image[i][j].red;        // red
            imI2.image[j][height1-1-i].green=imI1.image[i][j].green;        // green
            imI2.image[j][height1-1-i].blue=imI1.image[i][j].blue; // red, green, blue
        }
    }
}

void intensityInversion(const Image &imI1,Image &imI2){   //J(i,j)=M-I(i,j)
    int i;
    int j;
    imI2.h=imI1.h;
    imI2.w=imI1.w;
    for (i = 0; i < height1; i++) {
        for (j = 0; j < width1; j++) {
            imI2.image[i][j].red=(255-imI1.image[i][j].red);        // red
            imI2.image[i][j].green=(255-imI1.image[i][j].green);        // green
            imI2.image[i][j].blue=(255-imI1.image[i][j].blue); // red, green, blue
        }
    }
}

void maxFilter(const Image &imI1,Image &imI2){
    int max_red=0;
    int max_green=0;
    int max_blue=0;
    imI2.h=imI1.h;
    imI2.w=imI1.w;
    int i;
    int j;
    int ii;
    int jj;
    for (i = 0; i < height1; i++) {
        for (j = 0; j < width1; j++) {
            for (ii = -1; ii < 2; ii++) {
                for (jj = -1; jj < 2; jj++) {
                    if((i+ii<0)||(j+jj<0)||(i+ii>=width1)||(j+jj>=height1)){
                        //if it is out of the range, then we consider it as (0,0,0), can't be the max, just continue
                        continue;
                    }
                    else{
                        if(imI1.image[i+ii][j+jj].red>max_red){
                            max_red=imI1.image[i+ii][j+jj].red;
                        }
                        if(imI1.image[i+ii][j+jj].green>max_green){
                            max_green=imI1.image[i+ii][j+jj].green;
                        }
                        if(imI1.image[i+ii][j+jj].blue>max_blue){
                            max_blue=imI1.image[i+ii][j+jj].blue;
                        }
                    }
                }
            }
            imI2.image[i][j].red=(unsigned char)max_red;
            imI2.image[i][j].green=(unsigned char)max_green;
            imI2.image[i][j].blue=(unsigned char)max_blue;
            max_red=0;
            max_green=0;
            max_blue=0;
        }
    }
}

void meanFilter(const Image &imI1,Image &imI2){
    int sum_red=0;
    int sum_green=0;
    int sum_blue=0;
    imI2.h=imI1.h;
    imI2.w=imI1.w;
    int i;
    int j;
    int ii;
    int jj;
    for (i = 0; i < height1; i++) {
        for (j = 0; j < width1; j++) {
            for (ii = -1; ii < 2; ii++) {
                for (jj = -1; jj < 2; jj++) {
                    if((i+ii<0)||(j+jj<0)||(i+ii>=width1)||(j+jj>=height1)){
                        //if it is out of the range, the sum will not change, just continue
                        continue;
                    }
                    else{
                        sum_red=sum_red+imI1.image[i+ii][j+jj].red;
                        sum_green=sum_green+imI1.image[i+ii][j+jj].green;
                        sum_blue=sum_blue+imI1.image[i+ii][j+jj].blue;
                    }
                }
            }
            imI2.image[i][j].red=(unsigned char)(sum_red/9);
            imI2.image[i][j].green=(unsigned char)(sum_green/9);
            imI2.image[i][j].blue=(unsigned char)(sum_blue/9);
            sum_red=0;
            sum_green=0;
            sum_blue=0;
        }
    }
}

void medianFilter(const Image &imI1,Image &imI2){
        int red[9];
        int green[9];
        int blue[9];
        int i;
        int j;
        int ii;
        int jj;
        int count=0;
        imI2.h=imI1.h;
        imI2.w=imI1.w;
        for (i = 0; i < height1; i++) {
            for (j = 0; j < width1; j++) {
                for (ii = -1; ii < 2; ii++) {
                    for (jj = -1; jj < 2; jj++) {
                        if((i+ii<0)||(j+jj<0)||(i+ii>=width1)||(j+jj>=height1)){
                            red[count]=0;
                            green[count]=0;
                            blue[count]=0;
                            count++;
                        }
                        else{
                            red[count]=imI1.image[i+ii][j+jj].red;
                            green[count]=imI1.image[i+ii][j+jj].green;
                            blue[count]=imI1.image[i+ii][j+jj].blue;
                            count++;
                        }
                    }
                }
                sort(red,red+9);
                sort(green,green+9);
                sort(blue,blue+9);
                imI2.image[i][j].red=(unsigned char)red[4];
                imI2.image[i][j].green=(unsigned char)green[4];
                imI2.image[i][j].blue=(unsigned char)blue[4];
                count=0;
            }
        }
}

int main(int argc,char* argv[]) {
    int i;
    int j;
    int counter_t=0;
    int err=0;
    vector<int> position1;
    string operation;
    Image im1,im2;
    string templateString;
    for(i=0;i<argc;i++){
        // fill the command_cin using the agrc and argv, also take the ' ' in the original sentence into consider
        templateString=argv[i];
        command_cin += " "+templateString;
    }
    readImage(cin,im1);
    if(judgeHelp==0){  //if there is no --help or -h, judge if there is -t
        for(i=0;i<len1;i++){
            if(((command_cin[i-1]==' ')||(i==0))&&(command_cin[i]=='-')&&(command_cin[i+1]=='t')&&(command_cin[i+2]==' ')){
                position1.push_back(i);
                counter_t++;
            }
        }
        //if counter_t=1, then there is -t option
        if(counter_t==1) {
            for (j = position1[0] + 3; j < len1; j++) {
                if (command_cin[j] != ' ') {
                    operation += command_cin[j];
                }
                else {
                    break;
                }
            }
            if (operation == "verticalFlip") {
                verticalFlip(im1, im2);
            } else if (operation == "rotate90") {
                rotate90(im1, im2);
            } else if (operation == "intensityInversion") {
                intensityInversion(im1, im2);
            } else if (operation == "maxFilter") {
                maxFilter(im1, im2);
            } else if (operation == "meanFilter") {
                meanFilter(im1, im2);
            } else if (operation == "medianFilter") {
                medianFilter(im1, im2);
            } else {
                err=1;
                cout << TRANSFORM_ERROR << endl;
            }
        }
        if((err==0)&&(counter_t==1)){
            OutputImage(cout,im2);
        }
    }
    cin.clear();
    return 0;
}
