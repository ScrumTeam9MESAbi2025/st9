﻿// ReSharper disable CppTooWideScopeInitStatement
#include "BuildSystem.h"
#include "Game.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Tower.h"
#include "entities/EnemyManager.h"

#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_vec4.hpp>

#include "Wall.h"

constexpr float CellSize = 135.0f;


BuildSystem::BuildSystem() : m_selected(Utils::Cell::NOTHING)
{
	m_costs.insert({0,100});
	m_costs.insert({1,200});
	m_costs.insert({2,300});
	m_costs.insert({3,2500});
	m_costs.insert({4,6000});
	m_costs.insert({5,600});


	m_texture_textures.resize(6);
	m_texture_sprites.resize(6);

	m_texture_textures[0].loadFromFile("Resources/Images/top.png");
	m_texture_textures[1].loadFromFile("Resources/Images/tower_base.png");
	m_texture_sprites[0].setTexture(m_texture_textures[0]);
	m_texture_sprites[1].setTexture(m_texture_textures[1]);
	m_texture[0].create(135, 135);
	m_texture[0].clear(sf::Color::Transparent);
	m_texture[0].draw(m_texture_sprites[1]);
	m_texture[0].draw(m_texture_sprites[0]);
	m_texture[0].display();

	m_texture_textures[2].loadFromFile("Resources/Images/mg.png");
	m_texture_sprites[2].setTexture(m_texture_textures[2]);
	m_texture[1].create(135, 135);
	m_texture[1].clear(sf::Color::Transparent);
	m_texture[1].draw(m_texture_sprites[1]);
	m_texture[1].draw(m_texture_sprites[2]);
	m_texture[1].display();

	m_texture_textures[3].loadFromFile("Resources/Images/gold_mg.png");
	m_texture_sprites[3].setTexture(m_texture_textures[3]);
	m_texture[2].create(135, 135);
	m_texture[2].clear(sf::Color::Transparent);
	m_texture[2].draw(m_texture_sprites[1]);
	m_texture[2].draw(m_texture_sprites[3]);
	m_texture[2].display();

	m_texture_textures[4].loadFromFile("Resources/Images/Gold-Kanone.png");
	m_texture_sprites[4].setTexture(m_texture_textures[4]);
	m_texture[3].create(135, 135);
	m_texture[3].clear(sf::Color::Transparent);
	m_texture[3].draw(m_texture_sprites[1]);
	m_texture[3].draw(m_texture_sprites[4]);
	m_texture[3].display();


	m_texture_textures[5].loadFromFile("Resources/Images/Basic_Waffe.png");
	m_texture_sprites[5].setTexture(m_texture_textures[5]);
	m_texture[4].create(135, 135);
	m_texture[4].clear(sf::Color::Transparent);
	m_texture[4].draw(m_texture_sprites[1]);
	m_texture[4].draw(m_texture_sprites[5]);
	m_texture[4].display();
	m_textures.resize(8);

	m_textures[0].loadFromFile("Resources/Images/none.png");
	m_textures[1] = m_texture[0].getTexture();
	m_textures[2] = m_texture[1].getTexture();
	m_textures[3].loadFromFile("Resources/Images/geld_raffinerie.png");
	m_textures[4].loadFromFile("Resources/Images/wall.png");
	m_textures[5] = m_texture[2].getTexture();
	m_textures[6] = m_texture[3].getTexture();
	m_textures[7] = m_texture[4].getTexture();
	m_sprites.resize(8);

	m_sprites[0].setTexture(m_textures[0]);
	m_sprites[0].setColor(sf::Color::Transparent);
	
	m_sprites[1].setTexture(m_textures[7]);//turm 1, brauch eine neue textur
	m_sprites[2].setTexture(m_textures[2]);//turm 2
	m_sprites[3].setTexture(m_textures[3]);//turm 3
	m_sprites[4].setTexture(m_textures[5]);//turm 4
	m_sprites[5].setTexture(m_textures[6]);//turm 5
	m_sprites[6].setTexture(m_textures[1]);//turm 6

	m_sprites[1].setColor(sf::Color::Magenta);
	m_sprites[2].setColor(sf::Color::Yellow);
	m_sprites[3].setColor(sf::Color::White);
	m_sprites[4].setColor(sf::Color::Red);
	m_sprites[5].setColor(sf::Color::Blue);
	m_sprites[6].setColor(sf::Color::Black);

	m_sprites[7].setTexture(m_textures[4]);
}

