#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <set>

#define N 6
#define F 4
#define W 10

using namespace std;

struct Item{
    int id;
    double weight;
    double value;
};

int complexity;

/*Function Prototypes*/
void Knabsack0_1(struct Item S[]);
double FractionalKnabsack(struct Item L[], int wieght);
double KnabsackCombined(struct Item S[], struct Item L[]);
void display(double V[N+1][W+1]);
int compare(const void *a, const void *b);
int max(int a, int b);

int main(){
    Item discrete[] = {{0, 0, 0}, {1,3, 50}, {2, 2, 25}, {3, 4, 60}, {4,1, 15}, {5, 3, 40}, {6, 2, 30}};
    Item fractionables[] = {{7, 3, 50}, {8, 2, 30}, {9, 4, 50}, {10, 1, 10}};
    
    /*QuickSort in descending order*/
    qsort(fractionables, F, sizeof(struct Item), compare);
    
    cout << "knabsack0-1" << endl;
    Knabsack0_1(discrete);
    
    cout << setprecision(2) << fixed;
    
    cout << "\nKnabsackCombined" << endl;
    int optimal_value = KnabsackCombined(discrete, fractionables);
    
    cout << "\nOptimal Value = " << optimal_value << endl;
    cout << "Complexity: O(N*W) = " << complexity << endl;
    cout << "Complexity: O(N*W) = " << N*W + F*W << endl;
    
    return 0;
}

void Knabsack0_1(struct Item S[]){
    
    double V[N + 1][W + 1];  //value table V
    
    /*Loop tough each row of items and for each weight calculate maxmimum value*/
    for(int i = 1; i <= N; i++){
        for(int w = 0; w <= W; w++){
            if(S[i].weight < w)
                V[i][w] = max(V[i-1][w], V[i-1][w - (int)(S[i].weight)] + S[i].value);
            else
                V[i][w] = V[i-1][w];
        }
    }
    
    display(V);
}



double FractionalKnabsack(struct Item L[], int weight){
    double optimal_value = 0.0;
    int w = 0;
    
    /*iterate through the fractionable items*/
    for (int i = 0; i < F; i++){    complexity++;
        
        if (w + L[i].weight <= weight){
            /*include the whole item*/
            w += L[i].weight;
            optimal_value += L[i].value;
            
        } else {
            /*include fraction of the item*/
            double remaining_weight = weight - w;
            optimal_value += L[i].value * (remaining_weight / L[i].weight);
            break;
            
        }
    }
    
    return optimal_value;
}

double KnabsackCombined(struct Item S[], struct Item L[]){
    
    double optimal_value = 0.0;
    double V[N + 1][W + 1];    //value table
    double K[N + 1][W + 1];    //knabsack table
    
    /*Populating first row with fractional knabsack values*/
    for(int w = 0; w <= W; w++){    complexity++;
        V[0][W-w] = FractionalKnabsack(L, w);
    }
    
    /*knabsack0-1, dynamically calculate the values for the value table*/
    //Loop tough each row of items and for each weight calculate maxmimum value
    for(int i = 1; i <= N; i++){
        for(int w = 0; w <= W; w++){    complexity++;
            if(S[i].weight < w) /*compute knabsack table elements*/
                K[i][w] = max(K[i-1][w], K[i-1][w - (int)(S[i].weight)] + S[i].value);
            else  /*get the value from previous row*/
                K[i][w] = K[i-1][w];
            
            /*compute Combined Value table element from knabsack table*/
            V[i][w] = K[i][w] + V[0][w];
            /*update optimal value*/
            if (V[i][w] > optimal_value)
                optimal_value = V[i][w];
        }
    }
    
    display(V);
    
    return optimal_value;
}

//auxilarry function for displaying value table
void display(double V[N+1][W+1]){
    for(int i = 0; i <= N; i++){
        for(int w = 0; w <= W; w++){
            cout << V[i][w] << "\t";
        }
        cout << endl;
    }
}

//auxillary function for getting macn of 2 values
int max(int a, int b){
    return (a > b) ? a : b;
}

//auxilarry function for quick sort in descending
int compare(const void *a, const void *b){
    Item item1 = *(struct Item*)a;
    Item item2 = *(struct Item*)b;
    
        if (item1.value/item1.weight < item2.value/item2.weight) return 1;
        if (item1.value/item1.weight > item2.value/item2.weight) return -1;
        return 0;
}





//void createSetofIncludedItems(struct Item S[], double V[N + 1][W + 1]){
//    set<int> A;
//    double optimal_value = V[N][W];
//
//    while(optimal_value > 0){
//        /*check if the optimal value is in any of the previous*/
//        for(int n = N; n > 1; n++){
//            if (V[N-n][W] == V[N-n-1][W]){
//                A.insert(S[N-n-1].id);
//                optimal_value -= S[N-n-1].value;
//            } else {
//                A.insert(S[N-n].id);
//                optimal_value -= S[N-n-1].value;
//            }
//        }
//    }
//
//
//
//
//    set <int, greater <int> > :: iterator itr;
//    cout << "\nThe set of items incuded: ";
//    for (itr = A.begin(); itr != A.end(); ++itr){
//        cout << ' ' << *itr;
//    }
//    cout << endl;
//}
