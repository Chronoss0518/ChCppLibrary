# ゲーム開発用ライブラリ

このライブラリは基本的にゲーム開発を補助するためのライブラリです。<br>
内部的に行われていることはDirectXやOpenGL(未実装)などの機能をパック化した形になります。

# 使用環境

##### 現在動作確認済み使用言語

- c++14

##### 現在動作確認済みOS

- Windows10

# 内容

ライブラリは大きく分けて7つ存在します。

##### ChBase
Chライブラリの根幹を担う機能をまとめたライブラリ<br>

##### ChCpp
C++の機能のみで利用することが可能なライブラリ<br>
他のプラットフォームへ持って行き、コンパイルして利用することができる。<br>

##### ChWin
WinAPIをで利用する際に便利な機能をまとめたライブラリ<br>

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

# ExternulLibrary
このライブラリで使用する外部のライブラリを含みます。<br>
外部ライブラリは以下の通りです。

- OSS license | DirectX | Microsoft | [DownloadSite「https://www.microsoft.com/ja-JP/download/details.aspx?id=6812」](https://www.microsoft.com/ja-JP/download/details.aspx?id=6812)
- MIT license | DirectXTex | Microsoft | [GitHub「https://github.com/microsoft/DirectXTex」](https://github.com/microsoft/DirectXTex)
- zlib license | zlib | Jean-loup Gailly And Mark Adler | [GitHub「https://github.com/madler/zlib」](https://github.com/madler/zlib) And [HomePage「https://zlib.net/」](https://zlib.net/)
- MIT license | imgui | ocornut | [GitHub「https://github.com/ocornut/imgui」](https://github.com/ocornut/imgui)


# 使用方法

以下にそれぞれの使い方を記述していく。

[ChBaseライブラリ](https://github.com/Chronoss0518/GameLibrary/tree/master/ChWinLibrary/BasePack)

[ChCppライブラリ](https://github.com/Chronoss0518/GameLibrary/tree/master/ChWinLibrary/CPP)

[ChWinライブラリ](https://github.com/Chronoss0518/GameLibrary/tree/master/ChWinLibrary/WindowsObject)

[ChD3D9ライブラリ](https://github.com/Chronoss0518/GameLibrary/tree/master/ChWinLibrary/Direct3D9)

[ChD3D11ライブラリ](https://github.com/Chronoss0518/GameLibrary/tree/master/ChWinLibrary/Direct3D11)

[ChD3Dライブラリ](https://github.com/Chronoss0518/GameLibrary/tree/master/ChWinLibrary/Direct3DObject)

[ChImGuiライブラリ](https://github.com/Chronoss0518/GameLibrary/tree/master/ChWinLibrary/ImGUIAPI)

[ExternulLibrary(https://github.com/Chronoss0518/ChCppLibrary/tree/master/ChCppLibrary/External)

# 予定(上から順に行う予定)

- FBXモデルのロード機能の追加
- HitTestObject関連の機能の追加
- Collider関連の機能の追加
- NetWork関連の機能の追加
- Compresser(可逆圧縮)機能の追加
- ChTextObjectを改修
- ChD3D11の大規模修正
- ChWinライブラリを大規模修正※(作業量が大きいためペンディング)
- BaseObjectの継承方法の変更
- XWindowSystemのパック化ライブラリの追加
- OpenGLのパック化ライブラリの追加

# 更新(予定から移動したもの)

- ChBaseライブラリとChCppライブラリを調整する。
- ClassPertsをChCpライブラリとしてChCppからChBaseへ移行する。
- 外部ライブラリを容易に追加することができる機能を追加

# このライブラリのコンセプト

- できる限り他のライブラリを使わずに独立させたい
- 様々なソフト開発を容易にしたい
- あれば便利というものをまとめておきたい
- プラットフォーム関係なく開発できるようにしたい
- 他言語のライブラリ開発にも考え方を利用したい

# 歴史

学生時代にメモリの解放忘れや手順の間違いを無くせれば良いという考えでのみライブラリの開発を始めました。<br>
開発当時は利用環境がDirectX9だったため、DirectX9をパック化した簡潔なライブラリとなっておりました。<br>
学年が上がった関係で使用環境がDirectX9からDirectX11に変わり、今まで貯めていた機能を呼び出すだけでは利用することが不可能となってしまったため、ライブラリの開発方法を一新しました。<br>
現在は以下の事を目的として開発するようにしております。

1. 必要な手順を1つにまとめる。<br>
※例:D3DXIntersectを行う際にRayにあたかも3DModelが動いたかのように見せるための処理を組み込む。<br>
2. メモリの解放忘れを防ぐ。<br>
※例:LPD3DXTEXTURE9の解放忘れなどをRelease関数またはデストラクタで絶対に開放するようにする。<br>
3. クロスプラットフォームを可能とした開発を行う。
4. 拡張性を持たせる。<br>
※例:ClassPertsを継承させて様々な機能を追加したクラスを作成する。<br>
5. 協調性を持たせる。<br>
※例:XMFloat3クラスをパック化したChVec3_11クラスが存在するが、基本的に引数でXMFloat3を利用する。<br>

※現在は開発目的のうち3と5は実装できていない箇所が存在します。




