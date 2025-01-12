#include "Graphics++.hpp"

namespace Graphics {
    Graphics::_IsGraphicsLibraryLoaded _IsGraphicsLibraryLoadedF = nullptr;
    Graphics::_GetAvailableFonts _GetAvailableFontsF = nullptr;
    Graphics::_AddFont _AddFontF = nullptr;
    Graphics::_DrawLine _DrawLineF = nullptr;
    Graphics::_DrawRect _DrawRectF = nullptr;
    Graphics::_DrawGradientRect _DrawGradientRectF = nullptr;
    Graphics::_DrawTriangle _DrawTriangleF = nullptr;
    Graphics::_DrawEllipse _DrawEllipseF = nullptr;
    Graphics::_DisplayText _DisplayTextF = nullptr;
    Graphics::_DrawWatermark _DrawWatermarkF = nullptr;
    Graphics::_DrawImage _DrawImageF = nullptr;
    Graphics::_ShowNotification _ShowNotificationF = nullptr;
    Graphics::_SetGlobalFontSize _SetGlobalFontSizeF = nullptr;
    Graphics::_SetGlobalFontSizeStr _SetGlobalFontSizeStrF = nullptr;
    Graphics::_SetElementPosition _SetElementPositionF = nullptr;
    Graphics::_SetElementSize _SetElementSizeF = nullptr;
    Graphics::_SetElementColor _SetElementColorF = nullptr;
    Graphics::_SetElementText _SetElementTextF = nullptr;
    Graphics::_SetElementFont _SetElementFontF = nullptr;
    Graphics::_SetElementExtra _SetElementExtraF = nullptr;
    Graphics::_DeleteElement _DeleteElementF = nullptr;
    Graphics::_ClearRenderList _ClearRenderListF = nullptr;
    Graphics::_GetDisplaySize _GetDisplaySizeF = nullptr;


    bool Graphics::InitGraphics()
    {
        HMODULE hModule = GetModuleHandleA("Graphics++.dll");

        if (!hModule) {
            std::cerr << "The Graphics++.dll library was not founded. The Graphics++.dll library is required for this script to work." << "\n";
            return false;
        }

        // Получение адресов функций
        Graphics::_IsGraphicsLibraryLoadedF = (Graphics::_IsGraphicsLibraryLoaded)GetProcAddress(hModule, "IsGraphicsLibraryLoaded");
        Graphics::_GetAvailableFontsF = (Graphics::_GetAvailableFonts)GetProcAddress(hModule, "GetAvailableFonts");
        Graphics::_AddFontF = (Graphics::_AddFont)GetProcAddress(hModule, "AddFont");
        Graphics::_DrawLineF = (Graphics::_DrawLine)GetProcAddress(hModule, "DrawLineF");
        Graphics::_DrawRectF = (Graphics::_DrawRect)GetProcAddress(hModule, "DrawRect");
        Graphics::_DrawGradientRectF = (Graphics::_DrawGradientRect)GetProcAddress(hModule, "DrawGradientRect");
        Graphics::_DrawTriangleF = (Graphics::_DrawTriangle)GetProcAddress(hModule, "DrawTriangle");
        Graphics::_DrawEllipseF = (Graphics::_DrawEllipse)GetProcAddress(hModule, "DrawEllipse");
        Graphics::_DisplayTextF = (Graphics::_DisplayText)GetProcAddress(hModule, "DisplayText");
        Graphics::_DrawWatermarkF = (Graphics::_DrawWatermark)GetProcAddress(hModule, "DrawWatermark");
        Graphics::_DrawImageF = (Graphics::_DrawImage)GetProcAddress(hModule, "DrawImage");
        Graphics::_ShowNotificationF = (Graphics::_ShowNotification)GetProcAddress(hModule, "ShowNotification");
        Graphics::_SetGlobalFontSizeF = (Graphics::_SetGlobalFontSize)GetProcAddress(hModule, "SetGlobalFontSize");
        Graphics::_SetGlobalFontSizeStrF = (Graphics::_SetGlobalFontSizeStr)GetProcAddress(hModule, "SetGlobalFontSizeStr");
        Graphics::_SetElementPositionF = (Graphics::_SetElementPosition)GetProcAddress(hModule, "SetElementPosition");
        Graphics::_SetElementSizeF = (Graphics::_SetElementSize)GetProcAddress(hModule, "SetElementSize");
        Graphics::_SetElementColorF = (Graphics::_SetElementColor)GetProcAddress(hModule, "SetElementColor");
        Graphics::_SetElementTextF = (Graphics::_SetElementText)GetProcAddress(hModule, "SetElementText");
        Graphics::_SetElementFontF = (Graphics::_SetElementFont)GetProcAddress(hModule, "SetElementFont");
        Graphics::_SetElementExtraF = (Graphics::_SetElementExtra)GetProcAddress(hModule, "SetElementExtra");
        Graphics::_DeleteElementF = (Graphics::_DeleteElement)GetProcAddress(hModule, "DeleteElement");
        Graphics::_ClearRenderListF = (Graphics::_ClearRenderList)GetProcAddress(hModule, "ClearRenderList");
        Graphics::_GetDisplaySizeF = (Graphics::_GetDisplaySize)GetProcAddress(hModule, "GetDisplaySize");

        return true;
    }

