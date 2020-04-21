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
		xw->drawBigString(trans_x, trans_y, name, pieceColour);
	}
}
