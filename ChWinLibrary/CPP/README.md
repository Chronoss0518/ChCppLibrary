# ChCpp���C�u����

�Q�[�����J��������API�ɔ�ˑ��ƂȂ镔���̋@�\���܂Ƃ߂����C�u����

# �g�p���@

��̂̃N���X��ChCpp�Ƃ���Namespace�ŋ�؂��Ă���A
ChCpp���쐬����֗��@�\�Ƃ��ď�ʂɂ���ChStd,ChMath,ChPtr,ChStr,Ch3DMath�̌v6��ނ���Ȃ郉�C�u�����ō\������Ă���B<br>

���ꂼ��̃��C�u�����̎g�����̈ꕔ���ȉ��Ő�������B

### ChStd

�ǂ̃��C�u�����ł����p����悤�Ȋ�{�I�ȋ@�\���܂Ƃ߂����C�u�����B

##### EnumCast
enum�^�����邱�Ƃł���ɑΉ������l���擾�ł���B<br>
<hr>
enum class : unsigned char {A,B,C};<br>

unsigned char Num = EnumCast(A);

### ChPtr
�|�C���^�[�Ɋւ���@�\���܂Ƃ߂����C�u����<br>
<hr>

##### Shared,Make_S
Shared �� std::shared_ptr,Make_S��std::make_shared��ʖ��ŗp�ӂ��Ă��邾���ɂȂ�܂��B<br>
<hr>
class Tmp{};<br>

ChPtr::Shared &lt;tmp&gt; = ChPtr::Make_S&lt;tmp&gt;();