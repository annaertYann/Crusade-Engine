#pragma once
#include "BaseComponent.h"
#include "RenderComponents.h"
#include "Delay.h"
#include "GameObject.h"

namespace Crusade
{
	class Animation final
	{
	public:
		Animation(const std::string& filepath, const int& colloms,const float& framesPerSec , const bool& isLoop);//HORIZONTAL ANIMATION
		Animation(const std::string& filepath, const int& colloms, const int& rows,const float& framesPerSec, const bool& isLoop);//VERTICAL ANIMATION
		
		void Start(CTexture2DRender* renderer);
		void Update(CTexture2DRender* renderer,const float& deltaTime);
		void SetAsMultiSprite(const int& currentRow,const int& maxColloms);
		
		int GetTag()const { return m_Tag; }
		bool GetIsFinished() const{ return m_IsFinished; }
		std::string GetFilePath()const { return m_FilePath; }
	
	private:
		std::string m_FilePath{};
		float m_FramesPerSecond=10;
		int m_CurrentCollom=0;
		int m_CurrentRow=0;
		int m_Rows=1;
		int m_Colloms=1;
		int m_Width=0;
		int m_height=0;
		int m_MaxColloms = 1;
		
		bool m_IsLoop=true;
		bool m_IsFinished = false;
		bool m_IsVertical = false;
		
		inline static int m_NextTag = 0;
		int m_Tag = 0;
		Delay m_Delay{ 0 };
	};
	class Transition final
	{
	public:
		Transition(const std::shared_ptr<Animation>& from ,const std::shared_ptr<Animation>& to,const std::string& name , const bool& hasToFinishAnimation,const std::shared_ptr<bool>& condition=nullptr);
		bool ToTransition()const;
		std::string GetName() const{ return m_Name; }
		std::shared_ptr<Animation>GetFrom()const { return m_From; }
		std::shared_ptr<Animation>GetTo()const { return m_To; }
		std::shared_ptr<bool> GetCondition() const { return m_Condition; }
	private:
		bool m_HasToFinishAnimation=false;
		std::shared_ptr<Animation>m_From{};
		std::shared_ptr<Animation>m_To{};
		std::shared_ptr<bool> m_Condition{nullptr};
		std::string m_Name{};
	};
	
	class CAnimator2D final:public Component
	{
	public:
		explicit CAnimator2D(const std::shared_ptr<Animation>& startAnimation, const glm::vec2& destDimension = {});
		void Update() override;
		
		void AddTransition(Transition* transition) { m_Transitions.push_back(std::shared_ptr<Transition>{transition} ); }
		void TriggerTransition(const std::string& name);
		
		void SetDestDimensions(const int& w, const int& h)const { m_Renderer->SetDestDimensions(w, h); }
	private:
		void ResetAllConditions();
		void Start() override;
		std::vector<std::shared_ptr<Transition>>m_Transitions{};
		std::vector<std::shared_ptr<Animation>>m_Animations{};
		Animation* m_CurrentAnimation{};
		CTexture2DRender* m_Renderer{};
		glm::vec2 m_DestDimensions{};
	};
}
