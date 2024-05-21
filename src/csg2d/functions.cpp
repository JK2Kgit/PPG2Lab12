#include "functions.h"
#include "shape.h"
#include "circle.h"
#include "rectangle.h"
#include "complexShape.h"

sf::Vector2f rotate(const sf::Vector2f &v, float angle_rad)
{
	const float cs = std::cos(angle_rad);
	const float sn = std::sin(angle_rad);

	return { v.x*cs - v.y*sn, v.x*sn + v.y*cs };
}

void updateTexture(sf::Texture &t, const CSG2D::Shape &s, const sf::Color &foreground_color, const sf::Color &background_color)
{
	const auto tex_size = t.getSize();
	std::vector<sf::Uint8> tex_data(tex_size.x*tex_size.y*4u, 0u);
	const sf::Vector2f center = sf::Vector2f(tex_size)/2.f - sf::Vector2f(0.5f, 0.5f);
    for(std::size_t py = 0u; py < tex_size.y; ++py)
    {
	    for(std::size_t px = 0u; px < tex_size.x; ++px)
	    {
	        auto pos = sf::Vector2f(px, py) - center;
	        pos.y = -pos.y;
	        
	        const auto color = s.isIn(pos) ? foreground_color : background_color;

	        const std::size_t pi = py*tex_size.x + px;
	        const auto i = pi*4u;
	        tex_data[i] = color.r;
	        tex_data[i + 1u] = color.g;
	        tex_data[i + 2u] = color.b;
	        tex_data[i + 3u] = color.a;
	    }
    }
    t.update(tex_data.data());
}

