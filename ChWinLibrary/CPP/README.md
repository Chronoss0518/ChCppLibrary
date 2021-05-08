# ChCppライブラリ

ゲームを開発する上でAPIに非依存となる部分の機能をまとめたライブラリ

# 使用方法

大体のクラスはChCppというNamespaceで区切られており、
ChCppを作成する便利機能として上位にあるChStd,ChMath,ChPtr,ChStr,Ch3DMathの計6種類からなるライブラリで構成されている。<br>

それぞれのライブラリの使い方の一部を以下で説明する。

### ChStd

どのライブラリでも利用するような基本的な機能がまとめたライブラリ。

##### EnumCast
enum型を入れることでそれに対応した値を取得できる。<br>
<hr>
enum class : unsigned char {A,B,C};<br>

unsigned char Num = EnumCast(A);

### ChPtr
ポインターに関する機能をまとめたライブラリ<br>
<hr>

##### Shared,Make_S
Shared は std::shared_ptr,Make_Sはstd::make_sharedを別名で用意しているだけになります。<br>
<hr>
class Tmp{};<br>

ChPtr::Shared &lt;tmp&gt; = ChPtr::Make_S&lt;tmp&gt;();