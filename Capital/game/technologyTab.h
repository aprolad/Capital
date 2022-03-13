


extern simulation sim;
extern int choosenTab;

class technologyTab
{
public:
	bool active;
	void (*reset)();
	void mouseInvoke(int mx, int my);
	void draw();
};