BuildSystem* BuildSystem::get_instance()
{
	if (!s_instance)
		s_instance = new BuildSystem;
	return s_instance;
}

void BuildSystem::delete_instance()
{
	delete s_instance;
	s_instance = nullptr;
}

Utils::Cell BuildSystem::display()
{
	//texture.clear(sf::Color::Transparent);
	//texture.draw(m_texture_sprites[1]);
	//texture.draw(m_texture_sprites[0]);
	//texture.display();
	//m_textures[1] = texture.getTexture();
	//m_sprites[1].setTexture(m_textures[1]);
	//m_sprites[2].setTexture(m_textures[1]);
	ImGui::Begin("Build System");
	const float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
	const ImGuiStyle& style = ImGui::GetStyle();
	if(m_selected != Utils::Cell::TURRET)
		m_id = -1;
	for (uint32_t current_button_id = 0; current_button_id < m_sprites.size(); current_button_id++)
	{
		std::string button_id = "test" + std::to_string(current_button_id);
		ImGui::PushID((signed)current_button_id);
		if (ImGui::ImageButton(button_id.c_str(), m_sprites[current_button_id], { 135.0f,135.0f },m_sprites[current_button_id].getColor()))
		{

			//LOG_INFO("it works ig");
			int temp;
			if (current_button_id == 0)
			{
				temp = 0;
			}
			else if (current_button_id > 0 && current_button_id < 7)
			{
				m_id = (signed)current_button_id - 1;
				temp = 1;
			}
			else
			{
				temp = (signed)current_button_id - 5;
			}
			m_selected = static_cast<Utils::Cell>(temp);
		}
		if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
		{

			sf::Sprite temp;
			temp.setTexture(Game::get_game()->m_ui_textures[0]);
			temp.scale(0.1f, 0.1f);
			switch (current_button_id)
			{
			case 0:
				ImGui::BeginTooltip();
				ImGui::Text("Nichts");
				ImGui::EndTooltip();
				break;
			case 1:
				ImGui::BeginTooltip();
				ImGui::Text("Basic:"); // Brauch noch einen besseren sprite
				ImGui::Text("150 leben");
				ImGui::Text("%.0f V-Bucks",m_costs[0]);
				ImGui::SameLine();
				ImGui::Image(temp);
				ImGui::Text("0.15 Schaden");
				ImGui::Text("0.8 s Cooldown");
				ImGui::Text("6 radius");
				ImGui::Text("5 penetration");
				ImGui::Text("6 geschwindigkeit");
				ImGui::EndTooltip();
				break;
			case 2:
				ImGui::BeginTooltip();
				ImGui::Text("Maschienen Gewaehr:");
				ImGui::Text("300 leben");
				ImGui::Text("%.0f V-Bucks", m_costs[1]);
				ImGui::SameLine();
				ImGui::Image(temp);
				ImGui::Text("0.2 Schaden");
				ImGui::Text("0.15 s Cooldown");
				ImGui::Text("6 radius");
				ImGui::Text("1 penetration");
				ImGui::Text("8 geschwindigkeit");
				ImGui::EndTooltip();
				break;
			case 3:
				ImGui::BeginTooltip();
				ImGui::Text("Geld Raffinerie:");
				ImGui::Text("400 leben");
				ImGui::Text("%.0f V-Bucks", m_costs[2]);
				ImGui::SameLine();
				ImGui::Image(temp);
				ImGui::Text("Erzeugt alle 2 Sekunden 25 V-Bucks");
				ImGui::SameLine();
				ImGui::Image(temp);
				ImGui::EndTooltip();
				break;
			case 4:
				ImGui::BeginTooltip();
				ImGui::Text("Goldenes Maschienen Gewaehr:");
				ImGui::Text("1000 leben");
				ImGui::Text("%.0f V-Bucks", m_costs[3]);
				ImGui::SameLine();
				ImGui::Image(temp);
				ImGui::Text("1 Schaden");
				ImGui::Text("0.15 s Cooldown");
				ImGui::Text("6 radius");
				ImGui::Text("2 penetration");
				ImGui::Text("8 geschwindigkeit");
				ImGui::EndTooltip();
				break;
			case 5:
				ImGui::BeginTooltip();
				ImGui::Text("Schwere Gold Kanone:");
				ImGui::Text("3000 leben");
				ImGui::Text("%.0f V-Bucks", m_costs[4]);
				ImGui::SameLine();
				ImGui::Image(temp);
				ImGui::Text("2 Schaden");
				ImGui::Text("1.3 s Cooldown");
				ImGui::Text("20 radius");
				ImGui::Text("30 penetration");
				ImGui::Text("4 geschwindigkeit");
				ImGui::EndTooltip();
				break;

			case 6:
				ImGui::BeginTooltip();
				ImGui::Text("Schwere Kanone");
				ImGui::Text("700 leben");
				ImGui::Text("%.0f V-Bucks", m_costs[5]);
				ImGui::SameLine();
				ImGui::Image(temp);
				ImGui::Text("1.0 Schaden");
				ImGui::Text("1.0 s Cooldown");
				ImGui::Text("10 radius");
				ImGui::Text("5 penetration");
				ImGui::Text("5 geschwindigkeit");
				ImGui::EndTooltip();
				break;
			case 7:
				ImGui::BeginTooltip();
				ImGui::Text("Eine Wand mit:");
				ImGui::Text("2000 leben");
				ImGui::Text("25.0  V-Bucks");
				ImGui::SameLine();
				ImGui::Image(temp);
				ImGui::EndTooltip();
				break;
			default:
				ImGui::SetTooltip("I am a tooltip with a delay.");
				break;
			}
		}
		const float last_button_x2 = ImGui::GetItemRectMax().x;
		const float next_button_x2 = last_button_x2 + style.ItemSpacing.x + 135.0f; // Expected position if next button was on same line
		if (current_button_id + 1 < m_sprites.size() && next_button_x2 < window_visible_x2)
			ImGui::SameLine();
		ImGui::PopID();
	}
	ImGui::End();
	return m_selected;
}

