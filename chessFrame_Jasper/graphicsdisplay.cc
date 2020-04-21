#include "graphicsdisplay.h"
#include "info.h"
#include "colour.h"
#include <iostream>
#include <string>

using namespace std;

GraphicsDisplay::GraphicsDisplay(): xw{new Xwindow{500, 550}} {
	for (int y = 1; y <= BOARDSIZE; ++y) {
		for (int x = 1; x <= BOARDSIZE; ++x) {
			int cellColour = ((x + y) % 2 == 1) ? 
				Xwindow::SlateGray : Xwindow::GhostWhite;
			xw->fillRectangle(GAP * x, GAP * y, GAP, GAP, cellColour);
		}
	}
}

GraphicsDisplay::~GraphicsDisplay() {
	delete xw;
}

void GraphicsDisplay::notify(Subject &whoNotified) {
	// clear previous error messages first before making a move
	this->clearErrorMessage();

	Info i = whoNotified.getInfo();
	Position pos = i.pos;
	Piece *piece = i.piece;

	int refill_x = pos.col - 'a' + 1;
	int refill_y = BOARDSIZE - pos.row + 1;
	int cellColour = ((refill_x + refill_y) % 2 == 1) ? 
		Xwindow::SlateGray : Xwindow::GhostWhite;
	xw->fillRectangle(GAP * refill_x, GAP * refill_y, GAP, GAP, cellColour);

	if (piece) {
		int trans_x = PIECE_PLACEMENT + GAP * (pos.col - 'a');
		int trans_y = PIECE_PLACEMENT + GAP * (BOARDSIZE - pos.row);
		int pieceColour = (piece->getPieceColour() == Colour::White) ? 
			Xwindow::PowderBlue : Xwindow::Black;

		string name{1, piece->getPiece()}; // convert char to string
		xw->drawString(trans_x, trans_y, name, pieceColour);
	}
}

void GraphicsDisplay::displayErrorMessage(ErrorMessage &e) {
	// clear previous error messages first before displaying a new one
	this->clearErrorMessage();
	// add new one
	xw->drawString(50, 475, e.getErrorMessage(), Xwindow::Red);
}

void GraphicsDisplay::clearErrorMessage() {
	xw->fillRectangle(50, 450, 450, 100, Xwindow::White);
}

void GraphicsDisplay::displayMessage(string s, int line_num) {
	xw->drawString(50, 475 + 15 * line_num, s, Xwindow::Black);
}
