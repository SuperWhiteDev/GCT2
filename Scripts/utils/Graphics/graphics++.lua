
local graphics_base = require("graphics_base")

local graphics = { }


--[[
    Line class
]]
local Line = {}
Line.__index = Line

function Line.DrawLine(x1, y1, x2, y2, red, green, blue, alpha, thickness)
  local self = setmetatable({}, Line)
  self.element_id = graphics_base.DrawLine(x1, y1, x2, y2, red, green, blue, alpha, thickness)
  return self
end
function Line.SetPosition(self, x1, y1, x2, y2)
    graphics_base.SetElementPosition(self.element_id, x1, y1, x2, y2)
end
function Line.SetColor(self, red, green, blue, alpha)
    graphics_base.SetElementColor(self.element_id, red, green, blue, alpha)
end
function Line.SetThickness(self, thickness)
    graphics_base.SetElementExtra(self.element_id, thickness)
end
function Line.Delete(self)
    graphics_base.DeleteElement(self.element_id)
end


--[[
    Rect class
]]
local Rect = {}
Rect.__index = Rect

function Rect.DrawRect(x, y, width, height, red, green, blue, alpha, rounding)
  local self = setmetatable({}, Rect)
  self.element_id = graphics_base.DrawRect(x, y, width, height, red, green, blue, alpha, rounding, 0)
  return self
end
function Rect.SetPosition(self, x1, y1, x2, y2)
    graphics_base.SetElementPosition(self.element_id, x1, y1, x2, y2)
end
function Rect.SetSize(self, width, height)
    graphics_base.SetElementSize(self.element_id, width, height)
end
function Rect.SetColor(self, red, green, blue, alpha)
    graphics_base.SetElementColor(self.element_id, red, green, blue, alpha)
end
function Rect.SetRounding(self, rounding)
    graphics_base.SetElementExtra(self.element_id, rounding, -1)
end
function Rect.SetFlags(self, flags)
    graphics_base.SetElementExtra(self.element_id, -1, flags)
end
function Rect.Delete(self)
    graphics_base.DeleteElement(self.element_id)
end


--[[
    RectWithBorders class
]]
local RectWithBorders = {}
RectWithBorders.__index = RectWithBorders

function RectWithBorders.DrawRect(x, y, width, height, red, green, blue, alpha, border_r, border_g, border_b, border_thickness, rounding)
  local self = setmetatable({}, RectWithBorders)
  self.element_id = graphics_base.DrawRectWithBorders(x, y, width, height, red, green, blue, alpha, border_r, border_g, border_b, border_thickness, rounding, 0)
  return self
end
function RectWithBorders.SetPosition(self, x1, y1, x2, y2)
    graphics_base.SetElementPosition(self.element_id, x1, y1, x2, y2)
end
function RectWithBorders.SetSize(self, width, height)
    graphics_base.SetElementSize(self.element_id, width, height)
end
function RectWithBorders.SetColor(self, red, green, blue, alpha)
    graphics_base.SetElementColor(self.element_id, red, green, blue, alpha)
end
function RectWithBorders.SetBordersColor(self, red, green, blue)

end
function RectWithBorders.SetRounding(self, rounding)

end
function RectWithBorders.SetThickness(self, thickness)
    
end
function RectWithBorders.SetFlags(self, flags)
    
end
function RectWithBorders.Delete(self)
    graphics_base.DeleteElement(self.element_id)
end


--[[
    Gradient Rect class
]]
local GradientRect = {}
GradientRect.__index = GradientRect

function GradientRect.DrawRect(x, y, width, height, left_bottom_red, left_bottom_green, left_bottom_blue, left_bottom_alpha, left_top_red, left_top_green, left_top_blue, left_top_alpha, right_top_red, right_top_green, right_top_blue, right_top_alpha, right_bottom_red, right_bottom_green, right_bottom_blue, right_bottom_alpha)
  local self = setmetatable({}, GradientRect)
  self.element_id = graphics_base.DrawGradientRect(x, y, width, height, left_bottom_red, left_bottom_green, left_bottom_blue, left_bottom_alpha, left_top_red, left_top_green, left_top_blue, left_top_alpha, right_top_red, right_top_green, right_top_blue, right_top_alpha, right_bottom_red, right_bottom_green, right_bottom_blue, right_bottom_alpha)
  return self
end
function GradientRect.SetPosition(self, x1, y1)
    graphics_base.SetElementPosition(self.element_id, x1, y1)
end
function GradientRect.SetSize(self, width, height)
    graphics_base.SetElementSize(self.element_id, width, height)
end
function GradientRect.SetColor(self, left_bottom_red, left_bottom_green, left_bottom_blue, left_bottom_alpha, left_top_red, left_top_green, left_top_blue, left_top_alpha, right_top_red, right_top_green, right_top_blue, right_top_alpha, right_bottom_red, right_bottom_green, right_bottom_blue, right_bottom_alpha)
    graphics_base.SetElementExtra(self.element_id, left_bottom_red, left_bottom_green, left_bottom_blue, left_bottom_alpha, left_top_red, left_top_green, left_top_blue, left_top_alpha, right_top_red, right_top_green, right_top_blue, right_top_alpha, right_bottom_red, right_bottom_green, right_bottom_blue, right_bottom_alpha)
end
function GradientRect.Delete(self)
    graphics_base.DeleteElement(self.element_id)
end

--[[
    Triangle class
]]
local Triangle = {}
Triangle.__index = Triangle

