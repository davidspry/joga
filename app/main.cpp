#include <joga/joga.hpp>

#include <juce_gui_basics/juce_gui_basics.h>

#include <print>

int main(int argc, const char** argv)
{
    using namespace joga;
    using namespace juce;
    Component c1, c2, c3;

    HStack
    {
        VStack
        {
            Node{c1}.withFlexGrow(1),
            Node{c2}.withFlexGrow(1),
            Node{c3}.withFlexGrow(1)
        }
            .withRowGap(10)
            .withFlexGrow(1),
    }
        .withPadding(10)
        .withWidth(100)
        .withHeight(100)
        .layout();

    std::println("C1: {}", c1.getBounds().toString().toStdString());
    std::println("C2: {}", c2.getBounds().toString().toStdString());
    std::println("C3: {}", c3.getBounds().toString().toStdString());
}
