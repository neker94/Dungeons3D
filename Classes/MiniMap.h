
class MiniMap
{
public:
	MiniMap();
	void cellsRevealedNerby (int, int);
	void revealCell(int, int);
	void init();
	bool nerby [49];
	static const int SIZE = 7;
private:
	bool cellsRevealed [20*20];
	bool inMap(int, int);
	
};

