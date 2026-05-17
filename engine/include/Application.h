//
// Created by alex on 5/4/26.
//

#pragma once

#include "Core.h"
#include "include/Layer.h"
#include "include/LayerStack.h"
#include "include/Window.h"
#include <memory>

namespace Engine {

    class ENGINE_API Application
    {
    private:
        static Application* s_Instance;
        LayerStack m_LayerStack;
        std::unique_ptr<Window> m_Window;

    public:
        Application();
        ~Application();

        void Run();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        static Application& Get() { return *s_Instance; }

        Window& GetWindow() { return *m_Window; }
    };

    Application* CreateApplication();
}
