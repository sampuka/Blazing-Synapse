#include "BlazingSynapseServer.hpp"

#include <iostream>

using namespace std;

int main()
{
    BlazingSynapseServer *server = new BlazingSynapseServer;

    while(!server->hasClosed())
	;

    cout << "Reached end of main()" << endl;
    
    return 0;
}
