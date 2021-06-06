#include "MiniginPCH.h"
#include "Camera2D.h"
#include "utils.h"
using namespace Crusade;
bool Camera2D::m_IsWindowScaled = false;
float Camera2D::m_ScaleX = 1.f;
float Camera2D::m_ScaleY = 1.f;
Camera2D::Camera2D(const Point2f& startPos, const Window& window)
	:m_Position(startPos)
	,m_Window(window)
{
	if (!m_IsWindowScaled)
	{
		const Vector2f diffInWindow{ GetScaledWindowSize().width / window.width  , GetScaledWindowSize().height / window.height };
		Zoom(1 / diffInWindow.x, 1 / diffInWindow.y);
		for (int i{}; i < 500; i++)
		{
			Track(Point2f{ (startPos.x + (m_Window.width / 2) * diffInWindow.x) ,(startPos.y + (m_Window.height / 2) * diffInWindow.y) }, 10);
		}
		m_IsWindowScaled = true;
	}
}
void Camera2D::Track(const Point2f& target,const float& deltaTime)
{
	if (m_TrackDelay.Update(deltaTime))
	{
		m_TrackDelay.Start();
		CameraShake();

		Point2f temp{};
		temp.x = (m_Position.x + (m_Window.width/2)/m_ScaleX) - (target.x);
		temp.y = (m_Position.y + (m_Window.height/2)/m_ScaleY) - (target.y);

		temp.x /= m_LerpValue;
		temp.y /= m_LerpValue;

		m_Position.x -= temp.x;
		m_Position.y -= temp.y;
		glTranslatef(temp.x, temp.y, 0);
	}

}
void Camera2D::Translate(const float& x, const float& y)
{
	glTranslatef(x, y, 0);
}

void Camera2D::CameraShake()
{
	if (m_DoCameraShake)
	{
		m_ShakeCounter++;
		const Point2f ShakeStrength{ (m_Window.width/110)/m_ScaleX,(m_Window.height/110)/m_ScaleY };
		if (m_ShakeCounter % 2 == 0)
		{
			m_Position.x += ShakeStrength.x;
			m_Position.y += ShakeStrength.y;
			glTranslatef(-ShakeStrength.x, -ShakeStrength.y, 0);
		}
		else
		{
			m_Position.x -= ShakeStrength.x;
			m_Position.y -= ShakeStrength.y;
			glTranslatef(ShakeStrength.x, ShakeStrength.y, 0);
		}
		if (m_ShakeCounter >= m_NumberOfShakes)
		{
			m_DoCameraShake = false;
			m_ShakeCounter = 0;
		}
	}
}
void Camera2D::Zoom(const float& zoom)
{
	float scale = 1;
	scale *= zoom;
	m_Speed /= scale;
	m_ScaleX *= scale;
	m_ScaleY *= scale;
	Point2f temp{ GetScaledWindowSize().width / 2 + m_Position.x, GetScaledWindowSize().height / 2 + m_Position.y };

	const auto temp2{ temp };

	temp.x *= scale;
	temp.y *= scale;
	const auto diff{ temp - temp2 };

	glTranslatef(-diff.x, -diff.y, 0);
	m_Position += diff;
	m_Position.x /= scale;
	m_Position.y /= scale;
	glScalef(scale, scale, 1);
}
void Camera2D::Zoom(const float& zoomX,const float& zoomY)
{
	float scaleX = 1;
	float scaleY = 1;
	scaleX *= zoomX;
	scaleY *= zoomY;
	m_Speed /= scaleX;
	m_ScaleX *= scaleX;
	m_ScaleY *= scaleY;
	Point2f temp{ GetScaledWindowSize().width / 2 + m_Position.x, GetScaledWindowSize().height / 2 + m_Position.y };

	const auto temp2{ temp };

	temp.x *= scaleX;
	temp.y *= scaleY;
	const auto diff{ temp - temp2 };

	glTranslatef(-diff.x, -diff.y, 0);
	m_Position += diff;
	m_Position.x /= scaleX;
	m_Position.y /= scaleY;
	glScalef(scaleX, scaleY, 1);
}
Point2f Camera2D::GetMousePos()const
{
	Point2f mousePos{};
	int x{};
	int y{ };
	SDL_GetMouseState(&x, &y);

	x = int((x) * (1 / m_ScaleX));
	y = int((y) * (1 / m_ScaleY));

	const auto height = m_Window.height / m_ScaleY;


	mousePos = Point2f{ float(x) + m_Position.x , (height - float(y)) + m_Position.y };
	return mousePos;
}
Window Camera2D::GetScaledWindowSize()const
{
	Window window = m_OriginalWindow;
	window.width /= m_ScaleX;
	window.height /= m_ScaleY;
	return window;
}
Point2f Camera2D::GetPosition()const
{
	return m_Position;
}