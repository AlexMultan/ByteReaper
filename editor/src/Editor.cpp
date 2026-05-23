//
// Created by alex on 5/10/26.
//

#include "include/ByteReaper.h"

class ExampleLayer : public Engine::Layer
{
public:

    ExampleLayer() : Layer("Example")
    {

    }

    void OnAttach() override
    {
        REAPER_WARN("Application has started!");
    }

    void OnUpdate() override
    {
		
    }

    void OnDetach() override
    {
        REAPER_WARN("Application has shutdown!");
    }

};

class Game : public Engine::Application
{
public:

    Game()
    {
        PushLayer(new ExampleLayer());
    }
	
    ~Game()
    {
		
    }
};

Engine::Application* Engine::CreateApplication()
{
    return new Game;
}