//
// Created by nazarii on 10/14/25.
//

#ifndef QPHYS_APPLICATION_H
#define QPHYS_APPLICATION_H

#include <cstdint>
#include <memory>

#include "uniphys/engine.h"

struct AppConfig {
    std::uint32_t width{1280};
    std::uint32_t height{720};
    std::string title{"Untitled"};
};


class Application {
public:
    Application(AppConfig ap);
    ~Application();

    void init();
    void run();

private:
    void initWindow();
    void initGlad();
    void initImgui();

    void renderUi();


private:
    bool running_{true};
    void* window_;
    std::unique_ptr<qphys::Engine> engine_;
    AppConfig config_;
};

#endif //QPHYS_APPLICATION_H