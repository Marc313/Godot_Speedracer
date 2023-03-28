#include <Godot.hpp>
#include <Node.hpp>
#include <ParallaxBackground.hpp>

namespace godot {

class Autoscroll : public ParallaxBackground {
    GODOT_CLASS(Autoscroll, Node)

private:
    float scrollSpeed;

public:
    static void _register_methods();

    Autoscroll();
    ~Autoscroll();

    void _init();
    void _process(float delta);
};}