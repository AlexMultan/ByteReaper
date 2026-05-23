//
// Created by alex on 5/9/26.
//

#include "include/Window.h"
#include "include/Log.h"

Engine::Window::Window(const WindowProperties& props) : m_Window(nullptr), m_Properties(props)
{

}

Engine::Window::~Window()
{
    SDL_GL_DestroyContext(m_GLContext);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Engine::Window::Create()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_MainScale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

    SDL_WindowFlags windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY;

    m_Window = SDL_CreateWindow(
        m_Properties.title, (int)(m_Properties.width * m_MainScale), (int)(m_Properties.height * m_MainScale), windowFlags
        );

    if (!m_Window)
    {

    }

    m_GLContext = SDL_GL_CreateContext(m_Window);
    if (!m_GLContext)
    {
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }

    SDL_GL_MakeCurrent(m_Window, m_GLContext);
}

void Engine::Window::PollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            m_Running = false;
        }

        if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(m_Window))
        {
            m_Running = false;
        }

        if (m_EventCallback)
        {
            m_EventCallback(event);
        }
    }
}

void Engine::Window::SwapBuffers()
{
    SDL_GL_SwapWindow(m_Window);
}

void Engine::Window::SetMaxFPS(const double &fps)
{
    m_MaxFPS = fps;
}

void Engine::Window::SetVSyncEnabled(const bool &enabled)
{
    if (enabled)
    {
        SDL_GL_SetSwapInterval(1);
    }
}

void Engine::Window::PerformanceCounterStart()
{
    m_PerformanceCounterStart = SDL_GetPerformanceCounter();
}

void Engine::Window::PerformanceCounterEnd()
{
    m_PerformanceCounterEnd = SDL_GetPerformanceCounter();
    double elapsedTime = static_cast<double>(m_PerformanceCounterEnd - m_PerformanceCounterStart) / SDL_GetPerformanceFrequency() * 1000.0;
    if (elapsedTime < (1000 / m_MaxFPS))
    {
        SDL_Delay(static_cast<uint32_t>((1000 / m_MaxFPS) - elapsedTime));
    }
}
