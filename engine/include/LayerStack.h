//
// Created by alex on 5/4/26.
//

#pragma once

#include "include/Core.h"
#include "include/Layer.h"
#include <vector>

namespace Engine {

    class ENGINE_API LayerStack
    {
    private:
        std::vector<Layer*> m_Layers;
        std::vector<Layer*>::iterator m_Iterator;

    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }

        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
    };
}