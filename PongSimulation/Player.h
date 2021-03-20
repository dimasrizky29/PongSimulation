class Player
{
public:
    enum Players {
        PlayerX, PlayerY
    };
    const char* setPlayerName(Players player) {
        switch (player) {
        case PlayerX:
            return "Player X ";
            break;
        case PlayerY:
            return "Player Y ";
            break;
        };
    }
    float hit;
};

