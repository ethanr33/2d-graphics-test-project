
#include "doctest.h"
#include "rasterizer/Rasterizer.h"

TEST_CASE("Rasterize line") {

    Rasterizer r;
    FrameBuffer f(10, 10);

    std::vector<Command> commands;

    const uint32_t black = 0;

    SUBCASE("Horizontal line") {
        Primitive p(PRIMITIVE_TYPE::LINE, Vertex(0, 0), Vertex(5, 0));
        p.color = Color(255, 0, 0);

        const Color red = p.color;

        commands.push_back(AddPrimitiveCommand(p));

        r.make_fragments(commands);
        r.render_fragments(f);

        std::vector<Color> expected(100);
        expected.at(0) = red;
        expected.at(1) = red;
        expected.at(2) = red;
        expected.at(3) = red;
        expected.at(4) = red;
        expected.at(5) = red;

        for (int i = 0; i < 100; i++) {
            INFO("Check failed at ", i, " Expected: ", expected.at(i).to_hex(), " Found: ", f.get_frame_buffer().at(i).to_hex());
            CHECK(f.get_frame_buffer().at(i) == expected.at(i));
        }
    }

}