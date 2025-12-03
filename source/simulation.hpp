#pragma once
namespace sg {

    class SnazeSimulation {
    private:
    
    public:
        static bool is_over();
        static void process_events();
        static void update();
        static void render();
};
}