    bool Graphics::IsGraphicsLibraryLoaded() {
        if (!_IsGraphicsLibraryLoadedF) {
            Graphics::_IsGraphicsLibraryLoadedF = (Graphics::_IsGraphicsLibraryLoaded)GetProcAddress(GetModuleHandleA("Graphics++.dll"), "IsGraphicsLibraryLoaded");

            return false;
        }
        else return _IsGraphicsLibraryLoadedF();
    }
    void Graphics::GetAvailableFonts() { if (_GetAvailableFontsF) _GetAvailableFontsF(); }
    void Graphics::AddFont(const char* fontFile, const char* fontName, int64_t sizePixels) { if (_AddFontF) _AddFontF(fontFile, fontName, sizePixels); }
    ID Graphics::DrawLine(int64_t x1, int64_t y1, int64_t x2, int64_t y2, BYTE r, BYTE g, BYTE b, BYTE alpha, int64_t thickness) { if (!_DrawLineF) return 0; return _DrawLineF(x1, y1, x2, y2, r, g, b, alpha, thickness); }
    ID Graphics::DrawRect(int64_t x, int64_t y, int64_t width, int64_t height, BYTE r, BYTE g, BYTE b, BYTE alpha, int64_t rounding, ImDrawFlags flags) { if (!DrawRect) return 0; return _DrawRectF(x, y, width, height, r, g, b, alpha, rounding, flags); }
    ID Graphics::DrawGradientRect(int64_t x, int64_t y, int64_t width, int64_t height, BYTE LeftBottomColorR, BYTE LeftBottomColorG, BYTE LeftBottomColorB, BYTE LeftBottomAlpha, BYTE LeftTopColorR, BYTE LeftTopColorG, BYTE LeftTopColorB, BYTE LeftTopAlpha, BYTE RightTopColorR, BYTE RightTopColorG, BYTE RightTopColorB, BYTE RightTopAlpha, BYTE RightBottomColorR, BYTE RightBottomColorG, BYTE RightBottomColorB, BYTE RightBottomAlpha) { if (!_DrawGradientRectF) return 0; return _DrawGradientRectF(x, y, width, height, LeftBottomColorR, LeftBottomColorG, LeftBottomColorB, LeftBottomAlpha, LeftTopColorR, LeftTopColorG, LeftTopColorB, LeftTopAlpha, RightTopColorR, RightTopColorG, RightTopColorB, RightTopAlpha, RightBottomColorR, RightBottomColorG, RightBottomColorB, RightBottomAlpha); }
    ID Graphics::DrawTriangle(int64_t x1, int64_t y1, int64_t x2, int64_t y2, int64_t x3, int64_t y3, BYTE r, BYTE g, BYTE b, BYTE alpha) { if (!DrawTriangle) return 0; return _DrawTriangleF(x1, y1, x2, y2, x3, y3, r, g, b, alpha); }
    ID Graphics::DrawEllipse(int64_t x, int64_t y, int64_t radiusX, int64_t radiusY, BYTE r, BYTE g, BYTE b, BYTE alpha, int numSegments) { if (!_DrawEllipseF) return 0; return _DrawEllipseF(x, y, radiusX, radiusY, r, g, b, alpha, numSegments); }
    ID Graphics::DisplayText(const char* text, int64_t x, int64_t y, const char* font, int64_t fontSize, BYTE r, BYTE g, BYTE b, BYTE alpha) { if (!_DisplayTextF) return 0; return _DisplayTextF(text, x, y, font, fontSize, r, g, b, alpha); }
    ID Graphics::DrawWatermark(const char* text, int64_t x, int64_t y, int64_t width, int64_t height, BYTE startColorR, BYTE startColorG, BYTE startColorB, BYTE endColorR, BYTE endColorG, BYTE endColorB, BYTE alpha, const char* font, int64_t fontSize) { if (!_DrawWatermarkF) return 0; return _DrawWatermarkF(text, x, y, width, height, startColorR, startColorG, startColorB, endColorR, endColorG, endColorB, alpha, font, fontSize); }
    ID Graphics::DrawImage(const char* file, int64_t x, int64_t y, int64_t width, int64_t height) { if (!_DrawImageF) return 0; return _DrawImageF(file, x, y, width, height); }
    void Graphics::ShowNotification(const char* text, time_t duration) { if (_ShowNotificationF) _ShowNotificationF(text, duration); }
    void Graphics::SetGlobalFontSize(int64_t fontSize) { if (_SetGlobalFontSizeF) _SetGlobalFontSizeF(fontSize); }
    void Graphics::SetGlobalFontSizeStr(const char* fontSize) { if (_SetGlobalFontSizeStrF) _SetGlobalFontSizeStrF(fontSize); }
    void Graphics::SetElementPosition(ID id, const int64_t* coords) { if (_SetElementPositionF) _SetElementPositionF(id, coords); }
    void Graphics::SetElementSize(ID id, int64_t width, int64_t height) { if (_SetElementSizeF) _SetElementSizeF(id, width, height); }
    void Graphics::SetElementColor(ID id, BYTE r, BYTE g, BYTE b, BYTE alpha) { if (_SetElementColorF) _SetElementColorF(id, r, g, b, alpha); }
    void Graphics::SetElementText(ID id, const char* text) { if (_SetElementTextF) _SetElementTextF(id, text); }
    void Graphics::SetElementFont(ID id, const char* font, int64_t fontSize) { if (_SetElementFontF) _SetElementFontF(id, font, fontSize); }
    void Graphics::SetElementExtra(ID id, const int64_t* extras) { if (_SetElementExtraF) _SetElementExtraF(id, extras); }
    void Graphics::DeleteElement(ID id) { if (_DeleteElementF) _DeleteElementF(id); }
    void Graphics::ClearRenderList() { if (_ClearRenderListF) _ClearRenderListF(); }
    int64_t* Graphics::GetDisplaySize() { if (!_GetDisplaySizeF) return 0; return _GetDisplaySizeF(); }

