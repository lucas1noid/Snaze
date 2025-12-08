#pragma once
#include <cstdint>

namespace sg {
    class SnazeSimulation {
    private:
      enum game_state_e : std::uint8_t {
        WELCOME = 0, //! Boas vindas
        STARTING,    //! Tela inicial do jogo
        PLAYING,     //! Jogando (player ou IA)
        VICTORY,     //! Vitória
        GAMEOVER,     //! Derrota
        ENDING,      //! Finaliza o jogo
      };
    public:
     static bool is_over();
     static void process_events();
     static void update();
     static void render();
};
}
