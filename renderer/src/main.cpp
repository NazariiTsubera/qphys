//
// Created by nazarii on 10/14/25.
//
#include <iostream>
#include "application.h"


int main(int argc, char *argv[]){

    AppConfig config;
    Application app(config);
    app.init();
    app.run();
}