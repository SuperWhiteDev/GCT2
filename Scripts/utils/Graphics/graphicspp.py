from time import sleep
import utils.Graphics.graphics_base as graphics_base
global graphics_base

def IsGraphicsLibAvailable():
    if not graphics_base.IsGraphicsLibraryLoaded():
        while not graphics_base.IsGraphicsLibraryLoaded():
            sleep(0.1)
    
        graphics_base.SetGlobalFontSizeStr("medium")
    return True

class Line:
    def __init__(self, x1, y1, x2, y2, red, green, blue, alpha, thickness):
        IsGraphicsLibAvailable()
        self.element_id = graphics_base.DrawLine(x1, y1, x2, y2, red, green, blue, alpha, thickness)
    def __del__(self):
        graphics_base.DeleteElement(self.element_id)
    def set_position(self, x1, y1, x2, y2):
        graphics_base.SetElementPosition(self.element_id, x1, y1, x2, y2)

    def set_color(self, red, green, blue, alpha):
        graphics_base.SetElementColor(self.element_id, red, green, blue, alpha)

    def set_thickness(self, thickness):
        graphics_base.SetElementExtra(self.element_id, thickness)

class Rect:
    def __init__(self, x, y, width, height, red, green, blue, alpha, rounding):
        IsGraphicsLibAvailable()
        self.element_id = graphics_base.DrawRect(x, y, width, height, red, green, blue, alpha, rounding, 0)
    def __del__(self):
        graphics_base.DeleteElement(self.element_id)
    def set_position(self, x1, y1, x2, y2):
        graphics_base.SetElementPosition(self.element_id, x1, y1, x2, y2)

    def set_size(self, width, height):
        graphics_base.SetElementSize(self.element_id, width, height)

    def set_color(self, red, green, blue, alpha):
        graphics_base.SetElementColor(self.element_id, red, green, blue, alpha)

    def set_rounding(self, rounding):
        graphics_base.SetElementExtra(self.element_id, rounding, -1)

    def set_flags(self, flags):
        graphics_base.SetElementExtra(self.element_id, -1, flags)
        
class RectWithBorders:
    def __init__(self, x, y, width, height, red, green, blue, alpha, border_r, border_g, border_b, border_thickness, rounding):
        IsGraphicsLibAvailable()
        self.element_id = graphics_base.DrawRectWithBorders(x, y, width, height, red, green, blue, alpha, border_r, border_g, border_b, border_thickness, rounding, 0)
    def __del__(self):
        graphics_base.DeleteElement(self.element_id)
    def set_position(self, x1, y1, x2, y2):
        graphics_base.SetElementPosition(self.element_id, x1, y1, x2, y2)

    def set_size(self, width, height):
        graphics_base.SetElementSize(self.element_id, width, height)

    def set_color(self, red, green, blue, alpha):
        graphics_base.SetElementColor(self.element_id, red, green, blue, alpha)
        
    def set_borders_color(self, red, green, blue):
        pass

    def set_rounding(self, rounding):
        pass
    
    def set_thickness(self, thickness):
        pass

    def set_flags(self, flags):
        pass

class GradientRect:
    def __init__(self, x, y, width, height, 
                 left_bottom_red, left_bottom_green, left_bottom_blue, left_bottom_alpha, 
                 left_top_red, left_top_green, left_top_blue, left_top_alpha, 
                 right_top_red, right_top_green, right_top_blue, right_top_alpha, 
                 right_bottom_red, right_bottom_green, right_bottom_blue, right_bottom_alpha):
        IsGraphicsLibAvailable()
        self.element_id = graphics_base.DrawGradientRect(x, y, width, height, 
                                                         left_bottom_red, left_bottom_green, left_bottom_blue, left_bottom_alpha, 
                                                         left_top_red, left_top_green, left_top_blue, left_top_alpha, 
                                                         right_top_red, right_top_green, right_top_blue, right_top_alpha, 
                                                         right_bottom_red, right_bottom_green, right_bottom_blue, right_bottom_alpha)
    def __del__(self):
        graphics_base.DeleteElement(self.element_id)
    def set_position(self, x1, y1):
        graphics_base.SetElementPosition(self.element_id, x1, y1)

    def set_size(self, width, height):
        graphics_base.SetElementSize(self.element_id, width, height)

    def set_color(self, left_bottom_red, left_bottom_green, left_bottom_blue, left_bottom_alpha, 
                  left_top_red, left_top_green, left_top_blue, left_top_alpha, 
                  right_top_red, right_top_green, right_top_blue, right_top_alpha, 
                  right_bottom_red, right_bottom_green, right_bottom_blue, right_bottom_alpha):
        graphics_base.SetElementExtra(self.element_id, left_bottom_red, left_bottom_green, left_bottom_blue, left_bottom_alpha, 
                                      left_top_red, left_top_green, left_top_blue, left_top_alpha, 
                                      right_top_red, right_top_green, right_top_blue, right_top_alpha, 
                                      right_bottom_red, right_bottom_green, right_bottom_blue, right_bottom_alpha)
        
