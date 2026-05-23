//
// Created by alex on 5/4/26.
//

#pragma once

#include "include/Core.h"
#include "SDL3/SDL.h"
#include <functional>

namespace Engine {

    struct WindowProperties
    {
        const char* title;
        uint32_t width, height;
    };

    class ENGINE_API Window
    {
        using EventCallbackFn = std::function<void(SDL_Event&)>;

    private:
        EventCallbackFn m_EventCallback;
        SDL_Window* m_Window = nullptr;
        SDL_GLContext m_GLContext = nullptr;
        float m_MainScale;
        bool m_Running = true;
        WindowProperties m_Properties;
        uint64_t m_PerformanceCounterStart;
        uint64_t m_PerformanceCounterEnd;
        double m_MaxFPS = 144;

    public:
        Window(const WindowProperties& properties);
        virtual ~Window();

        void Create();
        void PollEvents();
        void SwapBuffers();
        void SetMaxFPS(const double& fps);
        void SetVSyncEnabled(const bool& enabled);
        void PerformanceCounterStart();
        void PerformanceCounterEnd();

        void SetEventCallback(const EventCallbackFn& callback)
        {
            m_EventCallback = callback;
        }

        inline bool IsRunning()
        {
            return m_Running;
        }

        inline const uint32_t& GetWidth() const
        {
            return m_Properties.width;
        }

        inline const uint32_t& GetHeight() const
        {
            return m_Properties.height;
        }

        inline SDL_Window* GetWindow()
        {
            return m_Window;
        }

        inline SDL_GLContext GetGLContext()
        {
            return m_GLContext;
        }

        inline void SetIsRunning(const bool& running)
        {
            m_Running = running;
        }
    };
}