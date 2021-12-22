#include "Map.h"

Map::Map(const float tile_size, const float v) : m_tileSize(tile_size),
                                                 m_platform_vel(v),
                                                 m_right_border(false),
                                                 m_platform_count(0),
                                                 m_score(0),
                                                 m_game_time(0) {
    if (tile_size <= 0)
        throw (std::invalid_argument("Failed const TILE_SIZE"));

    if (v <= 0)
        throw (std::invalid_argument("Failed const PLATFORM_VEL"));

    if (!m_texture.loadFromFile("../Files/texture.png")) {
        std::cout << "Failed to load texture.png file\n";
    }
    if (!m_font.loadFromFile("../Files/game_score.ttf")) {
        std::cerr << "Failed to load font from file '../Files/game_score.ttf'\n";
    }
}

Map::~Map() {
    m_vertices.clear();
    m_platform_vel_arr.clear();
    m_borders.clear();
    m_platform_idx.clear();
    m_coins_idx.clear();
}

void Map::setScore(const int score) {
    m_best_score = score;
}

void Map::setGameTime(const float time) {
    m_best_game_time = time;
}

void Map::readMap(const size_t num_of_level) {
    readLevelFile("../Files/Level_" + std::to_string(num_of_level) + ".txt");
}

void Map::readLevelFile(const std::string &fn) {
    std::string line;
    std::ifstream myfile(fn);
    if (!myfile.is_open()) {
        std::cout << "Failed to open level file \'" << fn << '\'' << std::endl;
        return;
    }

    size_t j = 0;
    size_t k = 0;

    while (!myfile.eof()) {
        getline(myfile, line);

        size_t num_tiles_x = line.size();
        k = std::max(k, num_tiles_x);

        for (size_t i = 0; i < num_tiles_x; ++i)
            if (line[i] != ' ')
                readTile(j, i, line[i]);

        ++j;
    }
    m_map_size.x = k;
    m_map_size.y = j;
}

void Map::readTile(int i, int j, char ch) {
    switch (ch) {

        case '*': {
            addTile(i, j, 0);
            break;
        }

        case '-': {
            addPlatform(i, j);
            break;
        }

        case 'o': {
            addCoin(i, j);
            break;
        }

        case '!': {
            sf::Vector2f finish_pos(j * m_tileSize, i * m_tileSize);
            m_finish_pos = finish_pos;
            break;
        }

        case 'h': {
            sf::Vector2f hero_pos(j * m_tileSize, i * m_tileSize);
            m_hero_pos = hero_pos;
            break;
        }

        default:
            break;
    }
}

void Map::addTile(int i, int j, int texture_num) {
    sf::Vector2f pos0(j * m_tileSize, i * m_tileSize);
    sf::Vector2f pos1((j + 1) * m_tileSize, i * m_tileSize);
    sf::Vector2f pos2((j + 1) * m_tileSize, (i + 1) * m_tileSize);
    sf::Vector2f pos3(j * m_tileSize, (i + 1) * m_tileSize);

    sf::Vertex vert0(pos0);
    sf::Vertex vert1(pos1);
    sf::Vertex vert2(pos2);
    sf::Vertex vert3(pos3);

    vert0.texCoords = sf::Vector2f(texture_num * m_texture.getSize().y, 0);
    vert1.texCoords = sf::Vector2f(m_texture.getSize().y + texture_num * m_texture.getSize().y, 0);
    vert2.texCoords = sf::Vector2f(m_texture.getSize().y + texture_num * m_texture.getSize().y, m_texture.getSize().y);
    vert3.texCoords = sf::Vector2f(texture_num * m_texture.getSize().y, m_texture.getSize().y);

    m_vertices.push_back(vert0);
    m_vertices.push_back(vert1);
    m_vertices.push_back(vert2);
    m_vertices.push_back(vert3);

    ++m_platform_count;
}

void Map::addPlatform(int i, int j) {
    if (!m_right_border) {
        addTile(i, j, 1);
        m_platform_idx.push_back(m_platform_count - 1);
        m_right_border = true;
    } else {
        auto platform_borders = std::make_pair(m_vertices[(m_platform_count - 1) * 4].position.x,
                                               (float) (j + 1) * m_tileSize);
        m_borders.push_back(platform_borders);
        m_platform_vel_arr.push_back(m_platform_vel);
        m_right_border = false;
    }
}

