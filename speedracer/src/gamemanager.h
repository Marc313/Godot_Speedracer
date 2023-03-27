#include <Godot.hpp>
#include <Node.hpp>

namespace godot {

class GameManager : public Node {
    GODOT_CLASS(GameManager, Node)

private:
    bool isTimer;
    float timer;

public:
    static void _register_methods();

    GameManager();
    ~GameManager();

    void _init();
    void _ready();
    void _process(float delta);
    void _on_player_death();

    float time_to_restart;
};
}