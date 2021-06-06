#pragma once
#include "Delay.h"
#include "BaseComponent.h"
#include "structs.h"
namespace Crusade
{
	class Camera2D final:public Component
	{
	public:
		explicit Camera2D(const Point2f& startPos, const Window& window);
		~Camera2D() = default;

		Camera2D(const Camera2D& other) = delete;
		Camera2D(Camera2D&& other) = delete;
		Camera2D& operator=(const Camera2D& other) = delete;
		Camera2D& operator=(Camera2D&& other) = delete;
		//SHAKE
		void DoCameraShake() { m_DoCameraShake = true; };
		//ZOOM
		void Zoom(const float& zoom);
		void Zoom(const float& zoomX,const float& zoomY);
		//MOVEMENT
		void Track(const Point2f& target, const float& deltaTime);
		static void Translate(const float& x, const float& y);
		//VAR
		Point2f GetMousePos() const;
		Window GetScaledWindowSize()const;
		Window GetOriginalWindow() const{ return m_OriginalWindow; }
		Point2f GetPosition()const;
		float GetScaleX()const { return m_ScaleX; }
		float GetScaleY()const { return m_ScaleY; }
	private:
		//SHAKE
		void CameraShake();
		bool m_DoCameraShake = false;
		int m_ShakeCounter = 0;
		int m_NumberOfShakes = 2;
		//TRACK
		Delay m_TrackDelay{ 0.001f };
		float m_LerpValue = 60; //Higher value equals slower tracking
		//VAR
		Point2f m_Position = {};
		float m_Speed = 400;
		static float m_ScaleX ;
		static float m_ScaleY ;
		static bool m_IsWindowScaled;
		Window m_Window{};
		Window m_OriginalWindow{"Original",640,480};
	};
}