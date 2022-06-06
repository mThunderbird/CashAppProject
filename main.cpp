#include "App.h"

int main()
{

    App myApp;

    myApp.start();

    while (myApp.isActive())
    {
        myApp.update();
    }

    myApp.finish();

    return 0;
}
