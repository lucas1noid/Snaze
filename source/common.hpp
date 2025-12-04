#pragma once

namespace sg {
   
    struct Position{
        int r, c;
    };

    //movimentos possiveis da cobrinha para todas as classes
    enum Direction{ 
    NONE, 
    UP, 
    DOWN, 
    LEFT, 
    RIGHT 
};
}
