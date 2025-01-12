local Graphics = require("graphics++")
local GraphicsBase = require("graphics_base")

while not GraphicsBase.IsGraphicsLibraryLoaded() do
    Wait(1)
end

GraphicsBase.GetAvailableFonts()

GraphicsBase.SetGlobalFontSizeStr("medium")

local rect1 = Graphics.Rect.DrawRect(30, 50, 600, 450, 255, 0, 255, 255, 1.0)
rect1:SetPosition(5, 50)
rect1:SetSize(300, 200)

local watermark1 = Graphics.Watermark.DrawWatermark("This is graphics++ demo script", 5.0, 5.0, 300.0, 4.0, 0, 255, 255, 255, 255, 0, 255, "", 18.0)
GraphicsBase.ShowNotification("Congratulations!!!\nYou've launched GCT2!", 10.0)

local gradient_rect_alpha = 255
local gradient_rect1 = Graphics.GradientRect.DrawRect(800.0, 800.0, 550, 150, 200, 0, 0, gradient_rect_alpha, 200, 200, 0, gradient_rect_alpha, 0, 200, 0, gradient_rect_alpha, 0, 200, 255, gradient_rect_alpha)

GraphicsBase.AddFont("C:\\Windows\\Fonts\\Arial\\ariblk.ttf", "MyFont", 16.0)
local gradient_rect_text = Graphics.Text.DrawText("Gradient Rect", 985.0, 865.0, 255, 0, 0, 255, "MyFont", 30.0)


local displayX, displayY = GraphicsBase.GetDisplaySize()
--local image1 = Graphics.Image.Image(GetGCTFolder().."\\Images\\picture.png", displayX-35.0, 0.0, 30.0, 30.0)

while true do
    -- Transition from red to green
    for i = 0, 255 do
        local r = 255 - i  -- Red is decreasing
        local g = i        -- Green is increasing
        local b = 0        -- Blue remains 0
        rect1:SetColor(r, g, b, 255)
        Wait(25)

        gradient_rect_alpha = gradient_rect_alpha - 1
        if gradient_rect_alpha < 0 then
            gradient_rect_alpha = 0
        end
        gradient_rect1:SetColor(200, 0, 0, gradient_rect_alpha, 200, 200, 0, gradient_rect_alpha, 0, 200, 0, gradient_rect_alpha, 0, 200, 255, gradient_rect_alpha)
        gradient_rect_text:SetColor(255, 0, 0, gradient_rect_alpha)
    end
    
    -- Transition from green to blue
    for i = 0, 255 do
        local r = 0        -- Red remains 0
        local g = 255 - i  -- Green is decreasing
        local b = i        -- Blue is increasing
        rect1:SetColor(r, g, b, 255)
        Wait(25)

        gradient_rect_alpha = gradient_rect_alpha + 1
        if gradient_rect_alpha > 255 then
            gradient_rect_alpha = 255
        end
        gradient_rect1:SetColor(200, 0, 0, gradient_rect_alpha, 200, 200, 0, gradient_rect_alpha, 0, 200, 0, gradient_rect_alpha, 0, 200, 255, gradient_rect_alpha)
        gradient_rect_text:SetColor(255, 0, 0, gradient_rect_alpha)
    end
    
    -- Transition from blue to red
    for i = 0, 255 do
        local r = i        -- Red is increasing
        local g = 0        -- Green remains 0
        local b = 255 - i  -- Blue is decreasing
        rect1:SetColor(r, g, b, 255)
        Wait(25)
    end

    gradient_rect_text:SetFont("Algerian", 30.0)
end