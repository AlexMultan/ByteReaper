//
// Created by alex on 5/4/26.
//

#pragma once

#include <string>
#include "include/Core.h"
#include "SDL3/SDL_events.h"

namespace Engine {
    class ENGINE_API Layer
    {
    protected:
        std::string m_DebugName;

    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach(){};
        virtual void OnDetach(){};
        virtual void OnUpdate(){};
        virtual void OnRender(){};
        virtual void OnEvent(SDL_Event &event){};

        inline const std::string& GetLayerName() const
        {
            return m_DebugName;
        }
    };

}
