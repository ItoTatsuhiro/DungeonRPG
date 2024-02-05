#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include <unordered_map>

// 3Dオブジェクトを作成する際のオリジナルを作成、所有するクラス
// ここでオリジナルのオブジェクトを作成し、クローンとして他のオブジェクトを作成する
// オブジェクトを作成する際は、このクラスの関数を経由して作成すること
class ObjectManager{
public :

	// オブジェクトマネージャーをインスタンス化するための関数
	// この関数を通じてオブジェクトマネージャーを取得する
	static ObjectManager* GetInstance();

	// オブジェクトマネージャークラスのデストラクタ
	~ObjectManager();

	//----------------------------------------------------------------------
	// オブジェクトのオリジナル、クローンを作成する関数
	// オブジェクトを作成する際は、以下の関数から作成すること
	// 関数は新たなメッシュを使用毎に順次追加予定

	// Boxのメッシュを持つオブジェクトのクローンを作成する関数
	// 同名のオリジナルが作成されていればクローンを返し、
	// 作成されていなければ作成してからクローンを返す
	// 引数：size...Boxの大きさ, name...オブジェクト名
	std::shared_ptr<ito::Object3D> createCube(float size, std::string name);

	// Planeのメッシュを持つオブジェクトのオリジナルを作成する関数
	// 同名のオリジナルが作成されていればクローンを返し、
	// 作成されていなければ作成してからクローンを返す
	// 引数：size...Planeの大きさ(z方向は不使用), name...オブジェクト名
	// ===========以下の変数はアニメーションを行う場合に使用===========
	// startPosOfCut...テクスチャの分割の開始地点(デフォルトは{ 0, 0, 0 })
	// endPosOfCut...テクスチャの分割の終了地点(デフォルトは{ 1, 1, 0 })
	std::shared_ptr<ito::Object3D> createPlane(tnl::Vector3 size, std::string name, tnl::Vector3 startPosOfCut = { 0, 0, 0 }, tnl::Vector3 endPosOfCut = { 1, 1, 0 });


	//----------------------------------------------------------------------
	// オブジェクトのオリジナルを削除する関数

	// 既に存在しているオリジナルのオブジェクトを削除する関数
	// 引数：name...削除するオブジェクトの名前
	void deleteOriginal(std::string name);


private :


	// オブジェクトマネージャークラスのコンストラクタ
	ObjectManager();


	// オリジナルのオブジェクトを保存するmap
	// 名前とオブジェクトを保存する
	std::unordered_map<std::string, std::shared_ptr<ito::Object3D>> originObjList_;


};