void BuildSystem::operator()(const bool left_click, const bool right_click, const bool should_do_docking,
                             std::vector<std::vector<std::vector<Utils::Cell>>>& map,
                             std::vector<std::shared_ptr<Entity>>& entities,
                             std::vector<std::shared_ptr<Tower>>& towers,
                             const glm::vec3 mouse_pos,
                             const glm::vec3 mainbuilding_pos
) const
{
	if (left_click && right_click)
		return;

	Utils::Pathfinding* pa = Utils::Pathfinding::get_instance();
	// Überprüfen, ob die Mausposition eine gültige Zelle ist
	if (!pa->is_valid(mouse_pos / CellSize))
		return;

	const bool is_windows_focused =
		( //wenn das haupt fenster kein dockspace ist wird geguckt ob irgendeins der ImGui Fenster gefocused ist oder ob eins gehovered ist
			!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow) &&
			!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)
			)
		||
		( //wenn das Haupt Fenster ein Dockspace ist, sind wir gerade in dem ImGui Fenster deshalb gucken wir ob das momentane Gefocused ist und gehovered
			should_do_docking &&
			ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow) &&
			ImGui::IsWindowHovered(ImGuiHoveredFlags_RootWindow)
			);


	// Berechnung der Zellposition der Maus
	const glm::ivec3 cell_mouse_pos = mouse_pos / CellSize;
	const glm::ivec3 cell_mainbuilding_pos = mainbuilding_pos / 135.0f;
	if((left_click || right_click) &&  (cell_mouse_pos == cell_mainbuilding_pos || cell_mouse_pos == cell_mainbuilding_pos + glm::ivec3{0,1,0}))
	{
		return;
	}

	// Behandlung von Linksklicks
	if (left_click && is_windows_focused)
	{
		// Überprüfen, ob eine Zelle ausgewählt ist und ob die aktuelle Zelle leer ist
		if (m_selected != Utils::Cell::NOTHING
			&&
			map[0][cell_mouse_pos.y][cell_mouse_pos.x] == Utils::Cell::NOTHING
			&&
			map[0][cell_mouse_pos.y][cell_mouse_pos.x] != m_selected)
		{
			// Platzierung eines Turms
			if (m_selected == Utils::Cell::TURRET &&
				map[0][cell_mouse_pos.y][cell_mouse_pos.x] != Utils::Cell::TURRET &&
				(Game::get_game()->m_geld >= m_costs.at(m_id)))
			{
				Game::get_game()->add_geld(-m_costs.at(m_id));
				std::shared_ptr<Tower> tower = std::make_shared<Tower>(cell_mouse_pos * 135,static_cast<towerKind>(m_id),static_cast<int>(m_costs.at(m_id)));
				towers.emplace_back(tower);
				entities.push_back(tower);
				Game::get_game()->getEntityMap()[0][cell_mouse_pos.y][cell_mouse_pos.x] = tower;

				// Aktualisieren der Karte
				map[0][cell_mouse_pos.y][cell_mouse_pos.x] = m_selected;
				EnemyManager::set_updated_tower(true);
			}
			//platzierung einer Mauer
			else if (m_selected == Utils::Cell::WALL &&
				map[0][cell_mouse_pos.y][cell_mouse_pos.x] != Utils::Cell::WALL &&
				Game::get_game()->m_geld >= 25)
			{
				Game::get_game()->add_geld(-25);
				entities.emplace_back(std::make_shared<Wall>(cell_mouse_pos * 135));
				Game::get_game()->getEntityMap()[0][cell_mouse_pos.y][cell_mouse_pos.x] = entities.back();

				// Aktualisieren der Karte
				map[0][cell_mouse_pos.y][cell_mouse_pos.x] = m_selected;
				EnemyManager::set_walls_update(true);
			}
			
			
		}
	}

	// Behandlung von Rechtsklicks
	if (right_click && is_windows_focused)
	{
		// Überprüfen, ob eine Zelle ausgewählt ist und ob die aktuelle Zelle nicht leer ist
		if (m_selected != Utils::Cell::NOTHING &&
			map[0][cell_mouse_pos.y][cell_mouse_pos.x] != Utils::Cell::NOTHING)
		{

			// Entfernen eines Turms oder einer Mauer
			if (map[0][cell_mouse_pos.y][cell_mouse_pos.x] == Utils::Cell::TURRET ||
				map[0][cell_mouse_pos.y][cell_mouse_pos.x] == Utils::Cell::WALL)
			{
				Game::get_game()->getEntityMap()[0][cell_mouse_pos.y][cell_mouse_pos.x].reset();

				// Entfernen eines Turms
				if (map[0][cell_mouse_pos.y][cell_mouse_pos.x] == Utils::Cell::TURRET)
				{
					for (auto it = towers.begin(); it != towers.end();)
					{
						if ((int)((*it)->get_pos().x / 135.0f) == cell_mouse_pos.x &&
							(int)((*it)->get_pos().y / 135.0f) == cell_mouse_pos.y)
						{
							Game::get_game()->add_geld(it->get()->get_value()/2.0);
							it->reset();
							it = towers.erase(it);
						}
						else
						{
							++it;
						}
					}
				}

				// Entfernen der Entitaet
				for (auto it = entities.begin(); it != entities.end();)
				{
					if ((int)((*it)->get_pos().x / 135.0f) == cell_mouse_pos.x &&
						(int)((*it)->get_pos().y / 135.0f) == cell_mouse_pos.y)
					{
						it->reset();
						it = entities.erase(it);
					}
					else
					{
						++it;
					}
				}
			}
			// Aktualisieren der Karte
			if(map[0][cell_mouse_pos.y][cell_mouse_pos.x] == Utils::Cell::TURRET)
				EnemyManager::set_updated_tower(true);
			if(map[0][cell_mouse_pos.y][cell_mouse_pos.x] == Utils::Cell::WALL)
				EnemyManager::set_walls_update(true);

			map[0][cell_mouse_pos.y][cell_mouse_pos.x] = Utils::Cell::NOTHING;
			
		}
	}
}
