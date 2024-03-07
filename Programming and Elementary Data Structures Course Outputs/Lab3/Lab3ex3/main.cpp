#include <string>
#include <iostream>
#include <cstring>

using namespace std;
const string help_message("Hey, I love Integers.");
const string add_message("This is add operation.");
const string small_message("This is small operation.");
const string no_op_message("No work to do!");



int main(int argc, char *argv[]) {
	int count;
    int judge=0;    //judge if there is add or small or help option
    int judge1=0;   //judge if there is help
    int judge2=0;   //judge if there is verbose
    cin>>count;
    int arr[count];
    int i;
    for(i=0;i<count;i++) {
        cin >> arr[i];
    }
    int sum=0;
    int small=arr[0];
    for(i=0;i<count;i++) {
        sum=sum+arr[i];
    }
    for(i=0;i<count;i++) {
        if(small>arr[i]){
            small=arr[i];
        }
    }
    int small1=small;
    const char* a[1]={"--add"};       //mode add
    const char* b[1]={"--small"};     //mode small
    const char* c[1]={"--help"};      //mode help
    const char* d[1]={"--verbose"};   //mode verbose
    for(i=0;i<argc;i++) {
        if((strcmp(argv[i], a[0]) == 0) || (strcmp(argv[i], b[0]) == 0)|| (strcmp(argv[i], c[0]) == 0)){
            judge=1;
            break;
        }
    }

    char *same[argc];
    for(i=0;i<argc;i++){
        same[i]=argv[i];
    }

    if(argc==0){
        cout<<no_op_message<<endl;
    }
    else if(judge==0){
        cout<<no_op_message<<endl;
    }
    else{
        for(i=1;i<argc;i++){
            if(strcmp(argv[i], c[0]) == 0){
                cout<<help_message<<endl;
                judge1=1;
                break;
            }
        }
        for(i=1;i<argc;i++){
            if(strcmp(argv[i], d[0]) == 0){
                judge2=1;
                break;
            }
        }
        if(judge2==1){
            for(i=1;i<argc;i++){
                small1=small;
                if((strcmp(argv[i], a[0])) == 0){
                    cout<<add_message;
                    cout<<sum<<endl;
                }
                else if((strcmp(argv[i], b[0])) == 0){
                    i++;
                    small1=small1+atoi(argv[i]);
                    cout<<small_message<<endl;
                    cout<<small1<<endl;
                }
            }
        }
        else if(judge2==0){
            for(i=1;i<argc;i++){
                if((strcmp(argv[i], a[0])) == 0){
                    cout<<sum<<endl;
                }
            }
            for(i=1;i<argc;i++){
               if((strcmp(argv[i], b[0])) == 0){
                    i++;
                    small1=small1+atoi(argv[i]);
                    cout<<small1<<endl;
                }
            }
        }
    }

	return 0;
}