class Triangle:
    def __init__(self, x1, y1, x2, y2, x3, y3, red, green, blue, alpha):
        IsGraphicsLibAvailable()
        self.element_id = graphics_base.DrawTriangle(x1, y1, x2, y2, x3, y3, red, green, blue, alpha)
    def __del__(self):
        graphics_base.DeleteElement(self.element_id)
    def set_position(self, x1, y1, x2, y2, x3, y3):
        graphics_base.SetElementPosition(self.element_id, x1, y1, x2, y2, x3, y3)
    
    def set_color(self, red, green, blue, alpha):
        graphics_base.SetElementColor(self.element_id, red, green, blue, alpha)

class Ellipse:
    def __init__(self, x, y, radius_x, radius_y, red, green, blue, alpha):
        IsGraphicsLibAvailable()
        self.element_id = graphics_base.DrawEllipse(x, y, radius_x, radius_y, red, green, blue, alpha, 30)
    def __del__(self):
        graphics_base.DeleteElement(self.element_id)
    def set_position(self, x, y):
        graphics_base.SetElementPosition(self.element_id, x, y)
    
    def set_radius(self, radius_x, radius_y):
        graphics_base.SetElementSize(self.element_id, radius_x, radius_y)
    
    def set_color(self, red, green, blue, alpha):
        graphics_base.SetElementColor(self.element_id, red, green, blue, alpha)
    
    def set_segments_count(self, segments):
        graphics_base.SetElementExtra(self.element_id, segments)

class Text:
    def __init__(self, text, x, y, r, g, b, alpha, font, font_size):
        IsGraphicsLibAvailable()
        self.element_id = graphics_base.DisplayText(text, x, y, font, font_size, r, g, b, alpha)
    def __del__(self):
        graphics_base.DeleteElement(self.element_id)
    def set_position(self, x, y):
        graphics_base.SetElementPosition(self.element_id, x, y)
    
    def set_label(self, text):
        graphics_base.SetElementText(self.element_id, text)
    
    def set_font(self, font, font_size):
        graphics_base.SetElementFont(self.element_id, font, font_size)
    
    def set_color(self, red, green, blue, alpha):
        graphics_base.SetElementColor(self.element_id, red, green, blue, alpha)

class Watermark:
    def __init__(self, text, x, y, width, height, start_r, start_g, start_b, end_r, end_g, end_b, alpha, font, font_size):
        IsGraphicsLibAvailable()
        self.element_id = graphics_base.DrawWatermark(text, x, y, width, height, start_r, start_g, start_b, end_r, end_g, end_b, alpha, font, font_size)
    def __del__(self):
        graphics_base.DeleteElement(self.element_id)
    def set_position(self, x1, y1):
        graphics_base.SetElementPosition(self.element_id, x1, y1)
    
    def set_size(self, width, height):
        graphics_base.SetElementSize(self.element_id, width, height)
    
    def set_label(self, text):
        graphics_base.SetElementText(self.element_id, text)
    
    def set_font(self, font, font_size):
        graphics_base.SetElementFont(self.element_id, font, font_size)
    
    def set_start_color(self, red, green, blue, alpha):
        graphics_base.SetElementColor(self.element_id, red, green, blue, alpha)
    
    def set_end_color(self, red, green, blue, alpha):
        graphics_base.SetElementExtra(self.element_id, red, green, blue, alpha)

class Image:
    def __init__(self, image_file, x, y, width, height):
        IsGraphicsLibAvailable()
        self.element_id = graphics_base.DrawImage(image_file, x, y, width, height)
    def __del__(self):
        graphics_base.DeleteElement(self.element_id)
    def set_position(self, x1, y1):
        graphics_base.SetElementPosition(self.element_id, x1, y1)
    
    def set_size(self, width, height):
        graphics_base.SetElementSize(self.element_id, width, height)
    
    def hide(self):
        graphics_base.SetElementExtra(self.element_id, 1)
    
    def show(self):
        graphics_base.SetElementExtra(self.element_id, 0)
        
class Notification:
    def __init__(self, message : str) -> None:
        IsGraphicsLibAvailable()
        graphics_base.ShowNotification(message, 10)
        
class NotificationWithDuration:  
    def __init__(self, message : str, duration : int) -> None:
        IsGraphicsLibAvailable()
        graphics_base.ShowNotification(message, duration)