void Map::addCoin(int i, int j) {

    addTile(i, j, 2);
    m_coins_idx[m_platform_count - 1] = true;

}

void Map::update(sf::Time dt) {
    size_t j = 0;

    for (auto it: m_platform_idx) {

        if (m_vertices[it * 4].position.x <= m_borders[j].first) {
            m_platform_vel_arr[j] = m_platform_vel;
        }

        if (m_vertices[it * 4 + 2].position.x >= m_borders[j].second) {
            m_platform_vel_arr[j] = -1 * m_platform_vel;
        }

        sf::Vector2f del(m_platform_vel_arr[j] * dt.asSeconds(), 0);

        m_vertices[it * 4].position += del;
        m_vertices[it * 4 + 1].position += del;
        m_vertices[it * 4 + 2].position += del;
        m_vertices[it * 4 + 3].position += del;

        ++j;
    }

    m_game_time += dt.asSeconds();
}

sf::Vector2i Map::getSize() {
    return m_map_size;
}

std::vector<sf::Vertex> &Map::getVertexArray() {
    return m_vertices;
}

bool Map::isCoin(int coin_idx) {
    if (m_coins_idx.find(coin_idx) != m_coins_idx.end())
        return true;
    return false;
}

bool Map::isCoinReach(int coin_idx) {
    if ((m_coins_idx.find(coin_idx) != m_coins_idx.end()) && m_coins_idx.at(coin_idx))
        return true;
    return false;
}

void Map::coinDel(int coin_idx) {

    ++m_score;
    m_coins_idx[coin_idx] = false;

    m_vertices[coin_idx * 4].texCoords = sf::Vector2f(3 * m_texture.getSize().y, 0);
    m_vertices[coin_idx * 4 + 1].texCoords = sf::Vector2f(m_texture.getSize().y + 3 * m_texture.getSize().y, 0);
    m_vertices[coin_idx * 4 + 2].texCoords = sf::Vector2f(m_texture.getSize().y + 3 * m_texture.getSize().y,
                                                          m_texture.getSize().y);
    m_vertices[coin_idx * 4 + 3].texCoords = sf::Vector2f(3 * m_texture.getSize().y, m_texture.getSize().y);
}

bool Map::isPlatformMoving(int platform_idx) {

    return (std::count(m_platform_idx.begin(),
                       m_platform_idx.end(),
                       platform_idx) != 0);
}

float Map::getPlatformVel(int platform_idx) {

    auto it = find(m_platform_idx.begin(),
                   m_platform_idx.end(),
                   platform_idx);

    if (it != m_platform_idx.end()) {
        int i = it - m_platform_idx.begin();
        return m_platform_vel_arr[i];
    } else {
        return -1;
    }
}

sf::Vector2f Map::getHeroPosition() {
    return m_hero_pos;
}

sf::Vector2f Map::getFinishPosition() {
    return m_finish_pos;
}

int Map::getScore() const {
    return m_score;
}

float Map::getGameTime() const {
    return m_game_time;
}


void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_vertices.data(), m_vertices.size(), sf::Quads, states);

    std::string score;

    if (m_best_score == 0)
        score = "Score: " + std::to_string(m_score) + " / " + std::to_string(m_coins_idx.size());
    else
        score = "Score: " + std::to_string(m_score) + " / " + std::to_string(m_coins_idx.size()) +
                " (Best: " + std::to_string(m_best_score) + ")";

    sf::Text text_score(score, m_font);
    text_score.setStyle(sf::Text::Bold);
    text_score.setFillColor(sf::Color::Yellow);
    text_score.setPosition((target.getView().getCenter().x + target.getSize().x / 2 - m_tileSize * 8),
                           (target.getView().getCenter().y - target.getSize().y / 2 + m_tileSize));
    target.draw(text_score);

    std::string time;

    if (m_best_game_time == 0)
        time = "Time: " + (std::to_string(m_game_time)) + "\n";
    else
        time = "Time: " + (std::to_string(m_game_time)) + "\n" +
               "(Best: " + std::to_string(m_best_game_time) + ")";

    sf::Text text_time(time, m_font);
    text_time.setStyle(sf::Text::Bold);
    text_time.setFillColor(sf::Color::Yellow);
    text_time.setPosition((target.getView().getCenter().x + target.getSize().x / 2 - m_tileSize * 8),
                          (target.getView().getCenter().y - target.getSize().y / 2 + 2 * m_tileSize));
    target.draw(text_time);

}
