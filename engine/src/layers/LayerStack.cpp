//
// Created by alex on 5/4/26.
//

#include "include/LayerStack.h"
#include <algorithm>

Engine::LayerStack::LayerStack()
{
    m_Iterator = m_Layers.begin();
}

Engine::LayerStack::~LayerStack()
{
    for (Layer* layer : m_Layers)
    {
        delete layer;
    }
}

void Engine::LayerStack::PushLayer(Layer* layer)
{
    m_Iterator = m_Layers.emplace(m_Iterator, layer);
}

void Engine::LayerStack::PushOverlay(Layer* overlay)
{

}

void Engine::LayerStack::PopLayer(Layer* layer)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end())
    {
        m_Layers.erase(it);
        m_Iterator--;
    }
}

void Engine::LayerStack::PopOverlay(Layer* overlay)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
    if (it != m_Layers.end())
    {
        m_Layers.erase(it);
    }
}