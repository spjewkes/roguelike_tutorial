#include "defs.hpp"
#include "gui.hpp"
#include "engine.hpp"
#include "destructible.hpp"

Gui::Gui()
{
	con = new TCODConsole(engine.screenWidth, PANEL_HEIGHT);
}

Gui::~Gui()
{
	delete con;
	log.clearAndDelete();
}

Gui::Message::Message(const char *text, const TCODColor &col) :
	col(col)
{
	this->text = new char[strlen(text)];
	strcpy(this->text,text);
}

Gui::Message::~Message()
{
	delete [] text;
}

void Gui::render()
{
	// Clear the gui console
	con->setDefaultBackground(TCODColor::black);
	con->clear();

	// Draw the health bar
	renderBar(1, 1, BAR_WIDTH, "HP", engine.player->destructible->hp, engine.player->destructible->maxHp,
			  TCODColor::lightRed, TCODColor::darkerRed);

	// Draw the message log
	int y = 1;
	float colorCoef = 0.4f;
	for (Message *message : log)
	{
		con->setDefaultForeground(message->col * colorCoef);
		con->print(MSG_X, y, message->text);
		y++;
		if (colorCoef < 1.0f)
		{
			colorCoef += 0.3f;
		}
	}

	renderMouseLook();

	// Blit the GUI console to the root console
	TCODConsole::blit(con, 0, 0, engine.screenWidth, PANEL_HEIGHT,
					  TCODConsole::root, 0, engine.screenHeight-PANEL_HEIGHT);
}

void Gui::renderBar(int x, int y, int width, const char *name,
				   float value, float maxValue, const TCODColor &barColor,
				   const TCODColor &backColor)
{
	// Fill the background
	con->setDefaultBackground(backColor);
	con->rect(x, y, width, 1, false, TCOD_BKGND_SET);

	int barWidth = static_cast<int>(value / maxValue * width);
	if ( barWidth > 0 )
	{
		// Draw the bar
		con->setDefaultBackground(barColor);
		con->rect(x, y, barWidth, 1, false, TCOD_BKGND_SET);
	}

	// Print text on top of the bar
	con->setDefaultForeground(TCODColor::white);
	con->printEx(x + width / 2, y, TCOD_BKGND_NONE, TCOD_CENTER,
				 "%s : %g/%g", name, value, maxValue);
}

void Gui::message(const TCODColor &col, const char *text, ...)
{
	// Build the text
	va_list ap;
	char buf[128];
	va_start(ap,text);
	vsprintf(buf,text,ap);
	va_end(ap);

	char *lineBegin = buf;
	char *lineEnd;

	do {
		// Make room for the new message
		if (log.size() == MSG_HEIGHT)
		{
			Message *toRemove = log.get(0);
			log.remove(toRemove);
			delete toRemove;
		}

		// Detect end of the line
		lineEnd = strchr(lineBegin,'\n');

		if (lineEnd)
		{
			*lineEnd = '\0';
		}

		// Add a new message to the log
		Message *msg = new Message(lineBegin, col);
		log.push(msg);

		// Go to next line
		lineBegin = lineEnd + 1;
	} while (lineEnd);
}

void Gui::renderMouseLook()
{
	if (!engine.world->isInFov(engine.mouse.cx, engine.mouse.cy))
	{
		// If mouse is out of FOV , nothing to render
		return;
	}

	char buf[128] = {'\0'};

	bool first = true;
	for (Actor *actor : engine.actors)
	{
		if (actor->x == engine.mouse.cx && actor->y == engine.mouse.cy)
		{
			if (!first)
			{
				strcat(buf, ", ");
			}
			else
			{
				first = false;
			}
			strcat(buf, actor->name);
		}
	}

	// Display the list of actors under the mouse cursor
	con->setDefaultForeground(TCODColor::lightGrey);
	con->print(1, 0, buf);
}
