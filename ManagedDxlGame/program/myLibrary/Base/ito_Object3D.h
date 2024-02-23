#pragma once
#include "../../dxlib_ext/mesh/dxlib_ext_mesh.h"
#include "ito_transform.h"


namespace ito {

	// オブジェクト3Dクラス
	// ゲーム内の3Dのオブジェクトに継承,または型として使用
	class Object3D {
	public :
		// コンストラクタ
		Object3D(){}
		// デストラクタ
		virtual ~Object3D(){}


	protected :
		// オブジェクトのアクティブ状態を示すフラグ
		bool isActive_ = true;
		// オブジェクトのメッシュ
		std::shared_ptr< dxe::Mesh > mesh_ = nullptr;
		// オブジェクトのテクスチャ
		std::shared_ptr< dxe::Texture > texture_ = nullptr;


	public :
		// 仮想関数：オブジェクトの更新処理用関数
		virtual void update(float delta_time) {}
		// 仮想関数：オブジェクトの描画処理用関数
		virtual void draw(std::shared_ptr<dxe::Camera> camera = nullptr){}

		// ゲッター...オブジェクトのアクティブ状態を取得する関数
		// 戻り値...isActive_(bool型、オブジェクトのアクティブ状態を示す)
		bool get_isActive_() const { return isActive_; }

		// セッター...オブジェクトのアクティブ状態を変更する関数
		// 引数：変更後のオブジェクトのアクティブ状態
		void set_isActive_(bool isActive) { isActive_ = isActive; }

		// ゲッター...オブジェクトのメッシュを取得する関数
		// 戻り値...オブジェクトのメッシュ
		std::shared_ptr< dxe::Mesh > get_mesh_() { return mesh_; }

		// セッター...オブジェクトのメッシュを設定する関数
		// 引数：設定するメッシュ
		void set_mesh_( std::shared_ptr< dxe::Mesh > mesh ) { 
			mesh_ = mesh;
		}


	};

}