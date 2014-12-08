
class Cell
{
public:
	Cell();
	void setExits(int exit);
	void setAsExit();
	void setObject(int obj_index);
	int getExits();

private:
	int exits;
	int object_index;
	bool isExit;
};

