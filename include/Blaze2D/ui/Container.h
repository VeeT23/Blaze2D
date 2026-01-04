
class Window;

namespace blaze 
{
	enum Anchor 
	{
		TOP_LEFT,
		TOP_CENTER,
		TOP_RIGHT,
		MIDDLE_LEFT,
		CENTER,
		MIDDLE_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT,
		OVERRIDE
	};

	class Container
	{
	public:

		//Container(Container& _parent_container);
		//Container(Window& _parent_window);

	private:
		int x;
		int y;
		int w;
		int h;
		
		Anchor anchor = Anchor::CENTER;

		Container* parent_container;
		Window* parent_window;

	}; // class container



} // namespace blaze