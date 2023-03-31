#include <Godot.hpp>
#include <Node.hpp>
#include <Input.hpp>
namespace godot {

class GameManager : public Node {
    GODOT_CLASS(GameManager, Node)

private:
    bool isGamePlaying;
    bool isTimer;
    float timer;
    Input* input;

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