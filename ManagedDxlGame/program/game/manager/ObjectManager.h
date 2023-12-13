#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include <unordered_map>

// 3Dオブジェクトを作成する際のテンプレを作成、所有するクラス
// ここでオリジナルのオブジェクトを作成し、それをコピーして他のオブジェクトを作成する
class ObjectManager{
public :
	// オブジェクトマネージャーをインスタンス化するための関数
	// この関数を通じてオブジェクトマネージャーを取得する
	static ObjectManager* GetInstance();

	
	// Boxのメッシュを持つオブジェクトのクローンを作成する関数
	// 同名のオリジナルが作成されていればクローンを返し、
	// 作成されていなければ作成してからクローンを返す
	// 引数：size...Boxの大きさ, name...オブジェクト名
	std::shared_ptr<ito::Object3D> createBox(float size, std::string name);

	// Planeのメッシュを持つオブジェクトのオリジナルを作成する関数
	// 引数：size...Planeの大きさ(z方向は不使用), name...オブジェクト名
	std::shared_ptr<ito::Object3D> createPlane(tnl::Vector3 size, std::string name);


private :

	ObjectManager();

	// オリジナルのオブジェクトを保存するmap
	// 名前とオブジェクトを保存する
	std::unordered_map<std::string, std::shared_ptr<ito::Object3D>> originObjList_;


};
