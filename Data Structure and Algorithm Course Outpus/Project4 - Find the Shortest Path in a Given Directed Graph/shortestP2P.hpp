#include<iostream>
#include<list>
#include<vector>
#include<climits>
// You are not allowed to include additional libraries, either in shortestP2P.hpp or shortestP2P.cc

#define INF INT_MAX

using namespace std;

class ShortestP2P {
  public:
      ShortestP2P() {}

      /* Read the graph from stdin
       * The input has the following format:
       *
       * Firstline: 1 unsigned int, the total number of verticies, X.
       * Secondline: 1 unsigned int, the total number of edges between vertices, Y.
       * A set of Y lines, each line contains tuple of 2 unsigned int and 1 int (not unsigned int!), in the format of: A(point 1, unsigned) B(point 2, unsigned) dist(distance, int)
       *
       * Example:
       * 4
       * 4
       * 0 1 5
       * 1 2 -1
       * 2 3 4
       * 3 1 6
       * 
       * 
       * 
       *
       * Vertices that are not connected have a infinitly large distance. You may use INF (previously defined at the top of this cope snippet) for infinitly large distance.
       * 
       * Special: when the graph is not proper, where there exist any pair of vertices whose minimum distance does not exist, terminate immediately by printing:
       * cout << "Invalid graph. Exiting." << endl;
       *
       * Note: vertex pairs that are not connected, which have infinitely large distances are not considered cases where "minimum distances do not exist".
       */
      void readGraph(){
          cin>>number_of_nodes;
          cin>>number_of_edges;
          unsigned int size_adjcy_mtrx=number_of_nodes*number_of_nodes;
          Nodes=new int[size_adjcy_mtrx];
          unsigned int i=0;
          for (i=0; i<number_of_nodes; i++){
              Nodes[number_of_nodes*i+i]=0;
          }
          for (i=0; i<number_of_nodes*number_of_nodes; i++){
              Nodes[i]=INF;
          }
          int source=0;
          int destination=0;
          int weight;
          unsigned int index=0;
          for (i=0; i<number_of_edges; i++){
              cin>>source;
              cin>>destination;
              cin>>weight;
              index=number_of_nodes*source+destination;
              Nodes[index]=weight;
          }
          bool valid=ifValid();
          if (!valid){
              std::cout<<"Invalid graph. Exiting.";
              std::exit(0);
          }
      }

      /* Input: 2 vertices A and B
       * Output: distance between them.
       * cout << dist << endl;
       *
       * When the A and B are not connected print INF:
       * cout << "INF" << endl;
       */
      void distance(unsigned int A, unsigned int B){
          unsigned int index=A*number_of_nodes+B;
          if (Nodes[index]!=INF){
              cout<<Nodes[A*number_of_nodes+B]<<endl;
          }
          else{
              cout<<"INF"<<endl;
          }
      }

    ~ShortestP2P(){
        delete [] Nodes;
    }

  private:
    // internal data and functions.
    unsigned int number_of_nodes, number_of_edges;
    int* Nodes;


    bool ifValid(){
        unsigned int k,i,j;
        bool judge1,judge2,judge3;
        for (k=0; k<number_of_nodes; k++){
            for (i=0; i<number_of_nodes; i++){
                for (j=0; j<number_of_nodes; j++){
                    judge1=(Nodes[number_of_nodes*i+k] != INF) && (Nodes[number_of_nodes*k+j] != INF);
                    judge2=(Nodes[number_of_nodes*i+k] + Nodes[number_of_nodes*k+j]) < Nodes[number_of_nodes*i+j];
                    if (judge1&&judge2){
                        Nodes[number_of_nodes*i+j]=Nodes[number_of_nodes*i+k]+Nodes[number_of_nodes*k+j];
                    }
                }
                judge3=Nodes[number_of_nodes*i+i]<0;
                if (judge3){
                    return false;
                }
            }
        }
        return true;
    }
};
