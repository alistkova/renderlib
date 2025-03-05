#include "core/ViewImpl.h"

#include <SDL2/SDL.h>
#include <SDL_video.h>

#include <memory>
#include <utility>

#include "graphics/vulkan/vk_engine.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_vulkan.h"

#include <stdint.h>

namespace {
constexpr auto kWindowFlags =
        static_cast<uint32_t>(SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
}

ViewImpl::ViewImpl(IModel::Ptr model) : _model(std::move(model)) {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("engine", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, 1700, 900, kWindowFlags);
    _model->registerWindow(window);
}

void ViewImpl::run() const {
    // imgui new frame
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    if (ImGui::Begin("background")) {
        VulkanEngine& engine = VulkanEngine::Get();
        ImGui::SliderFloat("Render Scale", &engine.renderScale, 0.3f, 1.f);
        // other code
    }
    ImGui::End();

    // make imgui calculate internal draw structures
    ImGui::Render();
}

void ViewImpl::process_event(const SDL_Event& e) {
    ImGui_ImplSDL2_ProcessEvent(&e);
}

ViewImpl::~ViewImpl() {
    SDL_DestroyWindow(window);
}
