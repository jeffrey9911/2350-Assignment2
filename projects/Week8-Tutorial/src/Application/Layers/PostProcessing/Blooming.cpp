#include "Blooming.h"
#include "Utils/ResourceManager/ResourceManager.h"
#include "Utils/JsonGlmHelpers.h"
#include "Utils/ImGuiHelper.h"

Blooming::Blooming() :
	PostProcessingLayer::Effect(),
	_multiplier(1.0f),
	_brightLim(0.1f),
	_exposure(1.0f),
	_gamma(1.0f)
{
	Name = "Blooming Effect";
	_format = RenderTargetType::ColorRgb8;

	_shader = ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string>{
		{ ShaderPartType::Vertex, "shaders/vertex_shaders/fullscreen_quad.glsl" },
		{ ShaderPartType::Fragment, "shaders/fragment_shaders/post_effects/custom.glsl" }
	});
}

Blooming::~Blooming() = default;

void Blooming::Apply(const Framebuffer::Sptr& gBuffer) 
{  
	_shader->Bind();  
	_shader->SetUniform("u_multiplier", _multiplier); 
	_shader->SetUniform("u_brightLim", _brightLim); 
	_shader->SetUniform("u_exposure", _exposure); 
	_shader->SetUniform("u_gamma", _gamma); 
	//gBuffer->BindAttachment(RenderTargetAttachment::Color0, 1);
}

void Blooming::RenderImGui()
{
	LABEL_LEFT(ImGui::SliderFloat, "Multiplier", &_multiplier, 0.0f, 10.0f);
	LABEL_LEFT(ImGui::SliderFloat, "Bright Limitation", &_brightLim, -10.0f, 10.0f);
	LABEL_LEFT(ImGui::SliderFloat, "Exposure", &_exposure, -10.0f, 10.0f);
	LABEL_LEFT(ImGui::SliderFloat, "Gamma", &_gamma, -10.0f, 10.0f);
}

Blooming::Sptr Blooming::FromJson(const nlohmann::json& data)
{
	Blooming::Sptr result = std::make_shared<Blooming>();
	return result;
}

nlohmann::json Blooming::ToJson() const
{
	return {};
}
