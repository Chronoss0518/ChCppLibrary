# ゲーム開発用ライブラリ

このライブラリは基本的にゲーム開発を補助するためのライブラリです。<br>
内部的に行われていることはDirectXやOpenGL(未実装)などの機能をパック化した形になります。

# 使用環境

##### 現在の使用言語

- c++14

##### 現在動作確認済みOS

- Windows10

# 内容

ライブラリは大きく分けて6つ存在します。

##### ChBase
Chライブラリの根幹を担う機能をまとめたライブラリ<br>

##### ChCpp
C++の機能のみで利用することが可能なライブラリ

##### ChWin
WinAPIをで利用する際に便利な機能をまとめたライブラリ

##### ChD3D9
Direct3D9を利用する際に便利な機能をまとめたライブラリ<br>
※現在更新予定なし(互換性を持たせておくため更新はあり)

##### ChD3D11
Direct3D11を利用する際に便利な機能をまとめたライブラリ

##### ChD3D
Direct3Dの機能ではあるもののDirect3DのDeviceに依存することなく利用することができる独立したライブラリ。<br>
ChD3D9ライブラリやChD3D11ライブラリを呼ぶ際に同時に呼ばれる。

##### ChImGui
3D環境でOSや3DLibraryに依存しないWindowを表示させるライブラリをパック化したライブラリ。
※現在更新予定なし

# 使用方法

最上位に度のライブラリでも利用することができる機能群(以降はChBaseと呼称する)があり、その下にChCpp,ChWin,ChD3D9,ChD3D11,ChD3D,ChImGuiとなっている。<br>

※ChBaseはChStd,ChPtr,ChFIO,ChMath,Ch3DMath,ChStrの6種類で構成されている。

以下にそれぞれの使い方を記述していく。

[ChBaseライブラリ](https://github.com/Chronoss0518/GameLibrary/tree/master/ChWinLibrary/BasePack)

[ChCppライブラリ](https://github.com/Chronoss0518/GameLibrary/tree/master/ChWinLibrary/CPP)

[ChWinライブラリ](https://github.com/Chronoss0518/GameLibrary/tree/master/ChWinLibrary/WindowsObject)

[ChD3D9ライブラリ](https://github.com/Chronoss0518/GameLibrary/tree/master/ChWinLibrary/Direct3D9)

[ChD3D11ライブラリ](https://github.com/Chronoss0518/GameLibrary/tree/master/ChWinLibrary/Direct3D11)

[ChD3Dライブラリ](https://github.com/Chronoss0518/GameLibrary/tree/master/ChWinLibrary/Direct3DObject)

[ChImGuiライブラリ](https://github.com/Chronoss0518/GameLibrary/tree/master/ChWinLibrary/ImGUIAPI)

# 予定(上から順に行う予定)

- NetWork関連の機能の追加
- Compresser(可逆圧縮)機能の追加
- FBXモデルのロード機能の追加
- ChWinライブラリを大規模修正
- ChD3D11の大規模修正
- BaseObjectの継承方法の変更
- XWindowSystemんおパック化ライブラリの追加
- OpenGLのパック化ライブラリの追加

# 歴史

学生時代に解放忘れや手順の間違いを無くせれば良いという考えでのみライブラリの開発を始めました。<br>
開発当時は利用環境がDirectX9だったため、DirectX9でのみ利用可能なライブラリとなっておりました。<br>
学年が上がった関係で使用環境がDirectX9からDirectX11に変わり、今まで貯めていた機能が呼び出すだけでは利用することが不可能となってしまったため、ライブラリの開発方法を一新しました。<br>
現在は以下の事を目的として開発するようにしております。

1. 必要な手順を1つにまとめる。※例:D3DXIntersectを行う際にRayにあたかも3DModelが動いたかのように見せるための処理を組み込む。
2. メモリの解放忘れを防ぐ。※例:LPD3DXTEXTURE9の解放忘れなどをRelease関数またはデストラクタで絶対に開放するようにする。
3. クロスプラットフォームを目指す。
4. 拡張性を持たせる。※例:BaseSystemクラスを継承して新しいSystemクラスを作成することで、SystemManager(SysManager())を使いまわす。
5. 協調性を持たせる。※例:XMFloat3クラスをパック化したChVec3_11クラスが存在するが、基本的はXMFloat3を利用する。

※開発目的のうち1と2は開発当時の思想で元から存在したコンセプトとなります。
※現在は開発目的のうち4と5は実装できていない箇所が存在します。