    bool IsGraphicsLibAvailable()
    {
        if (!Graphics::IsGraphicsLibraryLoaded())
        {
            while (!Graphics::IsGraphicsLibraryLoaded()) {
                Sleep(100);
            }

            InitGraphics();
            Graphics::SetGlobalFontSizeStr("medium");
        }
        return true;
    }


    Line::Line(int x1, int y1, int x2, int y2, int red, int green, int blue, int alpha, int thickness)
    {
        Graphics::IsGraphicsLibAvailable();
        this->ElementID = Graphics::DrawLine(x1, y1, x2, y2, red, green, blue, alpha, thickness);
    }
    void Line::SetPosition(int x1, int y1, int x2, int y2)
    {
        int64_t coords[4] = { x1, y1, x2, y2 };
        Graphics::SetElementPosition(this->ElementID, coords);
    }
    void Line::SetColor(int red, int green, int blue, int alpha)
    {
        Graphics::SetElementColor(this->ElementID, red, green, blue, alpha);
    }
    void Line::SetThickness(int thickness)
    {
        int64_t extras[1] = { thickness };
        Graphics::SetElementExtra(this->ElementID, extras);
    }


    Rect::Rect(int x, int y, int width, int height, int red, int green, int blue, int alpha, int rounding)
    {
        Graphics::IsGraphicsLibAvailable();
        this->ElementID = Graphics::DrawRect(x, y, width, height, red, green, blue, alpha, rounding, Graphics::ImDrawFlags::ImDrawFlags_None);
    }
    void Rect::SetPosition(int x1, int y1, int x2, int y2)
    {
        int64_t coords[4] = { x1, y1, x2, y2 };
        Graphics::SetElementPosition(this->ElementID, coords);
    }
    void Rect::SetSize(int width, int height)
    {
        Graphics::SetElementSize(this->ElementID, width, height);
    }
    void Rect::SetColor(int red, int green, int blue, int alpha)
    {
        Graphics::SetElementColor(this->ElementID, red, green, blue, alpha);
    }
    void Rect::SetRounding(int rounding)
    {
        int64_t extras[2] = { rounding, -1 };
        Graphics::SetElementExtra(this->ElementID, extras);
    }
    void Rect::SetFlags(int flags)
    {
        int64_t extras[2] = { -1, flags };
        Graphics::SetElementExtra(this->ElementID, extras);
    }


