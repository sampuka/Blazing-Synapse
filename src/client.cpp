#include "BlazingSynapseClient.hpp"

using namespace std;

int main()
{
    BlazingSynapseClient *client = new BlazingSynapseClient;

    while (!client->hasClosed())
	;

    cout << "Reached end of main()" << endl;
    
    return 0;
}
