#include "emp-sh2pc/emp-sh2pc.h"
#include <new>
using namespace emp;
using namespace std;

Integer min(Integer x, Integer y, Integer z){
    if((x<=y & x<=z).reveal<bool>()){
        return x;
    }
    if((y<=x & y<=z).reveal<bool>()){
        return y;
    }
    if((z<=y & z<=x).reveal<bool>()){
        return z;
    }
}


void editDistDP(int inputs_a[], int inputs_b[], int m, int n)
{
    // Create a table to store results of subproblems 
    Integer a[m];
    Integer b[n];

    for( int i=0; i<m; i++) {
        a[i] = Integer(32, inputs_a[i], ALICE);

    }
    for( int i=0; i<n; i++) {
        b[i] = Integer(32, inputs_b[i], BOB);
    }

    Integer dp[m+1][n+1];

    // Fill d[][] in bottom up manner 
    for (int i=0; i<=m; i++)
    {
        for (int j=0; j<=n; j++)
        {
            // If first string is empty, only option is to 
            // insert all characters of second string 
            if (i==0){
                dp[i][j] = Integer(32, j, PUBLIC);  // Min. operations = j 

            // If second string is empty, only option is to 
            // remove all characters of second string 
             }else if ((a[i-1] == b[j-1]).reveal<bool>()){
                dp[i][j] = dp[i-1][j-1];

            // If the last character is different, consider all 
            // possibilities and find the minimum 
            }else{
                dp[i][j] = Integer(32, 1, PUBLIC) + min(dp[i][j-1],dp[i-1][j], dp[i-1][j-1]); // Replace
            }
        }
    }
    cout << "Edit distance: " << dp[m][n].reveal<int>() << endl;
}

int main(int argc, char** argv) {

    int port, party;

    // run computation with semi-honest model
    parse_party_and_port(argv, &party, &port);
    NetIO * io = new NetIO(party==ALICE ? nullptr : "127.0.0.1", port);

    setup_semi_honest(io, party);

    if (argc != 4) {
      cout << "Usage: ./innerprod <party> <port> <input>" << endl
           << endl;
      delete io;
      return 0;
    }

    cout << "Calculating edit distance" << endl;

    string this_input = argv[3];

    //Write input
    ifstream file_a ("edit1.txt");
    ifstream file_b ("edit2.txt");

    ofstream myfile;

    if(atoi(argv[1]) == 1){
        myfile.open ("edit1.txt");
    }
    else if (atoi(argv[1]) == 2){
        myfile.open ("edit2.txt");
    }
    else{
        cout << "<party> needs to be either 1 or 2" << endl;
    }

    myfile << this_input;
    myfile.close();

    //Read input
    string alice_input;
    string bob_input;

    if (file_a.is_open() && file_b.is_open()){
        getline (file_a, alice_input);
        getline (file_b, bob_input);

        file_a.close();
        file_b.close();
    }
    else
        cout << "Unable to open file";

    cout << alice_input << " " << bob_input << endl;

    int inputs_a[alice_input.length()];
    int inputs_b[bob_input.length()];
    for(int i = 0; i < alice_input.length(); i++){
        inputs_a[i] = static_cast<int>(alice_input[i]);
    }
    for(int i = 0; i < bob_input.length(); i++){
        inputs_b[i] = static_cast<int>(bob_input[i]);
    }

    editDistDP(inputs_a, inputs_b, alice_input.length(), bob_input.length());

    delete io;
    
}
