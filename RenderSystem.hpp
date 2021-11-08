#pragma once

extern "C"{
    #include "raylib.h"
}

#include <string>
#include <memory>
#include <entt/entt.hpp>

struct PositionComponent;
struct CameraComponent;
struct RenderComponent
{
    Model model;
    float size;
};
class RenderSystem
{
    private:
        Camera camera;
    public:
        RenderSystem();
        ~RenderSystem();
        
        void AddRenderComponent(entt::entity& ent, entt::registry& reg, const std::string& modelRoute, float modelSize);
        
        void Update(const entt::registry& registry);
        void UpdatePlayerPosition(entt::entity& player, entt::entity& radio, entt::registry& reg);
};