    GradientRect::GradientRect(int x, int y, int width, int height, int left_bottom_red, int left_bottom_green, int left_bottom_blue, int left_bottom_alpha, int left_top_red, int left_top_green, int left_top_blue, int left_top_alpha, int right_top_red, int right_top_green, int right_top_blue, int right_top_alpha, int right_bottom_red, int right_bottom_green, int right_bottom_blue, int right_bottom_alpha)
    {
        Graphics::IsGraphicsLibAvailable();
        this->ElementID = Graphics::DrawGradientRect(x, y, width, height,
            left_bottom_red, left_bottom_green, left_bottom_blue, left_bottom_alpha,
            left_top_red, left_top_green, left_top_blue, left_top_alpha,
            right_top_red, right_top_green, right_top_blue, right_top_alpha,
            right_bottom_red, right_bottom_green, right_bottom_blue, right_bottom_alpha);
    }
    void GradientRect::SetPosition(int x1, int y1)
    {
        int64_t coords[2] = { x1, y1 };
        Graphics::SetElementPosition(this->ElementID, coords);
    }
    void GradientRect::SetSize(int width, int height)
    {
        Graphics::SetElementSize(this->ElementID, width, height);
    }
    void GradientRect::SetColor(int left_bottom_red, int left_bottom_green, int left_bottom_blue, int left_bottom_alpha, int left_top_red, int left_top_green, int left_top_blue, int left_top_alpha, int right_top_red, int right_top_green, int right_top_blue, int right_top_alpha, int right_bottom_red, int right_bottom_green, int right_bottom_blue, int right_bottom_alpha)
    {
        int64_t extras[16] = { left_bottom_red, left_bottom_green, left_bottom_blue, left_bottom_alpha,
            left_top_red, left_top_green, left_top_blue, left_top_alpha,
            right_top_red, right_top_green, right_top_blue, right_top_alpha,
            right_bottom_red, right_bottom_green, right_bottom_blue, right_bottom_alpha };
        Graphics::SetElementExtra(this->ElementID, extras);
    }


    Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3, int red, int green, int blue, int alpha)
    {
        Graphics::IsGraphicsLibAvailable();
        this->ElementID = Graphics::DrawTriangle(x1, y1, x2, y2, x3, y3, red, green, blue, alpha);
    }
    void Triangle::SetPosition(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        int64_t coords[6] = { x1, y1, x2, y2, x3, y3 };
        Graphics::SetElementPosition(this->ElementID, coords);
    }
    void Triangle::SetColor(int red, int green, int blue, int alpha)
    {
        Graphics::SetElementColor(this->ElementID, red, green, blue, alpha);
    }


    Ellipse::Ellipse(int x, int y, int radius_x, int radius_y, int red, int green, int blue, int alpha)
    {
        Graphics::IsGraphicsLibAvailable();
        this->ElementID = Graphics::DrawEllipse(x, y, radius_x, radius_y, red, green, blue, alpha, 30);
    }
    void Ellipse::SetPosition(int x, int y)
    {
        int64_t coords[2] = { x, y };
        Graphics::SetElementPosition(this->ElementID, coords);
    }
    void Ellipse::SetRadius(int radius_x, int radius_y)
    {
        Graphics::SetElementSize(this->ElementID, radius_x, radius_y);
    }
    void Ellipse::SetColor(int red, int green, int blue, int alpha)
    {
        Graphics::SetElementColor(this->ElementID, red, green, blue, alpha);
    }
    void Ellipse::SetSegmentsCount(int segments)
    {
        int64_t extras[1] = { segments };
        Graphics::SetElementExtra(this->ElementID, extras);
    }


    Text::Text(const std::string& text, int x, int y, int r, int g, int b, int alpha, const std::string& font, int font_size)
    {
        Graphics::IsGraphicsLibAvailable();
        this->ElementID = Graphics::DisplayText(text.c_str(), x, y, font.c_str(), font_size, r, g, b, alpha);
    }

    void Text::SetPosition(int x, int y)
    {
        int64_t coords[2] = { x, y };
        Graphics::SetElementPosition(this->ElementID, coords);
    }

    void Text::SetLabel(const std::string& text)
    {
        Graphics::SetElementText(this->ElementID, text.c_str());
    }

    void Text::SetFont(const std::string& font, int font_size)
    {
        Graphics::SetElementFont(this->ElementID, font.c_str(), font_size);
    }

    void Text::SetColor(int red, int green, int blue, int alpha)
    {
        Graphics::SetElementColor(this->ElementID, red, green, blue, alpha);
    }


    Watermark::Watermark(const std::string& text, int x, int y, int width, int height, int start_r, int start_g, int start_b, int end_r, int end_g, int end_b, int alpha, const std::string& font, int font_size)
    {
        Graphics::IsGraphicsLibAvailable();
        this->ElementID = Graphics::DrawWatermark(text.c_str(), x, y, width, height, start_r, start_g, start_b, end_r, end_g, end_b, alpha, font.c_str(), font_size);
    }

    void Watermark::SetPosition(int x, int y)
    {
        int64_t coords[2] = { x, y };
        Graphics::SetElementPosition(this->ElementID, coords);
    }

    void Watermark::SetSize(int width, int height)
    {
        Graphics::SetElementSize(this->ElementID, width, height);
    }

    void Watermark::SetLabel(const std::string& text)
    {
        Graphics::SetElementText(this->ElementID, text.c_str());
    }

    void Watermark::SetFont(const std::string& font, int font_size)
    {
        Graphics::SetElementFont(this->ElementID, font.c_str(), font_size);
    }

    void Watermark::SetStartColor(int red, int green, int blue, int alpha)
    {
        Graphics::SetElementColor(this->ElementID, red, green, blue, alpha);
    }

    void Watermark::SetEndColor(int red, int green, int blue, int alpha)
    {
        int64_t extras[4] = { red, green, blue, alpha };
        Graphics::SetElementExtra(this->ElementID, extras);
    }


    Image::Image(const std::string& image_file, int x, int y, int width, int height)
    {
        Graphics::IsGraphicsLibAvailable();
        this->ElementID = Graphics::DrawImage(image_file.c_str(), x, y, width, height);
    }

    void Image::SetPosition(int x, int y)
    {
        int64_t coords[2] = { x, y };
        Graphics::SetElementPosition(this->ElementID, coords);
    }

    void Image::SetSize(int width, int height)
    {
        Graphics::SetElementSize(this->ElementID, width, height);
    }

    void Image::Hide()
    {
        int64_t extras[1] = { true };
        Graphics::SetElementExtra(this->ElementID, extras);
    }

    void Image::Show()
    {
        int64_t extras[1] = { false };
        Graphics::SetElementExtra(this->ElementID, extras);
    }


    Notification::Notification(const std::string& message)
    {
        Graphics::IsGraphicsLibAvailable();
        Graphics::ShowNotification(message.c_str(), 10);
    }

}