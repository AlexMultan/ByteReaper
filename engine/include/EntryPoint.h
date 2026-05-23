//
// Created by alex on 5/4/26.
//

#pragma once

#include "include/Application.h"
#include "include/Log.h"

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
    Engine::Log::Init();
    auto app = Engine::CreateApplication();
    app->Run();
    delete app;
}
