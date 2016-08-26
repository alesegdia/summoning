#pragma once

#include <allegro5/allegro5.h>

#include <alligator/game/game.h>
#include <alligator/game/iscreen.h>
#include <alligator/input/input.h>
#include <alligator/util/matrix.h>

#include "../map/maprenderer.h"

class LD36;

class MapScreen : public IScreen {
public:
	MapScreen(LD36* g);
	virtual ~MapScreen();

	// IScreen interface
	void show() override;
	void update(double delta) override;
	void render() override ;
	void hide() override ;

private:

	LD36* m_game;
	Matrix2Di::SharedPtr m_map;
	IsometricTileMapRenderer::SharedPtr m_mapRenderer;
	bool m_enableMouseTravel = true;

};


