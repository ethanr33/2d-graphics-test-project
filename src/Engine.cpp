
#include <fstream>

#include "Engine.h"

void Engine::tick() {
    this->renderer.display();
}

void Engine::draw(const Primitive& p) {
    renderer.add_primitive(p);
}

void Engine::translate_viewport(double dx, double dy) {
    renderer.translate_absolute(dx, dy);
}

bool Engine::is_active() {

    if (this->performance_recording_enabled) {
        this->perf_stats.num_frames++;
    }

    return this->app_window.dispatch() != -1;
}

void Engine::add_event_handler(EVENT_TYPE type, std::function<void(MouseState)> handler) {
    this->app_window.get_mouse_pressed_handler()->connect(handler);
}

Engine::~Engine() {
    if (this->performance_recording_enabled) {
        auto end_time = std::chrono::high_resolution_clock::now();
        perf_stats.elapsed_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - this->init_time).count();

        std::ofstream out_file(this->performance_file_data_path + this->performance_file_data_name);

        double average_fps = 1000 * (double) perf_stats.num_frames / perf_stats.elapsed_time_ms;

        out_file << "Frame count: " + std::to_string(perf_stats.num_frames) << std::endl;
        out_file << "Time elapsed (ms): " + std::to_string(perf_stats.elapsed_time_ms) << std::endl;
        out_file << "Average FPS: " + std::to_string(average_fps) << std::endl;

        out_file.close();
    }
}