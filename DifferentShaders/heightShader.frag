#version 460 core

in float Height;
in vec2 TextureCoords;

in float u;
in float v;

uniform sampler2D grass_texture;
uniform sampler2D rock_texture;
uniform sampler2D sand_texture;

out vec4 FragColor;

void main()
{
    float h = 1-(Height)/35;

    float min_rock_slope = 0.5f;
    float max_grass_slope = 0.8f;
    float min_rockgrass_height = 0.4f;
    float max_sand_height = 0.5;

    float rock_grass_weight = h;

    float sand_rockgrass_weight = rock_grass_weight;

    rock_grass_weight = max(min_rock_slope,rock_grass_weight);
    rock_grass_weight = min(max_grass_slope,rock_grass_weight);
    rock_grass_weight -= min_rock_slope;
    rock_grass_weight /= max_grass_slope - min_rock_slope;


    sand_rockgrass_weight = max(min_rockgrass_height,sand_rockgrass_weight);
    sand_rockgrass_weight = min(max_sand_height,sand_rockgrass_weight);
    sand_rockgrass_weight -= min_rockgrass_height;
    sand_rockgrass_weight /= max_sand_height - min_rockgrass_height;


    vec4 temp =  mix(texture(grass_texture,TextureCoords*2000),texture(rock_texture,TextureCoords*2000),rock_grass_weight);

    temp =  mix(texture(sand_texture,TextureCoords*2000),temp,sand_rockgrass_weight*0.8);

    FragColor = mix(vec4(0,0.3f,0.5f,1.0),temp,sand_rockgrass_weight);
}