std::shared_ptr<CSG2D::Shape> createCSG2DScene()
{
    std::cout << "Creating" << std::endl;
    //auto logo_whole_area = std::make_shared<CSG2D::Circle>(420.f, sf::Vector2f(0.f, 0.f));
    auto nothing = std::make_shared<CSG2D::Circle>(0.f, sf::Vector2f(0.f, 0.f));

    auto middle_part = std::make_shared<CSG2D::Rectangle>(720.f, 420.f, sf::Vector2f(0.f, 0.f), 0.f);
    auto top_right_part = std::make_shared<CSG2D::Rectangle>(400.f, 420.f, sf::Vector2f(80.f, 140.f), std::numbers::pi / 3.0);
    auto top_left_part = std::make_shared<CSG2D::Rectangle>(400.f, 420.f, sf::Vector2f(-80.f, 140.f), -std::numbers::pi / 3.0);
    auto top_part = std::make_shared<CSG2D::ComplexShape>(top_right_part, top_left_part, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, 0.f), 0.f);
    auto bottom_part = std::make_shared<CSG2D::ComplexShape>(top_right_part, top_left_part, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, 0.f), -std::numbers::pi);
    auto top_and_bottom = std::make_shared<CSG2D::ComplexShape>(top_part, bottom_part, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, 0.f), -std::numbers::pi);
    auto bg = std::make_shared<CSG2D::ComplexShape>(top_and_bottom, middle_part, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, 0.f), 0.f);

    auto c_outer_radius = std::make_shared<CSG2D::Circle>(270.f, sf::Vector2f(0.f, 0.f));
    auto c_inner_radius = std::make_shared<CSG2D::Circle>(140.f, sf::Vector2f(0.f, 0.f));

    auto o_letter = std::make_shared<CSG2D::ComplexShape>(c_outer_radius, c_inner_radius, CSG2D::OPERATION::DIFFERENCE, sf::Vector2f(0.f, 0.f), 0.f);
    auto c_letter_cut_top = std::make_shared<CSG2D::Rectangle>(400.f, 200.f, sf::Vector2f(0.f, 40.f * sqrtf(3.f)), std::numbers::pi / 6.0);
    auto c_letter_cut_bottom = std::make_shared<CSG2D::Rectangle>(400.f, 200.f, sf::Vector2f(0.f, -40.f * sqrtf(3.f)), -std::numbers::pi / 6.0);
    auto c_letter_cut = std::make_shared<CSG2D::ComplexShape>(c_letter_cut_top, c_letter_cut_bottom, CSG2D::OPERATION::UNION, sf::Vector2f(250.f, 0.f), 0.f);

    auto c_letter = std::make_shared<CSG2D::ComplexShape>(o_letter, c_letter_cut, CSG2D::OPERATION::DIFFERENCE, sf::Vector2f(0.f, 0.f), 0.f);
    auto c_logo = std::make_shared<CSG2D::ComplexShape>(bg, c_letter, CSG2D::OPERATION::DIFFERENCE, sf::Vector2f(0.f, 0.f), 0.f);

    auto plus_horizontal = std::make_shared<CSG2D::Rectangle>(120.f, 40.f, sf::Vector2f(0.f, 0.f), 0.f);
    auto plus_vertical = std::make_shared<CSG2D::Rectangle>(120.f, 40.f, sf::Vector2f(0.f, 0.f), std::numbers::pi/2.f);
    auto plus = std::make_shared<CSG2D::ComplexShape>(plus_vertical, plus_horizontal, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, 0.f), 0.f);

    auto plus_1 = std::make_shared<CSG2D::ComplexShape>(plus, nothing, CSG2D::OPERATION::UNION, sf::Vector2f(140.f, 0.f), 0.f);
    auto plus_2 = std::make_shared<CSG2D::ComplexShape>(plus, nothing, CSG2D::OPERATION::UNION, sf::Vector2f(280.f, 0.f), 0.f);

    auto pluses = std::make_shared<CSG2D::ComplexShape>(plus_1, plus_2, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, 0.f), 0.f);
    auto cpp_logo = std::make_shared<CSG2D::ComplexShape>(c_logo, pluses, CSG2D::OPERATION::DIFFERENCE, sf::Vector2f(0.f, 0.f), 0.f);

    auto letter_j_bottom_outer =  std::make_shared<CSG2D::Circle>(60.f, sf::Vector2f(0.f, 0.f));
    auto letter_j_bottom_inner =  std::make_shared<CSG2D::Circle>(20.f, sf::Vector2f(0.f, 0.f));
    auto letter_j_bottom_circle =  std::make_shared<CSG2D::ComplexShape>(letter_j_bottom_outer, letter_j_bottom_inner, CSG2D::OPERATION::DIFFERENCE, sf::Vector2f(0.f, 0.f), 0.f);
    auto letter_j_bottom_bounding =  std::make_shared<CSG2D::Rectangle>(120.f, 60.f, sf::Vector2f(0.f, -30.f), 0.f);
    auto letter_j_bottom =  std::make_shared<CSG2D::ComplexShape>(letter_j_bottom_circle, letter_j_bottom_bounding, CSG2D::OPERATION::INTERSECTION, sf::Vector2f(0.f, -60.f), 0.f);
    auto letter_j_top = std::make_shared<CSG2D::Rectangle>(120.f, 40.f, sf::Vector2f(0.f, 40.f), 0.f);
    auto letter_j_side = std::make_shared<CSG2D::Rectangle>(40.f, 120.f, sf::Vector2f(40.f, 0.f), 0.f);
    auto letter_j_top_and_side = std::make_shared<CSG2D::ComplexShape>(letter_j_top, letter_j_side, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, 0.f), 0.f);
    auto letter_j= std::make_shared<CSG2D::ComplexShape>(letter_j_top_and_side, letter_j_bottom, CSG2D::OPERATION::UNION, sf::Vector2f(-80.f, 20.f), 0.f);

    auto letter_i_top = std::make_shared<CSG2D::Rectangle>(120.f, 40.f, sf::Vector2f(0.f, 60.f), 0.f);
    auto letter_i_bottom = std::make_shared<CSG2D::ComplexShape>(letter_i_top, nothing, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, 0.f), std::numbers::pi);
    auto letter_i_bottom_top = std::make_shared<CSG2D::ComplexShape>(letter_i_top, letter_i_bottom, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, 0.f), 0.f);
    auto letter_j_center = std::make_shared<CSG2D::Rectangle>(40.f, 120.f, sf::Vector2f(0.f, 0.f), 0.f);
    auto letter_i = std::make_shared<CSG2D::ComplexShape>(letter_i_bottom_top, letter_j_center, CSG2D::OPERATION::UNION, sf::Vector2f(80.f, 0.f), 0.f);

    auto signature = std::make_shared<CSG2D::ComplexShape>(letter_i, letter_j, CSG2D::OPERATION::UNION, sf::Vector2f(350.f, -400.f), 0.f);

    auto shp = std::make_shared<CSG2D::ComplexShape>(signature, cpp_logo, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, 0.f), 0.f);
    return shp;
}