function Triangle.DrawTriangle(x1, y1, x2, y2, x3, y3, red, green, blue, alpha)
  local self = setmetatable({}, Triangle)
  self.element_id = graphics_base.DrawTriangle(x1, y1, x2, y2, x3, y3, red, green, blue, alpha)
  return self
end
function Triangle.SetPosition(self, x1, y1, x2, y2, x3, y3)
    graphics_base.SetElementPosition(self.element_id, x1, y1, x2, y2, x3, y3)
end
function Triangle.SetColor(self, red, green, blue, alpha)
    graphics_base.SetElementColor(self.element_id, red, green, blue, alpha)
end
function Triangle.Delete(self)
    graphics_base.DeleteElement(self.element_id)
end


--[[
    Ellipse class
]]
local Ellipse = {}
Ellipse.__index = Ellipse

function Ellipse.DrawEllipse(x, y, radius_x, radius_y, red, green, blue, alpha)
  local self = setmetatable({}, Ellipse)
  self.element_id = graphics_base.DrawEllipse(x, y, radius_x, radius_y, red, green, blue, alpha, 30)
  return self
end
function Ellipse.SetPosition(self, x, y)
    graphics_base.SetElementPosition(self.element_id, x, y)
end
function Ellipse.SetRadius(self, radius_x, radius_y)
    graphics_base.SetElementSize(self.element_id, radius_x, radius_y)
end
function Ellipse.SetColor(self, red, green, blue, alpha)
    graphics_base.SetElementColor(self.element_id, red, green, blue, alpha)
end
function Ellipse.SetSegmentsCount(self, segments)
    graphics_base.SetElementExtra(self.element_id, segments)
end
function Ellipse.Delete(self)
    graphics_base.DeleteElement(self.element_id)
end

--[[
    Text class
]]
local Text = {}
Text.__index = Text

function Text.DrawText(text, x, y, r, g, b, alpha, font, font_size)
  local self = setmetatable({}, Text)
  self.element_id = graphics_base.DisplayText(text, x, y, font, font_size, r, g, b, alpha)
  return self
end
function Text.SetPosition(self, x, y)
    graphics_base.SetElementPosition(self.element_id, x, y)
end
function Text.SetLabel(self, text)
    graphics_base.SetElementText(self.element_id, text)
end
function Text.SetFont(self, font, font_size)
    graphics_base.SetElementFont(self.element_id, font, font_size)
end
function Text.SetColor(self, red, green, blue, alpha)
    graphics_base.SetElementColor(self.element_id, red, green, blue, alpha)
end
function Text.Delete(self)
    graphics_base.DeleteElement(self.element_id)
end

--[[
    Watermark class
]]
local Watermark = {}
Watermark.__index = Watermark

function Watermark.DrawWatermark(text, x, y, width, height, start_r, start_g, start_b, end_r, end_g, end_b, alpha, font, font_size)
  local self = setmetatable({}, Watermark)
  self.element_id = graphics_base.DrawWatermark(text, x, y, width, height, start_r, start_g, start_b, end_r, end_g, end_b, alpha, font, font_size)
  return self
end
function Watermark.SetPosition(self, x1, y1)
    graphics_base.SetElementPosition(self.element_id, x1, y1)
end
function Watermark.SetSize(self, width, height)
    graphics_base.SetElementSize(self.element_id, width, height)
end
function Watermark.SetLabel(self, text)
    graphics_base.SetElementText(self.element_id, text)
end
function Watermark.SetFont(self, font, font_size)
    graphics_base.SetElementFont(self.element_id, font, font_size)
end
function Watermark.SetStartColor(self, red, green, blue, alpha)
    graphics_base.SetElementColor(self.element_id, red, green, blue, alpha)
end
function Watermark.SetEndColor(self, red, green, blue, alpha)
    graphics_base.SetElementExtra(self.element_id, red, green, blue, alpha)
end
function Watermark.Delete(self)
    graphics_base.DeleteElement(self.element_id)
end

--[[
    Image class
]]
local Image = {}
Image.__index = Image

function Image.Image(image_file, x, y, width, height)
  local self = setmetatable({}, Image)
  self.element_id = graphics_base.DrawImage(image_file, x, y, width, height)
  return self
end
function Image.SetPosition(self, x1, y1)
    graphics_base.SetElementPosition(self.element_id, x1, y1)
end
function Image.SetSize(self, width, height)
    graphics_base.SetElementSize(self.element_id, width, height)
end
function Image.Hide(self)
    graphics_base.SetElementExtra(self.element_id, 1)
end
function Image.Show(self)
    graphics_base.SetElementExtra(self.element_id, 0)
end
function Image.Delete(self)
    graphics_base.DeleteElement(self.element_id)
end

--[[
    Notification class
]]
local Notification = {}
Notification.__index = Notification

function Notification.Notification(message)
    local self = setmetatable({}, Notification)
    graphics_base.ShowNotification(message, 10)
    return self
end
function Notification.NotificationWithDuration(message, duration)
    local self = setmetatable({}, Notification)
    graphics_base.ShowNotification(message, duration)
    return self
end


graphics.Line = Line
graphics.Rect = Rect
graphics.GradientRect = GradientRect
graphics.Triangle = Triangle
graphics.Ellipse = Ellipse
graphics.Text = Text
graphics.Watermark = Watermark
graphics.Image = Image
graphics.Notification = Notification

return graphics