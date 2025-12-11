#pragma once
#ifndef INPUT_READER_HPP
#define INPUT_READER_HPP

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

namespace sg
{
    class KeyboardController {
    public:
        KeyboardController() {
            // Salva as configurações originais do terminal
            tcgetattr(STDIN_FILENO, &original_terminal);
            
            // Configura o novo modo
            termios raw = original_terminal;
            raw.c_lflag &= ~(ICANON | ECHO); // Desliga buffer de linha e echo na tela
            raw.c_cc[VMIN] = 0;  // Não espera nenhum caractere mínimo para retornar
            raw.c_cc[VTIME] = 0; // Não espera tempo
            
            // Aplica
            tcsetattr(STDIN_FILENO, TCSANOW, &raw);

            // Configura leitura não-bloqueante (fcntl)
            int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
            fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
        }

        ~KeyboardController() {
            // Restaura o terminal ao normal quando o jogo fecha
            // Isso é CRUCIAL, senão o terminal do usuário fica "quebrado" ao sair
            tcsetattr(STDIN_FILENO, TCSANOW, &original_terminal);
        }

        // Retorna o char pressionado ou 0 se nada foi pressionado
        char readKey() {
            char c = 0;
            if (read(STDIN_FILENO, &c, 1) > 0) {
                return c;
            }
            return 0; 
        }

    private:
        termios original_terminal;
    };
}

#endif