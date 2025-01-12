local graphics = { }

function graphics.IsGraphicsLibraryLoaded()
    return Call("IsGraphicsLibraryLoaded", "boolean")
end

function graphics.GetAvailableFonts()
    Call("GetAvailableFonts", "nil")
end
function graphics.AddFont(fontFile, fontName, sizePixels)
    Call("AddFont", "nil string string float", fontFile, fontName, sizePixels)
end
function graphics.DrawLine(x1, y1, x2, y2, r, g, b, alpha, thickness)
    return Call("DrawLine", "number float float float float number number number number float", x1, y1, x2, y2, r, g, b, alpha, thickness)
end

function graphics.DrawRect(x, y, width, height, r, g, b, alpha, rounding, flags)
    return Call("DrawRect", "number float float float float number number number number float number", x, y, width, height, r, g, b, alpha, rounding, flags)
end

function graphics.DrawRectWithBorders(x, y, width, height, r, g, b, alpha, borderR, borderG, borderB, borderThickness, rounding, flags)
    return Call("DrawRectWithBorders", "number float float float float number number number number float number", x, y, width, height, r, g, b, alpha, borderR, borderG, borderB, borderThickness, rounding, flags)
end

function graphics.DrawGradientRect(x, y, width, height, left_bottom_red, left_bottom_green, left_bottom_blue, left_bottom_alpha, left_top_red, left_top_green, left_top_blue, left_top_alpha, right_top_red, right_top_green, right_top_blue, right_top_alpha, right_bottom_red, right_bottom_green, right_bottom_blue, right_bottom_alpha)
    return Call("DrawGradientRect", "number float float float float number number number number number number number number number number number number number number number number", x, y, width, height, left_bottom_red, left_bottom_green, left_bottom_blue, left_bottom_alpha, left_top_red, left_top_green, left_top_blue, left_top_alpha, right_top_red, right_top_green, right_top_blue, right_top_alpha, right_bottom_red, right_bottom_green, right_bottom_blue, right_bottom_alpha)
end

function graphics.DrawTriangle(x1, y1, x2, y2, x3, y3, r, g, b, alpha)
    return Call("DrawTriangle", "number float float float float float float number number number number", x1, y1, x2, y2, x3, y3, r, g, b, alpha)
end

function graphics.DrawEllipse(x, y, radiusX, radiusY, r, g, b, alpha, numSegments)
    return Call("DrawEllipse", "number float float float float number number number number number", x, y, radiusX, radiusY, r, g, b, alpha, numSegments)
end

function graphics.DisplayText(text, x, y, font, font_size, r, g, b, alpha)
    return Call("DisplayText", "number string float float string float number number number number", text, x, y, font, font_size, r, g, b, alpha)
end

function graphics.DrawWatermark(text, x, y, width, height, start_r, start_g, start_b, end_r, end_g, end_b, alpha, font, font_size)
    return Call("DrawWatermark", "number string float float float float number number number number number number number string float", text, x, y, width, height, start_r, start_g, start_b, end_r, end_g, end_b, alpha, font, font_size)
end

function graphics.DrawImage(image_path, x, y, width, height)
    return Call("DrawImage", "number string float float number number", image_path, x, y, width, height)
end

function graphics.ShowNotification(text, duration)
    Call("ShowNotification", "nil string number", text, duration)
end

function graphics.SetGlobalFontSize(font_size)
    Call("SetGlobalFontSize", "nil float", font_size)
end
function graphics.SetGlobalFontSizeStr(font_size)
    Call("SetGlobalFontSizeStr", "nil string", font_size)
end

function graphics.SetElementPosition(id, ...)
    Call("SetElementPosition", "nil number table", id, {...})
end

function graphics.SetElementSize(id, width, height)
    Call("SetElementSize", "nil number number number", id, width, height)
end

function graphics.SetElementColor(id, r, g, b, alpha)
    Call("SetElementColor", "nil number number number number number", id, r, g, b, alpha)
end

function graphics.SetElementText(id, text)
    Call("SetElementText", "nil number string", id, text)
end

function graphics.SetElementExtra(id, ...)
    Call("SetElementExtra", "nil number table", id, {...})
end

function graphics.SetElementFont(id, font, font_size)
    Call("SetElementFont", "nil number string float", id, font, font_size)
end

function graphics.DeleteElement(id)
    Call("DeleteElement", "nil number", id)
end

function graphics.ClearRenderList()
    Call("ClearRenderList", "nil")
end

function graphics.GetDisplaySize()
    local size = Call("GetDisplaySize", "table(2)")
    return size[1], size[2]
end

return graphics

--Call("DrawLine", "nil float float float float number number number number float", 0.0, 0.0, 300.0, 400.0, 255, 0, 0, 255, 1.0)
--Call("DrawRect", "nil float float float float number number number number float number", 1300.0, 90.0, 80.0, 385.0, 255, 255, 0, 255, 1.0, 0)
--Call("DrawTriangle", "nil float float float float float float number number number number", 1000.0, 1000.0, 1200.0, 1000.0, 1400.0, 1000.0, 0, 100, 199, 255)
--Call("DrawEllipse", "nil float float float float number number number number number", 500.0, 500.0, 70.0, 70.0, 0, 200, 140, 255, 30)
--Call("DisplayText", "nil string float float float number number number number", "hello", 100.0, 90.0, 50.0, 212, 107, 65, 255)
--Call("ShowNotification", "nil string number", "Executed by loader.lua", 5000)
