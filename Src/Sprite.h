/*
@file Sprite.h
*/
#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED
#include "BufferObject.h"
#include "Texture.h";
#include "Shader.h";
#include <glm/glm.hpp>
#include <vector>

/*
矩形構造体
*/
struct Rect
{
	glm::vec2 origin; // 左下原点
	glm::vec2 size;   // 縦横の幅
};

/*
スプライトクラス
*/
class Sprite
{
public:
	Sprite() = default;
	explicit Sprite(const Texture::Image2DPtr&);
	~Sprite() = default;
	Sprite(const Sprite&) = default;
	Sprite& operator=(const Sprite&) = default;

	// 座標の設定・取得
	void Position(const glm::vec3& p) { position = p; }
	const glm::vec3& Position() const { return position; }

	// 回転の設定・取得
	void Rotate(float r) { rotation = r; }
	float Rotation() const { return rotation; }

	// 拡大率の設定・取得
	void Scale(const glm::vec2& s){}
	const glm::vec2 & Scale() const { return scale; }
	
	// 色の設定・取得
	void Color(const glm::vec4 & c) { color = c; }
	 const glm::vec4 & Color() const { return color; }
	
	// 矩形の設定・取得
	void Rectangle(const Rect & r) { rect = r; }
	const Rect & Rectangle() const { return rect; }
	
	// テクスチャの設定・取得
	void Texture(const Texture::Image2DPtr & tex);
	const Texture::Image2DPtr & Texture() const { return texture; }

private:
	glm::vec3 position = glm::vec3(0);
	glm::f32 rotation = 0;
	glm::vec2 scale = glm::vec2(1);
	glm::vec4 color = glm::vec4(1);
	Rect rect = { glm::vec2(0,0), glm::vec2(1,1) };
	Texture::Image2DPtr texture;
};

#endif // SPRITE_H_INCLUDED