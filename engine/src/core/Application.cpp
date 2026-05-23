//
// Created by alex on 5/4/26.
//

#include "include/Application.h"

Engine::Application* Engine::Application::s_Instance = nullptr;

Engine::Application::Application()
{
    s_Instance = this;
    m_Window = std::make_unique<Window>(WindowProperties("ByteReaper", 1600, 900));
    m_Window->Create();
    m_Window->SetEventCallback([this](SDL_Event& event)
        {
            for (Layer* layer : m_LayerStack)
            {
                layer->OnEvent(event);
            }
        });
}

Engine::Application::~Application()
{

}

void Engine::Application::PushLayer(Layer* layer)
{
    m_LayerStack.PushLayer(layer);
}

void Engine::Application::PushOverlay(Layer* layer)
{
    m_LayerStack.PushOverlay(layer);
}

void Engine::Application::Run()
{
    for (Layer* layer : m_LayerStack)
    {
        layer->OnAttach();
    }

    while (m_Window->IsRunning())
    {
        m_Window->PerformanceCounterStart();
        m_Window->PollEvents();

        for (Layer* layer : m_LayerStack)
        {
            layer->OnUpdate();
        }

        for (Layer* layer : m_LayerStack)
        {
            layer->OnRender();
        }

        m_Window->SwapBuffers();
        m_Window->PerformanceCounterEnd();
    }
    for (Layer* layer : m_LayerStack)
    {
        layer->OnDetach();
    }
}