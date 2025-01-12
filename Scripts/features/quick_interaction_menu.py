import utils.Graphics.graphicspp as Graphics
global Graphics

class QuickInteractionMenu:
    def __init__(self, options, x, y, width, height):
        self.options = options
        self.keys = list(options.keys())
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.current_index = 0
        self.rects = []
        self.texts = []

        self.create_menu()

    def create_menu(self):
        # Create the background
        self.background = Graphics.Rect(self.x, self.y, self.width+20, len(self.keys) * (self.height + 5) - 5+20, 6, 4, 4, 128, 7)
        
        # Create options(buttons)
        for i, option in enumerate(self.keys):
            rect_y = self.y + i * (self.height + 5)
            rect = Graphics.Rect(self.x+10, rect_y+10, self.width, self.height, 24, 25, 23, 120, 2)
            self.rects.append(rect)
            text = Graphics.Text(option, self.x + 5+10, rect_y + 5+10, 255, 255, 255, 255, "Arial", 13)
            self.texts.append(text)

        self.update_menu()

    def update_menu(self):
        for i, rect in enumerate(self.rects):
            if i == self.current_index:
                rect.set_color(255, 0, 0, 120)  # Makes the option background red on hover
            else:
                rect.set_color(24, 25, 23, 120)  # Makes the option background the default colour
        
        
    def select_option(self):
        option_key = self.keys[self.current_index]
        if option_key in self.options:
            self.options[option_key]() # Call the function associated with the selected option

    def move_up(self):
        self.current_index = (self.current_index - 1) % len(self.keys)
        self.update_menu()

    def move_down(self):
        self.current_index = (self.current_index + 1) % len(self.keys)
        self.update_menu()
    def destroy(self):
        Graphics.graphics_base.DeleteElement(self.background.element_id)
        self.background = None
        
        for rect in self.rects:
            Graphics.graphics_base.DeleteElement(rect.element_id)
        for text in self.texts:
            Graphics.graphics_base.DeleteElement(text.element_id)
            
        self.rects = []
        self.texts = []
